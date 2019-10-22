#ifndef SET_H
#define SET_H

#include <iostream>

using namespace std;

class Node {
private:
  string data;
  Node *next;
public:
  Node(string);
  void setNext(Node*);
  string getData();
  Node *getNext();
};

class Set {
private:
  Node *head;
  string name;
public:
  Set();
  Node *getHead();
  void setName(string);
  bool insert(string);
  void fill(string);
  void prepend(string);
  bool contains(string);
  bool remove(string);
  void display();
};

#endif /* SET_H */
