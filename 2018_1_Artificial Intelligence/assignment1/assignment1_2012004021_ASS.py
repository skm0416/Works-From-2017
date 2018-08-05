class Tree(object):
	def __init__(self):
		self.origin = None
		self.depth = None
		self.value = None
		self.x = None
		self.y = None

def make_node(origin):
	print("now " + str(origin.x) +","+ str(origin.y))
	if check_matrix(origin,origin.x+1,origin.y):
		push_node(origin,origin.x+1,origin.y)
	if check_matrix(origin,origin.x,origin.y-1):
		push_node(origin,origin.x,origin.y-1)
	if check_matrix(origin,origin.x,origin.y+1):
		push_node(origin,origin.x,origin.y+1)
	if check_matrix(origin,origin.x-1,origin.y):
		push_node(origin,origin.x-1,origin.y)
		
	
def push_node(origin,x,y):
	global result_time,result_node,exit_list,done,heap,time
	time+=1
	H = Heuristic(x,y)
	temp = Tree()
	temp.x = x
	temp.y = y
	temp.value = matrix[x][y]
	temp.depth = origin.depth+1
	temp.origin = origin
	q.append((H+temp.depth,temp))
	q.sort(key=lambda tuple:tuple[0])
	if temp.value == '4' :
		result_time = time
		result_node = temp
		done = True

def check_matrix(origin,x,y):
	if x>-1 and y>-1 and x<m and y<n :
		if matrix[x][y] == '2' or matrix[x][y] == '4' :
			if check_origin(origin,x,y) :
				return True
		return False
	else :
		return False

def check_origin(origin,x,y):
	target = origin
	while 1:
		if target.x == x and target.y == y :
			return False
		elif target.origin == None :
			return True
		else :
			target = target.origin

def make_route(origin):
	target = origin.origin
	while 1:
		if target.origin == None :
			return True
		matrix[target.x][target.y] = '5'
		target = target.origin

def Heuristic(x,y):
	min = float("inf")
	for i in range(len(exit_list)) :
		temp = compare_length(x,y,exit_list[i][0],exit_list[i][1])
		if min>temp:
			min=temp
	return int(min)
def compare_length(x,y,X,Y):
	if x>X:
		difx = x-X
	else:
		difx = X-x
	if y>Y:
		dify = y-Y
	else:
		dify = Y-y
	return difx+dify

file_path = input("please input file path: ")
f = open(file_path + "\input.txt",'r')

line = f.readline()
line = line.split()
m = int(line[0])
n = int(line[1])

lines = f.readlines()
f.close()
i=0
matrix = [[0 for x in range(n)] for y in range(m)]

for line in lines:
	matrix[i] = line.split()
	i+=1

for i in range(m):
	print(matrix[i])


for x in range(m):
	for y in range(n):
		if matrix[x][y]=='3':
			start_x = x
			start_y = y
			break
			break


exit_list=[]
for x in range(m):
	for y in range(n):
		if matrix[x][y]=='3':
			start_x = x
			start_y = y
		if matrix[x][y]=='4':
			exit_list.append([x,y])

print("start at " + str(start_x) +","+ str(start_y))

root = Tree()
root.depth = 0
root.x = start_x
root.y = start_y
root.value = '3'
done = False
time = 0
result_time = 0
result_node = None

q = []
make_node(root)
while not done:
	target = q.pop(0)
	make_node(target[1])

target = result_node
time = result_time
print("end at " + str(target.x) +","+ str(target.y))
print("length "+str(target.depth-1))
print("time "+str(time))
make_route(target)

f = open(file_path + "\output.txt",'w')
for i in range(m):
	data = ""
	for j in range(n):
		data += str(matrix[i][j])+" "
	data += "\n"
	f.write(data)
f.write("---\n")
f.write("legnth="+str(target.depth-1)+"\n")
f.write("time="+str(time)+"\n")
f.close()