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

int sizeIsOne(TreeNodes* treeNodes){
    return (treeNodes->size == 1);
}

TreeNode* extractMin(TreeNodes* treeNodes){

    TreeNode* temp = treeNodes->array[0];
    treeNodes->array[0] = treeNodes->array[treeNodes->size - 1];

    treeNodes->size--;
    smallestNode(treeNodes, 0);

    return temp;
}

void instertNewNode(TreeNodes* treeNodes, TreeNode* treeNode){
    
    treeNodes->size++;
    int i = treeNodes->size - 1;

    while (i && treeNode->freq < treeNodes->array[(i -1 )/ 2]->freq){
        treeNodes->array[i] = treeNodes->array[(i - 1)/ 2];
        i = (i - 1) / 2;
    }

    treeNodes->array[i] = treeNode;
}

void buildNode(TreeNodes* treeNodes){
    
    int n = treeNodes->size - 1;
    int i;

    for (i = (n - 1) / 2; i >= 0; i--){
       smallestNode(treeNodes, i) ;
    }
}

void printArray(int arr[], int n){
    int i; 
    for (i = 0; i < n; i++){
        printf("%d", arr[i]);
    }

    printf("\n");
}

int checkLeaf(TreeNode* root){
    return !(root->left) && !(root->right);
}

TreeNodes* createNBuildNode(char data[], int freq[], int size){
    TreeNodes* treeNodes = createTreeNodes(size);

    int i;

    for (i = 0; i < size; i++){
        treeNodes->array[i] = newNode(data[i], freq[i]);
    }

    treeNodes->size = size;
    buildNode(treeNodes);

    return treeNodes;
}

TreeNode* createHuffTree(char data[], int freq[], int size){
    TreeNode *left, *right, *top;

    TreeNodes* treeNodes = createNBuildNode(data, freq, size);

    while (!sizeIsOne(treeNodes)){
        left = extractMin(treeNodes);
        right = extractMin(treeNodes);

        top = newNode('$', left->freq, right->freq);

        top->left = left;
        top->right = right;

        instertNewNode(treeNodes, top);
    }

    return extractMin(treeNodes);
}

void printCodes(TreeNode* root, int arr[], int top){
    if (root->left) {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }

    if (root->right){
        arr[top] = 1;
        printCodes(root->right,arr, top + 1);
    }

    if (checkLeaf(root)){
        printf("%c: ", root->data);
        printArray(arr, top);
    }


}
