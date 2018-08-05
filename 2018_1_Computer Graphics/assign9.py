import glfw
from OpenGL.GL import *
from OpenGL.GLU import *
import numpy as np

gCamAng = 0.

def drawFrame():
	glBegin(GL_LINES)
	glColor3ub(255,0,0)
	glVertex3fv(np.array([0.,0.,0.]))
	glVertex3fv(np.array([1.,0.,0.]))
	glColor3ub(0,255,0)
	glVertex3fv(np.array([0.,0.,0.]))
	glVertex3fv(np.array([0.,1.,0.]))
	glColor3ub(0,0,255)
	glVertex3fv(np.array([0.,0.,0.]))
	glVertex3fv(np.array([0.,0.,1.]))
	glEnd()

def drawBox():
	glBegin(GL_QUADS)
	glVertex3fv(np.array([1,1,0.]))
	glVertex3fv(np.array([-1,1,0.]))
	glVertex3fv(np.array([-1,-1,0.]))
	glVertex3fv(np.array([1,-1,0.]))
	glEnd()

def render(camAng, count):
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
	glEnable(GL_DEPTH_TEST)


	glLoadIdentity()

	glOrtho(-1,1,-1,1,-10,10)

	gluLookAt(1*np.sin(camAng),1,1*np.cos(camAng), 0,0,0, 0,1,0)

	drawFrame()

	glPushMatrix()
	glTranslatef(-.5+(count%360)*.003,0,0)

	glPushMatrix()
	glScalef(.2,.2,.2)
	glColor3ub(0,0,255)
	drawBox()
	glScalef(2.5,2.5,2.5)
	drawFrame()
	glPopMatrix()

	glPushMatrix()
	glRotatef(count%360,0,0,1)
	glTranslatef(.5,0,.01)

	glPushMatrix()
	glScalef(.5,.1,.1)
	glColor3ub(255,0,0)
	drawBox()
	glScalef(1.,5.,5.)
	drawFrame()
	glPopMatrix()

	glTranslatef(.5,0,.01)
	glScalef(.2,.2,.2)
	glColor3ub(0,255,0)
	glRotatef(count%360,0,0,1)
	drawBox()
	glScalef(2.5,2.5,2.5)
	drawFrame()

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