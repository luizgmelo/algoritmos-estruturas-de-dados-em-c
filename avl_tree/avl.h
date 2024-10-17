
typedef struct NODE* AVL;

AVL* create_avl();
void free_avl(AVL* root);
int avl_insert(AVL* root, int value);
int avl_remove(AVL* root, int value);
int avl_isEmpty(AVL *root);
int avl_height(AVL *root);
void avl_preOrder(AVL *root);
void avl_inOrder(AVL *root);
void avl_postOrder(AVL *root);
