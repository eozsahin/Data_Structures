/*
 * sequnce_pair.h
 *
 *  Created on: Dec 1, 2013
 *      Author: emreozsahin
 */

#ifndef SEQUNCE_PAIR_H_
#define SEQUNCE_PAIR_H_

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define TRUE 1
#define FALSE 0

typedef struct Node{
	int thisnode;
	float width;
	float height;
	int* left_arr;
}Node;

Node* loadFile(char *filename,int,int*,int*);

int checkArgCount(int);
FILE* getFilePtr(char filename[]);
void printNodeArray(Node* ,int);
void printSeqPairs(int*,int*,int);
int getSize(char* filename);
Node* createAdjList(Node* node,int* pair_1, int* pair_2,int size);
void printAdjList(Node* node,int);
//void setupAdjMatrix(Node* node,int);





#endif /* SEQUNCE_PAIR_H_ */
