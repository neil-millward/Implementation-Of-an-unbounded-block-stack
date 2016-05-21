//Author: Neil Millward | P#: P13197943
//Compilation commands: gcc -c blocked_stack_int.c | gcc demo_blocked_stack.c blocked_stack_int.o -o filename

/****************************************************************************************************************************************
The purpose of this program is to dynamically allocate memory to new node containing an items array when an item is pushed.
Initially the empty stack has no nodes allocated at all, as soon as an item is pushed a node containing an array of items (ints)
is created. Once this has filled up then another node (with items array) is allocated and then linked to the first block and so 
on. 

Side note. for a purculiar reason my function indentation differs depending on what IDE I use to open the file. This is frustrating as
I take pride in my code and that includes the presentation. I can assure you I wrote it nice and neat with correct indentation!
*****************************************************************************************************************************************/

#include <stdio.h>//standard input/output library
#include <assert.h>//include  assert as use  assert to condition check
#include <stdlib.h>//standard library
#include "blocked_stack_int.h"//include custom header file containing all the function headers. 

/***************************************************************************************************************************************
As C does not have a data type of boolean and uses type int to express boolean with a 1 and 0 I took it upon myself to typedef a       
boolean by typedefing int as bool and defining both true and false to 1 and 0 respectively. This is not neccessary yet I done so in    
order to add some "syntaxual sugar", as in a real world enviroment not everyone may be aware of the lack of boolean in C.              
Like to think this shows some creativity, albeit simple creativity.                                                                                           *
****************************************************************************************************************************************/ 

typedef int bool;
#define true 1
#define false 0

/**************************************************************************************************************************************
struct node * top; is a pointer to the top of a nodes                                                                                 
int size; overall size of items in nodes used.                                                                                         
int block_size; max amount of elements stored in each individual node                                                                 
**************************************************************************************************************************************/

struct stack_int_implementation 
{
	struct node * top; 
	int size;	
	int block_size; 
};

/***********************************************************************************************************************************                                                                                                                                
int *items; pointer to  items array                                                                                                                                                                                                                                
int top; int that holds top value of node                                                                                                                                                                                                                      
struct node * next; pointer to next node or null                                                                                   
***********************************************************************************************************************************/

struct node 
{
	int *items;  
	int top;	
	struct node * next; 
};

/*************************************************************************************************************************************
Inititalising a new stack, setting the size to 0, the top to null as inititally wont be pointing at anything and the block size      
will be passed into the program (eg 10)(int block_size).                                                                             
                                                                                                                                     
s->top is then set to NULL as inititally the top will not be pointing to anything until a new node is created.                       
                                                                                                                                     
s->size = 0 as this is a new stack and the top is pointing to Null.                                                                  
                                                                                                                                     
s -> block_size = block_size; block size is being passed into the function. this is used to determine                                
the max amount of elements stored in each individual node.  

side note: (stack_int)) is short for stack_int_implementation as is typedeffed in the header file.                                                                          
*************************************************************************************************************************************/

stack_int *  new_blocked_stack_int(int block_size)
{
	stack_int *s = (stack_int*)malloc(sizeof(stack_int));
	s -> top = NULL;
	s -> size = 0;
	s -> block_size = block_size;	
}

/*************************************************************************************************************************************
Function to display if the stack is empty.                                                                                           
                                                                                                                                     
As you can see in the return type, it is of type bool, this is because I have typedeffed int to bool in this case.                   

returns True if the size is equal to 0 if not == 0 then false.                                         
                                                                                                                                     
assert(s != NULL); is a check to see of the stack "s" is not equal to NULL, NULL being that there is not memory being allocated for  
the stack.                                                                                                                           
                                                                                                                                     
If "s" is == NULL then the if statement will not run. If "s" if != to NULL then that means there is a stack allocated in the memory  
and therefore will run the function.                                                                                                 
                                                                                                                                     
if(s->size==0) will check if the size of the stack is == 0, this is because when a stack has elements in it the size is incremented  
by how many elements are in the stack. For instance if you had a stack of 4 elements the size would also be 4. If the stack had no   
elements it would == 0 and therefore be empty.                                                                                       
                                                                                                                                     
The function will the return 1 (True) if the stack is empty and 0 (False) is the stack is not empty.                                 
**************************************************************************************************************************************/

