/***********************************************************
 * Author:          Kelsey Helms
 * Date Created:    July 21, 2016
 * Filename:        animal.c
 *
 * Overview:
 * This program is a guessing the animal game!
 *
 * Inputs and outputs are defined by functions.
 ************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
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

/***********************************************************
 * function to initialize the binary search tree.
 *
 * param tree
 * pre: tree is not null
 * post: tree size is 0
 * root is null
 ***********************************************************/

void initBSTree(struct BSTree *tree)
{
    assert (tree != 0);
    tree->cnt  = 0;
    tree->root = 0;
}

/***********************************************************
 * function to create a binary search tree.
 *
 * param: none
 * pre: none
 * post: tree->count = 0
 * tree->root = 0;
 ***********************************************************/

struct BSTree* newBSTree()
{
    struct BSTree *tree = (struct BSTree *)malloc(sizeof(struct BSTree));
    assert(tree != 0);
    
    initBSTree(tree);
    return tree;
}

/***********************************************************
 * function to free the nodes of a binary search tree
 *
 * param: node  the root node of the tree to be freed
 * pre: none
 * post: node and all descendants are deallocated
 ***********************************************************/

void _freeBST(struct Node *node)
{
    if (node != 0)
    {
        _freeBST(node->left);
        _freeBST(node->right);
        free(node);
    }
}

/************************************************************
 * function to clear the nodes of a binary search tree
 *
 * param: tree - a binary search tree
 * pre: tree ! = null
 * post: the nodes of the tree are deallocated
 * tree->root = 0;
 * tree->cnt = 0
 ***********************************************************/
void clearBSTree(struct BSTree *tree)
{
    assert (tree != 0);
    _freeBST(tree->root);
    tree->root = 0;
    tree->cnt  = 0;
}

/***********************************************************
 * function to deallocate a dynamically allocated binary
 * search tree
 *
 * param: tree   the binary search tree
 * pre: tree != null;
 * post: all nodes and the tree structure itself are
 * deallocated.
 ***********************************************************/
void deleteBSTree(struct BSTree *tree)
{
    assert (tree != 0);
    clearBSTree(tree);
    free(tree);
}

/***********************************************************
 * function to determine if  a binary search tree is empty.
 *
 * param: tree - the binary search tree
 * pre:  tree is not null
 ***********************************************************/
int isEmptyBSTree(struct BSTree *tree)
{
    assert (tree != 0);
    return (tree->cnt == 0);
}

/***********************************************************
 * function to determine the size of a binary search tree
 *
 * param: tree - the binary search tree
 * pre: tree is not null
 ***********************************************************/
int sizeBSTree(struct BSTree *tree)
{
    return tree->cnt;
}

/***********************************************************
 * recursive helper function to add a node to the binary
 * search tree.
 *
 * param:  cur - the current root node
 * val - the value to be added to the binary search tree
 * pre:	val is not null
 ***********************************************************/
struct Node *_addNode(struct Node *cur, TYPE val)
{
    assert (val != NULL);
    struct Node *newNode;
    
    if(cur == 0)
    {
        newNode = (struct Node *)malloc(sizeof(struct Node));
        assert (newNode != 0);
        newNode->val = val;
        newNode->left = 0;
        newNode->right = 0;
        
        return newNode;
    }
    if(compare(cur->val, val) <= 0)
        cur->right = _addNode(cur->right, val);
    
    else
        cur->left = _addNode(cur->left, val);
    
    return cur;
}

/***********************************************************
 * function to add a value to the binary search tree
 *
 * param: tree - the binary search tree
 * val - the value to be added to the tree
 *
 * pre:	tree is not null
 * val is not null
 * pose:  tree size increased by 1
 * tree now contains the value, val
 ***********************************************************/
void addBSTree(struct BSTree *tree, TYPE val)
{
    assert (tree != 0);
    tree->root = _addNode(tree->root, val);
    tree->cnt++;
}


/***********************************************************
 * function to determine if the binary search tree contains
 * a particular element
 *
 * param: tree - the binary search tree
 * val - the value to search for in the tree
 * pre:	tree is not null
 * val is not null
 * post:	none
 ***********************************************************/
int containsBSTree(struct BSTree *tree, TYPE val)
{
    assert (tree != 0);
    assert (val != NULL);
    struct Node* itr = tree->root;
    
    while(itr != 0)
    {
        if(compare(val, itr->val) == 0)
            return 1;
        
        else if (compare(val, itr->val) < 0)
            itr = itr->left;
        
        else
            itr = itr->right;
    }
    
    return 0;
}

/***********************************************************
 * helper function to find the left most child of a node
 * return the value of the left most child of cur
 *
 * param: cur - the current node
 * pre:	cur is not null
 * post: none
 ***********************************************************/
TYPE _leftMost(struct Node *cur)
{
    assert (cur != 0);
    
    while(cur->left != 0)
        cur = cur->left;
    
    return cur->val;
}


/***********************************************************
 * recursive helper function to remove the left most
 * child of a node
 *
 * param: cur - the current node
 * pre:	cur is not null
 * post: the left most node of cur is not in the tree
 ***********************************************************/
struct Node *_removeLeftMost(struct Node *cur)
{
    assert (cur != 0);
    
    if(cur->left != 0)
    {
        cur->left = _removeLeftMost(cur->left);
        return cur;
    }
    
    struct Node *rightNode = cur->right;
    free(cur);
    
    return rightNode;
}
/***********************************************************
 * recursive helper function to remove a node from the tree
 *
 * param: cur - the current node
 * val - the value to be removed from the tree
 * pre:	val is in the tree
 * cur is not null
 * val is not null
 ***********************************************************/
