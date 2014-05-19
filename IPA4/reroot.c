/*
 * packing.c

 *
 *  Created on: Oct 18, 2013
 *      Author: emreozsahin
 */
#include "reroot.h"


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
	//printf("\n");
	//printf("ok");
	char com = 'L';
	char dir = 'L';
	float w = arr[base].posx;
	float h = arr[base].posy;
	//printf("w beg: %f, h beg: %f\n",w,h);


	rerootTree(arr,base,com,dir,arr[base].cutline,arr[arr[base].lcnode].posx,arr[arr[base].rcnode].posx,arr[arr[base].lcnode].posy,arr[arr[base].rcnode].posy,&w,&h,arr[base].lcnode,arr[base].rcnode);

	printf("\n");
	//printCordData(arr,num_nodes);

	printf("Best width: %le\n",w);
	printf("Best height: %le\n\n",h);


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

void printCordData(Block* arr, int num_nodes){
	int i;
	for(i = 1; i <= num_nodes;i++){
		printf("arr[%d].posx : %f , arr[%d].posy : %f\n",i,arr[i].posx,i,arr[i].posy);
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


void rerootTree(Block* arr,int base,char coming,char direction,char b_mode,float l_posx,float r_posx,float l_posy,float r_posy,float *fin_w,float *fin_h,int l_sibling,int r_sibling){
	//if base case return
	if(arr[base].lcnode ==  -1 && arr[base].rcnode == -1){
			return;
	}

	//printf("base %d     >, l_child(%.f,%.f)  r_child(%.f,%.f)\n",base,l_posx,l_posy,r_posx,r_posy);
	//printf("and after..\n");
	float tmpx;
	float tmpy;
	float main_x = 0;
	float main_y = 0;
	int curr_rchild = arr[base].rcnode;//r_sibling;
	int curr_lchild = arr[base].lcnode;
	//printf("r_sib: %d, l_sib %d\n",r_sibling,l_sibling);
	//l_sibling = arr[base].lcnode;
	//r_sibling = arr[base].rcnode;
	//printf("curr_rchild %d, curr_lchild %d\n",curr_rchild,curr_lchild);

	char mode = arr[base].cutline;
	//int parnode = arr[base].parnode;


	//printf("dir: %c, com: %c\n",direction,coming);

	if(direction == 'L' && coming =='L'){
		//intermediate steps

		//printf("int step: r_pos(%.f,%.f), r_child(%.f,%.f)\n",r_posx,r_posy,arr[curr_rchild].posx,arr[curr_rchild].posy);
		if(b_mode == 'H'){
			if(r_posx < arr[curr_rchild].posx){
				tmpx = arr[curr_rchild].posx;
			}
			else{
				tmpx = r_posx;
			}

			tmpy = r_posy + arr[curr_rchild].posy;
		}

		else if(b_mode == 'V'){
			if(r_posy> arr[curr_rchild].posy){
				tmpy = r_posy;
			}
			else {
				tmpy = arr[curr_rchild].posy;
			}

			tmpx = r_posx + arr[curr_rchild].posx;
		}

		//node calc
		//printf("base %d mode: %c, dir: %c>, l_child(%.f,%.f)  r_child(%.f,%.f)\n",base,mode,direction,arr[curr_lchild].posx,arr[curr_lchild].posy,tmpx,tmpy);
		if(mode == 'H'){
			if(arr[curr_lchild].posx > tmpx){
				main_x = arr[curr_lchild].posx;
			}
			else{
				main_x = tmpx;
			}
			main_y = tmpy + arr[curr_lchild].posy;
		}
		else if(mode == 'V'){
			if(arr[curr_lchild].posy > tmpy){
				main_y =  arr[curr_lchild].posy;
			}
			else{
				main_y = tmpy;
			}

			main_x = arr[curr_lchild].posx + tmpx;
		}


		r_posx = tmpx;
		r_posy = tmpy;



		if(main_x*main_y < (*fin_w)*(*fin_h)){
			(*fin_w) = main_x;
			(*fin_h) = main_y;
		}
		else if(main_x*main_y == (*fin_w)*(*fin_h) && main_x < (*fin_w)){
			(*fin_w) = main_x;
			(*fin_h) = main_y;
		}





	}else if(direction == 'R' && coming == 'R'){
		//printf("int step: l_pos(%.f,%.f), lchild(%.f,%.f)\n",l_posx,l_posy,arr[curr_lchild].posx,arr[curr_lchild].posy);

		if(b_mode == 'H' ){
			if(arr[curr_lchild].posx > l_posx){
				tmpx = arr[curr_lchild].posx;
			}
			else{
				tmpx = l_posx;
			}
			tmpy = arr[curr_lchild].posy + l_posy;
		} else if(b_mode == 'V'){
			if(arr[curr_lchild].posy > l_posy){
				tmpy = arr[curr_lchild].posy;
			}
			else{
				tmpy = l_posy;
			}
			tmpx = arr[curr_lchild].posx + l_posx;
		}

		//printf("base %d mode: %c, dir: %c>, l_child(%.f,%.f)  r_child(%.f,%.f)\n",base,mode,direction,arr[curr_rchild].posx,arr[curr_rchild].posy,tmpx,tmpy);

		if(mode == 'H'){
			if(arr[curr_rchild].posx > tmpx){
				main_x = arr[curr_rchild].posx;
			}else{
				main_x = tmpx;
			}

			main_y = tmpy + arr[curr_rchild].posy;
		}
		else if(mode == 'V'){
			if(arr[curr_rchild].posy > tmpy){
				main_y = arr[curr_rchild].posy;
			}
			else{
				main_y = tmpy;
			}
			main_x =  tmpx + arr[curr_rchild].posx;
		}


		l_posx = tmpx;
		l_posy = tmpy;




		if(main_x*main_y < (*fin_w)*(*fin_h)){
			(*fin_w) = main_x;
			(*fin_h) = main_y;
		}
		else if(main_x*main_y == (*fin_w)*(*fin_h) && main_x < (*fin_w)){
			(*fin_w) = main_x;
			(*fin_h) = main_y;
		}


	}
	else if(direction == 'L' && coming == 'R'){
		//printf("int step: r_pos(%.f,%.f), r_child(%.f,%.f)\n",r_posx,r_posy,arr[curr_rchild].posx,arr[curr_rchild].posy);
		if(b_mode == 'H'){
			if(l_posx < arr[curr_rchild].posx){
				tmpx = arr[curr_rchild].posx;
			}
			else{
				tmpx = l_posx;
			}

			tmpy = l_posy + arr[curr_rchild].posy;
		}

		else if(b_mode == 'V'){
			if(l_posy> arr[curr_rchild].posy){
				tmpy = l_posy;
			}
			else {
				tmpy = arr[curr_rchild].posy;
			}

			tmpx = l_posx + arr[curr_rchild].posx;
		}

		//node calc
		//printf("base %d mode: %c, dir: %c>, l_child(%.f,%.f)  r_child(%.f,%.f)\n",base,mode,direction,arr[curr_lchild].posx,arr[curr_lchild].posy,tmpx,tmpy);
		if(mode == 'H'){
			if(arr[curr_lchild].posx > tmpx){
				main_x = arr[curr_lchild].posx;
			}
			else{
				main_x = tmpx;
			}
			main_y = tmpy + arr[curr_lchild].posy;
		}
		else if(mode == 'V'){
			if(arr[curr_lchild].posy > tmpy){
				main_y =  arr[curr_lchild].posy;
			}
			else{
				main_y = tmpy;
			}

			main_x = arr[curr_lchild].posx + tmpx;
		}


		r_posx = tmpx;
		r_posy = tmpy;



		if(main_x*main_y < (*fin_w)*(*fin_h)){
			(*fin_w) = main_x;
			(*fin_h) = main_y;
		}
		else if(main_x*main_y == (*fin_w)*(*fin_h) && main_x < (*fin_w)){
			(*fin_w) = main_x;
			(*fin_h) = main_y;
		}



	}else if(direction == 'R' && coming == 'L'){
		//printf("int step: l_pos(%.f,%.f), lchild(%.f,%.f)\n",l_posx,l_posy,arr[curr_lchild].posx,arr[curr_lchild].posy);

		if(b_mode == 'H' ){
			if(arr[curr_lchild].posx > r_posx){
				tmpx = arr[curr_lchild].posx;
			}
			else{
				tmpx = r_posx;
			}
			tmpy = arr[curr_lchild].posy + r_posy;
		} else if(b_mode == 'V'){
			if(arr[curr_lchild].posy > r_posy){
				tmpy = arr[curr_lchild].posy;
			}
			else{
				tmpy = r_posy;
			}
			tmpx = arr[curr_lchild].posx + r_posx;
		}

		//printf("base %d mode: %c, dir: %c>, l_child(%.f,%.f)  r_child(%.f,%.f)\n",base,mode,direction,arr[curr_rchild].posx,arr[curr_rchild].posy,tmpx,tmpy);

		if(mode == 'H'){
			if(arr[curr_rchild].posx > tmpx){
				main_x = arr[curr_rchild].posx;
			}else{
				main_x = tmpx;
			}

			main_y = tmpy + arr[curr_rchild].posy;
		}
		else if(mode == 'V'){
			if(arr[curr_rchild].posy > tmpy){
				main_y = arr[curr_rchild].posy;
			}
			else{
				main_y = tmpy;
			}
			main_x =  tmpx + arr[curr_rchild].posx;
		}


		l_posx = tmpx;
		l_posy = tmpy;




		if(main_x*main_y < (*fin_w)*(*fin_h)){
			(*fin_w) = main_x;
			(*fin_h) = main_y;
		}
		else if(main_x*main_y == (*fin_w)*(*fin_h) && main_x < (*fin_w)){
			(*fin_w) = main_x;
			(*fin_h) = main_y;
		}


	}

//
//	printf("final  lposx %.f, l_posy %.f , rposx %.f, rposy %.f\n",base,l_posx,l_posy,r_posx,r_posy);
//	printf("tmpx %.f,  tmpy %.f\n",tmpx,tmpy);
//	printf("main_x %.f main_y %.f \n",main_x,main_y);
//	printf("w: %.f , h: %.f\n",(*fin_w),(*fin_h));
//	printf("-------\n");

	int l = arr[curr_rchild].lcnode;
	int r = arr[curr_rchild].rcnode;
	if(arr[r].cutline != 'H'  && arr[r].cutline != 'V'){
		direction  = 'L';
	}else if(arr[l].cutline != 'H' && arr[l].cutline != 'V'){
		direction = 'R';
	}



	//printf("going left\n");
	rerootTree(arr,arr[base].lcnode,'L',direction,mode,l_posx,r_posx,l_posy,r_posy,fin_w,fin_h,l_sibling,r_sibling);
	//printf("going right\n");
	rerootTree(arr,arr[base].rcnode,'R',direction,mode,l_posx,r_posx,l_posy,r_posy,fin_w,fin_h,l_sibling,r_sibling);

}




