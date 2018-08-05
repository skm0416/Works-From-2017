import glfw
from OpenGL.GL import *
import numpy as np

def render(T):
	glClear(GL_COLOR_BUFFER_BIT)
	glLoadIdentity()

	#draw coordinate
	glBegin(GL_LINES)
	glColor3ub(255,0,0)
	glVertex2fv((0.0,0.0))
	glVertex2fv([1.0,0.0])
	glColor3ub(0,255,0)
	glVertex2fv((0.0,0.0))
	glVertex2fv([0.0,1.0])
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
	window = glfw.create_window(640,640,"Hello World", None, None)
	if not window:
		glfw.terminate()
		return

	#Make the window's context current
	glfw.make_context_current(window)

	glfw.swap_interval(5)
	count = 0

	#Loop until the user closes the window
	while not glfw.window_should_close(window):
		#Poll events
		glfw.poll_events()

		#Render here, e.g. using pyOpenGL
		#th = np.radians(count%360)
		#T = np.array([[np.cos(th),-np.sin(th)],[np.sin(th),np.cos(th)]])
		
		#T = np.array([[-1,0],[0,1]])

		a = (count%10)*.2
		T = np.array([[1.,a],[0.,1.]])
		render(T)
		count+=1

		#Swap front and back buffers
		glfw.swap_buffers(window)

	glfw.terminate()

if __name__ == "__main__":
	main()