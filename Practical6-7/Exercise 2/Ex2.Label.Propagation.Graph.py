import sys
import numpy as np
import random as rnd
from networkx import *
from random import shuffle
from collections import defaultdict
from collections import OrderedDict
from datetime import datetime

startTime = datetime.now()

def find_max_occurrence_label(neighbors_labels, previous_label):

    new_label = previous_label
    d = defaultdict(int)
    b=False
    for i in neighbors_labels:
        b=True
        d[i]+=1

    if(b):
        result = max(d.iteritems(), key=lambda x: x[1])
        new_label = result[0]

    return new_label

G = nx.read_adjlist('youtube.dat', nodetype=int)
min_node = np.min(G.nodes())
max_node = np.max(G.nodes())
num_iterations =10,

print "Number of nodes: ",+max_node
print "Number of edges: ",+len(G.edges)

#List to hold the ids fo the nodes, we populate with the ids of the nodes we have in the graph.
nodes_list = []
for i in range(min_node, max_node+1):
    nodes_list.append(i)

#nodes_list2=G.nodes()

#We set a unique label for each node, in this case it is the id of the node.
for i in range(min_node, max_node+1):
    G.add_node(i, label=i)


label=nx.get_node_attributes(G,'label')


neighbors_labels = []
label_results = []
clean_label_results = []

f = open('Communities_youtube.dat','w')


for i in range(0,100):
    shuffle(nodes_list)
    #print nodes_list
    for node in nodes_list:
        #b=False
        #print "Node: ", node
        for neighbor in G.neighbors(node):
            b=True
#            print "Neighbor: ",neighbor, nodes_list[neighbor-1]
#            print "Label of the neighbor: ", label[nodes_list[neighbor-1]]
            #print "Neighbor: ",nodes_list[neighbor-1]
            for neighbor2 in G.neighbors(nodes_list[neighbor-1]):
#                print "Neighbor2 in List of Neighbor: ", neighbor2
#                print "Label of the neighbor2 in List of Neighbor: ", label[neighbor2]
                neighbors_labels.append(label[neighbor2])
                #print neighbor2, label[neighbor2]
#        print neighbors_labels
        #print neighbors_labels
        new_label = find_max_occurrence_label(neighbors_labels,label[node])
#        print "Old Label: ", label[node]
#        print "New Label Value: ", new_label
        G.add_node(node, label= new_label)
        label[node] = new_label
        neighbors_labels=[]

        #nx.set_node_attributes(G, 'label', new_label)
        #G.add_node(node, label=new_label)

#        print "Node label after making the change: ", label[node]

#    print 'Moving to second loop over the actual graph.'
    for node in G.nodes():
        label_results.append(label[node])
    #print label_results

    clean_label_results = list(OrderedDict.fromkeys(label_results))
    #print clean_label_results

    num_communities = len(clean_label_results)
    print ("Iteration "+str(i+1)+" value for community :"+str(num_communities))
    f.write(str(i+1)+" "+str(num_communities))
    f.write("\n")
    label_results=[]
#print 'Number of Communities is: '
#print num_communities
f.close()

print 'Execution Time: '+str(datetime.now() - startTime)
print('End of Script')
