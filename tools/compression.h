typedef struct leaf{
  int value;
  int weight;
  int birthtime;

  struct leaf* lchild;
  struct leaf* rchild;
}LEAF;

typedef struct stacknode{
  struct stacknode* below;
  LEAF *data;
} STACKNODE;

STACKNODE * Stack_push(STACKNODE * t, LEAF *tn);
STACKNODE * Stack_pop(STACKNODE * stk);
void destroyTree(LEAF* tree);
void Stack_show(STACKNODE * top);
void Stack_destruct(STACKNODE * stk);
LEAF * createLeaf(int nodeValue);
