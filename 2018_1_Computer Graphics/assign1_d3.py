class Student(object):
	def __init__(self,name):
		self.name = name
	def set_age(self,age):
		self.age = age
	def set_major(self,major):
		self.major = major

anna = Student('anna')
anna.set_age(21)
anna.set_major('physics')

print(anna.name)
print(anna.age)
print(anna.major)

class MasterStudent(Student):
	def set_lab(self,lab):
		self.lab = lab

tom = MasterStudent('tom')

tom.set_age(25)
tom.set_major('computer science')
tom.set_lab('graphics lab')
print(tom.name)
print(tom.age)
print(tom.major)
print(tom.lab)