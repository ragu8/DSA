#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};


struct Node* newNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}


struct Node* insert(struct Node* root, int data) {
    if (root == NULL) {
        return newNode(data);
    }

    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }

    return root;
}


struct Node* findMin(struct Node* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}


struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL) {
        return root;
    }

    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    } else {
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        struct Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }

    return root;
}


struct Node* search(struct Node* root, int key) {
    if (root == NULL || root->data == key) {
        return root;
    }

    if (key < root->data) {
        return search(root->left, key);
    }

    return search(root->right, key);
}


void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}


void preorder(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}


void postorder(struct Node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}


struct Node* lowestCommonAncestor(struct Node* root, int p, int q) {
    if (root == NULL) {
        return NULL;
    }

    if (p < root->data && q < root->data) {
        return lowestCommonAncestor(root->left, p, q);
    } else if (p > root->data && q > root->data) {
        return lowestCommonAncestor(root->right, p, q);
    }

    return root;
}


void bstToArray(struct Node* root, int* arr, int* index) {
    if (root != NULL) {
        bstToArray(root->left, arr, index);
        arr[(*index)++] = root->data;
        bstToArray(root->right, arr, index);
    }
}

int main() {
    struct Node* root = NULL;
    int choice, data, key;

    while (1) {
        printf("\nBinary Search Tree Operations:\n");
        printf("1. Insert\n2. Delete\n3. Search\n4. Find Min\n");
        printf("5. Inorder Traversal\n6. Preorder Traversal\n7. Postorder Traversal\n");
        printf("8. Lowest Common Ancestor\n9. Convert to Sorted Array\n10. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the data to insert: ");
                scanf("%d", &data);
                root = insert(root, data);
                break;
            case 2:
                printf("Enter the key to delete: ");
                scanf("%d", &key);
                root = deleteNode(root, key);
                break;
            case 3:
                printf("Enter the key to search: ");
                scanf("%d", &key);
                if (search(root, key) != NULL) {
                    printf("Key found in the tree.\n");
                } else {
                    printf("Key not found in the tree.\n");
                }
                break;
            case 4:
                if (root == NULL) {
                    printf("The tree is empty.\n");
                } else {
                    struct Node* minNode = findMin(root);
                    printf("Minimum value in the tree: %d\n", minNode->data);
                }
                break;
            case 5:
                printf("Inorder Traversal: ");
                inorder(root);
                printf("\n");
                break;
            case 6:
                printf("Preorder Traversal: ");
                preorder(root);
                printf("\n");
                break;
            case 7:
                printf("Postorder Traversal: ");
                postorder(root);
                printf("\n");
                break;
            case 8:
                printf("Enter the values of two nodes to find their lowest common ancestor: ");
                int p, q;
                scanf("%d %d", &p, &q);
                struct Node* lca = lowestCommonAncestor(root, p, q);
                if (lca != NULL) {
                    printf("Lowest Common Ancestor: %d\n", lca->data);
                } else {
                    printf("Nodes not found in the tree.\n");
                }
                break;
            case 9:
                if (root == NULL) {
                    printf("The tree is empty.\n");
                } else {
                    int arr[100], index = 0;
                    bstToArray(root, arr, &index);
                    printf("Sorted Array: ");
                    for (int i = 0; i < index; i++) {
                        printf("%d ", arr[i]);
                    }
                    printf("\n");
                }
                break;
            case 10:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

