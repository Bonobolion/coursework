#include "ops.h"


void getFile(fstream *file) {
  while (!file->is_open()) {
    string input;
    cout << "Enter valid filename: ";
    cin >> input;
    file->open(input);
  }
}
void parseToSet(string line, Set *list) {
  stringstream strs(line);
  string tok;
  while (getline(strs,tok,',')) {
    list->insert(tok);
  }
}
string extractName(string *str) {
  string sub = str->substr(0,str->find(':'));
  str->erase(0,str->find(':')+1);
  return sub;
}
Set setUnion(Set a, Set b) {
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
  Set tmpA = setUnion(a,b);
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
