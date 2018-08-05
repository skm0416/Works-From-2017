import glfw
from OpenGL.GL import *
from OpenGL.GLU import *
import numpy as np

gType = np.identity(4)
gAng = np.radians(0)

Q = np.identity(4)
Q[:3,3] = [-.1,.0,.0]

E = np.identity(4)
E[:3,3] = [.1,.0,.0]

th = np.radians(-10)
A = np.identity(4)
A[:3,:3] = [[np.cos(th),0.,np.sin(th)],
			[0.,1., 0.],
			[-np.sin(th),0., np.cos(th)]]

th = np.radians(10)
D = np.identity(4)
D[:3,:3] = [[np.cos(th),0.,np.sin(th)],
			[0.,1., 0.],
			[-np.sin(th),0., np.cos(th)]]

th = np.radians(-10)
W = np.identity(4)
W[:3,:3] = [[1.,0.,0.],
			[0.,np.cos(th), -np.sin(th)],
			[0.,np.sin(th), np.cos(th)]]

th = np.radians(10)
S = np.identity(4)
S[:3,:3] = [[1.,0.,0.],
			[0.,np.cos(th), -np.sin(th)],
			[0.,np.sin(th), np.cos(th)]]
		
def drawTriangle():
	glBegin(GL_TRIANGLES)
	glColor3ub(255,255,255)
	glVertex3fv( (np.array([.0,.5,0.,1.]))[:-1] )
	glVertex3fv( (np.array([.0,.0,0.,1.]))[:-1] )
	glVertex3fv( (np.array([.5,.0,0.,1.]))[:-1] )
	glEnd()

def key_callback(window,key,scancode,action,mods):
	global gType,gAng,Q,E,A,D,W,S

	if action==glfw.PRESS or action==glfw.REPEAT:
		if key==glfw.KEY_1:
			gAng = gAng + np.radians(-10)
		if key==glfw.KEY_3:
			gAng = gAng + np.radians(10)
		if key==glfw.KEY_Q:
			gType = Q @ gType
		if key==glfw.KEY_E:
			gType = E @ gType
		if key==glfw.KEY_A:
			gType = gType @ A
		if key==glfw.KEY_D:
			gType = gType @ D
		if key==glfw.KEY_W:
			gType = gType @ W
		if key==glfw.KEY_S:
			gType = gType @ S

def render(M, camAng):
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
	glEnable(GL_DEPTH_TEST)
	glLoadIdentity()

	glOrtho(-1,1,-1,1,-1,1)

	gluLookAt(.1*np.sin(camAng),.1,.1*np.cos(camAng), 0,0,0, 0,1,0)

	#draw coordinate
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

	glMultMatrixf(gType.T)
	drawTriangle()

def main():
	#initialize the library
	if not glfw.init():
		return
	#Create a windowed mode window and its OpenGL context
	window = glfw.create_window(480,480,"2012004021", None, None)
	if not window:
		glfw.terminate()
		return

	glfw.set_key_callback(window,key_callback)
	#Make the window's context current
	glfw.make_context_current(window)

	glfw.swap_interval(1)

	#Loop until the user closes the window
	while not glfw.window_should_close(window):
		#Poll events
		glfw.poll_events()

		global gType,gAng
		render(gType,gAng)
		#Swap front and back buffers
		glfw.swap_buffers(window)

	glfw.terminate()

if __name__ == "__main__":
	main()