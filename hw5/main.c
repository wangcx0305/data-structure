/*
  File: bst.c
  Implementation of the binary search tree data structure.
 
*/
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "bst.h"
#include "structs.h"


struct Node {
    TYPE         val;
    struct Node *left;
    struct Node *right;
};

struct BSTree {
    struct Node *root;
    int          cnt;
};

/*----------------------------------------------------------------------------*/

/*
  function to print the result of a test function
  param: predicate:  the result of the test 
  nameTestFunction : the name of the function that has been tested
  message

*/
void printTestResult(int predicate, char *nameTestFunction, char *message){
    if (predicate)
	printf("\x1B[32m" "%s(): PASS %s\n" "\033[0m", nameTestFunction, message);
    else
	printf("\x1B[31m" "%s(): FAIL %s\n" "\033[0m", nameTestFunction, message);        
}

/*
  Function to test if nodes are added correctly.
*/
void testAddNode() {
   struct BSTree *tree	= newBSTree();
   struct data *test_data;
  
   test_data = malloc(sizeof(struct data));
   test_data->number = 90;
   test_data->name = "Root";
   addBSTree(tree, test_data);
   /*Check the Root node*/
   printTestResult( (compare(tree->root->val, test_data) == 0), "testAddNode", "Inserting 90 as Root");
   printTestResult( (tree->cnt == 1), "testAddNode", "Increase tree->cnt to 1 when inserting 90 as Root");

   test_data = malloc(sizeof(struct data));
   test_data->number = 10;
   test_data->name = "Root->L";
   addBSTree(tree, test_data);
   /*Check the position of the second element that is added to the BST tree*/
   printTestResult( (compare(tree->root->left->val, test_data) == 0), "testAddNode", "Inserting 10 as Root->L");
   printTestResult( (tree->cnt == 2), "testAddNode", "Increase tree->cnt to 2 when inserting 10 as Root->L");

   test_data = malloc(sizeof(struct data));
   test_data->number = 100;
   test_data->name = "Root->R";
   addBSTree(tree, test_data);
   /*Check the position of the third element that is added to the BST tree*/
   printTestResult( (compare(tree->root->right->val, test_data) == 0), "testAddNode", "Inserting 100 as Root->R");
   printTestResult( (tree->cnt == 3), "testAddNode", "Increase tree->cnt to 3 when inserting 100 as Root->R");

   test_data = malloc(sizeof(struct data));
   test_data->number = 5;
   test_data->name = "Root->L->L";
   addBSTree(tree, test_data);
   /*Check the position of the fourth element that is added to the BST tree*/
   printTestResult( (compare(tree->root->left->left->val, test_data) == 0), "testAddNode", "Inserting 5 as Root->L->L");
   printTestResult( (tree->cnt == 4), "testAddNode", "Increase tree->cnt to 4 when inserting 5 as Root->L->L");

   test_data = malloc(sizeof(struct data));
   test_data->number = 50;
   test_data->name = "Root->L->R";
   addBSTree(tree, test_data);
   /*Check the position of the fifth element that is added to the BST tree*/
   printTestResult( (compare(tree->root->left->right->val, test_data) == 0), "testAddNode", "Inserting 50 as Root->L->R");
   printTestResult( (tree->cnt == 5), "testAddNode", "Increase tree->cnt to 5 when inserting 50 as Root->L->R");

   test_data = malloc(sizeof(struct data));
   test_data->number = 40;
   test_data->name = "Root->L->R->L";
   addBSTree(tree, test_data);
   /*Check the position of the sixt element that is added to the BST tree*/
   printTestResult( (compare(tree->root->left->right->left->val, test_data) == 0), "testAddNode", "Inserting 40 as Root->L->R->L");
   printTestResult( (tree->cnt == 6), "testAddNode", "Increase tree->cnt to 6 when inserting 40 as Root->L->R->L");

   printf("Deleting the BSTree...\n");
   deleteBSTree(tree);
   printf("Returning from testAddNode().\n");
}

/*
  Function to test that the BST contains the elements that we added to it
*/
void testContainsBSTree() {
  /* printf("test the test \n");*/
    struct BSTree *tree = buildBSTTree();
    struct data myData;

    myData.number = 90;
    myData.name = "Root";
    printTestResult(containsBSTree(tree->root, &myData), "containsBSTree", "When test containing 90 as Root");

    myData.number = 10;
    myData.name = "Root->L";
    printTestResult(containsBSTree(tree->root, &myData), "containsBSTree", "When test containing 10 as Root->Left");
    
    myData.number = 5;
    myData.name = "Root->L->L";
    printTestResult(containsBSTree(tree->root, &myData), "containsBSTree", "When test containing 5 as Root->Left->Left");
        
    myData.number = 50;
    myData.name = "Root->L->R";
    printTestResult(containsBSTree(tree->root, &myData), "containsBSTree", "When test containing 50 as Root->Left->Right");

    myData.number = 40;
    myData.name = "Root->L->R->L";
    printTestResult(containsBSTree(tree->root, &myData), "containsBSTree", "When test containing 40 as Root->Left->Right->Left");

    myData.number = 55;
    myData.name = "Root->L->R->R";
    printTestResult(containsBSTree(tree->root, &myData), "containsBSTree", "When test containing 55 as Root->Left->Right->Right");

    myData.number = 100;
    myData.name = "Root->R";
    printTestResult(containsBSTree(tree->root, &myData), "containsBSTree", "When test containing 100 as Root->Right");

    myData.number = 110;
    myData.name = "Root->R->R";
    printTestResult(containsBSTree(tree->root, &myData), "containsBSTree", "When test containing 110 as Root->Right->Right");

    myData.number = 105;
    myData.name = "Root->R->R->L";
    printTestResult(containsBSTree(tree->root, &myData), "containsBSTree", "When test containing 105 as Root->Right->Right->Left");

    /*Check if containsBSTree will properly recognize if a number is not in the tree.   */
    myData.number = 1337;
    myData.name = "Root->N->A->N";
    printTestResult(!containsBSTree(tree->root, &myData), "containsBSTree", "When testing if 1337 is not in the tree.");

    printf("Deleting the BSTree...\n");
    deleteBSTree(tree);
    printf("Returning from testContainsBSTree().\n");

}

