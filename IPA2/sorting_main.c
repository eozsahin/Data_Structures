/*
 * sorting_main.c
 *
 *  Created on: Oct 9, 2013
 *      Author: emreozsahin
 */

#include "sorting.h"


int main(int argc, char *argv[]){

	//local variable declarations
	clock_t stime1;
	clock_t stime2;
	clock_t ftime1;
	clock_t ftime2;
	double fstime;
	double fulltime;

	ftime1 = clock();
	//load file
	Node *node_data = Load_File(argv[1]);

	ftime2 = clock();
	stime1 = clock();
	//sort the linked list
	Shell_Sort(node_data);
	stime2 = clock();

	// print the time
	fstime = ((double)(stime2 - stime1)/CLOCKS_PER_SEC);
	fulltime = ((double)(ftime2 - ftime1)/CLOCKS_PER_SEC);

	printf("\nI/O time: %le\n",fulltime);
	printf("Sorting time: %le\n",fstime);

	return 0;
}
