/*
 * sorting.c


 *
 *  Created on: Sep 12, 2013
 *      Author: emreozsahin
 */

#include "sorting.h"


void freeMemory(long *Array){ //this function frees the allocated memory
	free(Array);
} /* freeMemory function*/


int CheckArgCount(int argc){
	if(argc < 6)	// if the argument count is less
	{
		PrintError(NO_FILE_NAME);//print error
		return FALSE;//return false to main
	}
		return TRUE;
}

int pwr(int a , int b)
{
	//power function, a is the base and b is the power

	//local variable declarations
	int f = 1;
	f = f*a;
	if(b)	//multiplies a b times itself
	{
		while(b > 1)
		{
			f = f*a;//update f every cycle
			b--;
		}
	}
	else{
		f = 1;
	}
	return f; //returns the answer

} /* pwr function*/


int getHeightSeq2(int size_array){
	//returns the height of seq2
	float n = 0.0;
	int x = pwr(3.0,n);

	while((size_array / x) > 1 )//check the upper limit of the triangle
		{
			x = pwr(3.0,n); //increases the height
			n++;
		}

	return n; //returns the height
} /*getHeightSeq2 function*/

void PrintArray(long *Array, long size){
	//this function is implemented to debug by printing the array

	//local variable declarations
	int i;

	for (i = 0; i<size ;i++){
		printf("%ld ",Array[i]); //prints all the array elements
	}
	printf("\n");
} /* PrintArray function*/

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

int getSize(FILE* fptr){
	//gets the size of t

	//local variable declarations
	int size;

		fscanf(fptr, "%d", &size);//scans the size

	return size;//returns the size

} /*getSize function*/



long *Load_File(char *Filename, int *size){
	//using the file pointer, this function allocates memory for array and pushes
	//data into an array and returns it

	//local variable declarations
	int i = 0;
	long new_size;
	FILE* fptr;

	fptr = getFilePtr(Filename); //get the file pointer
	if(fptr == NULL) //check
	{
		return FALSE;
	}
	new_size = getSize(fptr); //set the new size

	long *Array = (long*)malloc(sizeof(long)*(new_size)); //allocate memory for array

	for(i = 0; i<new_size;i++){ //pushes the data into array
		 fscanf(fptr,"%ld",&Array[i]);
	}

	*size = new_size; //update size
	fclose(fptr); //close the file
	return Array; //update array

} /*Load_File function*/

int Save_File(char *Filename ,long *Array, int size){
	//Save_File function writes the data into a specified output file

	//local variable declarations
	FILE* Fptr;
	int i;

	Fptr = fopen(Filename,"w+");//open file to overwrite

	if(Fptr == NULL) //if fptr is accessed
	{
		return FALSE;
	}

	for(i=0;i< size; i++) //print the data into the file
	{
		fprintf(Fptr,"%ld\n",Array[i]);
	}
	fclose(Fptr);

	return TRUE; //return 1

} /*Save_File function*/


void PrintError(int error){
	//this file includes the error messages

	//switch case structure for errors
	switch(error){
		case NO_FILE_NAME:
			printf("Check arguments before begin!");
			break;
		case FN_NOT_FOUND:
			printf("Command not found or given agruments!");
			break;
	}
} /* Print_Error function*/



int Print_Seq_2(char *Filename, int Size){
	// seq2 	1
	// 		  2   3
	//   	4   6   9
	//    8   12  18  27
	// 16   24   36  54  81
	// Print_Seq_2 generates the the sequence above and prints into a file

	//local variable declarations
	FILE* fp;
	long int h = 0;
	long int size_seq;
	float p = 0;
	float q = 0;
	int res = 0;
	int p_org;

	fp = fopen(Filename,"w+"); // open file
	h = getHeightSeq2(Size); // get the height of the tree
	size_seq = h*(h+1)/2; // get the number of elements

	fprintf(fp,"%ld\n",size_seq); //print number of elements
	fprintf(fp,"1\n"); // start the sequence

	q = 0; //sequence variable 2^p and 3^a
	p = 1;
	p_org = p;

	while(size_seq - 1 > 0){//while there are elements
		res = pwr(2.0,p)*pwr(3.0,q); //calculate the element
		fprintf(fp,"%d\n",res);//print the element into the file

		p--;//generate sequnce
		q++;
		size_seq--;

		if( p < 0) //if p = 0 increase the original p and continue
		{
			h--;
			q = 0;
			p = p_org + 1;
			p_org++;
		}
	}
	fclose(fp);

	return TRUE; //return from function
} /*Print_Seq_2 function*/

