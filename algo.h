#ifndef ALGO_
#define ALGO_
    
//Finds the shortest path using the dijkstra Algorithm
int dijkstra(pnode *head,int amount_of_Nodes, int src, int dest);

//The main TSP function
int TSP(pnode *head,int *cities, int length,int amount_of_Nodes);

// This function is the tsp algorithm
int TSPalgorithm(pnode *head,int *cities,int start,int length,int amount_of_Nodes);

//An auxiliary function to get the shortest path
int min(int x,int y, int w);

//An auxiliary function that given an array and an index, it returns a copy of that array without the index
int* copyArray(int *arr, int remove, int length);

//An auxiliary function used by dijkstra, will return -1 in case the node doesn't exist
int placeCalc(pnode *head, int node_id,int amount_of_Nodes);

//The opisite of placeCalc - calculate the node id by its positon in the graph
int get_Id_by_Pos(pnode *head, int pos, int amount_of_Nodes);

#endif