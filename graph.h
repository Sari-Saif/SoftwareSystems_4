#ifndef GRAPH_
#define GRAPH_

typedef struct GRAPH_NODE_ *pnode;;

typedef struct edge_ {
    int weight;
    pnode endpoint;
    struct edge_ *next;
} edge, *pedge;


typedef struct GRAPH_NODE_ {
    int node_num;
    pedge edges;
    struct GRAPH_NODE_ *next;
} node, *pnode;

//-----------

//Build a new graph with the given amount of nodes
void build_graph_cmd(pnode *head, int num_of_nodes);

//Prints the Graph - used for debugging
void printGraph_cmd(pnode head);

//Adds a new node to the Graph
void add_node(pnode *head, int node_id);

//Returns a pointer to the node in the graph with the given Id
pnode getNode(pnode *head, int node_id);

//Adds a new edge to the given node
void addEdge(pnode node, int dest, int w, pnode *head);

//Remove the node with given id from the graph
void removeNode(pnode *head, int node_id);

//Remove the first edge from the given node
void removeEdge(pnode node);

//Remove the given Graph
void removeGraph(pnode *head);

//Removes an edge by the id of its destination
void removeEdge2(pnode node,int node_id);

//-----------

#endif
