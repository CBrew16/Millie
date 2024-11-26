//
// Created by Cameron Brewster on 2024-11-23.
//

#include "myrecord_avl.h"

#include <stddef.h>
#include <stdlib.h>
#define MAX 100
#include <math.h>
#include <stdio.h>


void inOrder(AVLNODE *rootp_source, AVLNODE **arr, int *index) {
    if(rootp_source == NULL) {
        return; // Base/Edge case. This is when the recursion knows to stop. When it reaches the bottom node
    }

    inOrder(rootp_source -> left,arr, index); // Traversing the left subtree


    arr[*index] = rootp_source; // Enqueing the node into the tree
    (*index)++; //incrementing the index

    inOrder(rootp_source -> right, arr, index); // Traversing the right subtree
    // The line above is updating the index and adding it to the queue

}

AVLNODE* merge_avl(AVLNODE *rootp_dest, AVLNODE *rootp_source) {

    if(rootp_dest == NULL) {
        return rootp_source; // Edge case if theres no tree to add to
    }

    if(rootp_source == NULL) {
        return rootp_dest;
    }

    int size = avl_count_nodes(rootp_source) ; // initializing array size


    // Call insert function
    //Insert already handles rotations

    //Allocate memory for the array
    AVLNODE **arr = (AVLNODE **)malloc(size * sizeof(AVLNODE*)); // Dynamically allocating memory for a large array
    if(arr == NULL) {

        return NULL;
    }

    int index = 0;
    inOrder(rootp_source, arr, &index); // Calling the inOrder traverse function

    for(int i = 0; i< size; i++) {
        // Looping and inserting the queue into the tree
        // Sending in the created queue array and each element's data
        if (!avl_search(rootp_dest, arr[i]->data.name)) {  // Only insert if the node doesn't exist
            avl_insert(&rootp_dest, arr[i]->data);
        }
    }
    printf("After merging the two trees:\n");
    avl_print_in_order(rootp_dest);  // Print the tree after merge

    free(arr);

    return rootp_dest; // Return the new tree
}


void inOrder_values(AVLNODE *dsroot, float *values, int *index){
    if(dsroot == NULL){
    return;} // Edge case

    inOrder_values(dsroot->left,values,index); // Recursively searching left

    values[*index] = dsroot ->data.score; // Enqueue a score from the tree
    (*index)++ ; // Updating the index pointer

    inOrder_values(dsroot->right,values, index); // Recursively search right and update array
}


void calculate_stats(AVLDS* dsroot){
    if(dsroot == NULL) {
        return;
    }

    if(dsroot-> root == NULL){ // Edge case if tree DNE
    dsroot -> count = 0;
    dsroot -> mean = 0.0;
    dsroot -> stddev = 0.0;
    return; // Edge case if tree DNE
}
    dsroot -> count = avl_count_nodes(dsroot->root); // Determining the number of nodes
    float *values = (float * )malloc(dsroot->count * sizeof(float)); //Allocating memory for the array

    if(values == NULL) {
        exit(EXIT_FAILURE); // Exit if the memory allocation fails
    }

    int index = 0; // Starting the array index at 0
    inOrder_values(dsroot->root, values, &index);  // Calling the inOrder_values function to fill the array

    // Completing the calculations:

    double sum = 0.0;
    double squared_sum = 0.0;

    for(int i = 0; i < dsroot->count; i++) { // Looping through the array
        sum += values[i]; // finding the sum
        squared_sum += values[i] * values[i]; // Finding squared sum
    }
    dsroot -> mean = sum/ dsroot -> count; // updating the mean
    dsroot->stddev = sqrt((squared_sum - (sum * sum) / dsroot->count) / dsroot->count);


    free(values); // Free the temp array
}





AVLNODE* merge_avlds(AVLNODE* rootp_dest, AVLNODE* rootp_source) {
    if(rootp_dest == NULL) {
        return rootp_source; // Edge case if theres no tree to add to
    }

    if(rootp_source == NULL) {
        return rootp_dest;
    }

    // Merge the trees
    rootp_dest = merge_avl(rootp_dest, rootp_source); // Merging the two trees
    return rootp_dest; // Returning the updated tree
}


void avlds_clean(AVLDS *dsroot) {
   if(dsroot == NULL) {
       return; // Edge case if tree DNE
   }

    avl_clean(&dsroot -> root); // calling the AVL_clean function

    dsroot -> count = 0;
    dsroot -> mean = 0.0;
    dsroot -> stddev = 0.0; // Updating the values stored in AVLDS struct
    dsroot->root = NULL;
}

int remove_record(AVLDS *dsroot, char *name) {
    if(dsroot == NULL) {
        return 0; // Return 0 if Tree DNE and insertion fails
    }
    // calling the avl_delete function
    avl_delete(&dsroot->root, name);

    if(dsroot-> root == NULL) { // Checking if  deletion didnt happen
        return 0;
    }
    return 1;
}
int add_record(AVLDS *dsroot,RECORD data) {
    if(dsroot == NULL) {
        return 0; //Edge case if the tree DNE
    }

    avl_insert(&dsroot->root,data);
    return 1;
}