/*
 Author: Matthew Ajayi
 Date: August 6th 2017
 Purpose: test program.
 
 University of Guelph, 2017.
 CIS*2520 (DE) S17
*/

#include "balancedTreeAPI.h"
#include "posSystem.h"

//Create tree algorithm and assign all values to parameters
Tree *createBalancedBinTree(int (*compareFP) (void *data1, void *data2), void (*destroyFP) (void *toBeDeleted),void *(*copyFP)(void *toBeCopy))
{	
	Tree *theTree = (Tree*) malloc(sizeof(Tree));
	theTree -> root = NULL;
	theTree -> compareFP = compareFP;
	theTree -> destroyFP = destroyFP;
	theTree -> copyFP = copyFP;
	return theTree;
}

//Create node function
TreeNode *createBalancedBinNode(void *data)
{
	TreeNode * ptr = (TreeNode*) malloc(sizeof(TreeNode));
	ptr -> data = data;
	ptr -> left = NULL;
	ptr -> right = NULL;
	ptr -> height = 1;
	return ptr;
}

//Insert node to tree algorithm with helper function
void treeInsertNode(Tree *theTree, void *toBeInserted)
{
	if(theTree == NULL || toBeInserted == NULL)
	{
		printf("NULL Value was inserted into the tree\n");
		return;
	}

    //helper function
    theTree -> root = insert(theTree -> root, toBeInserted, theTree -> compareFP);

	return;

}

//Helper function to recursively go through the tree and add node to null spots and balances afterwards
TreeNode * insert(TreeNode * root, void * data, int (*compareFP) (void *data1, void *data2))
{
	if (root == NULL)
	{
		root = createBalancedBinNode(data);
		return root;
	}


	else
	{
		//data < root
		if(compareFP(data,root -> data) == 0)
		{
			root -> left = insert(root -> left, data, compareFP);

			if(balance(root -> left, root -> right) > 1)
			{
				if(compareFP(data, root -> left -> data) == 0)
				{
					root = rotateRightWithLeftChild(root);//case b
				}

				else
				{
					root = doubleRotateWithLeftChild(root);//case d
				}
			}
		}

		//data > root
		else if(compareFP(data,root -> data) == 1)
		{
			
			root -> right = insert(root -> right, data, compareFP);

			if(balance(root -> right, root -> left) > 1)
			{
				
				if(compareFP(data,root -> right -> data) == 1)
				{
					root = rotateLeftWithRightChild(root);//case a
				}

				else
				{	
					root = doubleRotateWithRightChild(root);//case c
				}

			}
		}
	}

    
	root -> height = max(height(root -> left), height(root -> right)) + 1;

	return root;
}

//Delete node wrapper function
void treeDeleteNode(Tree *theTree, void *toBeDeleted)
{
	if(theTree == NULL)
	{
		return;
	}
    
    //delete node helper function
	theTree -> root = deleteNode(theTree -> root, toBeDeleted, theTree -> compareFP, theTree -> destroyFP);
}

//helps to recurisively traverse through the tree and delete nodes one by one
TreeNode * deleteNode(TreeNode * node, void * data , int (*compareFP) (void *data1, void *data2), void (*destroyFP) (void *data))
{
    
	
    if(node == NULL)
    {
    	return node;
    }
    
    // while(node != NULL)
    // {
        Data * d = (Data *) malloc(sizeof(Data));
        d = (Data*) (node -> data);

    //less than case
    if(strcmp(data, d -> productName) < 0)
    {
    	node -> left = deleteNode(node -> left, data, compareFP, destroyFP);
    }
    //greater than case
    else if(strcmp(data, d -> productName) > 0)
    {
    	node -> right = deleteNode(node -> right, data, compareFP, destroyFP);
    }

    else if(strcmp(data, d -> productName) == 0)//if equal
    {
    	
    	if(treeHasTwoChildren(node) != 0)
    	{
    	    TreeNode * temp = node->left ? node->left: node->right;

    	    if(temp == NULL)
    	    {
    	    	temp = node;
    	    	node = NULL;
    	    }

    	    else
    	    {
    	    	*node = *temp;
    	    }

            
    	    destroyFP(temp);


    	}

    	else
    	{
    		TreeNode * temp = findMin(node -> right);
    		node -> data = temp -> data;
    		node -> right = deleteNode(node -> right, temp -> data, compareFP, destroyFP);
    	}

    }

    //}

    if(node == NULL)
    {
    	return node;
    }

    node -> height = max(height(node -> left), height(node -> right)) + 1;

    int bal = balance(node -> left, node -> right);

    //left left case
    if (bal > 1 && balance(node->left->left, node -> left -> right) >= 0)
        return rotateRightWithLeftChild(node);
 
    // Left Right Case
    if (bal > 1 && balance(node->left->left, node -> left -> right) < 0)
    {
    	node -> left = rotateLeftWithRightChild(node -> left);
        return rotateRightWithLeftChild(node);
    }
 
    // Right Right Case
    if (bal < -1 && balance(node->right -> left, node -> right -> right) <= 0)
        return rotateLeftWithRightChild(node);
 
    // Right Left Case
    if (bal < -1 && balance(node->right -> left, node -> right -> right) > 0)
    {
        node -> right = rotateRightWithLeftChild(node -> right);
        return rotateLeftWithRightChild(node);
    }

    

    return node;

}

