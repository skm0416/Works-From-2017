import math # for math.log2() function

DIMENSION = 300
WORDS = 338
THRESHOLD = 0.2
USE_COSINE_OR_EUCLID = 1 # 1 for cosine, 0 for euclid

#######test result############################################
## similarity&threshold / entropy / gini / number of clusters
## cosine 0.2 : 1.025408 / 0.575631 / 82 cluster
## cosine 0.4 : 0.474918 / 0.781150 / 184 cluster
## cosine 0.6 : 0.122810 / 0.939842 / 286 cluster
## cosine 0.8 : 0.005917 / 0.997041 / 331 cluster
## euclid 0.2 : 2.812333 / 0.155741 / 7 cluster
## euclid 0.4 : 2.454356 / 0.221349 / 39 cluster
## euclid 0.6 : 0.801368 / 0.667789 / 217 cluster
## euclid 0.8 : 0.061405 / 0.973373 / 327 cluster
##############################################################

## 1. calculate similarity

def similarity(v1,v2):
	if USE_COSINE_OR_EUCLID:
		return cosine_similarity(v1,v2)
	else:
		return euclidean_similarity(v1,v2)

def cosine_similarity(v1,v2):
	return scalar_product(v1,v2) / (l2_norm(v1) * l2_norm(v2))

def scalar_product(v1,v2):
	sum = 0
	for i in range(DIMENSION):
		sum += v1[i]*v2[i]
	return sum

def l2_norm(v):
	sum = 0
	for i in range(DIMENSION):
		sum += v[i]*v[i]
	sum = sum**(1/2)
	return sum

def euclidean_similarity(v1,v2):
	sum = 0
	for i in range(DIMENSION):
		dif = v1[i]-v2[i]
		sum += dif*dif
	sum = sum**(1/2)
	return sum

file_path = input("please input file path: ")
f = open(file_path + "\WordEmbedding.txt",'r')

lines = f.readlines()
f.close()

word = lines[0:][::2]
for i in range(WORDS):
	word[i] = word[i].replace('\n','')

vectors_origin = lines[1:][::2]
split_vectors = [[0 for x in range(DIMENSION)] for y in range(WORDS)]
for i in range(WORDS):
	split_vectors[i] = vectors_origin[i].split(",")

vector = [[float(split_vectors[y][x]) for x in range(DIMENSION)] for y in range(WORDS)]
del(vectors_origin)
del(split_vectors)

similarity_list = []
similarity_matrix = [[0 for x in range(WORDS)] for y in range(WORDS)]
for x in range(WORDS):
	for y in range(x+1,WORDS):
		similarity_matrix[x][y] = similarity(vector[x],vector[y])
		temp_pair = (similarity_matrix[x][y],x,y)
		similarity_list.append(temp_pair)

similarity_list = sorted(similarity_list, key=lambda similarity: similarity[0])
similarity_list.reverse()

max_value = similarity_list[0][0]
min_value = similarity_list[len(similarity_list)-1][0]
balance_value = max_value - min_value


## 2. complete-link clustering

class cluster(object):
	def __init__(self):
		self.similarity = None
		self.left = None
		self.right = None
		self.up = None
		self.list = []

def find_root_cluster(target):
	while target.up is not None :
		target = target.up
	return target

def single_cluster(value):
	temp = cluster()
	temp.list.append(value)
	temp.similarity = 1
	clusters.append(temp)
	clustered_index[value] = temp

def make_cluster(similarity,value1,value2,left,right):
	temp = cluster()
	if left is not None :
		left = find_root_cluster(left)
		temp.left = left
		left.up = temp
		temp.list.extend(left.list)
	if right is not None :
		right = find_root_cluster(right)
		temp.right = right
		right.up = temp
		temp.list.extend(right.list)
	temp.list.append(value1)
	temp.list.append(value2)
	temp.list = list(set(temp.list))
	temp.list.sort()
	if USE_COSINE_OR_EUCLID == 0 : # euclide balance min~max to 0~1
		temp.similarity = ((similarity - min_value) / balance_value)		
	else :
		temp.similarity = similarity
	clusters.append(temp)
	clustered_index[value1] = temp
	clustered_index[value2] = temp

