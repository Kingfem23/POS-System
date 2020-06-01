/*
 Author: Matthew Ajayi
 Date: August 6th 2017
 Purpose: test program.
 
 University of Guelph, 2017.
 CIS*2520 (DE) S17
*/


#ifndef STUDENT_TREE_API_
#define STUDENT_TREE_API_
#include "balancedTreeAPI.h"

/*You may add anything to this .h file that you need to add to your tree ADT*/

//YOU MUST LEAVE THESE TYPEDEFS AS IS. 
/**typedef for struct treenode*/
typedef struct BalancedBinTreeNode TreeNode;

/**typedef for struct tree*/
typedef struct BalancedBinTree Tree;




/*Struct definitions for the tree and the tree node.
*/
struct BalancedBinTree {
  //define your tree here.  You can change these if you need to but your tree must be abstract.
    TreeNode *root; ///< pointer to generic data that is to be stored in the tree
    int (*compareFP) (void *data1, void *data2); ///< function pointer to a comparison function for the purpose of inserting and deleting elements
    void (*destroyFP) (void *data); ///< function pointer to a function to free a single pointer that is deleted from the tree
    void *(*copyFP)(void *toBeCopy); ///< function pointer to a function that copies pointer data
  };



struct BalancedBinTreeNode{
    void *data; ///< pointer to generic data that is to be stored in the heap
    TreeNode *left; ///< pointer to left tree node of current node. Null if empty.
    TreeNode *right; ///< pointer to right tree node of current node. Null if empty.
    
    //Add additional structure elements here
    int height;
};

//Function prototypes

/**Function to determine compare void pointers
 *@param first is void pointer
 *@param second is void pointer
 *@return 0 if values are less and 1 if values are greater.
 **/
int compareFP( void * first,  void *  second);

/**Function helper to traverse and insert node and balance the tree
 *@param root is the root node or parent
 *@param data is void pointer
 *@param compare is the function pointer passed in from the wrapper function
 *@return TreeNode
 **/
TreeNode * insert(TreeNode * root, void * data, int (*compareFP) (void *data1, void *data2));

/**Function keep track of the height of each node
 *@param N is the current node to get the height checked
 *@return height of the node
 **/
int height(TreeNode *N);

/**Function to get the max height of the tree
 *@param a is the height of the first node
 *@param b is the height of the seconds node
 *@return height of the node
 **/
int max(int a, int b);

/**Function to get the balance factor of the tree
 *@param rootLeft is the left root node passed in
 *@param rootRight is the right root node passed in
 *@return balance factor
 **/
int balance(TreeNode * rootLeft, TreeNode * rootRight);

/**Function helper to rotate the tree to the right
 *@param node is the root of the tree
 *@return TreeNode
 **/
TreeNode * rotateRightWithLeftChild(TreeNode * node);

/**Function helper to double rotate the tree to the left
 *@param node is the root of the tree
 *@return TreeNode
 **/
TreeNode * doubleRotateWithLeftChild(TreeNode * node);

/**Function helper to rotate the tree to the left
 *@param node is the root of the tree
 *@return TreeNode
 **/
TreeNode * rotateLeftWithRightChild(TreeNode * node);

/**Function helper to double rotate the tree to the right
 *@param node is the root of the tree
 *@return TreeNode
 **/
TreeNode * doubleRotateWithRightChild(TreeNode * node);

/**Function helper to traverse the tree in preorder fashion
 *@param root is the root node passed in
 *@param printNodeFP is the function pointer passed in from the wrapper function
 *@return void
 **/
void preOrder(TreeNode *root, void (*printNodeFP) (void *data));

/**Function helper to traverse the tree in inorder fashion
 *@param root is the root node passed in
 *@param printNodeFP is the function pointer passed in from the wrapper function
 *@return void
 **/
void inOrder(TreeNode *root, void (*printNodeFP) (void *data));

/**Function helper to traverse the tree in preorder fashion
 *@param root is the root node passed in
 *@param printNodeFP is the function pointer passed in from the wrapper function
 *@return void
 **/
void postOrder(TreeNode * root, void (*printNodeFP) (void *data));

/**Function pointer to print data
 *@param root is the root data to be printed
 *@return void
 **/
void printNodeFP(void * root);

/**Function helper to traverse the tree to find a specfic node
 *@param theTree is the root node passed in
 *@param data is the value to be searched
 *@param compareFP is the function pointer passed in from the wrapper function
 *@return TreeNode
 **/
TreeNode * findNode(TreeNode * theTree, void * data,  int (*compareFP) (void *data1, void *data2));

/**Function helper to traverse the tree to find leftmost node
 *@param theTree is the root node passed in
 *@return TreeNode
 **/
TreeNode * findMin(TreeNode *theTree);

/**Function helper to traverse the tree to find a specfic node
 *@param node is the root node passed in
 *@param data is the value to be searched
 *@param compareFP is the function pointer passed in from the wrapper function
 *@param destroyFP is the function pointer passed in from the wrapper function
 *@return TreeNode
 **/
TreeNode * deleteNode(TreeNode * node, void * data, int (*compareFP) (void *data1, void *data2), void (*destroyFP) (void *data));

/**Function helper to free node and its data
 *@param data is the data to be freed
 *@return void
 **/
void destroyFP(void * data);

/**Function helper to traverse the tree to delete entire tree
 *@param root is the root node passed in
 *@param destroyFP is the function pointer passed in from the wrapper function
 *@return TreeNode
 **/
TreeNode * deleteTree(TreeNode* root, void (*destroyFP) (void *data));

/**Function pointer to copy data
 *@param data is the value to be searched
 *@return void *
 **/
void * copyFP(void * data);



#endif

