#include "set.h"

Node::Node(string newData) {
  data = newData;
  next = NULL;
}
void Node::setNext(Node *n) {
  next = n;
}
string Node::getData() {
  return data;
}
Node *Node::getNext() {
  return next;
}

Set::Set() {
  head = NULL;
  name = "NO_NAME";
}
Node *Set::getHead() {
  return head;
}
void Set::setName(string newName) {
  name = newName;
}
bool Set::insert(string newData) {
  if (this->contains(newData)) {
    return false;
  }
  this->prepend(newData);
  return true;
}
void Set::fill(string newData) {
  this->prepend(newData);
}
void Set::prepend(string x) {
  Node *y = new Node(x);
  y->setNext(head);
  head = y;
}
bool Set::contains(string x) {
  Node *y = head;
  while (y != NULL) {
    if (y->getData() == x) {
      return true;
    }
    y = y->getNext();
  }
  return false;
}
bool Set::remove(string newData) {
  if (head->getData() == newData) {
    head = NULL;
    return true;
  }
  Node *z = head;
  Node *y = head->getNext();
  while (y != NULL) {
    if (y->getData() == newData) {
      z->setNext(y->getNext());
      return true;
    }
    z = y;
    y = y->getNext();
  }
  return false;
}
void Set::display() {
  cout << name << ":\t{ ";
  Node *y = head;
  while (y != NULL) {
    cout << y->getData();
    y = y->getNext();
    if (y != NULL) {
      cout << ", ";
    }
  }
  cout << " }\n";
}