int Print_Seq_1(char *filename, int Size){
	//seq1 h(i) = 2*h(i-1)+1
	// 1, 3, 7, 15, 31...
	//Print_Seq_1 function generates the sequence above for a given file and outputs it

	FILE* fptr;
	fptr = fopen(filename,"w+");//open file to overwrite

	//variable declarations
    int i = 0;
    int counter = 0;

    //printf("size: %d\n",Size);
    for (i = 0; i < 2;i++) // loop 2 times, first get the size and second display the sequence
    {
    	int h = 1;
		for(counter = 0; h < Size; counter++ ) {
			if(i) // in second loop print the sequence
				fprintf(fptr,"%d\n",h);

			h = (h*2)+1; //update statement

		}
		if(!i) //in first loop print the size
		{
			fprintf(fptr,"%d\n",counter);
		}
    }

    fclose(fptr);

	return TRUE;
} /*Print_Seq_1 function*/

// Sorting algorithm functions

void Shell_Insertion_Sort_Seq1(long *Array, int size, double *N_Comp, double *N_Move){
	//this funtion implements shell insertion sort using seq1

	//local variable declarations
	int h = 1;
	int j = 0;
	int i;
	int temp;
	int iter = 0;
	int res;

	while(h < size){
			h = h*2+1;
			iter++;
		} //obtain the sequence
		res = h;
	while(iter > 0)	{ //rewind the sequence
		res = (res-1)/2;
		for(i = res; i < size; i++)//for every size
		{
			(*N_Move)++;
			temp = Array[i]; //store the element in temp
			j = i;

			while(j >= res && Array[j-res] > temp){ // compare with other elements and insert
				Array[j] = Array[j-res];
				j -= res;//shift element
				(*N_Move)++;
				(*N_Comp)++;

			}
			Array[j] = temp;//insert element
			(*N_Move)++;
		}
		iter--;//decrease the counter
	}

}

void Shell_Bubble_Sort_Seq1(long *Array, int size, double *N_Comp, double *N_Move){
	//this function uses shell bubble sort on a given array using sequence 1

	//local variable declarations
	int h = 1;
	int j = 0;
	int i;
	int temp;
	int iter = 0;
	int res;

	while(h < size){ //obtain the sequence
		h = h*2+1;
		iter++;
	}
	res = h;

	while(iter > 0){ //rewind the sequence
		res = (res-1)/2;//define sub array
		for(i = 0; i < size; i++)//for every element
		{
			j = i;

			while((j+res) < size){ //if it is in the limits
				(*N_Comp)++;


				if(Array[j] > Array[j+res])//if the first subarray has a higher value
				{
					temp = Array[j+res];//swap
					Array[j+res] = Array[j];
					Array[j] = temp;

					(*N_Move) = (*N_Move) + 3;
				}
				j+=res;//move to the other subarray

			}

		}
	  iter--;//decrease counter
	}



} /*Shell_Bubble_sort_Seq1*/

