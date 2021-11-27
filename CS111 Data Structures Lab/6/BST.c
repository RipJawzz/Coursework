/* 
 * File:   main.c
 * Author: Lenovo
 *
 * Created on February 1, 2019, 8:05 PM
 */

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int key; 
    //sat. data
    struct Node *left;
    struct Node *right; 
    struct Node *parent; 
}; 

// A utility function to create a new BST node 
struct Node *createNewNode(int data) { 
    struct Node *newNode =  (struct Node *)malloc(sizeof(struct Node)); 
    newNode->key = data; 
    newNode->left = NULL; 
    newNode->right = NULL;
    newNode->parent = NULL;
    return newNode; 
} 

// C function to search a given key in a given BST 
struct Node* search(struct Node* node, int key)  {
    // Base Cases: root is null or key is present at root 
    if (node == NULL || node->key == key) 
       return node; 
     
    // Key is greater than root's key 
    if (node->key < key) 
       return search(node->right, key); 
  
    // Key is smaller than root's key 
    return search(node->left, key); 
} 

/* Given a binary tree, print its nodes according to the 
  "bottom-up" postorder traversal. */
void printPostorder(struct Node* node) {
     if (node == NULL) 
        return; 
  
     // first recur on left subtree 
     printPostorder(node->left); 
  
     // then recur on right subtree 
     printPostorder(node->right); 
  
     // now deal with the node 
     printf("%d ", node->key); 
} 
  
/* Given a binary tree, print its nodes in inorder*/
void printInorder(struct Node* node) { 
     if (node == NULL) 
          return; 
  
     /* first recur on left child */
     printInorder(node->left); 
  
     /* then print the data of node */
     printf("%d ", node->key);   
  
     /* now recur on right child */
     printInorder(node->right); 
} 
  
/* Given a binary tree, print its nodes in preorder*/
void printPreorder(struct Node* node) { 
     if (node == NULL) 
          return; 
  
     /* first print data of node */
     printf("%d ", node->key);   
  
     /* then recur on left subtree */
     printPreorder(node->left);   
  
     /* now recur on right subtree */
     printPreorder(node->right); 
}     
  
/* Given a non-empty binary search tree, return the minimum data value found in that  
tree. Note that the entire tree does not need to be searched. */
struct Node* findMinIterative(struct Node* node) { 
    if(node == NULL) {
        return node;
    }
    /* loop down to find the leftmost node */
    while(node->left != NULL) {
        node = node->left;
    }
    return node;
}


struct Node* findMinRecursive(struct Node* node) {
/*
    if(node == NULL || node->left == NULL)
        return node;
*/
    if(node == NULL) {
        return node;
    }
    if(node->left == NULL) {
        return node;
    }
    return findMinRecursive(node->left);
}


// Function to find the node with maximum value i.e. rightmost leaf node 
struct Node* findMaxIterative(struct Node* node) { 
    if(node == NULL) {
        return node;
    }
    /* loop down to find the rightmost node */
    while(node->right != NULL) {
        node = node->right;
    }
    return node;
}


struct Node* findMaxRecursive(struct Node* node) { 
/*
    if(node == NULL || node->right == NULL) {
        return node;
    }
*/
    if(node == NULL) {
        return node;
    }
    if(node->right == NULL) {
        return node;
    }    
    return findMaxRecursive(node->right);
}


struct Node* inOrderSuccessor(struct Node *node)  {
    if(node == NULL) {
        return node;
    }
    if( node->right != NULL ) {
        return findMinRecursive(node->right);
    }
    struct Node *p = node->parent; 
    while(p != NULL && node == p->right)  {
        node = p; 
        p = p->parent; 
    } 
    return p; 
} 


struct Node* inOrderSuccessorTopDown(struct Node* root, struct Node* node) {
    if( node->right != NULL )
        return findMinRecursive(node->right);
 
    struct Node *successor = NULL;
 
