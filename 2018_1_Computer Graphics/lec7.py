import glfw
from OpenGL.GL import *
from OpenGL.GLU import *
import numpy as np



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

	glBegin(GL_TRIANGLES)
	glColor3ub(255,255,255)
	glVertex3fv( (M @ np.array([.0,.5,0.,1.]))[:-1] )
	glVertex3fv( (M @ np.array([.0,.0,0.,1.]))[:-1] )
	glVertex3fv( (M @ np.array([.5,.0,0.,1.]))[:-1] )
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

	#Make the window's context current
	glfw.make_context_current(window)

	glfw.swap_interval(1)
	count = 0

	#Loop until the user closes the window
	while not glfw.window_should_close(window):
		#Poll events
		glfw.poll_events()

		th = np.radians(-60)
		R = np.identity(4)
		R[:3,:3] = [[1.,0.,0.],
					[0.,np.cos(th), -np.sin(th)],
					[0.,np.sin(th), np.cos(th)]]

		T = np.identity(4)
		T[:3,3] = [.4,0.,.2]

		camAng = np.radians(count % 360)
		render(R@T,camAng)
		count +=1
		#Swap front and back buffers
		glfw.swap_buffers(window)

	glfw.terminate()

if __name__ == "__main__":
	main()