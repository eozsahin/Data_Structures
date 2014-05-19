/*
 * sorting.main.c
 *
 *  Created on: Sep 12, 2013
 *      Author: emreozsahin
 */
#include "sorting.h"

int main(int argc, char *argv[]){

	//variable declarations
	clock_t time1;
	clock_t time2;
	clock_t stime1;
	clock_t stime2;
	double fstime;
	double ftime;

	time1 = clock();

	int size;
	long *Array;
	double N_Comp = 0;
	double N_Move = 0;

	if(!CheckArgCount(argc)){ //check argc
		return EXIT_FAILURE;
	}

	Array = Load_File(argv[3],&size); // load the file with ptr

	if(!strcmp(argv[1],"1")) //branch if 1st sequence
	{
		if(Print_Seq_1(argv[4],size) == TRUE)
		{
			if(!strcmp(argv[2],"i")) //branch if insertion sort
			{
				//PrintDebugSt(SHELL_I_1);
				stime1 = clock();
				Shell_Insertion_Sort_Seq1(Array,size, &N_Comp, &N_Move);
				stime2 = clock();
			}
			else if(!strcmp(argv[2],"b")) //branch if bubble sort
			{
				//PrintDebugSt(SHELL_B_1);
				stime1 = clock();
				Shell_Bubble_Sort_Seq1(Array, size, &N_Comp, &N_Move);
				stime2 = clock();

			}
			else
			{ PrintError(FN_NOT_FOUND); } //no command
		}

	}

	else if (!strcmp(argv[1],"2")) //brand if the required seq is the second sequence
	{
		if(Print_Seq_2(argv[4],size) == TRUE)
		{
			if(!strcmp(argv[2],"i")){ //branch if inserton sort
				//PrintDebugSt(SHELL_I_2);
				stime1 = clock();
				Shell_Insertion_Sort_Seq2(Array, size, &N_Comp, &N_Move);
				stime2 = clock();

			}
			else if(!strcmp(argv[2],"b")) //branch if bubble sort
			{
				//PrintDebugSt(SHELL_B_2);
				stime1 = clock();
				Shell_Bubble_Sort_Seq2(Array, size, &N_Comp, &N_Move);
				stime2 = clock();
			}
			else
			{ PrintError(FN_NOT_FOUND);}// no command found
		}


	}
	else{ PrintError(FN_NOT_FOUND); } //no command found

	//printing outputs
	time2 = clock();

	ftime = ((double)(time2 - time1)/CLOCKS_PER_SEC); //get the i/o time
	fstime = ((double)(stime2 - stime1)/CLOCKS_PER_SEC); //get sort time

	PrintInfo(N_Move, N_Comp,ftime,fstime); // print these to terminal
	Save_File(argv[5],Array,size);

	freeMemory(Array); //free memory


	return 0;
}