bool stack_int_isempty(stack_int * s)
{
	assert(s != NULL);
	if(s->size==0)

		return 1;
	else
		return 0;	
}

/*************************************************************************************************************************************
Function that returns the size of the stack.

assert(s != NULL); is a check to see if the stack "s" is not equal to NULL, NULL being that there is not memory being allocated for
the stack.

return the size of the stack if s != NUll.
*************************************************************************************************************************************/

int stack_int_size(stack_int * s)
{
	assert(s != NULL);

	return s->size;
	
}

/*************************************************************************************************************************************************
Function that pushes an item onto the top of the items array. 

if statement checks if the top of the stack  is == null(not pointing to a node) OR  if the next block that is being pointed
to (s->top->items[s->top->top]==block_size) both item and top is equal to the block size, if true then create a new node.
struct node * n =(struct node*)malloc(sizeof(struct node)); is creating a new node, and allocating the size of the node by getting the 
structs variables in the implementation.

"n -> items=(int*)malloc(s->block_size * (sizeof(int)));"- means that the items variable in the newly created node is allocated memory 
of the size of block_size. in the demo test programs case (10). Also * (sizeof(int))) is making the block size be compatible with type int 
(typecasting).

Once the new node is created I then update the pointers... "n->next=s->top" makes the newly created node point to the top
of the previous node. 
						
s->top=n updates the original stack top to point to the new node. 

n->top=0; sets the new nodes top to 0, as it is new and contains no elements to point to.

if the if statement clause is false then the element will be pushed onto the current stack this is achieved by "s->top->items[s->top->top] = x;". 
The line of code  passes x onto the items array and then updates the top pointer to equal x. if x was 1 the top would be pointing at index 
1 and the item passed into the array would be one. 

As the top is now x(the value pushed) top needs to be incremented  as if the item array is full top needs to point to the new node and not 
the top element.

s->size++ is incrementaing the size of stack as an element has been pushed onto the items array.
**************************************************************************************************************************************************/

void stack_int_push(stack_int *s, int x)
{	
    assert(s!=NULL);
	if (s -> top == NULL || s->top->items[s->top->top] == s->block_size)
	{
		struct node * n =(struct node*)malloc(sizeof(struct node));
		n -> items=(int*)malloc((s->block_size)* sizeof(int));
		n->next=s->top;
		s->top=n;
		n->top=0;		
	}
	
	{
		s->top->items[s->top->top] = x;
		s->top->top++;	
		s->size++;
	}	
}

/*************************************************************************************************************************************
Function that will pop the top item off the stack. 

Return void as a return is not needed as pop is not ment to be showing the element you are popping, just that you are deleing the
element from memory. Normally a return type of int in this case would often be seen as it is useful to the user to see what
element has been popped.

assert(s != NULL); is a check to see of the stack "s" is not equal to NULL, NULL being that there is not memory being allocated for the stack.
If "s" is == NULL then the if statement will not run. If "s" if != to NULL then that means there is a stack allocated in the memory and
therefore will run the function. 

struct node *del is the creation of a new node that I use later in the function to temporary store what s->top is pointing at.

if (stack_int_isempty(s)) is another check to see if the stack is empty by calling said function. Reason for the check is that if the stack
was empty then there would be nothing to pop, as explained in the print statement withing the if statement when the condition is met(true).

If the condition is not met (false) then s->top->top-- decrements the top by index 1 in order to get the top item of the array as 
oppsosed to the pointer pointing to the next node or null.

Another if statement is then run if (s->top->top==0), if the condition is TRUE then del will point to s->top. The current s->top will then
point to s->top->next.

I then free(del); in order to delete the original top element from memory.

s->size-- is decrementing the size as an item is popped off.
*************************************************************************************************************************************/