def pair_complete_check(value1,value2,left,right):
	check_list = []
	if left is not None :
		left = find_root_cluster(left)
		check_list.extend(left.list)
	if right is not None :
		right = find_root_cluster(right)
		check_list.extend(right.list)
	check_list.append(value1)
	check_list.append(value2)
	check_list = list(set(check_list))
	check_list.sort()
	if (now_index*3 - len(similarity_list)) >= 0: # use other algorithm for big cluster
		for i in range(now_index+1,len(similarity_list)):
			if similarity_list[i][1] in check_list and similarity_list[i][2] in check_list:
				return False
	else :
		for x in range(len(check_list)):
			for y in range(x+1,len(check_list)):
				if (check_list[(x)],check_list[(y)]) not in checked_pair:
					return False
	#print("pair complete : %d , %d" % (value1,value2))
	print(check_list)
	return True

def complete_cluster(similarity,value1,value2):
	checked_pair.append((value1,value2))
	left = clustered_index[value1]
	right = clustered_index[value2]
	if pair_complete_check(value1,value2,left,right):
		make_cluster(similarity,value1,value2,left,right)

clustered_index = [None for x in range(WORDS)]
checked_pair = []
clusters = []
		
for x in range(WORDS):
	single_cluster(x)

now_index = 0
for i in range(len(similarity_list)):
	now_index = i
	if i%1000 == 0:
		print("\n%d / %d\n" % (i,len(similarity_list)))
	complete_cluster(similarity_list[i][0],similarity_list[i][1],similarity_list[i][2])

print("number of clusters : %d" % len(clusters))



## 3. divide cluster with threshold

def explore_cluster(target):
	if target.similarity <= THRESHOLD :
		if target.left is not None :
			explore_cluster(target.left)
		if target.right is not None :
			explore_cluster(target.right)
	else :
		divided_clusters.append(target)
		for x in target.list :
			cluster_number[x] = (len(divided_clusters)-1)

cluster_number = [0 for x in range(WORDS)]
divided_clusters = []
explore_cluster(clusters[int(len(clusters)-1)])

f = open(file_path + "\WordClustering.txt",'w')
for x in range(len(lines)):
	f.write(lines[x])
	if int(x%2) == int(1) :
		f.write(str(cluster_number[int((x-1)/2)])+"\n")
f.close()

f = open(file_path + "\Cluster_group.txt",'w')
for x in range(len(divided_clusters)):
	f.write("cluster "+str(x)+"\n")
	for word_index in divided_clusters[x].list :
		f.write(word[word_index]+" ")
	f.write("\n")
f.close()



## 4. read word class from WordTopic.txt

f = open("WordTopic.txt",'r')
lines = f.readlines()
f.close()

class_dictionary = dict()
class_data = []
for line in lines:
	if len(line) > 1:
		class_data.append(line[:-1].lower())
class_index = -1
for x in class_data:
	if x[0] is '[':
		class_index=class_index+1
	else :
		class_dictionary[word.index(x.strip())] = class_index



## 5. analyze cluster with word class

def e(value):
	return -(value*math.log2(value))

def entropy_and_gini(list):
	list_sum = 0
	entropy_sum = 0
	gini_sum = 0
	for x in list:
		list_sum += x
	for x in list:
		if x is not 0 :
			entropy_sum += e(x/list_sum)
			gini_sum += (x*x)/(list_sum*list_sum)
	return entropy_sum, gini_sum

def word_list_to_purity(list):
	number_of_same_class = [0 for x in range(8)]
	for target_word in list:
		index = class_dictionary.get(target_word)
		number_of_same_class[index] += 1
	return entropy_and_gini(number_of_same_class)

number_of_same_class = []
total_cluster_entropy = 0
total_cluster_gini = 0
for i in range(len(divided_clusters)):
	temp_entropy, temp_gini = word_list_to_purity(divided_clusters[i].list)
	print("%dth cluster's entropy : %f gini : %f" % (i,temp_entropy,temp_gini))
	total_cluster_entropy += temp_entropy * len(divided_clusters[i].list) / WORDS
	total_cluster_gini += temp_gini * len(divided_clusters[i].list) / WORDS


print("\ntotal weighted entropy: %f" % total_cluster_entropy)
print("total weighted gini: %f" % total_cluster_gini)
print("total cluster number : %d" % len(divided_clusters))