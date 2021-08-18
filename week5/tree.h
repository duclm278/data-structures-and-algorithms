#ifndef __TREE_H__
#define __TREE_H__

struct TreeNode
{
  char *label;
  struct TreeNode *leftMostChild;
  struct TreeNode *rightSibling;
  struct TreeNode *parent;
};

typedef struct TreeNode *Tree;

Tree createRoot(char *label);
Tree addChild(Tree p, char *label);

Tree find(Tree p, char *label);

int height(Tree p);
int size(Tree p);

void pre_order(Tree p, void (*f)(char *label));

#endif
