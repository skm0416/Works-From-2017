import glfw
from OpenGL.GL import *
import numpy as np

v = np.arange(0,2*np.pi,np.pi/6)

gType = GL_LINE_LOOP

def key_callback(window,key,scancode,action,mods):
	global gType
	if action==glfw.RELEASE:
		if key==glfw.KEY_1:
			gType = GL_POINTS
		if key==glfw.KEY_2:
			gType = GL_LINES
		if key==glfw.KEY_3:
			gType = GL_LINE_STRIP
		if key==glfw.KEY_4:
			gType = GL_LINE_LOOP
		if key==glfw.KEY_5:
			gType = GL_TRIANGLES
		if key==glfw.KEY_6:
			gType = GL_TRIANGLE_STRIP
		if key==glfw.KEY_7:
			gType = GL_TRIANGLE_FAN
		if key==glfw.KEY_8:
			gType = GL_QUADS
		if key==glfw.KEY_9:
			gType = GL_QUAD_STRIP
		if key==glfw.KEY_0:
			gType = GL_POLYGON

def render():
	glClear(GL_COLOR_BUFFER_BIT)
	glLoadIdentity()
	glBegin(gType)
	for i in range(0,12):
		glVertex2f(np.cos(v[i]),np.sin(v[i]))	
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

	#Loop until the user closes the window
	while not glfw.window_should_close(window):
		#Poll events
		glfw.poll_events()

		#Render here, e.g. using pyOpenGL
		render()

		#Swap front and back buffers
		glfw.swap_buffers(window)

	glfw.terminate()

if __name__ == "__main__":
	main()