//rotate the tree to the right using left child
TreeNode * rotateRightWithLeftChild(TreeNode * node)
{
    TreeNode * temp = node -> left;
    node -> left = temp -> right;
    temp -> right = node;
    temp -> height = max(height(temp -> left), height(temp -> right)) + 1;
    node -> height = max(height(node -> left), height(node -> right)) + 1;
    return temp;
}

//double rotate the left sub tree
TreeNode * doubleRotateWithLeftChild(TreeNode * node)
{
    node -> left = rotateRightWithLeftChild(node -> left);
    node = rotateLeftWithRightChild(node);
    return node;
}

//rotate the left tree with right child
TreeNode * rotateLeftWithRightChild(TreeNode * node)
{
	TreeNode * temp = node -> right;
    node -> right = temp -> left;
    temp -> left = node;
    temp -> height = max(height(temp -> left), height(temp -> right)) + 1;
    node -> height = max(height(node -> left), height(node -> right)) + 1;
    return temp;
}

//double rotate the right sub tree
TreeNode * doubleRotateWithRightChild(TreeNode * node)
{
	node -> right = rotateLeftWithRightChild(node -> right);
    node = rotateRightWithLeftChild(node);
    return node;

}



//Compare function
int compareFP( void * first,  void *  second)
{
    if(*(int*)first > *(int*)second)
    {
        return 1;
    }

    else if(*(int*)first < *(int*)second)
    {
        return 0;
    }

    else
    {
    	return 2;
    }
}

//get height of the tree
int height(TreeNode *N)
{
	if (N == NULL)
		return 0;
	return N->height;
}

// A utility function to get maximum of two integers
int max(int a, int b)
{
	return (a > b)? a : b;
}

//function used to get height difference for current tree
int balance(TreeNode * rootLeft, TreeNode * rootRight)
{
	int right, left;

	right = height(rootRight);
	left = height(rootLeft);
	return left - right;
	//}
	
}
//print in preorder wrapper function
void treePreOrderPrint(Tree *theTree, void (*printNodeFP) (void *data))
{
	if (treeIsEmpty(theTree) == 1 || theTree -> root == NULL)
	{
		printf("Sorry theres nothing to print");
		return;
	}
    
    else
    {
        preOrder(theTree -> root, printNodeFP);
	}


}

//print inorder wrapper function
void treeInOrderPrint(Tree *theTree, void (*printNodeFP) (void *data))
{
	if (treeIsEmpty(theTree) == 1 || theTree -> root == NULL)
	{
		printf("Sorry theres nothing to print");
		return;
	}
    
    else
    {
    	inOrder(theTree -> root, printNodeFP);
    }

}

//post order wrapper function
void treePostOrderPrint(Tree *theTree, void (*printNodeFP) (void *data))
{
	if (treeIsEmpty(theTree) == 1 || theTree -> root == NULL)
	{
		printf("Sorry theres nothing to print");
		return;
	}
    
    else
    {
    	postOrder(theTree -> root, printNodeFP);
    }

}

//function pointer to print data
void printNodeFP(void * root)
{
    Data * d = (Data*) malloc(sizeof(Data));
    d = root;

    printf("productID:%s, productName:%s, pub:%s, genre:%s, taxable: %d, quantity: %d, price: $%.2f\n", d -> iD, d -> productName, d -> pub, d -> genre, d -> tax, d -> quantity, d -> price);

    // int * j = root;
    // printf("%d ", *j);
}

//preorder traversal and helper function 
void preOrder(TreeNode *root, void (*printNodeFP) (void *data))
{
    if(root != NULL)
    {
        //Data * d = (Data*) (root -> data);
        //printf("productID:%s, productName:%s, pub:%s, genre:%s, taxable: %d, quantity: %d, price: $%.2f\n", d -> iD, d -> productName, d -> pub, d -> genre, d -> tax, d -> quantity, d -> price);
    	printNodeFP(root -> data);
        preOrder(root->left, printNodeFP);
        preOrder(root->right, printNodeFP);
    }

}

