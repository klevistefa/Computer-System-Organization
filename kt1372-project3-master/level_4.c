/*
 * author: Klevis Tefa
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "proj3.h"


// Implement a C function called level_4_opt. It should perform the same 
// task as the implemented level_4 function. 
// In the comments for the function describe why your changes make the
// function more cache friendly. 
//


// Note: Data structures like linked lists are not very
// cache friendly (their nodes can be scattered all over
// the heap). The following method compacts the nodes of a linked 
// list into adjacent memory locations in an array and it also
// preserves the traditional linked list connections. 
// Your own code needs to accomplish the same. 
 

void level_4(node** head, int length)
{
    // malloc a contiguous block of memory on the heap
    // that is big enough for the entire list.
    node* new_list = malloc(sizeof(node) * length);

    // go through the list and make a copy of all the 
    // nodes and place them into the contiguous block in order
    node* n = *head;
    int i;
    for(i = 0 ; i < length ; ++i) {
        node copy = { n->value, NULL };
        new_list[i] = copy;
        n = n->next;
    }

    // go through the list again and "link" each node in 
    // the contiguous block to the next node in memory; 
    // free all the nodes in the old list
    n = *head;
    for(i = 0 ; i < length - 1 ; ++i) {
        // link each node in the new list
        new_list[i].next = &new_list[i+1];
        // free the old nodes
        node* free_me = n;
        n = n->next;
        free(free_me);
    }

    // free the last node of the old list
    free(n);

    // point head at the new packed list
    *head = new_list;
}


/*In this case I tried to combine the two for-loops in a single loop. This meaning that
both compacting the nodes of the linked list into adjacent memory location in an array, and
linking the nodes together properly are combined in one loop iteration. Which results in fewer
cache misses since you deal with two things at once rather then finshing one thing for all the nodes
and then going back from the beginning to finish the rest.
*/
void level_4_opt(node** head, int length)
{
    // malloc a contiguous block of memory on the heap
    // that is big enough for the entire list.
    node* new_list = malloc(sizeof(node) * length);
    node* n = *head;

    int i;
    //going through the who linked list
    for(i = 0 ; i < length - 1 ; ++i) {
        //creating a copy of the current node being processed
        node copy = {n->value, NULL};
        //copying that node to the new contiguous block of memory
        new_list[i] = copy;
        //linking that node to the memory address where the next node will be placed in the next iteration
        new_list[i].next = &new_list[i+1];
        //after we have coppied the node to the new memory we can now free it
        node* free_me = n;
        //getting the next node in the linked list
        n = n->next;
        //freeing the node that was processed because we're fully done with it 
        free(free_me);
    }

    //The above loop didn't copy and link the last node because we would have an error if we would connect the last copy of the linked list to &new_list[i+1]
    //because we would pass the boundaries of the new_list. Therefore we process the tail manually.
    //Since n is now the tail from the last loop we make a copy of the tail and put it at i which now is of value (length-1, i.e: the last element of array)
    node copy = {n->value, NULL};
    new_list[i] = copy;

    //Freeing the last node of the old linked list
    free(n);
    //Point head at the new packed linked list
    *head = new_list;

}


/* DO NOT MODIFY THE FUNCTION THAT FOLLOWS */


void addFront(data * s,  node ** head) {
    if (head == 0 ) return;
    if (s == 0 ) return; 
    
    //allocate memory for storing the node 
    node *n = ( node *)malloc(sizeof( node));
    //make sure that the memory was allocated,
    //if not, just quit
    if (n == NULL) return;
    n->value = *s;
    
    n->next = (*head);
    (*head) = n;
}