/*
  Function to test the left_Most_element 

*/
void testLeftMost() {
    struct BSTree *tree = buildBSTTree();
    struct data *myData;

    myData = (struct data*)tree->root->left->left->val;
    printTestResult( (compare(_leftMost(tree->root)->val, myData) == 0), "_leftMost", "Left most of Root"); 
    printTestResult( (compare(_leftMost(tree->root->left)->val, myData) == 0), "_leftMost", "Left most of Left of Root");
    
    myData = (struct data*)tree->root->left->right->left->val;
    printTestResult( (compare(_leftMost(tree->root->left->right)->val, myData) == 0), "_leftMost", "Left most of Left of Right of Root");

    myData = (struct data*)tree->root->right->right->left->val;
    printTestResult( (compare(_leftMost(tree->root->right->right)->val, myData) == 0), "_leftMost", "Left most of Right of Right of Root");

    printf("Deleting the BSTree...\n");
    deleteBSTree(tree);
    printf("Returning from testLeftMost().\n");

}

void testRemoveLeftMost() {
    struct BSTree *tree = buildBSTTree();
    struct data *myData;
    struct data *delete_val; /*In this case we need another struct to delete value 105
    Since _removeLeftMost is not supposed to delete the value (it may be pointed to by another element in the tree)
    we will need to manually delete it ourselves once the node has been deleted.*/

    myData = tree->root->left->left->val;
    _removeLeftMost(tree->root);
    printTestResult( (tree->root->left->left == NULL), "_removeLeftMost", "Removing leftmost from Root");
    free(myData);

    delete_val = tree->root->left->val;
    myData = tree->root->left->right->val;
    _removeLeftMost(tree->root);
    printTestResult( (compare(tree->root->left->val, myData) == 0), "_removeLeftMost", "Removing leftmost from Root again");
    free(delete_val);

    delete_val = tree->root->right->right->left->val;
    myData = tree->root->right->right->left->right->val;
    _removeLeftMost(tree->root->right->right);
    free(delete_val);
    printTestResult( (compare(tree->root->right->right->left->val, myData) == 0), "_removeLeftMost", "removing leftmost from Root->Right->Right");

    printf("Deleting the BSTree...\n");
    deleteBSTree(tree);
    printf("Returning from testRemoveLeftMost().\n");
}

void testRemoveNode() {
    struct BSTree *tree = buildBSTTree();
    struct data *myData;
    /*Grabs the expected value from the tree, then deletes a node and checks if the new value in that place matches the expected value.*/

    myData = tree->root->right->val;
    _removeNode(tree->root, tree->root->val);
    printTestResult( (compare(tree->root->val, myData) == 0), "_removeNode", "Testing remove Root\n");

    myData = tree->root->right->left->val;
    _removeNode(tree->root, tree->root->right->val);
    printTestResult( (compare(tree->root->right->val, myData) == 0), "_removeNode", "Testing remove Root->Right\n"); /*Keep in mind that the tree has changed.*/

    myData = tree->root->left->right->left->val;
    _removeNode(tree->root, tree->root->left->val);
    printTestResult( (compare(tree->root->left->val, myData) == 0), "_removeNode", "Testing remove Root->Left\n");
        
    myData = tree->root->right->val;
    _removeNode(tree->root, tree->root->val);
    printTestResult( (compare(tree->root->val, myData) == 0), "_removeNode", "Testing remove Root again\n");
    
    struct data not_in_tree;
    not_in_tree.number = 9000;
    printf("Testing invalid remove. The two lines below should match exactly\n");
    printTree(tree);
    _removeNode(tree->root, &not_in_tree); /*Should print error message and leave tree unchanged.*/
    printTree(tree);

    printf("Deleting the BSTree...\n");
    deleteBSTree(tree);
    printf("Returning from testRemoveNode().\n");
}

/*
  Main function for testing different Functions of the Assignment#4.
*/

int main(int argc, char *argv[]){	

    /*After implementing your code, please uncommnet the following calls to the test functions and test your code */
    testAddNode();
	
    printf("\n");
    testContainsBSTree();
	
    printf("\n");
    testLeftMost();
	
    printf("\n");
    testRemoveLeftMost();
	
    printf("\n");
    testRemoveNode();
	
    return 0;
}
