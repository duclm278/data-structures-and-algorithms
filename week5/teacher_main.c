#include <stdio.h>
#include <string.h>
#include "tree.h"

char s[100];

void func(char *l)
{
  strcat(s, l);
  strcat(s, ", ");
}

int main()
{
  Tree t = createRoot("a");
  Tree b = addChild(t, "b");
  Tree c = addChild(t, "c");
  Tree d = addChild(t, "d");
  Tree e = addChild(b, "e");
  Tree f = addChild(c, "f");
  Tree g = addChild(c, "g");

  printf("h = %d\n", height(t));
  printf("size = %d\n", size(t));

  strcpy(s, "");
  pre_order(t, func);
  printf("%s\n", s);

  return 0;
}
