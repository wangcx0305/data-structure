#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "avl.h"


/* Alocate and initialize AVL tree structure. */
struct AVLTree * newAVLTree()
{
	struct AVLTree *tree = (struct AVLTree *)malloc(sizeof(struct AVLTree));
	assert(tree != 0);
	
	initAVLTree(tree);
	return tree;
}

/* Initialize AVL tree structure. */
void initAVLTree(struct AVLTree *tree)
{
	tree->cnt = 0;
	tree->root = 0;

}

void _freeAVL(struct AVLnode *node)
{
	if (node != 0) {
		_freeAVL(node->left);
		_freeAVL(node->right);		
		free(node);
	}
}

/* Deallocate nodes in AVL tree. */
void clearAVLTree(struct AVLTree *tree)
{
	_freeAVL(tree->root);
	tree->root = 0;
	tree->cnt  = 0;
}

/* Deallocate nodes in AVL tree and deallocate the AVL tree structure. */
void deleteAVLTree(struct AVLTree *tree)
{
	clearAVLTree(tree);
	free(tree);
}


/* return height of current node */
int h(struct AVLnode *current)
{
	if (current == 0)
		return -1;
	return current->height;
}

/* set height for current node */
void setHeight (struct AVLnode * current)
{
	int lch = h(current->left);
	int rch = h(current->right);
	if (lch < rch)
		current->height = 1 + rch;
	else
		current->height = 1 + lch;
}

/* return balance factor value */
int bf(struct AVLnode * current)
{
	return h(current->right) - h(current->left);
}

/* left-rotate subtree of current node */
struct AVLnode * rotateLeft(struct AVLnode * current)
{
	/* write this function */ 
    struct AVLnode * newtop = current->right;
    current->right = newtop->left;
    newtop->left = current;
    setHeight(current);
    setHeight(newtop);
    return newtop;
}

/* right-rotate subtree of current node */
struct AVLnode * rotateRight(struct AVLnode * current)
{
	/* write this function */
    struct AVLnode * newtop = current->left;
    current->left = newtop->right;
    newtop->right = current;
    setHeight(current);
    setHeight(newtop);
    return newtop;
    

}

/* balance subtree of current node */
struct AVLnode * _balance(struct AVLnode * current)
{
	int cbf = bf(current);

	/* write this function */ 
    if(cbf < -1){
        dcbf = bf(current->left);
        if(dcbf > 0){
            current->left = rotateLeft(current->left);
        }
        return rotateRight(current);
    }
    else if(cbf > 1){
        dcbf = bf(current->right);
        if(dcbf < 0){
            current->right = rotateRight(current->right);
        }
        return rotateLeft(current);
    }
    setHeight(current);
	return current;
}

/* add newValue to subtree of current node */
struct AVLnode * AVLnodeAdd(struct	AVLnode * current, TYPE newValue)
{
	struct AVLnode * newnode;

	/* write this function */ 
    if(current == 0){
        newnode->val = newValue;
        newnode->leftchild = NULL;
        newnode->rightchild = NULL;
        newnode->height = 0;
        return newnode;
    }
    if(current->value > newValue){
        current->left = AVLnodeAdd(current->left, newValue);
    }
    if(current->value < newValue){
        current->right = AVLnodeAdd(current->right, newValue);
    }
	
	return _balance(current);
}

/* add val to AVL tree */
void addAVLTree(struct AVLTree *tree, TYPE val)
{
	tree->root = AVLnodeAdd(tree->root, val);	
	tree->cnt++;
}

/* determine if val is contained in the AVL tree */
int containsAVLTree(struct AVLTree *tree, TYPE val)
{
	struct AVLnode* cur = tree->root;

	/* write this function */
    while(cur){
        if(cur->value == val)
            return 1;
        if(cur->value < val)
            cur = cur->right;
        else
            cur = cur->left;
    }
    return 0;


}

/* find leftmost value from subtree of current node */
TYPE _leftMost(struct AVLnode *cur)
{
	while(cur->left != 0)
		cur = cur->left;
	return cur->val;
}

/* remove leftmost node from subtree of current node */
struct AVLnode * _removeLeftmost(struct AVLnode * cur)
{
	struct AVLnode * temp;

	if(cur->left != 0){
		cur->left = _removeLeftmost(cur->left);
		return _balance(cur);
	}

	temp = cur->right;
	free(cur);
	return temp;
}

/* remove val from subtree of cur node */
struct AVLnode * _removeNode(struct AVLnode * cur, TYPE val)
{
	struct AVLnode * temp;

	if(EQ(val, cur->val)){
		if(cur->right != 0){
			cur->val = _leftMost(cur->right);
			cur->right = _removeLeftmost(cur->right);
			return _balance(cur);
		} else {
			temp = cur->left;
			free(cur);
			return temp;
		}
	} else if (LT(val, cur->val))
		cur->left = _removeNode(cur->left, val);
	else cur->right = _removeNode(cur->right, val);

	return _balance(cur);
}

/* remove val from AVL tree */
void removeAVLTree(struct AVLTree * tree, TYPE val)
{
	if(containsAVLTree(tree, val)){
		tree->root = _removeNode(tree->root, val);
		tree->cnt--;
	}
}