//inorder traversal and helper function
void inOrder(TreeNode *root, void (*printNodeFP) (void *data))
{
    if(root != NULL)
    {
        //Data * d = (Data*) (root -> data);
        inOrder(root->left, printNodeFP);
        //printf("productID:%s, productName:%s, pub:%s, genre:%s, taxable: %d, quantity: %d, price: $%.2f\n", d -> iD, d -> productName, d -> pub, d -> genre, d -> tax, d -> quantity, d -> price);

        printNodeFP(root -> data);
        inOrder(root->right, printNodeFP);
    }

}

//postorder traversal and helper function
void postOrder(TreeNode * root, void (*printNodeFP) (void *data))
{
	if(root != NULL)
    {
        //Data * d = (Data*) (root -> data);
        postOrder(root->left, printNodeFP);
        postOrder(root->right, printNodeFP);
        //printf("productID:%s, productName:%s, pub:%s, genre:%s, taxable: %d, quantity: %d, price: $%.2f\n", d -> iD, d -> productName, d -> pub, d -> genre, d -> tax, d -> quantity, d -> price);

        printNodeFP(root -> data);
    }
}

//Finding the minimum value in the tree by going to the furthest left value
void * treeFindMin(Tree *theTree)
{
	if(theTree == NULL)
	{
        return NULL;
	}


    TreeNode* current = theTree -> root;
 
    //loop down to find the leftmost node
    while (current->left != NULL)
    {
        current = current->left;
    }

    return current -> data;
}

//Findiing max value by looping to the rightmost value
void * treeFindMax(Tree *theTree)
{
	if(theTree == NULL)
	{
		
        return NULL;
	}

	TreeNode* current = theTree -> root;
 
    //loop down to find the rightmost node
    while (current->right != NULL)
    {
        current = current->right;
    }

    return current -> data;
}

//Search for a node value
void * treeFindNode(Tree *theTree, void *data)
{
	if(theTree == NULL || data == NULL)
	{
        //printf("HERE\n");
		return NULL;
	}

	//helper function to traverse and find a node
	TreeNode * node = findNode(theTree -> root, data, theTree -> compareFP);

	if(node == NULL)
	{

		return NULL;
	}

	else
	{
		return node-> data;
	}

}

//helper function to traverse and find a node
TreeNode * findNode(TreeNode * theTree, void * data, int (*compareFP) (void *data1, void *data2))
{

    if( theTree != NULL)
    {
        Data * d = (Data *) malloc(sizeof(Data));
        d = (Data*) (theTree -> data);
        while(theTree != NULL)
        {
            
            if( strcmp(data, d -> productName) < 0 )
            {
                //printf("2\n");
                return findNode(theTree -> left,  data, compareFP);
            }
            
            else if(strcmp(data, d -> productName) >0)
            {
                //printf("3\n");
                return findNode(theTree -> right, data, compareFP);
            }

            else if(strcmp(data, d -> productName) == 0)
            {
                //printf("Found: %s\n", d ->productName);
                return theTree;
            }
        }

        
    }
	
    else
    {
        printf("Not found\n");
        return NULL;
    }
   

    return NULL;    	
}


//Check if tree is empty
int treeIsEmpty(Tree *theTree)
{
	if(theTree == NULL || theTree -> root == NULL)
	{
		return 1;
	}

	else
	{
		return 0;
	}
}

//Check if node has two children
int treeHasTwoChildren(TreeNode *root)
{
	if(root -> left != NULL && root -> right != NULL)
	{
		return 0;
	}

	else
	{
		return 1;
	}
	
}

//Find min helper function for delete
TreeNode * findMin(TreeNode *theTree)
{
    TreeNode* current = theTree;
 
    //loop down to find the leftmost node
    while (current->left != NULL)
    {
        current = current->left;
    }
    return current;
}

//Destroy or free data function pointer
void destroyFP(void * data)
{
	free(data);
}

//Destroy tree wrapper function
void destroyBalancedBinTree(Tree *toBeDeleted)
{
	if(toBeDeleted == NULL)
	{
        printf("Nothing left\n");
		return;
	}
    //helper function to delete entire tree
	toBeDeleted -> root = deleteTree(toBeDeleted -> root, toBeDeleted -> destroyFP);
}

//Helper function to traverse and delete the entire tree
TreeNode * deleteTree(TreeNode * root, void (*destroyFP) (void *data))
{
	if(root == NULL)
	{
		return NULL;
	}

	deleteTree(root -> left, destroyFP);
	deleteTree(root -> right, destroyFP);
	destroyFP(root -> data);

	return NULL;

}

//copyFP
void * copyFP(void * data)
{
	void * d = (void*) malloc(sizeof(void *));
	d = data;
	return d;
}

