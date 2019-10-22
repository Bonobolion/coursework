#include <iostream>

#include "set.h"

using namespace std;

Set union(Set a, Set b) {
  Node *a_ptr = a.getHead();
  Node *b_ptr = b.getHead();
  Set tmp;
  while (a_ptr != NULL) {
    tmp.fill(a_ptr->getData());
    a_ptr = a_ptr->getNext();
  }
  while (b_ptr != NULL) {
    tmp.insert(b_ptr->getData());
    b_ptr = b_ptr->getNext();
  }
  return tmp;
}
Set intersection(Set a, Set b) {
  Set tmp;
  Node *a_ptr = a.getHead();
  while (a_ptr != NULL) {
    if (b.contains(a_ptr->getData())) {
      tmp.fill(a_ptr->getData());
    }
    a_ptr = a_ptr->getNext();
  }
  return tmp;
}
Set difference(Set a, Set b) {
  Node *a_ptr = a.getHead();
  Node *b_ptr = b.getHead();
  Set tmp;
  while (a_ptr != NULL) {
    tmp.fill(a_ptr->getData());
    a_ptr = a_ptr->getNext();
  }
  while (b_ptr != NULL) {
    tmp.remove(b_ptr->getData());
    b_ptr = b_ptr->getNext();
  }
  return tmp;
}
Set symdiff(Set a, Set b) {
  Set tmpA = union(a,b);
  Set tmpB = intersection(a,b);
  return difference(tmpA,tmpB);
}
Set complement(Set a, Set b) {
  Node *a_ptr = a.getHead();
  Node *b_ptr = b.getHead();
  Set tmp;
  while (a_ptr != NULL) {
    tmp.fill(a_ptr->getData());
    a_ptr = a_ptr->getNext();
  }
  while (b_ptr != NULL) {
    tmp.remove(b_ptr->getData());
    b_ptr = b_ptr->getNext();
  }
  return tmp;
}

int main() {
  Set a;
  Set b;
  Set c;
  Set d;
  Set e;
  Set f;
  Set g;
  Set u;
  u.insert("a");
  u.insert("b");
  u.insert("c");
  u.insert("d");
  u.insert("e");
  u.insert("f");

  a.insert("a");
  b.insert("a");
  a.insert("b");
  b.insert("c");
  a.insert("d");
  b.insert("e");
  a.setName("A");
  b.setName("B");
  c.setName("UNION");
  c = union(a,b);
  d.setName("INTERSECT");
  e.setName("DIFFERENCE");
  f.setName("SYMDIFF");
  g.setName("COMPLEMENT");
  d = intersection(a,b);
  e = difference(a,b);
  f = symdiff(a,b);
  g = complement(u,a);

  a.display();
  b.display();
  c.display();
  d.display();
  e.display();
  f.display();
  g.display();
  u.display();

  return EXIT_SUCCESS;
}
