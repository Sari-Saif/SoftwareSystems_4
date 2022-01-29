#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "algo.h"

//Finds the shortest path using the dijkstra Algorithm
int dijkstra(pnode *head,int amount_of_Nodes,  int src, int dest){
    //Test if the nodes even exist
    pnode sourceNode = getNode(head,src);
    pnode destinationNode = getNode(head,dest);
    if(sourceNode==NULL || destinationNode==NULL){
        //In case they don't exist then is no path so return -1
        return -1;
    }
    //Create the array that save the distance and the Queue
    int *d = (int*)malloc(sizeof(int)*amount_of_Nodes);
    int *Queue = (int*)malloc(sizeof(int)*amount_of_Nodes);
    int start = 0,end =amount_of_Nodes-1, Min, min_id, edge_dest_id;
    // Check if memory was allocated
    if (d==NULL || Queue ==NULL)
    {
        printf("Memory Not allocated");
        exit(0);
    }
    //initialize the array and Queue
    int i;
    for (i = 0; i < amount_of_Nodes; i++){
        d[i] = -1;
        Queue[i] = i;
    }
    d[placeCalc(head,src,amount_of_Nodes)] = 0;//TODO
    //Run the algorithm
    while (start<end)
    {
        //Extract the Min in the Queue

        Min = start;
        for (i = start+1; i <= end; i++){
            if(d[Queue[i]] == min(d[Queue[Min]],d[Queue[i]],0))
                Min = i;
        }
        min_id = Queue[Min];
        //Remove min from the Queue
        Queue[Min] = Queue[start];
        Queue[start] = min_id;
        start++;
        //Go over the edges of the min node
        pnode minNode = getNode(head,get_Id_by_Pos(head,min_id,amount_of_Nodes));//TODO - not a real id need to be changed
        edge *curEdge = minNode -> edges;
        while (curEdge != NULL)
        {
            //Relax algorithm
            edge_dest_id = curEdge->endpoint->node_num;
            d[placeCalc(head,edge_dest_id,amount_of_Nodes)] = min(d[placeCalc(head,edge_dest_id,amount_of_Nodes)],d[min_id],curEdge->weight);
            curEdge = curEdge-> next;
        }
    }
    int res = d[placeCalc(head,dest,amount_of_Nodes)];
    //Deallocate the arrays
    free(d);
    free(Queue);
    return res;
}

//The main TSP function
int TSP(pnode *head,int *cities, int length,int amount_of_Nodes){
    int minDist = -1, i;
    //Easy Cases
    if(length == 0 || length == 1)
        minDist = 0;
    //Run the TSP algorithm
    else{
        for (i = 0; i < length; i++)
        {
            int *copy = copyArray(cities,i,length);
            minDist = min(minDist,TSPalgorithm(head,copy,cities[i],length-1, amount_of_Nodes),0);
        }
    }
    //Deallocate the memory of the array
    free(cities);
    return minDist;
}

// This function is the tsp algorithm
int TSPalgorithm(pnode *head,int *cities,int start,int length,int amount_of_Nodes){
    int res = -1,minDist = -1,i, path,tsp;
    // Base Cases
    if(length == 0)
        res = 0;
    else if(length == 1)
        res =  dijkstra(head,amount_of_Nodes,start,cities[0]);
        //Recursive Tsp call on a smaller amount of cities
    else{
        for (i = 0; i < length; i++)
        {
            int *copy = copyArray(cities,i,length);
            path = dijkstra(head,amount_of_Nodes,start,cities[i]);
            if(path != -1){
                tsp = TSPalgorithm(head,copy,cities[i],length-1,amount_of_Nodes);
                minDist = min(minDist, tsp,path);
            }
            else{
                free(copy);
            }

        }
        res = minDist;
    }
    //Deallocate the memory
    free(cities);
    return res;
}
//An auxiliary function used by dijkstra, will return -1 in case the node doesn't exist
int placeCalc(pnode *head, int node_id,int amount_of_Nodes){
    int place = amount_of_Nodes-1;
    int found = 0;
    node *current = *head;
    while (current!= NULL && found == 0){
        if(current -> node_num == node_id)
            found = 1;
        else{
            place--;
            current = current -> next;
        }
    }
    return place;
}

//The opisite of placeCalc - calculate the node id by its positon in the graph
int get_Id_by_Pos(pnode *head, int pos, int amount_of_Nodes){
    int place = amount_of_Nodes-1;
    int found = 0;
    node *current = *head;
    while (current!= NULL && found == 0){
        if(place == pos)
            found = 1;
        else{
            place--;
            current = current -> next;
        }
    }
    return current-> node_num;
}


//An auxiliary function to get the shortest path
int min(int x,int y,int w){
    if(x==-1 && y==-1)
        return -1;
    if(x==-1)
        return y + w;
    if(y==-1)
        return x;
    if(x<=(y+w))
        return x;
    return y+w;
}

//An auxiliary function that given an array and an index, it returns a copy of that array without the index
int* copyArray(int *arr, int remove, int length){
    int *copy = (int*)malloc(sizeof(int)*(length-1));
    if(copy==NULL){
        printf("No Memory");
        exit(0);
    }
    int i,count=0;
    for (i = 0; i < length; i++)
    {
        if(i!=remove){
            copy[count] = arr[i];
            count++;
        }
    }
    return copy;

}