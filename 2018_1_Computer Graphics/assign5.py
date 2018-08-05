import glfw
from OpenGL.GL import *
import numpy as np


gType = np.identity(2)
th = np.radians(10)


def key_callback(window,key,scancode,action,mods):
	global gType
	if action==glfw.PRESS:
		if key==glfw.KEY_1:
			gType = np.identity(2)
		if key==glfw.KEY_W:
			gType = np.array([[0.9,0.],[0.,1.]]) @ gType
		if key==glfw.KEY_E:
			gType = np.array([[1.1,0.],[0.,1.]]) @ gType
		if key==glfw.KEY_S:
			gType = np.array([[np.cos(th),-np.sin(th)],[np.sin(th),np.cos(th)]]) @ gType
		if key==glfw.KEY_D:
			gType = np.array([[np.cos(-th),-np.sin(-th)],[np.sin(-th),np.cos(-th)]]) @ gType
		if key==glfw.KEY_X:
			gType = np.array([[1.,-0.1],[0.,1.]]) @ gType
		if key==glfw.KEY_C:
			gType = np.array([[1.,0.1],[0.,1.]]) @ gType
		if key==glfw.KEY_R:
			gType = np.array([[1.,0.],[0.,-1.]]) @ gType

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
	glVertex2fv(T @ np.array([0.0,0.5]))
	glVertex2fv(T @ np.array([0.0,0.0]))
	glVertex2fv(T @ np.array([0.5,0.0]))
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

		render(gType)
		#Swap front and back buffers
		glfw.swap_buffers(window)

	glfw.terminate()

if __name__ == "__main__":
	main()