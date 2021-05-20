#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

Tree makeNode(char *label)
{
  struct TreeNode *n = (struct TreeNode *)malloc(sizeof(struct TreeNode));
  n->label = strdup(label);
  n->leftMostChild = NULL;
  n->rightSibling = NULL;
  n->parent = NULL;
  return n;
}

Tree createRoot(char *label)
{
  Tree n = makeNode(label);
  return n;
}

Tree addChild(Tree p, char *label)
{
  Tree n = makeNode(label);
  Tree tmp;

  n->parent = p;
  tmp = p->leftMostChild;

  if (tmp == NULL)
  {
    p->leftMostChild = n;
  }
  else
  {
    while (tmp->rightSibling != NULL)
      tmp = tmp->rightSibling;
    tmp->rightSibling = n;
  }
  return n;
}

Tree find(Tree p, char *label)
{
  Tree tmp, n;

  if (strcmp(p->label, label) == 0)
    return p;
  tmp = p->leftMostChild;
  while (tmp != NULL)
  {
    n = find(tmp, label);
    if (n != NULL)
      return n;
    tmp = tmp->rightSibling;
  }
  return NULL;
}

int height(Tree p)
{
  Tree tmp, n;
  int maxHeight, h;

  if (p->leftMostChild == NULL)
    return 1;
  maxHeight = 0;
  tmp = p->leftMostChild;
  while (tmp != NULL)
  {
    h = height(tmp);
    if (maxHeight < h)
      maxHeight = h;
    tmp = tmp->rightSibling;
  }
  return maxHeight + 1;
}

int size(Tree p)
{
  int s;
  Tree tmp;

  if (p == NULL)
    return 0;
  s = 1;
  tmp = p->leftMostChild;
  while (tmp != NULL)
  {
    s += size(tmp);
    tmp = tmp->rightSibling;
  }
  return s;
}

void pre_order(Tree p, void (*f)(char *label))
{
  Tree tmp;

  if (p == NULL)
    return;
  f(p->label);

  tmp = p->leftMostChild;
  while (tmp != NULL)
  {
    pre_order(tmp, f);
    tmp = tmp->rightSibling;
  }
  return;
}

void post_order(Tree p, void (*f)(char *label))
{
  Tree tmp;

  if (p == NULL)
    return;

  tmp = p->leftMostChild;
  while (tmp != NULL)
  {
    post_order(tmp, f);
    tmp = tmp->rightSibling;
  }

  f(p->label);
  return;
}
