#include "stdio.h"
#include "stdlib.h"
#include "avl.h"

typedef struct NODE {
  int value;
  int height;
  struct NODE *left;
  struct NODE *right;
} NODE;

AVL* create_avl() {
  AVL* root = (AVL *)malloc(sizeof(AVL));
  if (root != NULL) {
    *root = NULL;
  }
  return root;
}

void free_node(struct NODE* node) {
  if (node == NULL) {
    return;
  }
  free_node(node->left);
  free_node(node->right);
  free(node);
  node = NULL;
}

void free_avl(AVL *root) {
  if (root == NULL) {
    return;
  }
  free_node(*root);
  free(root);
}

int node_height(struct NODE* node) { 
  if (node == NULL) {
    return -1;
  }

  return node->height;
}

int balance_factor(struct NODE* node) {
  return labs(node_height(node->left) - node_height(node->right));
}

int max(int x, int y) {
  if (x > y) {
    return x;
  } else {
    return y;
  }
}

int avl_isEmpty(AVL* root) {
  if (root == NULL) {
    return 1;
  }
  if (*root == NULL) {
    return 1;
  }
  return 0;
}

int totalNodeAVL(AVL* root) {
  if (root == NULL) {
    return 0;
  }
  if (*root == NULL) {
    return 0;
  }
  int left_height = totalNodeAVL(&((*root)->left));
  int right_height = totalNodeAVL(&((*root)->right));
  return(left_height + right_height + 1);
}

int avl_height(AVL *root) {
  if (root == NULL) {
    return 0;
  }
  if (*root == NULL) {
    return 0;
  }
  int left_height = avl_height(&((*root)->left));
  int right_height = avl_height(&((*root)->right));
  if (left_height > right_height) {
    return (left_height + 1);
  }
  return (right_height + 1);
}

void avl_preOrder(AVL* root) {
  if (root == NULL) {
    return;
  }
  if (*root == NULL) {
    return;
  }
  printf("NO %d; H(%d); FB(%d)\n", (*root)->value, (*root)->height, balance_factor(*root));
  avl_preOrder(&((*root)->left));
  avl_preOrder(&((*root)->right));
}

void leftRotation(AVL* A) { //RR
  struct NODE* B;
  B = (*A)->right;
  (*A)->right = B->left;
  B->left = *A;
  (*A)->height = max(node_height((*A)->left), node_height((*A)->right)) + 1;
  B->height = max(node_height(B->left), node_height(B->right)) + 1;
  (*A) = B;
}

void rightRotation(AVL* A) { //LL
  struct NODE* B;
  B = (*A)->left;
  (*A)->left = B->right;
  B->right = *A;
  (*A)->height = max(node_height((*A)->left), node_height((*A)->right)) + 1;
  B->height = max(node_height(B->left), node_height(B->right)) + 1;
  (*A) = B;
}

void leftRightRotation(AVL* A) { //RL
  leftRotation(&((*A)->left));
  rightRotation(A);
}

void rightLeftRotation(AVL* A) { //LR
  rightRotation(&((*A)->right));
  leftRotation(A);
}

int avl_insert(AVL* root, int value) {
  int res;
  if (*root == NULL) {
    NODE* new = (NODE *)malloc(sizeof(NODE));
    
    if (new == NULL) {
      return 0;
    }

    new->value = value;
    new->height = 0;
    new->left = NULL;
    new->right = NULL;
    *root = new;
    return 1;
  }

  if ((*root)->value > value) {
    // left side
    if ((res=(avl_insert(&((*root)->left), value))) == 1) { 
      if (balance_factor(*root) >= 2) {
        if ((*root)->left->value > value) {
          // LL case
          rightRotation(root);
        } else {
          // LR
          leftRightRotation(root);
        }
      }
    }
  } else if ((*root)->value < value) {
    // right side
    if ((res=(avl_insert(&((*root)->right), value))) == 1) {
      if (balance_factor(*root) >= 2) {
        if ((*root)->right->value < value) {
          leftRotation(root);
        } else {
          rightLeftRotation(root);
        }
      }
    }
  } else {
    printf("Valor duplicado\n");
    return 0;
  }

  (*root)->height = max(node_height((*root)->left), node_height((*root)->right)) + 1;

  return res;
}

struct NODE* sucessor(struct NODE* node) {
  struct NODE* no1 = node;
  struct NODE* no2 = node->left;
  while (no2 != NULL) {
    no1 = no2;
    no2 = no2->left;
  }
  return no1;
}

int avl_remove(AVL* root, int value) {
  if (*root == NULL) {
    return 0;
  }

  int res;
  if ((*root)->value > value) {
    if((res=avl_remove(&((*root)->left), value)) == 1) {
      if (balance_factor(*root) >= 2) {
        if (node_height((*root)->right->left) <= node_height((*root)->right->right)) {
          leftRotation(root);
        } else {
          rightLeftRotation(root);
        }
      }
    }
  } else if ((*root)->value < value) {
    if((res=avl_remove(&((*root)->right),value)) == 1) {
      if (balance_factor(*root) >= 2) {
        if (node_height((*root)->left->right) <= node_height((*root)->left->left)) {
          rightRotation(root);
        } else {
          leftRightRotation(root);
        }
      }
    }
  } else {
    // found
    //

    // one child or leaf
    if ((*root)->left == NULL || (*root)->right == NULL) {
      struct NODE* oldNode = (*root);
      if ((*root)->left != NULL) {
        *root = (*root)->left;
      } else {
        *root = (*root)->right;
      }
      free(oldNode);
    } else {
      // two children
      NODE* succ;
      succ = sucessor((*root)->right);
      (*root)->value = succ->value;
      avl_remove(&((*root)->right), (*root)->value);
      if (balance_factor(*root) >= 2) {
        if (node_height((*root)->left->right) <= node_height((*root)->left->left)) {
          rightRotation(root);
        } else {
          leftRightRotation(root);
        }
      }
    }

    if (*root != NULL) {
      (*root)->height = max(node_height((*root)->left), node_height((*root)->right)) + 1;
    }

    return 1;
  }

  (*root)->height = max(node_height((*root)->left), node_height((*root)->right)) + 1;
  return res;
}



int main() {
  AVL* avl;
  int res,i;
  int N = 10, data[10] = {1,2,3,10,4,5,9,7,8,6};

  avl = create_avl();

  for(i=0;i<N;i++){
      res = avl_insert(avl,data[i]);
  }

  printf("\nAVL tree:\n");
  avl_preOrder(avl);
  printf("\n\n");

  avl_remove(avl, 6);
  printf("\nAVL tree:\n");
  avl_preOrder(avl);
  printf("\n\n");

  avl_remove(avl, 7);
  printf("\nAVL tree:\n");
  avl_preOrder(avl);
  printf("\n\n");

  avl_remove(avl, 10);
  printf("\nAVL tree:\n");
  avl_preOrder(avl);
  printf("\n\n");

  free_avl(avl);

  return 0;
}
