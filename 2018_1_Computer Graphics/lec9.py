import glfw
from OpenGL.GL import *
from OpenGL.GLU import *
import numpy as np

gCamAng = 0.

def drawTriangleTransformedBy (M): 
	glColor3ub(255,255,255)
	glBegin (GL_TRIANGLES)
	glVertex3fv( (M@ np.array([.0,.5,0.,1.]))[:-1] )
	glVertex3fv( (M@ np.array([.0,.0,0.,1.]))[:-1] )
	glVertex3fv( (M@ np.array([.5,.0,0.,1.]))[:-1] )
	glEnd()

def drawTriangle():
	glColor3ub(255,255,255)
	glBegin(GL_TRIANGLES)
	glVertex3fv(np.array([.0,.5,0.]))
	glVertex3fv(np.array([.0,.0,0.]))
	glVertex3fv(np.array([.5,.0,0.]))
	glEnd()

def drawFrameTransFormedBy1 (M):
	glBegin(GL_LINES)
	glColor3ub(255,0,0)
	glVertex3fv((M @ np.array([0.,0.,0.,1.]))[:-1])
	glVertex3fv((M @ np.array([1.,0.,0.,1.]))[:-1])
	glColor3ub(0,255,0)
	glVertex3fv((M @ np.array([0.,0.,0.,1.]))[:-1])
	glVertex3fv((M @ np.array([0.,1.,0.,1.]))[:-1])
	glColor3ub(0,0,255)
	glVertex3fv((M @ np.array([0.,0.,0.,1.]))[:-1])
	glVertex3fv((M @ np.array([0.,0.,1.,1.]))[:-1])
	glEnd()

def drawFrameTransFormedBy2 (M):
	glBegin(GL_LINES)
	glColor3ub(255,0,0)
	glVertex3fv(M[:3,3])
	glVertex3fv(M[:3,3] + M[:3,0])
	glColor3ub(0,255,0)
	glVertex3fv(M[:3,3])
	glVertex3fv(M[:3,3] + M[:3,1])
	glColor3ub(0,0,255)
	glVertex3fv(M[:3,3])
	glVertex3fv(M[:3,3] + M[:3,2])
	glEnd()

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

def render(camAng):
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
	glEnable(GL_DEPTH_TEST)


	glLoadIdentity()

	glOrtho(-1,1,-1,1,-10,10)

	gluLookAt(1*np.sin(camAng),1,1*np.cos(camAng), 0,0,0, 0,1,0)

	th = np.radians(60)
	R = np.identity(4)
	R[:3,:3] = [[1.,0.,0.],
				[0.,np.cos(th),-np.sin(th)],
				[0.,np.sin(th),np.cos(th)]]
	T = np.identity(4)
	T[:3,3] = [.4,0.,.2]
	drawFrame()

	glMultMatrixf(R.T)
	glMultMatrixf(T.T)
	drawTriangle()
	drawFrame()


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
		render(gCamAng)
		#Swap front and back buffers
		glfw.swap_buffers(window)

	glfw.terminate()

if __name__ == "__main__":
	main()