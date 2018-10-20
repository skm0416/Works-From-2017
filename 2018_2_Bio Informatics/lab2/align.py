import sys

f1 = sys.argv[1]
f2 = sys.argv[2]
f3 = sys.argv[3]

file1 = open(f1,'r')
file2 = open(f2,'r')
file3 = open(f3,'r')

lines1 = file1.readlines()
lines2 = file2.readlines()
lines3 = file3.readlines()

seq1 = lines1[1]
seq2 = lines2[1]

output = ""
check = False
for char in lines3[0]:
	if check is True:
		output+= char
	if char == "=":
		check = True
match = int(output)


output = ""
check = False
for char in lines3[1]:
	if check is True:
		output+= char
	if char == "=":
		check = True
mismatch = int(output)


output = ""
check = False
for char in lines3[2]:
	if check is True:
		output+= char
	if char == "=":
		check = True
gap = int(output)

print("input information")
print("seq1 : " + seq1)
print("seq2 : " + seq2)
print("match : "+str(match))
print("mismatch : "+str(mismatch))
print("gap : "+str(gap))
print("")
seq1 = " "+seq1
seq2 = " "+seq2
row = len(seq1)
col = len(seq2)
score = [[0 for x in range(col)] for y in range(row)]
backtrack = [[0 for x in range(col)] for y in range(row)]

def max(a,b):
	if(a<b):
		return b
	else:
		return a

def LCSBackTrack(v,w,islocal):
	if(islocal is False):
		for i in range(len(v)):
			score[i][0] = i*gap 
		for j in range(len(w)):
			score[0][j] = j*gap 

	for i in range(1,len(v)):
		for j in range(1,len(w)):
			now = max(score[i-1][j]+gap,score[i][j-1]+gap)
			now = max(now,score[i-1][j-1]+mismatch)
			if(v[i] == w[j]):
				now = max(now,score[i-1][j-1]+match)
			if(islocal is True):
				now = max(0,now)
			score[i][j] = now
			if(islocal is True and now == 0):
				backtrack[i][j] = 0 #not local
			elif(now == score[i-1][j]+gap):
				backtrack[i][j] = 1 #down
			elif(now == score[i][j-1]+gap): 
				backtrack[i][j] = 2 #right
			elif(now == score[i-1][j-1]+match and v[i] == w[j]):
				backtrack[i][j] = 3 #match
			elif(now == score[i-1][j-1]+mismatch):
				backtrack[i][j] = 4 #mismatch

def OutputLCS(i,j):
	global outs1,outs2,num_mismatch,num_gap,num_match
	if(i == 0 and j == 0):
		return
	if(backtrack[i][j] == 0):
		return
	elif(backtrack[i][j] == 1):
		OutputLCS(i-1,j)
		outs1 += seq1[i]
		outs2 += "-"
		num_gap += 1
	elif(backtrack[i][j] == 2):
		OutputLCS(i,j-1)
		outs1 += "-"
		outs2 += seq2[j]
		num_gap += 1
	elif(backtrack[i][j] == 3):
		OutputLCS(i-1,j-1)
		outs1 += seq1[i]
		outs2 += seq2[j]
		num_match += 1
	elif(backtrack[i][j] == 4):
		OutputLCS(i-1,j-1)
		outs1 += seq1[i]
		outs2 += seq2[j]
		num_mismatch += 1

outs1 = ""
outs2 = ""
num_match = 0
num_mismatch = 0
num_gap = 0
LCSBackTrack(seq1,seq2,False)
OutputLCS(row-1,col-1)

print("global alignment")
print("matches: "+str(num_match))
print("mismatches: "+str(num_mismatch))
print("gaps: "+str(num_gap))
print("score: "+str(score[row-1][col-1]))
print(outs1)
print(outs2)
print("")


# local alignment

outs1 = ""
outs2 = ""
num_match = 0
num_mismatch = 0
num_gap = 0
score = [[0 for x in range(col)] for y in range(row)]
backtrack = [[0 for x in range(col)] for y in range(row)]
LCSBackTrack(seq1,seq2,True)
highscore = 0
x=0
y=0
for i in range(0,row):
	for j in range(0,col):
		if(score[i][j] > highscore):
			highscore = score[i][j]
			x = j
			y = i
OutputLCS(y,x)

print("local alignment")
print("matches: "+str(num_match))
print("mismatches: "+str(num_mismatch))
print("gaps: "+str(num_gap))
print("score: "+str(highscore))
print(outs1)
print(outs2)