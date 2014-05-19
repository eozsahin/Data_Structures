/*
 * sorting.h
 *
 *  Created on: Sep 12, 2013
 *      Author: emreozsahin
 */

#ifndef SORTING_H_
#define SORTING_H_

//import libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//print error symbols
#define NO_FILE_NAME 0
#define FN_NOT_FOUND 1
//define constants
#define TRUE 1
#define FALSE 0

//print debug definitions
#define FILE_LOADED 11
#define SIZE_OBTAINED 12
#define CONSTRUCTING_ARRAY 13
#define PRINTING_ARRAY 14
#define SHELL_I_1 15
#define SHELL_I_2 16
#define SHELL_B_1 17
#define SHELL_B_2 18


// FUNCTION DECLARATIONS

int CheckArgCount(int argc);

//functions that needed to implemented
long *Load_File(char *Filename, int *Size);
int Save_File(char *Filename, long *Array, int Size);
void Shell_Insertion_Sort_Seq1(long *Array, int Size, double *N_comp, double *N_move);
void Shell_Insertion_Sort_Seq2(long *Array, int Size, double *N_comp, double *N_move);
void Shell_Bubble_Sort_Seq1(long *Array, int Size, double *N_comp, double *N_move);
void Shell_Bubble_Sort_Seq2(long *Array, int Size, double *N_comp, double *N_move);
int Print_Seq_1(char* Filename, int Size);
int Print_Seq_2(char* Filename, int Size);

//own implemented functions
int getHeightSeq2(int sz);
int getSize(FILE* fptr);
FILE* getFilePtr(char filename[]);
int Print_Seq_1(char *Filename, int Size);
int Print_Seq_2(char *Filename, int Size);
void CloseFile(FILE *fptr);
void PrintDebugSt(int key);
void PrintInfo(double moves, double comps, double ftime, double fstime);
void PrintOutput(long *Array, int size);
int pwr(int a, int b);
void freeMemory(long *Array);

//debug functions
void PrintArray(long *Array,long Size);
void PrintError(int error);
void testOutput();



#endif /* SORTING_H_ */
