#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "algo.h"

//Build a new graph with the given amount of nodes
void build_graph_cmd(pnode *head, int num_of_nodes){
    //Remove the former graph
    removeGraph(head);
    int i;
    // Create the new nodes
    for (i = 0; i < num_of_nodes; i++)
        add_node(head,i);
}

//Prints the Graph - used for debugging
void printGraph_cmd(pnode head){
    // Go over the nodes and print for each Id:_ ,edges{ d:_ ,w:_, ... , } 
    node *current = head;
    while(current != NULL)
    {
        printf("Id: %d, egdes{",current->node_num);
        edge *cur = current -> edges;
        while(cur != NULL){
            printf("d:%d w:%d, ",cur -> endpoint -> node_num,cur -> weight);
            cur = cur->next;
        }
        printf("}\n");
        current = current->next;
    }
}

//Adds a new node to the Graph
void add_node(pnode *head, int node_id){
    //Create the New Node
    pnode newNode = (pnode)malloc(sizeof(node));
    newNode -> node_num = node_id;
    newNode -> edges = NULL;
    newNode -> next = *head;
    // change the pointer of head to the new node
    *head = newNode;
}

//Returns a pointer to the node in the graph with the given Id 
pnode getNode(pnode *head, int node_id){
    node *current = *head;
    while (current != NULL)
    {
        if (current -> node_num == node_id)
            return current;
        current = current -> next;
    }
    return NULL;
}

//Adds a new edge to the given node
void addEdge(pnode node, int dest, int w, pnode *head){
    // Create the new egde
    pedge newEdge = (pedge)malloc(sizeof(edge));
    newEdge -> weight = w;
    newEdge -> endpoint = getNode(head,dest);
    newEdge -> next = node -> edges;
    //Add the edge to the node
    node -> edges = newEdge;
}

//Remove the given Graph
void removeGraph(pnode *head){
    //Remove each node one by one
    while (*head != NULL)
        removeNode(head,(*head) -> node_num);
}

//Remove the node with given id from the graph
void removeNode(pnode *head, int node_id){
    if( *head == NULL)
        return;
    node *current = *head;
    node **prev = head;
    int found = 0;
    //find the node
    while (current != NULL && found == 0)
    {
        if (current -> node_num == node_id) {
            //if the node was found make the node pointing to it point to the next
            *prev = current -> next;
            found = 1;
        }
        else {
            prev = &(current->next);
            current = current->next;
        }
    }
    //Deallocate the memory of the node and its edges
    if(current != NULL) {
        while (current->edges != NULL)
            removeEdge(current);
        //deallocate the memory of the node
        free(current);
    }
}

//Remove the first edge from the given node
void removeEdge(pnode node){
    edge *newEdge = (node->edges);
    if(newEdge != NULL){
        node -> edges = newEdge -> next;
        //deallocating the memory of the edge
        free(newEdge);
    }
}

//Removes an edge by the id of its destination
void removeEdge2(pnode node,int node_id){
    edge *newEdge = (node->edges);
    edge **prev = &(node->edges);
    int found = 0;
    while(newEdge != NULL && found == 0)
    {
        if(newEdge -> endpoint -> node_num == node_id){
            *prev = newEdge->next;
            found = 1;
        }
        else{
            prev = &(newEdge->next);
            newEdge = newEdge -> next;
        };
    }
    //Deallocate the memory of the edge
    if(found==1){
        free(newEdge);
    }
}