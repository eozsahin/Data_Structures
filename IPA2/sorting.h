/*
 * sorting.h
 *
 *  Created on: Sep 24, 2013
 *      Author: emreozsahin
 */

#ifndef SORTING_H_
#define SORTING_H_

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define FALSE 0
#define TRUE 1




//structure for list
typedef struct list {
	struct Node *node;
	struct list *next;
} List;

//structure for node
typedef struct node {
	long value;
	struct node *next;
} Node;
//necessary function for the project
int Save_File(char *Filename ,Node *list);
Node *Load_File(char *Filename);
void Shell_Sort(Node *list);

//user functions
int checkArgCount(int argc);
FILE* getFilePtr(char filename[]);
Node *CreateNode(long val);
Node *NodeInsert(Node *node, long int val);
Node *NodeInsert2(Node *node, long int val);
Node* reverseList(Node* head);
void ListPrint(Node *node);
void switchNodes(Node *prev_higher, Node *higher, Node * small);




#endif /* SORTING_H_ */
