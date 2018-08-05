for i in range(10):
	print(i)
for i in range(3, 10):
	print(i)
for i in range(0,10,2):
	print(i)

i=0
while i<10:
	i+=1
	print(i)

def sign(x):
	if x>0:
		return 'positive'
	elif x<0:
		return 'negative'
	else:
		return 'zero'

for x in [-1,0,1]:
	print(sign(x))