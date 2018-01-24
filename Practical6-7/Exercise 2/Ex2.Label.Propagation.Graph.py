import sys
import numpy as np
import random as rnd
from networkx import *
from random import shuffle
from collections import defaultdict
from collections import OrderedDict

def find_max_occurrence_label(neighbors_labels):
    new_label = 0
    d = defaultdict(int)
    for i in neighbors_labels:
        d[i]+=1
    result = max(d.iteritems(), key=lambda x: x[1])
    new_label = result[0]
    return new_label

G = nx.read_adjlist('Test.txt', nodetype=int)
min_node = np.min(G.nodes())
max_node = np.max(G.nodes())

#list to hold the ids fo the nodes, we populate with the ids of the nodes we have in the graph.
nodes_list = []
for i in range(min_node, max_node+1):
    nodes_list.append(i)

#We set a unique label for each node, in this case it is the id of the node.
for i in range(min_node, max_node+1):
    G.add_node(i, label=i)

label=nx.get_node_attributes(G,'label')

neighbors_labels = []
label_results = []
clean_label_results = []

f = open('Communities.dat','w')

for i in range(0,11):
    shuffle(nodes_list)
    for node in nodes_list:
        for neighbor in G.neighbors(node):
            neighbors_labels.append(label[neighbor])
        new_label = find_max_occurrence_label(neighbors_labels)
        G.add_node(node, label=new_label)

    for node in G.nodes():
        label_results.append(label[node])

    clean_label_results = list(OrderedDict.fromkeys(label_results))

    num_communities = len(clean_label_results)

    f.write(str(num_communities))
    f.write("\n")

#print 'Number of Communities is: '
#print num_communities

f.close()

print('End of Script')
