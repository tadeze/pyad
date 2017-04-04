# TreeNode

import json
import queuelib.queue

# TreeNode
class Node:
    def __init__(self,depth=-99,splittingAtt=-1, \
                 splittingPoint=-99,nodesize=-1,minAttVal=0,maxAttVal=0):
        self.assign(depth,splittingAtt,splittingPoint,nodesize,minAttVal,maxAttVal)

    def assign(self,depth=-99,splittingAtt=-1, \
                 splittingPoint=-99,nodesize=-1,minAttVal=0,maxAttVal=0):
        # Assign node
        self.depth=depth
        self.minAttVal=minAttVal
        self.maxAttVal=maxAttVal
        self.splittingAtt=splittingAtt
        self.splittingPoint=splittingPoint
        self.nodesize=nodesize

    def print_node(self):
        return "Depth:{0:f},splittingAtt:{1:f},splittingPoint:{2:f},nodesize:{3:f},minAttVal:{4:f},maxAttVal:{5:f}".format(
            self.depth,self.splittingAtt,self.splittingPoint,self.nodesize,self.minAttVal,self.maxAttVal)
    def assign_node(self,json_node):
        ## Assign node from json fragment
        if len(json_node)<6:
            self.assign(depth=json_node["depth"])
        else:
            self.assign(depth=json_node["depth"],splittingAtt=json_node["splittingAtt"],
                        splittingPoint=json_node["splittingPoint"],
                    nodesize=json_node["nodesize"],minAttVal=json_node["minAttVal"],
                        maxAttVal=json_node["maxAttVal"])

    def equals(self,node):
        return (self.depth==node.depth) & (self.splittingAtt==node.splittingAtt)& \
                (self.nodesize==node.nodesize) & (self.splittingPoint==node.splittingPoint) 
    def equal_attribute_range(self,node):
        return self.minAttVal==node.minAttVal & self.maxAttVal==node.maxAttVal

def query_point(X):
    # Query a point and trace the path the point across the trees
    pass


def json_parser():
    js_clean = json.load(open('results/clean.json','r'))   # Read json files
    js_conta = json.load(open('results/contaminated.json','r'))

    clean_nodes = []
    unclean_nodes =[]
    dis_agreement=[]
    for j in range(len(js_clean["trees"])):

        # Take one tree for example
        tree_clean= js_clean["trees"][j]
        tree_unclean = js_conta["trees"][j]
        dis_cnt=0
        #Assum the trees has equal depth or take the longer one
        n_nodes = len(tree_clean) if len(tree_clean) > len(tree_unclean) else len(tree_unclean)
        for i in range(n_nodes):

            current_clean_tree =  tree_clean[i]
            current_unclean_tree = tree_unclean[i]

            if current_clean_tree is None or current_unclean_tree is None:
                break
            clean_node = Node()
            unclean_node =Node()

            clean_node.assign_node(current_clean_tree)
            unclean_node.assign_node(current_unclean_tree)

            # now check the difference
            if clean_node.equals(unclean_node) is False:
                dis_cnt = dis_cnt+1




            clean_nodes.append(clean_node)
            unclean_nodes.append(unclean_node)
        dis_agreement.append((j,dis_cnt))


    return dis_agreement,clean_nodes,unclean_nodes

if __name__ == '__main__':
    dis,clean,unclean = json_parser()
    print dis
