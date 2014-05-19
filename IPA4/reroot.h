/*
 * packing.h
 *
 *  Created on: Oct 18, 2013
 *      Author: emreozsahin
 */

#ifndef PACKING_H_
#define PACKING_H_

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define TRUE 1
#define FALSE 0

typedef struct block{
	int thisnode;
    int parnode;
    int lcnode;
    int rcnode;
	char cutline;
	float width;
	float height;
	float posx;
	float posy;

}Block;

typedef struct Pos{
	float posx;
	float posy;
}POS;



FILE* getFilePtr(char filename[]);
int checkArgCount(int argc);
void printArray(Block* array, int num_size);
Block* loadFile(char* filename,int *num_blocks,int *num_nodes);
int findBase(Block *arr, int num_nodes);
POS* travelTree_dim(Block* arr,int base);
void travelTree_cor1(Block* arr,int base);
void saveFile(Block* arr,int num,char filename[]);
void printDim(Block* arr, int n);
void printCor(Block* arr,int m);
void printClock(double k);
void rerootTree(Block* arr,int base,char direction,char,char b_mode,float,float,float,float,float*,float*,int,int);
void printCordData(Block *, int);


#endif /* PACKING_H_ */