    while (root != NULL) {
        if (node->key < root->key) {
            successor = root;
            root = root->left;
        }
        else if (node->key > root->key)
            root = root->right;
        else
           break;
    }
    return successor;
}


struct Node* inOrderPredecessor(struct Node* node) {
    if(node == NULL) {
        return node;
    }
    if(node->left != NULL ) {
        return findMaxRecursive(node->left);
    }
    struct Node* p = node->parent;
    while(p !=NULL && node == p->left) {
        node = p;
        p = p->parent;
    }
    return p; 
}

struct Node* inOrderPredecessorTopDown(struct Node* root, struct Node* node) {
    if( node->left != NULL )
        return findMaxRecursive(node->left);
  
    struct Node *predecessor = NULL;
  
    while (root != NULL) {
        if (node->key > root->key) {
            predecessor = root;
            root = root->right;
        }
        else if (node->key < root->key)
            root = root->left;
        else
           break;
    }
    return predecessor;
}

/* A utility function to insert a new node with given key in BST */
struct Node* insertWithParent(struct Node* node, int key) 
{ 
    /* If the tree is empty, return a new node */
    if (node == NULL) {
        return createNewNode(key); 
    }
  
    /* Otherwise, recur down the tree */
    if (key < node->key) {
        struct Node *lchild = insertWithParent(node->left, key); 
        node->left = lchild; 
        // Set parent of root of left subtree 
        lchild->parent = node; 
    }
    else if (key > node->key) {
        struct Node *rchild = insertWithParent(node->right, key); 
        node->right = rchild; 
        // Set parent of root of right subtree 
        rchild->parent = node; 
    }
  
    /* return the (unchanged) node pointer */
    return node; 
} 

/* Given a binary search tree and a key, this function deletes the key 
   and returns the new root */
struct Node* deleteWithParent(struct Node* node, int key) {
    // base case 
    if (node == NULL) {
        return node;
    }
  
    // If the key to be deleted is smaller than the root's key, 
    // then it lies in left subtree 
    if (key < node->key) {
        node->left = deleteWithParent(node->left, key); 
    }
  
    // If the key to be deleted is greater than the root's key, 
    // then it lies in right subtree 
    else if (key > node->key) {
        node->right = deleteWithParent(node->right, key); 
    }
  
    // if key is same as root's key, then This is the node 
    // to be deleted 
    else { 
        // node with only one child or no child 
        if (node->left == NULL)  {
            struct Node *temp = node->right; 
            free(node); 
            return temp; 
        } 
        else if (node->right == NULL) {
            struct Node *temp = node->left; 
            free(node); 
            return temp; 
        } 
  
        // node with two children: Get the inorder successor (smallest 
        // in the right subtree) 
        struct Node* temp = findMinRecursive(node->right); 
  
        // Copy the inorder successor's content to this node 
        node->key = temp->key; 
  
        // Delete the inorder successor 
        node->right = deleteWithParent(node->right, temp->key); 
    } 
    return node; 
} 


/* A utility function to insert a new node with given key in BST */
struct Node* insert(struct Node* node, int key) 
{ 
    /* If the tree is empty, return a new node */
    if (node == NULL) {
        return createNewNode(key); 
    }
  
    /* Otherwise, recur down the tree */
    if (key < node->key) {
        node->left = insert(node->left, key);
    }
    else if (key > node->key) {
        node->right = insert(node->right, key);
    }
  
    /* return the (unchanged) node pointer */
    return node; 
} 


/* Given a binary search tree and a key, this function deletes the key 
   and returns the new root */
struct Node* delete(struct Node* node, int key) {
    // base case 
    if (node == NULL) {
        return node;
    }
  
    // If the key to be deleted is smaller than the root's key, 
    // then it lies in left subtree 
    if (key < node->key) {
        node->left = delete(node->left, key); 
    }
  
    // If the key to be deleted is greater than the root's key, 
    // then it lies in right subtree 
    else if (key > node->key) {
        node->right = delete(node->right, key); 
    }
  
