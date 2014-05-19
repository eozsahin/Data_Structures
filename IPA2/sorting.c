/*


 * sorting.c
 *
 *  Created on: Sep 24, 2013
 *      Author: emreozsahin
 */
#include "sorting.h"


int CheckArgCount(int argc){
	if(argc < 3)	// if the argument count is less
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

Node *CreateNode(long val){
	//create a node with the specified value
	Node *new = (Node*)malloc(sizeof(Node));
	new -> value = val; //set value
	new -> next = NULL;//set next

	return new;
}

void switchNodes(Node *prev_higher, Node *higher, Node * small){//switches the higher with smaller
	if(small !=  NULL && higher != NULL && prev_higher != NULL){//if non are invalid
		//do the exchange
		Node * temp = small;
		Node * temp_nxt = small->next;
		prev_higher -> next = temp;
		small -> next  = higher;
		higher -> next = temp_nxt;
	}
	else{printf("switch not occured\n");}

}

Node *NodeInsert(Node *node, long int val){
	//Insert node at the front
	Node *new = CreateNode(val);
	new -> next = node;


	return new;
}

Node *NodeInsert2(Node *node, long int val){
	//Insert node at the back(not used though)
	Node *new = CreateNode(val);
	if(node != NULL){
		while(node ->next != NULL){
			node = node -> next;
		}//find the last element and init
		node->next = new;
	}
	else{
		node = new;
	}

	return node;
}

Node* reverseList(Node* head)
{
	// this function reverses the order of the list

	//local variable declarations
	Node* cursor = NULL;
	Node* nxt = NULL;
	if(head->next == NULL)
	{
		return head;
	}
	else
	{
		while (head)
		{
			// do the reverse
			nxt = head->next;
			head->next = cursor;
			cursor = head;
			head = nxt;
		}
	}
    return cursor;
}

void ListPrint(Node *start_node){
	// this function prints the elements in the list
	while(start_node != NULL){
		printf("%ld\n",start_node->value);
		start_node = start_node -> next;
	}
}


Node *Load_File(char *Filename){
	//using the file pointer, this function allocates memory for array and pushes
	//data into an array and returns it

	//local variable declarations
	long int i;
	FILE* fptr;
	Node *node = NULL;

	fptr = getFilePtr(Filename); //get the file pointer
	if(fptr == NULL) //check
	{
		return FALSE;
	}

	while(!feof(fptr))
	{ //pushes the data into list

		 fscanf(fptr,"%ld",&i);
		 //node = NodeInsert(node,i);
		 node = NodeInsert(node,i);

	};

	fclose(fptr); //close the file
	return node->next; //update array

} /*Load_File function*/

int Save_File(char *Filename ,Node *list){
	//Save_File function writes the data into a specified output file

	//local variable declarations

	FILE* Fptr;

	Fptr = fopen(Filename,"w+");//open file to overwrite

	if(Fptr == NULL) //if fptr is accessed
	{
		return FALSE;
	}

	while(list != NULL) //print the data into the file
	{
		fprintf(Fptr,"%ld\n",list->value);
		list = list -> next;
	}
	fclose(Fptr);

	return TRUE; //return 1


} /*Save_File function*/

void Shell_Sort(Node *list){
	
	//local variable declarations
	int h = 1;
	int l;
	int k;
	int mod;
	int iter = 0;
	int cnt = 0;
	int res = 0;
	int size;

	//printf("in shell sort\n");
	Node *copy_list = list;

	while(copy_list !=NULL){
		copy_list = copy_list->next;
		cnt++;
	}//get the size of the list
	//printf("cnt: %d\n",cnt);
	size = cnt;

	while(h < size){ //obtain the sequence
		h = h*2+1;
		iter++;//get the size
	}
	res = h;
	//printf("iter: %d\n",iter);


	//printf("in while loop\n");

	while(iter > 0){ //rewind the sequence
		res = (res-1)/2;//define sub array
		list = reverseList(list);
		Node *sub_n = (Node*) malloc(sizeof(Node)*size*iter);//alloc memory

		//printf("filling the list\n");

		 k = 0;
		while(list != NULL && k < size){ // fill the nodes
			mod = k % res;

			//printf("mod: %d , res: %d\n", mod,res);
			//printf("list value: %ld\n",list->value);
			long int node_val = list->value;

			sub_n[mod].next = NodeInsert(sub_n[mod].next,node_val);

			list = list -> next;

			k++;
		}




		int iterator2 = 0;
		//printf("printing nodes\n");
		//printf("\n\n!!!!before sorted!!!!\n\n");
		for(iterator2 = 0; iterator2 < res ;iterator2++)//reverse the list because of insert at front
		{
			sub_n[iterator2].next = reverseList(sub_n[iterator2].next);
			//ListPrint(sub_n[iterator2].next);
			//printf("+\n");
		}



		//printf("sorting the sub nodes\n");
		//sorting takes place
		Node *ptr = NULL;
		Node *p = NULL;
		int z;
		int m =0;
		for(l = 0;l < res ; l++){//for every gap
			z = size-res;
			   for(m = 0; m < z; z -=res){ //while decreasing the size

						//do bubble sort
					   for( ptr = &sub_n[l]; ptr->next != NULL; ptr = ptr->next ) {
							 p = ptr->next;
							if( p->next !=NULL && ( p->value  >  p->next->value  )) {
								switchNodes(ptr,p,p->next);

								z = 2*res;
							}
					   }

			   }
		}

		//forming the original after k sorting

		int modulus;
		int sub_size = 0;
		while( sub_size < size){
			//printf("sub_size: %d", sub_size);
			if(res > 0){
			modulus = sub_size % res;
			}
			else
			{
				modulus = 0;
			}
			long int sub_n_val = (sub_n[modulus].next)->value;
			//printf("sub_n_val: %ld, mod2 %d\n",sub_n_val,modulus);
			list = NodeInsert(list,sub_n_val);
			sub_n[modulus].next = (sub_n[modulus].next)->next;


			sub_size++;
		}

	  iter--;//decrease counter

	}
	//printf("\n\n**** final list ******\n\n");

	list = reverseList(list);
	Save_File("output.txt",list); //save the output into a file

}
