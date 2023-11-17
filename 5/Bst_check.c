#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};


struct TreeNode* newNode(int data) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}


bool isBST(struct TreeNode* root, struct TreeNode* prev) {

    if (root == NULL) {
        return true;
    }


    if (!isBST(root->left, prev)) {
        return false;
    }


    if (prev != NULL && root->data <= prev->data) {
        return false;
    }


    prev = root;


    return isBST(root->right, prev);
}

int main() {

    struct TreeNode* root = newNode(2);
    root->left = newNode(1);
    root->right = newNode(3);


    bool validBST = isBST(root, NULL);

    if (validBST) {
        printf("The given tree is a valid BST.\n");
    } else {
        printf("The given tree is not a valid BST.\n");
    }

    return 0;
}

