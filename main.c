#include <stdio.h>
#include <stdlib.h>

#define MAX_TREE_HT 50

struct HuffmanTreeNode{
    char data;

    unsigned freq;

    struct HuffmanTreeNode *left, *right;
}; 
typedef struct HuffmanTreeNode TreeNode;

struct HuffmanTreeNodes {
    unsigned size;

    unsigned capacity;

    TreeNode** array;

    
};
typedef struct HuffmanTreeNodes TreeNodes;
