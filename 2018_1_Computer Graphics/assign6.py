import glfw
from OpenGL.GL import *
import numpy as np

gType = np.identity(3)
Q = np.array([[1.,0.,-0.1],
			[0.,1.,.0],
			[0.,0.,1.]])
E = np.array([[1.,0.,0.1],
			[0.,1.,.0],
			[0.,0.,1.]])
th = np.radians(10)
A = np.array([[np.cos(th), -np.sin(th),0.],
			[np.sin(th), np.cos(th), 0.],
			[0., 0., 1.]])
D = np.array([[np.cos(-th), -np.sin(-th),0.],
			[np.sin(-th), np.cos(-th), 0.],
			[0., 0., 1.]])

def key_callback(window,key,scancode,action,mods):
	global gType,Q,E,A,D
	if action==glfw.PRESS:
		if key==glfw.KEY_1:
			gType = np.identity(3)
		if key==glfw.KEY_Q:
			print(Q)
			gType = Q @ gType
		if key==glfw.KEY_E:
			print(E)
			gType = E @ gType
		if key==glfw.KEY_A:
			print(A)
			gType = gType @ A
		if key==glfw.KEY_D:
			print(D)
			gType = gType @ D

def render(T):
	glClear(GL_COLOR_BUFFER_BIT)
	glLoadIdentity()

	#draw coordinate
	glBegin(GL_LINES)
	glColor3ub(255,0,0)
	glVertex2fv(np.array([0.0,0.0]))
	glVertex2fv(np.array([1.0,0.0]))
	glColor3ub(0,255,0)
	glVertex2fv(np.array([0.0,0.0]))
	glVertex2fv(np.array([0.0,1.0]))
	glEnd()

	#draw triangle
	glBegin(GL_TRIANGLES)
	glColor3ub(255,255,255)
	glVertex2fv((T@np.array([.0,.5,1.]))[:-1] )
	glVertex2fv((T@np.array([.0,.0,1.]))[:-1] )
	glVertex2fv((T@np.array([.5,.0,1.]))[:-1] )
	glEnd()

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
		
		#Render here, e.g. using pyOpenGL
		global gType
		render(gType)

		#Swap front and back buffers
		glfw.swap_buffers(window)

	glfw.terminate()

if __name__ == "__main__":
	main()