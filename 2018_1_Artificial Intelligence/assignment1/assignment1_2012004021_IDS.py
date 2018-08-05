class Tree(object):
	def __init__(self):
		self.origin = None
		self.depth = None
		self.value = None
		self.x = None
		self.y = None

class stack:
	def __init__(self):
		self.__storage = []
	def isEmpty(self):
		return len(self.__storage) == 0
	def push(self,p):
		self.__storage.append(p)
	def pop(self):
		return self.__storage.pop()

def make_node(origin,time):
	global result_time,result_node,done
	if check_matrix(origin,origin.x+1,origin.y):
		temp = Tree()
		temp.x = origin.x+1
		temp.y = origin.y
		temp.value = matrix[origin.x+1][origin.y]
		temp.depth = origin.depth+1
		temp.origin = origin
		stack.push(temp)
		if temp.value == '4' :
			result_time = time
			result_node = temp
			done = True
	if check_matrix(origin,origin.x,origin.y-1):
		temp = Tree()
		temp.x = origin.x
		temp.y = origin.y-1
		temp.value = matrix[origin.x][origin.y-1]
		temp.depth = origin.depth+1
		temp.origin = origin
		stack.push(temp)
		if temp.value == '4' :
			result_time = time
			result_node = temp
			done = True
	if check_matrix(origin,origin.x,origin.y+1):
		temp = Tree()
		temp.x = origin.x
		temp.y = origin.y+1
		temp.value = matrix[origin.x][origin.y+1]
		temp.depth = origin.depth+1
		temp.origin = origin
		stack.push(temp)
		if temp.value == '4' :
			result_time = time
			result_node = temp
			done = True
	if check_matrix(origin,origin.x-1,origin.y):
		temp = Tree()
		temp.x = origin.x-1
		temp.y = origin.y
		temp.value = matrix[origin.x-1][origin.y]
		temp.depth = origin.depth+1
		temp.origin = origin
		stack.push(temp)
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



print("start at " + str(start_x) +","+ str(start_y))

root = Tree()
root.depth = 0
root.x = start_x
root.y = start_y
root.value = '3'
length = 1
stack = stack()
done = False
result_time = 0
result_node = None
while not done:
	stack.push(root)
	time = 0
	while not done:
		if stack.isEmpty() :
		 	break
		target = stack.pop()
		time+=1
		if int(target.depth) < length :
			make_node(target,time)
	if not done:		
		print("length "+str(length)+" failed")
		length+=1

target = result_node
time = result_time
print("end at " + str(target.x) +","+ str(target.y))
print("length "+str(length-1))
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
f.write("legnth="+str(length-1)+"\n")
f.write("time="+str(time)+"\n")
f.close()