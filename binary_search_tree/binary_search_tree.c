#include <stdio.h>
#include <stdlib.h>

typedef struct node_t {
  int value;
  struct node_t *left;
  struct node_t *right;
} node_t;

struct node_t *bst_node(int value) {
  node_t *node = (node_t *)malloc(sizeof(node_t)*1);
  node->value = value;
  node->left = NULL;
  node->right = NULL;
  return node;
}

node_t *bst_create() {
  return NULL;
}

node_t *bst_insertion(node_t *root, int value) {

  if (root == NULL) {
    // Root case
    root = bst_node(value);
  } else if (value < (root->value)) {
    // Left side
    if (root->left == NULL) {
      root->left = bst_node(value);
    } else {
      bst_insertion(root->left, value);
    }
  } else {
    // Right side
    if (root->right == NULL) {
      root->right = bst_node(value);
    } else {
      bst_insertion(root->right, value);
    }
  }

  return root;
}

node_t *bst_search(node_t *root, int value) {

  if (root == NULL) {
    return NULL;
  } 

  if (value == root->value) {
    return root;
  } else if (value < root->value){
    return bst_search(root->left, value);
  } else {
    return bst_search(root->right, value);
  }
}

node_t *bst_sucessor(node_t *root, int value) {

  node_t *curr = root->right;

  while (curr != NULL && curr->left != NULL) {
    curr = curr->left;
  }

  return curr;
}

node_t *bst_delete(node_t *root, int value) {

  if (root == NULL) {
    return NULL;
  }
  
  if (value < (root->value)) {
    root->left = bst_delete(root->left, value);
  } else if (value > (root->value)){
    root->right = bst_delete(root->right, value);
  } else {

    // If is Leaf
    if (root->left == NULL && root->right == NULL) {
      free(root);
      return NULL;
    }

    // If has only left child
    if (root->left != NULL && root->right == NULL) {
      node_t *temp = root->left;
      free(root);
      return temp;
    }

    // If has only right child
    if (root->left == NULL && root->right != NULL) {
      node_t *temp = root->right;
      free(root);
      return temp;
    }
    
    // If has two children
    node_t *succ = bst_sucessor(root, value);
    root->value = succ->value;
    root->right = bst_delete(root->right, succ->value);
  }

  return root;
}

void inOrder_traversal(node_t *root) {
  if (root == NULL) {
    return;
  }

  inOrder_traversal(root->left);
  printf("%d ", root->value);
  inOrder_traversal(root->right); 
}

void preOrder_traversal(node_t *root) {
  if (root == NULL) {
    return;
  }

  printf("%d ", root->value);
  preOrder_traversal(root->left);
  preOrder_traversal(root->right); 
}

void postOrder_traversal(node_t *root) {
  if (root == NULL) {
    return;
  }

  postOrder_traversal(root->left); 
  postOrder_traversal(root->right);
  printf("%d ", root->value);
}

int main(void) {
  node_t *root = bst_create();
  
  root = bst_insertion(root, 20);
  root = bst_insertion(root, 13);
  root = bst_insertion(root, 17);
  root = bst_insertion(root, 8);
  root = bst_insertion(root, 38);
  root = bst_insertion(root, 25);
  root = bst_insertion(root, 56);

  /*             20
   *            /  \
   *          13   38
   *          /\   /\
   *         8 17 25  56
  */

  inOrder_traversal(root);

  node_t *found;
  found = bst_search(root, 40);
  if (found == NULL) {
    printf("Not found!\n");
  } else {
    printf("FOUND: %d\n", found->value);
  }

  root = bst_delete(root, 38);

  /*             20
   *            /  \
   *          13   56
   *          /\   /\
   *         8 17 25
  */

  inOrder_traversal(root);
  printf("\n");

  /*             20
   *            /  \
   *          13   56
   *          /\   /\
   *         8 17 25
  */

  root = bst_delete(root, 56);

  /*             20
   *            /  \
   *          13   25
   *          /\   
   *         8 17 
  */

  inOrder_traversal(root);
  printf("\n");

  root = bst_delete(root, 17);
  root = bst_delete(root, 8);

  /*             20
   *            /  \
   *          13   25
  */

  inOrder_traversal(root);
  return 0;
}
