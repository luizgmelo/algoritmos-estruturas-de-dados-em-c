#include <stdio.h>
#include <stdlib.h>
#include "llrb.c"

typedef struct node_t {
  int value;
  struct node_t *left;
  struct node_t *right;
  int color;
} node_t;

llrb* llrb_create() {
  llrb* root = (llrb *)malloc(sizeof(llrb));
  if (root != NULL) {
    *root = NULL;
  }
  return root;
}

void llrb_free_node(struct node_t* node) {
  if (node == NULL) {
    return;
  }
  llrb_free_node(node->left);
  llrb_free_node(node->right);
  free(node);
  node = NULL;
}

void llrb_free(llrb* root) {
  if (root == NULL) {
    return;
  }
  llrb_free_node(*root);
  free(root);
}

// Properties
int color(struct node_t* node) {
  if (node == NULL) {
    return BLACK; // Black
  }
  return node->color; // Red
}

void changeColor(struct node_t* node) {
  node->color = !node->color;
  if (node->left != NULL) {
    node->left->color = !node->left->color;
  }
  if (node->right != NULL) {
    node->right->color = !node->right->color;
  }
}

// Rotations

// Left-rotation
struct node_t* rotateLeft(struct node_t* A) {
  struct node_t* B = A->right;
  A->right = B->left;
  B->left = A;
  B->color = A->color;
  A->color = RED;
  return B;
}

// Right-rotation
struct node_t* rotateRight(struct node_t* A) {
  struct node_t* B = A->left;
  A->left = B->right;
  B->right = A;
  B->color = A->color;
  A->color = RED;
  return B;
}

// =================================
// INSERTION 
// =================================

struct node_t* insert_node(node_t *root, int value, int *resp) {
  if (root == NULL) {
    struct node_t* new = (struct node_t *)malloc(sizeof(struct node_t));
    if (new == NULL) {
      *resp = 0;
      return NULL;
    }
    
    new->value = value;
    new->color = RED;
    new->left = NULL;
    new->right = NULL;
    *resp = 1;
    return new;
  }

  if (value == root->value) {
    //duplicated value
    *resp = 0;
  } else {
    if (value < root->value) {
      root->left = insert_node(root->left, value, resp);
    } else {
      root->right = insert_node(root->right, value, resp);
    }
  }
    
  // Balance

  // Red node is always left child
  if (color(root->right) == RED && color(root->left) == BLACK) {
    root = rotateLeft(root);
  }

  //Filho e Neto são vermelhos
  //Filho vira pai de 2 nós vermelhos
  if (color(root->left) == RED && color(root->left->left) == RED) {
    root = rotateRight(root);
  }

  // Two children red
  if (color(root->left) == RED && color(root->right) == RED) {
    changeColor(root);
  }

  return root;
}

// =================================
// SEARCH VALUE 
// =================================
int llrb_search(llrb* root, int value) {
  if (root == NULL) {
    return 0;
  }
  struct node_t* current = *root;
  while (current != NULL) {
    if (value == current->value) {
      return 1;
    } else {
      if (value < current->value) {
        current = current->left;
      } else {
        current = current->right;
      }
    }
  }
  return 0;
}

int llrb_insert(llrb* root, int value) {
  int resp;

  *root = insert_node(*root,value,&resp);
  if ((*root) != NULL) {
    (*root)->color = BLACK;
  }

  return resp;
}

// =================================
// REMOVE 
// =================================
struct node_t* balance(struct node_t* node) {
  // Red node is always left child
  if (color(node->right) == RED) {
    node = rotateLeft(node);
  }

  //Filho e Neto são vermelhos
  //Filho vira pai de 2 nós vermelhos
  if (color(node->left) == RED && color(node->left->left) == RED) {
    node = rotateRight(node);
  }

  // Two children red
  if (color(node->left) == RED && color(node->right) == RED) {
    changeColor(node);
  }
  
  return node;
}

struct node_t* move2LeftRed(struct node_t* node) {
  changeColor(node);
  if(color(node->right->left) == RED) {
    node->right = rotateRight(node->right);
    node = rotateLeft(node);
    changeColor(node);
  }
  return node;
}

struct node_t* move2RightRed(struct node_t* node) {
  changeColor(node);
  if(color(node->left->left) == RED) {
    node = rotateRight(node);
    changeColor(node);
  }
  return node;
}

struct node_t* findMin(node_t* node) {
  node_t *prev = node;
  node_t *current = node->left;
  while (current != NULL) {
    prev = current;
    current = current->left;
  }
  return prev;
}

struct node_t* removeMin(node_t* node) {
  if (node->left == NULL) {
    free(node);
    return NULL;
  }
  if (color(node->left) == BLACK && color(node->left->left) == BLACK) {
    node = move2LeftRed(node);
  }

  node->left = removeMin(node->left);
  return balance(node);
};

struct node_t* removeNode(node_t* node, int value) {
  if (value < node->value) {
    if (color(node->left) == BLACK && color(node->left->left) == BLACK) {
      node = move2LeftRed(node);
    }

    node->left = removeNode(node->left, value);
  } else {
    if (color(node->left) == RED) {
      node = rotateRight(node);
    }

    if (value == node->value && (node->right == NULL)) {
      free(node);
      return NULL;
    }

    if (color(node->right) == BLACK &&  color(node->right->left) == BLACK) {
      node = move2RightRed(node);
    }

    if (value == node->value) {
      struct node_t* x = findMin(node->right);
      node->value = x->value;
      node->right = removeMin(node->right);
    } else {
      node->right = removeNode(node->right, value);
    }
  }
  return balance(node);
};

int llrb_remove(llrb *root, int value) {
  if (llrb_search(root, value)) {
    struct node_t* h = *root;
    *root = removeNode(h, value);
    if (*root != NULL) {
      (*root)->color = BLACK;
    }
    return 1;
  } else {
    return 0;
  }
}

void llrb_inOrder(llrb* root, int H) {
  if (root == NULL) {
    return;
  }

  if (*root != NULL) {
    llrb_inOrder(&((*root)->left), H+1);

    if ((*root)->color == RED) {
      printf("%dR: H(%d) \n",(*root)->value,H);
    } else {
      printf("%dB: H(%d) \n",(*root)->value,H);
    }

    llrb_inOrder(&((*root)->right), H+1);
  }
}

int main() {

  llrb *root = llrb_create(); 

  llrb_insert(root, 2);
  llrb_insert(root, 28);
  llrb_insert(root, 14);
  llrb_insert(root, 48);
  llrb_insert(root, 32);


  llrb_inOrder(root, 0);


  return 0;
}
