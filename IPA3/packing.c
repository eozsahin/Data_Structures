/*
 * packing.c

 *
 *  Created on: Oct 18, 2013
 *      Author: emreozsahin
 */
#include "packing.h"


int main(int argc, char *argv[]){

	int num_nodes;
	int num_blocks;
	int base;

	int chk = checkArgCount(argc);


	if(!chk){
		return EXIT_FAILURE;
	}

	Block *arr = loadFile(argv[1],&num_blocks,&num_nodes);
	base = findBase(arr,num_nodes);

	clock_t t1 = clock();
	POS *res = travelTree_dim(arr,base);
	res = 0;
	clock_t t2 = clock();
	printDim(arr,base);
	printf("\n");


	arr[base].posx = 0;
	arr[base].posy = 0;

	clock_t d1 = clock();
	travelTree_cor1(arr,base);
	clock_t d2 = clock();

	double time1 = (double)((t2-t1)/(CLOCKS_PER_SEC));
	double time2 = (double)((d2-d1)/(CLOCKS_PER_SEC));

	printCor(arr,num_blocks);
	printf("\n");
	printClock((double)time1+time2);

	saveFile(arr,num_blocks,argv[2]);

	free(res);
	free(arr);
	return 0;

}/* MAIN FUNCTION */





int checkArgCount(int argc){
	if(argc < 2)	// if the argument count is less
		{
			//PrintError(NO_FILE_NAME);//print error
			return FALSE;//return false to main
		}
			return TRUE;
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

void printDim(Block* arr,int base){
	printf("Width: %le\nHeight %le\n",arr[base].posx,arr[base].posy);
}
void printCor(Block* arr,int num){
	printf("X-coordinate: %le\nY-coordinate: %le\n",arr[num].posx,arr[num].posy);
}
void printClock(double n){
	printf("Elapsed Time: %le\n",n);
}

Block* loadFile(char *filename, int* num_blocks, int* num_nodes){


	int j = 0;
	int k = 0;

	FILE *fptr = getFilePtr(filename);

	fscanf(fptr,"%d",num_blocks);
	fscanf(fptr,"%d",num_nodes);

	Block *node_arr = (Block*)malloc(sizeof(Block)*((*num_nodes)+1));

	for(k = 1; k <= (*num_blocks);k++){
		fscanf(fptr,"%d",&node_arr[k].thisnode);
		fscanf(fptr,"%d",&node_arr[k].parnode);
		fscanf(fptr,"%d",&node_arr[k].lcnode);
		fscanf(fptr,"%d",&node_arr[k].rcnode);
		fseek(fptr,3,SEEK_CUR);
		fscanf(fptr,"%f",&node_arr[k].width);
		fscanf(fptr,"%f",&node_arr[k].height);
	}
	//test statement



	for(j = k; j <=(*num_nodes);j++){
		fscanf(fptr,"%d",&node_arr[j].thisnode);
		fscanf(fptr,"%d",&node_arr[j].parnode);
		fscanf(fptr,"%d",&node_arr[j].lcnode);
		fscanf(fptr,"%d",&node_arr[j].rcnode);
		fscanf(fptr,"%c",&node_arr[j].cutline);
		fscanf(fptr,"%c",&node_arr[j].cutline);
		fseek(fptr,5,SEEK_CUR);
	}

	fclose(fptr);
	return node_arr;

}

void printArray(Block *array, int num_nodes){
	int k = 1;

	for(k = 1; k <= num_nodes;k++){
		printf("node_array[%d].thisnode: %d\n",k, array[k].thisnode);
		printf("node_array[%d].parnode: %d\n",k, array[k].parnode);
		printf("node_array[%d].lcnode: %d\n",k, array[k].lcnode);
		printf("node_array[%d].rcnode: %d\n",k, array[k].rcnode);
		printf("node_array[%d].cutline: %c\n",k,array[k].cutline);
		printf("node_array[%d].width: %f\n",k, array[k].width);
		printf("node_array[%d].height: %f\n",k, array[k].height);
		printf("node_array[%d].posx: %f\n",k, array[k].posx);
		printf("node_array[%d].posy: %f\n",k, array[k].posy);

	}



}

void saveFile(Block * arr,int num_blocks,char* file){
	int i;

	FILE* fptr = fopen(file,"w");

	if(fptr != NULL){
		fprintf(fptr,"%d\n",num_blocks);
		for(i = 1;i<=num_blocks;i++)
		{
			fprintf(fptr,"%d %le %le %le %le\n",arr[i].thisnode,arr[i].width,arr[i].height,arr[i].posx,arr[i].posy);
		}
	}
	else{printf("file pointer is null!");}
	fclose(fptr);
}

int findBase(Block * array, int num_nodes){

	while(num_nodes > 0){
		if(array[num_nodes].parnode == -1){
			return num_nodes;
		}

		num_nodes--;
	}

	return -1;
}


POS* travelTree_dim(Block* arr,int base){
	POS*ret = (POS*)malloc(sizeof(POS));
	if(arr[base].lcnode == -1 && arr[base].rcnode == -1)
	{

		ret->posx = arr[base].width;
		ret->posy = arr[base].height;
		arr[base].posx = ret->posx;
		arr[base].posy = ret->posy;
		return ret ;

	}
	else{

	POS* r = travelTree_dim(arr,arr[base].lcnode);
	POS* l = travelTree_dim(arr,arr[base].rcnode);


		char mode = arr[base].cutline;
			if(mode == 'H'){
				ret->posy = l->posy + r->posy;
				if(r->posx > l->posx){
				ret->posx = r->posx;
				}
				else{
					ret->posx = l->posx;
				}

			}
			else if(mode == 'V')
			{
				ret->posx = l->posx + r->posx;
				if(r->posy >l->posy)
				{
					ret->posy = r->posy;
				}
				else
				{
					ret->posy = l->posy;
				}

			}
			arr[base].posx = ret->posx;
			arr[base].posy = ret->posy;
			return ret;
	}
}



void travelTree_cor1(Block* arr,int base){
	if(arr[base].lcnode == -1 && arr[base].rcnode == -1)
	{
		return;
	}
	char mode = arr[base].cutline;
	int lchild = arr[base].lcnode;
	int rchild = arr[base].rcnode;

	if(mode =='H')
		{
		arr[lchild].posx = arr[base].posx;
		arr[lchild].posy =  arr[base].posy + arr[rchild].posy;
		arr[rchild].posx = arr[base].posx;
		arr[rchild].posy = arr[base].posy;
		}
	else if (mode == 'V'){
		arr[rchild].posx = arr[base].posx + arr[lchild].posx;
		arr[rchild].posy = arr[base].posy;
		arr[lchild].posx = arr[base].posx;
		arr[lchild].posy = arr[base].posy;
		}

	 travelTree_cor1(arr,arr[base].lcnode);
	 travelTree_cor1(arr,arr[base].rcnode);


}
