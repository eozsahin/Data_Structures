/*
 * sequence_pair.c

 *
 *  Created on: Dec 1, 2013
 *      Author: emreozsahin
 */

#include "sequence_pair.h"

int main(int argc,char *argv[]){

	int num_nodes = 0;

	num_nodes = getSize(argv[1]);
	int first_pair[num_nodes];
	int second_pair[num_nodes];

	Node* node_arr = loadFile(argv[1],num_nodes,first_pair,second_pair);

	printNodeArray(node_arr,num_nodes);
	printSeqPairs(first_pair,second_pair,num_nodes);



	//int adj_matrix[num_nodes][num_nodes];
	//setupAdjMatrix(adj_matrix,num_nodes);


	//createAdjList(node_arr,first_pair,second_pair,num_nodes);
	//printAdjList(node_arr,num_nodes);

	return 0;
}

Node* createAdjList(Node* node, int* pair_1, int* pair_2,int size){
	int temp_node;
	int temp_left;
	int num;
	int cnt;
	int j;
	int i;
	int k;
	//int temp_array[size] = {0};


	for(i = 1; i<=size;i++){
		temp_node = pair_1[i];
		num = node[i].thisnode;
		if(i == 1){
			for(cnt = 1;cnt<=size;cnt++){
				node[num].left_arr[0] = 2;//starting point
			}

		}
		for(k = i-1;k>0;k--){
			for(j = 1;j<=size;j++){
				if(temp_node == pair_2[j]){

				}else if(temp_node == pair_1[k]){
					temp_left = pair_1[k];
					//adj_matrix[temp_node][temp_left] = 1;
					node[num].left_arr[temp_left] = 1;

				}
			}
		}

	}

	return node;

}

Node* mallocLeftArr(Node* node, int size){
	int i;
	int j;
	for(i=1;i<= size;i++){
		node[i].left_arr = (int*)malloc(sizeof(int)*(size+1));
	}

	for(i = 1;i<=size;i++)
	{
		for (j = 0; j <= size; j++) {
			node[i].left_arr[j] = 0;
		}

	}
	return node;
}

//void setupAdjMatrix(Node* node,int size){
//	int i;
//	int j;
//	for (i = 1; i <= size; i++) {
//		for (j = 1; j <= size; j++) {
//			adj_mat[i][j] = 0;
//		}
//
//	}
//}


void printAdjList(Node* node,int size){

	int i;
	int j;

	for (i = 1; i <= size; i++) {
		for (j = 1; j <= size; j++) {
			printf("%d ",node[i].left_arr[j]);
		}
		printf("\n");
	}

}

int checkArgCount(int argc){
	if(argc < 2)	// if the argument count is less
		{
			//PrintError(NO_FILE_NAME);//print error
			return FALSE;//return false to main
		}
			return TRUE;
}

void printNodeArray(Node* arr,int size){
	int i;

	for(i = 1; i <= size;i++){
		printf("Node: %d , w: %f , h: %f\n",i,arr[i].width,arr[i].height);
	}
}

void printSeqPairs(int* f_pair,int* sec_pair,int size){
	int i;
	for (i = 1; i <= size; i++) {
		printf("%d ",f_pair[i]);
	}
	printf("\n");
	for (i = 1; i <= size; i++) {
		printf("%d ",sec_pair[i]);
	}

}

int getSize(char *filename){
	int size = 0;

	FILE *fptr = getFilePtr(filename);
	fscanf(fptr,"%d",&size);

	fclose(fptr);
	return size;

}


FILE* getFilePtr(char filename[]){
	//returns the file pointer of the file

	//local variable declarations
	FILE *Fptr;

	Fptr = fopen(filename,"r");//open the file
	if(Fptr == NULL)
	{
		return NULL; //if the pointer is null return false
	}
	return Fptr;//if everything is ok return true

} /*getFilePtr function*/

Node* loadFile(char *filename, int num_nodes,int* first_pair,int* second_pair){
	int i;

	FILE *fptr = getFilePtr(filename);

	Node *node_arr = (Node*)malloc(sizeof(Node)*((num_nodes)+1));

	fseek(fptr,2,SEEK_CUR);

	for(i = 1; i <= num_nodes;i++){
		fscanf(fptr,"%d",&node_arr[i].thisnode);
		fscanf(fptr,"%f",&node_arr[i].width);
		fscanf(fptr,"%f",&node_arr[i].height);
	}

	for(i = 1;i <= num_nodes;i++){
		 fscanf(fptr,"%d",&first_pair[i]);
	}

	for(i = 1;i <= num_nodes;i++){
		fscanf(fptr,"%d",&second_pair[i]);
	}

	return node_arr;
}





