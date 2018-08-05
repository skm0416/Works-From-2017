import glfw
from OpenGL.GL import *
from OpenGL.GLU import *
import numpy as np

gCamAng = 0.

def drawUnitCube() :
	glBegin(GL_QUADS)
	glVertex3f( 0.5, 0.5,-0.5)
	glVertex3f(-0.5, 0.5,-0.5)
	glVertex3f(-0.5, 0.5, 0.5)
	glVertex3f( 0.5, 0.5, 0.5)

	glVertex3f( 0.5,-0.5, 0.5)
	glVertex3f(-0.5,-0.5, 0.5)
	glVertex3f(-0.5,-0.5,-0.5)
	glVertex3f( 0.5,-0.5,-0.5)

	glVertex3f( 0.5, 0.5, 0.5)
	glVertex3f(-0.5, 0.5, 0.5)
	glVertex3f(-0.5,-0.5, 0.5)
	glVertex3f( 0.5,-0.5, 0.5)

	glVertex3f( 0.5,-0.5,-0.5)
	glVertex3f(-0.5,-0.5,-0.5)
	glVertex3f(-0.5, 0.5,-0.5)
	glVertex3f( 0.5, 0.5,-0.5)

	glVertex3f(-0.5, 0.5, 0.5)
	glVertex3f(-0.5, 0.5,-0.5)
	glVertex3f(-0.5,-0.5,-0.5)
	glVertex3f(-0.5,-0.5, 0.5)

	glVertex3f( 0.5, 0.5,-0.5)
	glVertex3f( 0.5, 0.5, 0.5)
	glVertex3f( 0.5,-0.5, 0.5)
	glVertex3f( 0.5,-0.5,-0.5)
	glEnd()

def drawSphere(numLats,numLongs):
	for i in range(0,numLats +1):
		lat0 = np.pi * (-0.5 + float(float(i-1)/float(numLats)))
		z0 = np.sin(lat0)
		zr0 = np.cos(lat0)

		lat1 = np.pi * (-0.5 + float(float(i)/float(numLats)))
		z1 = np.sin(lat1)
		zr1 = np.cos(lat1)

		glBegin(GL_QUAD_STRIP)

		for j in range(0, numLongs +1):
			lng = 2 * np.pi * float(float(j-1)/float(numLongs))
			x = np.cos(lng)
			y = np.sin(lng)
			glVertex3f(x * zr0, y * zr0, z0)
			glVertex3f(x * zr1, y * zr1, z1)
		glEnd()



def render(camAng, count):
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
	glEnable(GL_DEPTH_TEST)


	glLoadIdentity()

	glOrtho(-1,1,-1,1,-10,10)

	gluLookAt(1*np.sin(camAng),1,1*np.cos(camAng), 0,0,0, 0,1,0)

	glPushMatrix()
	glRotatef((count%1080)/3,0,1,0)

	glPushMatrix()
	glScalef(.2,.2,.2)
	glColor3ub(0,0,255)
	drawSphere(6,6)
	glPopMatrix()

	glPushMatrix()
	glRotatef(count%360,0,0,1)
	glTranslatef(1.5,0,0)

	glScalef(.2,.2,.2)
	glColor3ub(0,255,0)
	glPushMatrix()
	glRotatef(count%360,0,0,1)
	drawSphere(6,6)
	glPopMatrix()

	glRotatef(6*(count%60),0,1,0)
	glTranslatef(1.5,0,0)
	glScalef(.5,.5,.5)
	glColor3ub(255,0,0)
	drawSphere(6,6)

	glPushMatrix()
	glScalef(.3,.3,.3)
	glRotatef(18*(count%20),1,0,0)
	glTranslatef(0,3,3)
	glColor3ub(0,0,255)
	drawSphere(6,6)
	glPopMatrix()

	glPopMatrix()

	glPushMatrix()
	glRotatef(count%360,0,0,1)
	glTranslatef(0,0.8,0)

	glScalef(.1,.1,.1)
	glColor3ub(0,255,0)
	glPushMatrix()
	glRotatef(count%360,0,1,0)
	drawSphere(6,6)
	glPopMatrix()

	glRotatef(6*(count%60),1,0,0)
	glTranslatef(0,0,2)
	glScalef(.5,.5,.5)
	glColor3ub(255,0,0)
	drawSphere(6,6)

	glPopMatrix()
	glPopMatrix()



def key_callback(window,key,scancode,action,mods):
	global gCamAng
	if action==glfw.PRESS or action==glfw.REPEAT:
		if key==glfw.KEY_1:
			gCamAng += np.radians(-10)
		elif key==glfw.KEY_3:
			gCamAng += np.radians(10)


def main():
	#initialize the library
	if not glfw.init():
		return
	#Create a windowed mode window and its OpenGL context
	window = glfw.create_window(480,480,"2012004021", None, None)
	if not window:
		glfw.terminate()
		return

	#Make the window's context current
	glfw.make_context_current(window)
	glfw.set_key_callback(window,key_callback)
	glfw.swap_interval(1)
	count = 0

	#Loop until the user closes the window
	while not glfw.window_should_close(window):
		#Poll events
		glfw.poll_events()
		render(gCamAng,count)
		#Swap front and back buffers
		glfw.swap_buffers(window)
		count +=1

	glfw.terminate()

if __name__ == "__main__":
	main()