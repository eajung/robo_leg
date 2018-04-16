#slice_data.py
#07-22-2017
#Mai Linh Ngo



file1 = input('Enter name of 1st coord. file (include .txt extension): ')
file2 = input('Enter name of 2nd coord. file (include .txt extension): ')

#############################################
#READ x-coordinate
#############################################

read_x = open(file1,'r')
l = read_x.readlines()
final_list = []
for i in l:
    final_list.append(i.strip())
read_x.close()

#############################################
#READ y-coordinate
#############################################

print('Now reading second coordinate')
read_y = open(file2,'r')
m = read_y.readlines()
final_list2 = []
for j in m:
    final_list2.append(j.strip())
read_y.close()

print('size of final_list is', len(final_list))
print('size of final_list2 is', len(final_list2))




#============================================
#====SORTING=================================
#============================================
skip = int(input("how many data points? "))
sort_x = []
sort_y = []
for i in range(0,skip):
        sort_x.append(final_list[i])
        sort_y.append(final_list2[i])
print('size of sort_x is:',len(sort_x))
print('size of sort_y is:',len(sort_y))



###########################################
#OUTPUTTING FILES###
###########################################
out_x = input("Enter name of output file for x-coord: ")
out_y = input("Enter name of output file for y-coord: ")

#X
#f = open('out_x.txt', 'w') # create file 
f = open(out_x, 'w') # create file 
for i in sort_x:
    f.write(str(i) + "\n")
f.close()

#Y
g = open(out_y, 'w') # create file blah
for j in sort_y:
    g.write(str(j) + "\n")
g.close()



    