void Shell_Insertion_Sort_Seq2(long *Array, int size, double *N_Comp, double *N_Move){
	//this function uses shell insertion sort to sort a given array using sequence 2

	//local variable declaration
	int j = 0;
	int i;
	int temp;
	//tree variables
	int iter = 0;
	int h = 0;
	float p = 0.0;
	float q = 0.0;
	int res = 0;

	h = getHeightSeq2(size); //get height of the tree
	iter = h*(h+1)/2;//get number of elements in a sequence

	p = 0.0;
	q = h - 1;
	while(iter > 0){
		res = pwr(2.0,p)*pwr(3.0,q);//obtain sub array

		for(i = res; i < size; i++)//for every element
			{
				(*N_Move)++;
				temp = Array[i];
				j = i;
				while(j >= res && Array[j-res] > temp){//look to insert the item into corresponding sub array
					Array[j] = Array[j-res];
					j -= res;
					(*N_Move)++;
					(*N_Comp)++;
				}
			Array[j] = temp;
			(*N_Move)++;
		//getting the tree sequence
		}
		p++;
		q--;
		iter--;

		if( q < 0)
		{
			h--;
			q = h - 1;
			p = 0;
		}
	}

}
void Shell_Bubble_Sort_Seq2(long *Array, int size, double *N_Comp, double *N_Move){
	//this function uses shell insertion sort to sort a given array using sequence 2

	//local variable declarations
	int j = 0;
	int i;
	int temp;
	//tree var
	int iter = 0;
	int h = 0;
	float p = 0.0;
	float q = 0.0;
	int res = 0;

	h = getHeightSeq2(size);
	iter = h*(h+1)/2;

	p = 0.0;
	q = h - 1;
	while(iter > 0){
		res = pwr(2.0,p)*pwr(3.0,q);//obtain the sequence gap

		//sorting for normal insertion
		for(i = 0; i < res; i++)//for every element
			{
				j = i;
				while((j+res) < size ){//search through sub arrays
					(*N_Comp)++;
					if(Array[j] > Array[j+res])//if not in order
					{
						temp = Array[j+res];//swap
						Array[j+res] = Array[j];
						Array[j] = temp;

						(*N_Move) = (*N_Move) + 3;
					}
					j+=res;//update j
				}
			}

		//do calculations for next element in sequence
		p++;
		q--;
		iter--;

		if( q < 0)
		{
			h--;
			q = h - 1;
			p = 0;
		}
	}
}


void PrintInfo(double moves, double comps, double ftime, double fstime){
	//PrintInfo prints the required data for the output on to terminal

	//required data for output and print them
	printf("Number of comparisons: %le \n", comps);
	printf("Number of moves: %le \n", moves);
	printf("I/O time %lf \n",ftime);
	printf("Sorting time: %lf \n",fstime);

}


void PrintDebugSt(int key){
	//Print debug statements

	//switch case structure for print debug function
	switch (key) {
		case FILE_LOADED:
			printf("*** File loaded completely..\n");
			break;
		case CONSTRUCTING_ARRAY:
			printf("***Array is constructed...\n");
			break;
		case SIZE_OBTAINED:
			printf("***File size obtained...\n");
			break;
		case PRINTING_ARRAY:
			printf("*** File is being printed...\n");
			break;
		case SHELL_B_1:
			printf("\nShell Bubble Sort Seq 1\n");
			break;
		case SHELL_B_2:
			printf("\nShell Bubble Sort Seq 2\n");
			break;
		case SHELL_I_1:
			printf("\nShell Insertion Sort Seq 1\n");
			break;
		case SHELL_I_2:
			printf("\nShell Insertion Sort Seq 2\n");
			break;
	}
}


void testOutput(){
	//testOutput function is used for debugging. It checks the output file if it is sorted or not

	//local variable declarations
	FILE* fptr;
	fptr = fopen("output.txt","r");//open file to read
	long int test1;
	long int test2;
	int counter = 0;
	int s = 0;

	while(!feof(fptr)){//while not end of the file
		counter = counter + 2;

		fscanf(fptr,"%ld",&test1);  //grab consecutive numbers and compare
		fscanf(fptr,"%ld",&test2);

		if(test1 > test2)
		{
			printf("cnt: %d \n*********ARRAY NOT SORTED!!!!**********\n",counter); //print debug statement
			s = 1;
			break;
		}
	}
	if(!s)
	{
		printf("\n*********** ARRAY SORTED PROPERLY****************\n"); //print debug statement
	}

	fclose(fptr); //close the file

}