    // if key is same as root's key, then This is the node 
    // to be deleted 
    else { 
        // node with only one child or no child 
        if (node->left == NULL)  {
            struct Node *temp = node->right; 
            free(node); 
            return temp; 
        } 
        else if (node->right == NULL) {
            struct Node *temp = node->left; 
            free(node); 
            return temp; 
        } 
  
        // node with two children: Get the inorder successor (smallest 
        // in the right subtree) 
        struct Node* temp = findMinRecursive(node->right); 
  
        // Copy the inorder successor's content to this node 
        node->key = temp->key; 
  
        // Delete the inorder successor 
        node->right = delete(node->right, temp->key); 
    } 
    return node; 
} 

/*
 * 
 */
int main(int argc, char** argv) {
    struct Node *root = NULL; 
/*
    root = insertWithParent(root, 50); 
    root = insertWithParent(root, 30); 
    root = insertWithParent(root, 20); 
    root = insertWithParent(root, 40); 
    root = insertWithParent(root, 70); 
    root = insertWithParent(root, 60); 
    root = insertWithParent(root, 80);
*/
    
    struct Node *node;
    node = findMinRecursive(root);
    if(node == NULL) {
        printf("There is no minimum element as the tree is NULL!\n");
    } else {
        printf("The minimum element is: %d\n", node->key);
    }
    
    
    // print inoder traversal of the BST 
    printf("\nInorder traversal of BST is as follows....\n");
    printInorder(root); 
    printf("\nPreorder traversal of BST is as follows....\n");
    printPreorder(root); 
    printf("\nPostorder traversal of BST is as follows....\n");
    printPostorder(root); 
    
    
    
    /* SEARCH PROCEDURE */
    int element;
    printf("\nEnter the element which you want to search: ");
    scanf("%d",&element);  
    node = search(root, element); 
    if(node == NULL) {
        printf("The element is not present!\n");
    } else {
        printf("The element is present!\n");
    }
    
    
    /* FIND MINIMUM */
    node = findMinIterative(root);
    if(node == NULL) {
        printf("There is no minimum element as the tree is NULL!\n");
    } else {
        printf("The minimum element is: %d\n", node->key);
    }
    
    node = findMinRecursive(root);
    if(node == NULL) {
        printf("There is no minimum element as the tree is NULL!\n");
    } else {
        printf("The minimum element is: %d\n", node->key);
    }
    
    /* FIND MAXIMUM */
    node = findMaxIterative(root);
    if(node == NULL) {
        printf("There is no maximum element as the tree is NULL!\n");
    } else {
        printf("The maximum element is: %d\n", node->key);
    }
    
    node = findMaxRecursive(root);
    if(node == NULL) {
        printf("There is no maximum element as the tree is NULL!\n");
    } else {
        printf("The maximum element is: %d\n", node->key);
    }
    
    
    
    printf("\nEnter the element whose inorder successor you want to find: ");
    scanf("%d",&element);  
    node = search(root, element); 
    if(node == NULL) {
        printf("The element is not present! So Inorder successor is not possible!\n");
    } else {
        struct Node *succ =  inOrderSuccessor(node); 
        if(succ ==  NULL) {
            printf("Inorder successor doesn't exit\n"); 
        } else {
            printf("Inorder successor of %d is %d \n", node->key, succ->key);     
        }
    }
    
    
    printf("\nEnter the element whose inorder predecessor you want to find: ");
    scanf("%d",&element);  
    node = search(root, element); 
    if(node == NULL) {
        printf("The element is not present! So Inorder predecessor is not possible!\n");
    } else {
        struct Node *prec =  inOrderPredecessor(node); 
        if(prec ==  NULL) {
            printf("Inorder predecessor doesn't exit\n"); 
        } else {
            printf("Inorder predecessor of %d is %d \n", node->key, prec->key);     
        }
    }

    return (EXIT_SUCCESS);
}

