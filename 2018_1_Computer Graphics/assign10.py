import glfw
from OpenGL.GL import *
from OpenGL.GLU import *
import numpy as np

gCamAng = 0.

def myLookAt(eye, at, up):
	w = eye-at/np.sqrt(np.dot(eye-at,eye-at))
	u = np.cross(up,w)/np.sqrt(np.dot(np.cross(up,w),np.cross(up,w)))
	v = np.cross(w,u)
	M = np.identity(4)

	M[:3,:1] = u.reshape(3,1)
	M[:3,1:2] = v.reshape(3,1)
	M[:3,2:3] = w.reshape(3,1)
	M[:3,3:] = eye.reshape(3,1)

	glMultMatrixf(M)

def render(camAng):
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
	glEnable(GL_DEPTH_TEST)

	glLoadIdentity()

	glOrtho(-1,1,-1,1,-10,10)

	eye = np.array([1*np.sin(camAng),1,1*np.cos(camAng)])
	at = np.array([0,0,0])
	up = np.array([0,1,0])
	myLookAt(eye,at,up)

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