#filter_out.py
#07-19-2017
#Mai Linh Ngo

#############################################
#READ x-coordinate
#############################################

read_x = open('bigx.txt','r')
l = read_x.readlines()
#print(l)
final_list = []
for i in l:
    final_list.append(i.strip())
print("Now Without:")
#print(final_list)
read_x.close()

#############################################
#READ y-coordinate
#############################################

print('Now reading second coordinate')
read_y = open('bigy.txt','r')
m = read_y.readlines()
#print(m)
final_list2 = []
for j in m:
    final_list2.append(j.strip())
print("Now Without:")
#print(final_list2)
read_y.close()

print('size of final_list is', len(final_list))
print('size of final_list2 is', len(final_list2))
print('val. of final_list[50]=', (final_list[50]))
print('Type of final_list[50]=', type(final_list[50]))
print(type(float(final_list[50])))


###============================================
###====SORTING=================================
###============================================
##sort_x = []
##sort_y = []
##for i in range(0, len(final_list)-1):
##    z = float(final_list[i])
##    #print("i'm in the loop")
##    #print("z is:",z)
##    if z < 10:
##        sort_x.append(z)
##        sort_y.append(z)
##    else:
##        continue
##
##print('size of sort_x is:',len(sort_x))
##print('size of sort_y is:',len(sort_y))

#============================================
#====SORTING=================================
#============================================

sort_x = []
sort_y = []
for i in range(0, len(final_list)-1):
    z = float(final_list2[i])
    #print("i'm in the loop")
    #print("z is:",z)
    if z < 10:
        sort_x.append(final_list[i])
        sort_y.append(final_list2[i])
    else:
        continue

print('size of sort_x is:',len(sort_x))
print('size of sort_y is:',len(sort_y))
#print(sort_x)
#print(sort_y)







###########################################
#OUTPUTTING FILES###
###########################################

#X
f = open('out_x.txt', 'w') # create file blah
for i in sort_x:
    f.write(str(i) + "\n")
f.close()

#Y
g = open('out_y.txt', 'w') # create file blah
for j in sort_y:
    g.write(str(j) + "\n")
g.close()



    
