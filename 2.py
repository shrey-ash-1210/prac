'''
implement all the functions of dictionary (adt) using hashing and handle collisions using with/without replacement
data is set of key,value pairs. keys are mapped to values, keys must be comparbale and unique. functions to implement insert(key,value), find(key) and delete(key)
'''
def insert(data,mp):
	h=data[0]%10
	if(mp[h]==None):
		mp[h]=data
		
	elif(mp[h]!=None and mp[h][2]==-1):
		i=h+1
		while(i!=h):
			if(i==10):
				i=0
			elif(mp[i]!=None):
				i+=1
			elif(mp[i]==None):
				mp[i]=data
				mp[h][2]=i
				break
				
	elif(mp[h]!=None and mp[h][2]!=-1):
		k=mp[h][2]
		while(mp[k][2]!=-1):
			k=mp[k][2]
		i=k+1
		while(i!=k):
			if(i==10):
				i=0
			elif(mp[i]!=None):
				i+=1
			elif(mp[i]==None):
				mp[i]=data
				mp[k][2]=i	
				break

def find(key,mp):
	h=key%10
	if(mp[h]!=None and mp[h][0]==key):
		print(mp[h])
	elif(mp[h]!=None and(mp[h][0]!=key and mp[h][2]!=-1)):
		k=mp[h][2]
		while(mp[k]!=None and(mp[k][0]!=key or mp[k][2]!=-1)):
			k=mp[k][2]
		if(mp[k]!=None and mp[k][0]==key):
			print(mp[k])
		else:
			print("Not found")
	elif(mp[h]==None):
		print("Not Found")	
		
		
def main():
	mp=[None]*10
	while(True):
		print("1. Insert")
		print("2. Delete")
		print("3. Find")
		c=int(input("Enter your choice: "))
		if(c==1):
			key=int(input("Enter the key: "))
			val=int(input("Enter the value: "))
			temp=[key,val,-1]
			insert(temp,mp)
			print(mp)
		elif(c==3):
			key=int(input("Enter the key to be searched: "))
			find(key,mp)
		else:
			break;
main()