void stack_int_pop(stack_int *s)
{
	
	assert(s != NULL);
	struct node *del;
	if(stack_int_isempty(s))
	{
		printf("Error: Stack is empty, nothing to pop\n");
		exit(1);
	}
	else
		s->top->top--;

	if(s->top->top==0)
	{
		del = s->top;
		s->top=s->top->next;
		free(del);
		
	}

	s->size--;
	
}

/**************************************************************************************************************************************
Function that returns the top element.

assert(s != NULL); is a check to see of the stack "s" is not equal to NULL, NULL being that there is not memory being allocated for the 
stack.

If assert(s == NULL) then the if statement will not run. If s != NULL then that means there is a stack allocated in the memory and 
therefore will run the function. 

if (stack_int_isempty(s)) is another check to see if the stack is empty by calling said function. Reason for the check is that if the 
stack was empty then there would be no element to at the top  to show.

return s->top->items will return the top item of the array. [(s->top->top)-1] will return what top is pointing to.
**************************************************************************************************************************************/

int stack_int_top(stack_int *s)
{	
	assert(s != NULL);
	if(stack_int_isempty(s))
	{
		printf("stack is empty\n");
		exit (1);
	}
	
	else

		return s->top->items[(s->top->top)-1];	
	
}		

/**************************************************************************************************************************************
Function to display all elements.

assert(s != NULL); is a check to see of the stack "s" is not equal to NULL, NULL being that there is not memory being allocated for the 
stack.

struct node * display is a pointer used to point to the top of the stack : display = s->top. Then a while loop is
initiated to check if the display pointer is != NUll as if the top is NULL then the display pointer will not be pointing to a block
and therefore the loop is not intiated and no printing of the elements will take place.

While (display != NULL) then that means the display pointer is pointing to the top of a stack and therefore will have
elements (ints) to print. 

In order to get every  element in the items array I will have to use a loop: for (i=display->top-1; i >=0;i--), i is set to display->
top-1 as display->top initially will be a pointer to a node so in order to get the top element of the items array the top needs to be 
decremented by index 1. Then i>=0 which is True, i-- will then go from the top of the items array to 0 in order to iterate through the 
array top to bottom as that is how a stack is processed(FILO). In order to print the elements in a vertical manner I used a new line /n.

display->items[i] in the print statement allows all of stacks to be displayed as [i] in this case as stated is iterating through the
array.

display =  display->next is equivilent to  s->top->next and therefore points to the next node or NULL.

if(display != NULL) printf("------\n") is a line of code that first checks if the display pointer is pointing to a memory location,
if TRUE then initiate print function.  This is used to make the display more pleasing to the eye in the output. if display = NULL then 
the while loop  will not  run as if display is pointing to NULL there will be no need to print as there is no elements to print.
**************************************************************************************************************************************/

void stack_int_display(stack_int *s)
{
	
	
	assert(s != NULL);
	struct node * display;
	int i;
	if(!stack_int_isempty(s))
	{	
		printf("Top>>");
		display = s->top;
		while (display != NULL){

		for (i=display->top-1; i >=0;i--)

		printf("\t| %i | \n",display->items[i]);
		display = display -> next;
		if(display != NULL)
		printf("\t------\n");		

		}


		
	}
	else
	{
		printf("STACK>>|EMPTY|\n");
	}
}

/******************************************************************************************************************************
Function to release the stack and corresponding items from memory.

assert(s != NULL); is a check to see of the stack "s" is not equal to NULL, NULL being that there is not memory being allocated
for the stack.

free(s) will free the stack from memory.

Even though the stack is deleted there is still items in the memory that are not getting pointed
to but are in memory regardless. Then used free(s->top->items) to remove said elements
from the memory.
*******************************************************************************************************************************/
void stack_int_release(stack_int *s)
{
	assert(s != NULL);
	free(s->top->items);
	free(s);
}













