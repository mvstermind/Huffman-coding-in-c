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


TreeNode* newNode(char data, unsigned freq){
    TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));

    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;

    return temp;
};

TreeNodes* createTreeNodes(unsigned capacity){
    TreeNodes* treeNodes = (TreeNodes*)malloc(sizeof(TreeNodes));

    treeNodes->size = 0;
    treeNodes->capacity = capacity;
    treeNodes->array = (TreeNode**)malloc(
        treeNodes->capacity * sizeof(TreeNode*));

    return treeNodes;
}


void swapNodes(TreeNode** a, TreeNode** b){
    TreeNode* t = *a;
    *a = *b;
    *b = t;
}

void smallestNode(TreeNodes* treeNode, int idx){
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < treeNode->size && treeNode->array[left]->freq){
        smallest = left;
    }

    if (right < treeNode->size && treeNode->array[right]->freq 
        < treeNode->array[smallest]->freq){
            smallest = right;
    }

    if (smallest != idx){
        swapNodes(&treeNode->array[smallest], &treeNode->array[idx]);
        smallestNode(treeNode, smallest);
    }

}
