import random
import enum
import math

#2012004021 심규민

def max(a,b):
	if(a>b):
		return a
	else:
		return b

class DNA(enum.Enum):#use with DNA.A.value
	a = 0
	A = 0
	c = 1
	C = 1
	g = 2
	G = 2
	t = 3
	T = 3

def getprofile():
	for y in range(t):
		for x in range(k):
			profile[DNA[Bestmotifs[y][x]].value][x] +=1
	return

def getscore():
	score = 0
	for x in range(k):
		score += max(max(profile[0][x],profile[1][x]),max(profile[2][x],profile[3][x]))
	return score

def getprobability(y,x):
	value = 1
	for i in range(k):
		value *= profile[DNA[line[3+y][x+i]].value][i]+1
	return value

def printmotif():
	for i in range(t):
		print("{0:<3d}".format(i) + Bestmotifs[i])
	return

f = open("test01.txt",'r')
line = f.readlines()

k = int(line[0]) # length of motifs
t = int(line[1]) # number of string
m = int(line[2]) # max length of each string
print("k "+line[0], end="")
print("t "+line[1], end="")
print("m "+line[2], end="")

profile = [[0 for x in range(k)] for y in range(4)]
Bestmotifs = []
Bestscore = 0

for x in range(t):
	y = random.randrange(0,m-k-2)
	Bestmotifs.append(line[3+x][y:y+k])

getprofile()
Bestscore = getscore()

count = 0
while(count < t*math.sqrt(t)): #stop when score gained 0 for t^3/2 times
	print("converge count "+str(count)+" until "+str(int(t*math.sqrt(t))))
	probability = 1
	index = 0
	j = random.randrange(0,t)
	for x in range(k):
		profile[DNA[Bestmotifs[j][x]].value][x] -=1
	for x in range(m-k+1):
		temp = getprobability(j,x)
		if(probability < temp):
			index = x
			probability = temp
	
	before_motif = Bestmotifs[j]
	after_motif = line[3+j][index:index+k]
	Bestmotifs[j] = after_motif
	for x in range(k):
		profile[DNA[after_motif[x]].value][x] +=1
	gained_score = getscore() - Bestscore
	if(gained_score is 0):
		count+=1
	Bestscore = Bestscore + gained_score
	#print("score gained "+str(gained_score))
	#printmotif()

printmotif()
for y in range(4):
	for x in range(k):
		print(profile[y][x]/t, end=" ")
	print()