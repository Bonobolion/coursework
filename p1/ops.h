#ifndef OPS_H
#define OPS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

#include "set.h"

void getFile(fstream *file);
void parseToSet(string line, Set *list);
string extractName(string *str);
Set setUnion(Set a, Set b);
Set intersection(Set a, Set b);
Set difference(Set a, Set b);
Set symdiff(Set a, Set b);
Set complement(Set u, Set a);

#endif /* OPS_H */
