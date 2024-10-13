// Left-Leaning Red-Black Tree
#ifndef RBTREE_H_
#define RBTREE_H_

#define RED 0
#define BLACK 1

typedef struct node_t node_t;
typedef struct node_t* llrb;


llrb* llrb_create();
void llrb_free_node(node_t* node);
void llrb_free(llrb* root);
int llrb_insert(llrb* root, int value);
int llrb_remove(llrb* root, int value);
int llrb_isEmpty(llrb* root);
int llrb_search(llrb* root, int value);
void llrb_preOrder(llrb* root, int H);
void llrb_inOrder(llrb* root, int H);
void llrb_postOrder(llrb* root, int H);

#endif