struct Node *_removeNode(struct Node *cur, TYPE val)
{
    assert (cur != 0);
    assert (val != NULL);
    
    if(compare(cur->val, val) == 0)
    {
        if(cur->right == 0)
        {
            struct Node *temp = cur->left;
            free(cur);
            return temp;
        }
        
        cur->val = _leftMost(cur->right);
        cur->right = _removeLeftMost(cur->right);
    }
    else if(compare(cur->val, val) > 0)
        cur->left = _removeNode(cur->left, val);
    else
        cur->right = _removeNode(cur->right, val);
    
    return cur;
    
}
/***********************************************************
 function to remove a value from the binary search tree
 param: tree - the binary search tree
 val - the value to be removed from the tree
 pre: tree is not null
 val is not null
 val is in the tree
 post:	tree size is reduced by 1
 ***********************************************************/
void removeBSTree(struct BSTree *tree, TYPE val)
{
    assert (tree != 0);
    assert (val != NULL);
    if (containsBSTree(tree, val))
    {
        tree->root = _removeNode(tree->root, val);
        tree->cnt--;
    }
}

/*----------------------------------------------------------------------------*/

#if 1
#include <stdio.h>

/*----------------------------------------------------------------------------*/
void printNode(struct Node *cur)
{
    if (cur == 0) return;
    printf("(");
    printNode(cur->left);
    /*Call print_type which prints the value of the TYPE*/
    print_type(cur->val);
    printNode(cur->right);
    printf(")");
}

void printTree(struct BSTree *tree)
{
    if (tree == 0) return;
    printNode(tree->root);
}
/*----------------------------------------------------------------------------*/

#endif

/*----------------------------------------------------------------------------*/


struct BSTree *animalTree(struct BSTree *animals) {
    
    char animalName[200];
    int number;
    
    FILE *dataFile = fopen("animal.txt","r");
    
    if(dataFile == NULL)
    {
        printf("ERROR: Data file 'animal.txt' not found...");
        exit(1);
    }
    while(fscanf(dataFile, "%199[^,], %d", animalName, &number) == 2)
    {
        
        struct data *animalData = malloc(sizeof(struct data));
        animalData->number = number;
        animalData->name = strdup(animalName);
        addBSTree(animals, animalData);
    }
    
    fclose(dataFile);
    return animals;
    
}


void startScreen()
{
    
    printf("****************************************\n");
    printf("*                                      *\n");
    printf("* Welcome to Kelsey's Animal Guessing  *\n");
    printf("*                 Game!                *\n");
    printf("*                                      *\n");
    printf("****************************************\n");
    
}

void instructions()
{
    printf("\n\nThis is a simple animal guessing game, \nmaking use of the binary search tree \ndata structure.\n\n");
    printf("Please think of an animal.\n\n");
    printf("Answer Y/N or Q to any question asked \nby the game, and if you can stump the \nprogram, it'll ask ");
    printf("you to add a new \nanimal to the mix!");
    printf("\n\nHave fun!\n\n");
    
}

void game(struct BSTree *animals)
{
    struct Node *cur = animals->root;
    char userAnswer;
    int currentNode, previousNode;
    
    while(cur != NULL)
    {
        previousNode = currentNode;
        currentNode = ((struct data*) cur->val)->number;
        
        print_type(cur->val);
        printf("(Y for Yes / N for No / Q for Quit)\n");
        printf(" >> ");
        scanf("%c", &userAnswer);
        getchar() != '\n';
        printf("\n");
        
        if(userAnswer == 'N' || userAnswer == 'n')
        {
            cur = cur->right;
        }
        else if(userAnswer == 'Q' || userAnswer == 'q')
        {
            printf("Goodbye!\n\n");
            exit(1);
        }
        else if(userAnswer == 'Y' || userAnswer == 'y')
        {
            cur = cur->left;
            
        }
        else
        {
            printf("Invalid answer. Please try again.\n\n");
        }
    }
    
    
    if(userAnswer == 'N' || userAnswer == 'n')
    {
        char newQuestion[200] = {'\0'};
        char newAnimal[200] = {'\0'};
        int newHeight = 0; // new node height;
        
        if(previousNode > currentNode)
        {
            newHeight = previousNode+(currentNode-previousNode)/2;
        }
        else
        {
            
            newHeight = currentNode-(previousNode-currentNode)/2;
        }
        
        printf("You stumped me! I couldn't guess the animal.\nPlease give me a yes or no question to help me figure out your animal.\n>> ");
        scanf("%199[^\n]", newQuestion);
        printf("What is the animal you are thinking of? \n>> ");
        getchar() != '\n';
        scanf("%199[^\n]", newAnimal);
        FILE *writeData = fopen("animal.txt", "a");
        fprintf(writeData, "%s,%d\n", &newQuestion, newHeight);
        fprintf(writeData, "Is it a %s?,%d", &newAnimal, newHeight+(currentNode - newHeight)/2);
        fclose(writeData);
        
        printf("Your question and animal have been added.\n\n");
        printf("Thanks for playing!\n");
    }
    
    if(userAnswer == 'Y' || userAnswer == 'y')
    {
        printf("I guessed your animal! \n");
        printf("Want to play again?\n");
        printf(" >> ");
        scanf("%c", &userAnswer);
        getchar() != '\n';
        printf("\n");
        
        if(userAnswer == 'Y' || userAnswer == 'y')
        {
            printf("\n\n");
            game(animals);
        }
        else
            printf("\n\nGoodbye!");
    }
    
}

int main(int argc, char *argv[])
{
    struct BSTree *animals = newBSTree();
    
    startScreen();
    instructions();
    animalTree(animals);
    game(animals);
    return 0;
}