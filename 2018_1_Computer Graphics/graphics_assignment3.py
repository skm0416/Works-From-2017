import glfw
from OpenGL.GL import *
from OpenGL.GLU import *
import numpy as np

gCamAng = 0.
gCamHeight = .3
gZoom = 10
gWireframe = False
gVertex_array = []
gNormal_array = []
gObject_ready = False

def render(ang):
    global gCamAng, gCamHeight, gZoom, gWireframe
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT)

    glEnable(GL_DEPTH_TEST)
    if gWireframe :
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE)
    else :
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    gluPerspective(45, 1, 1,100)

    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()
    gluLookAt(gZoom*np.sin(gCamAng),gZoom*gCamHeight,gZoom*np.cos(gCamAng), 0,0,0, 0,1,0)

    drawFrame()

    glEnable(GL_LIGHTING)
    glEnable(GL_LIGHT0)
    glEnable(GL_LIGHT1)
    glEnable(GL_LIGHT2)

    # light position
    glPushMatrix()

    lightPos = (30,40,80,0.3)
    lightPos2 = (-50,-20,60,0.5)
    lightPos3 = (60,-60,80,0.4)
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos)
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos2)
    glLightfv(GL_LIGHT2, GL_POSITION, lightPos3)

    glPopMatrix()

    # light intensity for each color channel
    LightColor1 = (.1,.1,.1,.1)
    LightColor2 = (1.,0.,0.,.2)
    LightColor3 = (1.,0.,0.,.3)
    glLightfv(GL_LIGHT0, GL_AMBIENT, LightColor1)
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LightColor2)
    glLightfv(GL_LIGHT0, GL_SPECULAR, LightColor3)

    LightColor4 = (.2,.2,.2,.1)
    LightColor5 = (0.,0.,1.,.4)
    LightColor6 = (0.,0.,1.,.1)

    glLightfv(GL_LIGHT1, GL_AMBIENT, LightColor4)
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LightColor5)
    glLightfv(GL_LIGHT1, GL_SPECULAR, LightColor6)

    LightColor7 = (.3,.3,.3,.1)
    LightColor8 = (0.,1.,0.,.3)
    LightColor9 = (0.,1.,0.,.3)

    glLightfv(GL_LIGHT2, GL_AMBIENT, LightColor7)
    glLightfv(GL_LIGHT2, GL_DIFFUSE, LightColor8)
    glLightfv(GL_LIGHT2, GL_SPECULAR, LightColor9)

    # material reflectance for each color channel
    MaterialColor = (.4,.4,.4,.4)
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, MaterialColor)
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, MaterialColor)

    glPushMatrix()

    glColor3f(0, 0, 0)
    drawObjElement_glDrawArray()
    glPopMatrix()

    glDisable(GL_LIGHTING)

def drawObjElement_glDrawArray():
    global gVertex_array, gNormal_array, gObject_ready
    if gObject_ready is False:
        return
    glEnableClientState(GL_VERTEX_ARRAY)
    glEnableClientState(GL_NORMAL_ARRAY)
    glNormalPointer(GL_FLOAT,gNormal_array.itemsize*3,gNormal_array)
    glVertexPointer(3,GL_FLOAT,gVertex_array.itemsize*3,gVertex_array)
    glDrawArrays(GL_TRIANGLES,0,len(gVertex_array))

def drawFrame():
    glBegin(GL_LINES)
    glColor3ub(255, 0, 0)
    glVertex3fv(np.array([0.,0.,0.]))
    glVertex3fv(np.array([1.,0.,0.]))
    glColor3ub(0, 255, 0)
    glVertex3fv(np.array([0.,0.,0.]))
    glVertex3fv(np.array([0.,1.,0.]))
    glColor3ub(0, 0, 255)
    glVertex3fv(np.array([0.,0.,0]))
    glVertex3fv(np.array([0.,0.,1.]))
    glEnd()

def key_callback(window, key, scancode, action, mods):
    global gCamAng, gCamHeight, gZoom, gWireframe
    if action==glfw.PRESS or action==glfw.REPEAT:
        if key==glfw.KEY_1:
            gCamAng += np.radians(-10)
        elif key==glfw.KEY_3:
            gCamAng += np.radians(10)
        elif key==glfw.KEY_2:
            gCamHeight += .1
        elif key==glfw.KEY_W:
            gCamHeight += -.1
        elif key==glfw.KEY_A:
            if gZoom >= 0.5:
                gZoom -= .5
        elif key==glfw.KEY_S:
            gZoom += .5
        elif key==glfw.KEY_Z:
            gWireframe = not gWireframe


def drop_callback(window, path):
    global gVertex_array, gNormal_array, gObject_ready
    gObject_ready = True
    gVertex_array = []
    gNormal_array = []
    real_path = str(path)
    real_path = real_path[2:-2]
    f = open(real_path,'r')
    lines = f.readlines()
    f.close()
    v_array = []
    vn_array = []
    f_array = []
    for line in lines :
        if line[0] is 'v':
            if line[1] is 'n':
                vn_array.append(line[2:-1].split())
            elif line[1] is ' ':
                v_array.append(line[1:-1].split())
        elif line[0] is 'f':
            f_array.append(line[1:-1].split())

    count_3 = 0
    count_4 = 0
    count_more = 0
    for f in f_array:
        if len(f) is 3:
            count_3+=1
            for data in f: # vertex // normal
                index = data.split("/")
                gVertex_array.append(v_array[int(index[0])-1])
                if len(index) < 3 :
                    gNormal_array.append([0.,0.,0.])
                else :  
                    gNormal_array.append(vn_array[int(index[2])-1])
        elif len(f) is 4:
            count_4+=1
            for data in f[:3]: # vertex // normal
                index = data.split("/")
                gVertex_array.append(v_array[int(index[0])-1])
                if len(index) < 3 :
                    gNormal_array.append([0.,0.,0.])
                else :  
                    gNormal_array.append(vn_array[int(index[2])-1])
            del f[1]
            for data in f: # vertex // normal
                index = data.split("/")
                gVertex_array.append(v_array[int(index[0])-1])
                if len(index) < 3 :
                    gNormal_array.append([0.,0.,0.])
                else :  
                    gNormal_array.append(vn_array[int(index[2])-1])
        else:
            count_more+=1
            
    gVertex_array = np.array(gVertex_array,'float32')
    gNormal_array = np.array(gNormal_array,'float32')

    print("\nfile name : %s" % str(real_path.split('\\')[-1:])[2:-2])
    print("total numbers of faces : %d" % (count_3+count_4+count_more))
    print("face with 3 vertices : %d" % count_3)
    print("face with 4 vertices : %d" % count_4)
    print("face with more than 4 vertices : %d" % count_more)


def main():
    global gVertexArraySeparate

    if not glfw.init():
        return
    window = glfw.create_window(640,640,'obj_viewer', None,None)
    if not window:
        glfw.terminate()
        return
    glfw.make_context_current(window)
    glfw.set_key_callback(window, key_callback)
    glfw.set_drop_callback(window, drop_callback)
    glfw.swap_interval(1)

    count = 0
    while not glfw.window_should_close(window):
        glfw.poll_events()
        ang = count % 360
        render(ang)
        count += 1
        glfw.swap_buffers(window)

    glfw.terminate()

if __name__ == "__main__":
    main()