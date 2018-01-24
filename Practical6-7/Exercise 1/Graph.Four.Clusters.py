import sys
import numpy as np
import random as rand
#import pygraphviz as pgv

max_nodes = 400

#p = float(sys.argv[1])

p = input("Enter the value for p: ")
print 'Recall that the value of q must be smaller than p.'
q = input("Enter the value for q: ")

if q >= p:
    print 'The value of q must be smaller than p. End of script.'
    sys.exit()

graph= np.empty([0,2], dtype=int)

print 'Generating random graph with 400 nodes. Values for p: ',p, 'and q', q,'.'

for n1 in range(1,max_nodes):
    for n2 in range(n1+1,max_nodes+1):

        random_value = rand.random()

        if(int(n1/100)==int(n2/100)):
            probability=p
        else:
            probability=q

        if (random_value <= probability):
            graph=np.concatenate((graph,[[n1,n2]]), axis=0)


output_file = '01.Output_p_'+str(p)+'_q_'+str(q)+'.dat'
print 'Writing file '+output_file

np.savetxt(output_file, graph, fmt='%d')

f = open(output_file,'r')
lines = f.readlines()

new_file_name = '01.Output_p_'+str(p)+'_q_'+str(q)+'.dl'
newf = open(new_file_name,'w')

print 'Writing file '+new_file_name
newf.write('DL n=400\n')
newf.write('format = edgelist1\n')
newf.write('data:\n')
for line in lines:
    newf.write(line)
newf.close()
f.close()

print 'End of script'
