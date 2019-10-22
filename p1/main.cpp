/*
 *  Title: p1
 *  Course: csce 2110
 *  Author: Bowen Lyons
 *  Description:
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

#include "set.h"
#include "ops.h"

int main(int argc, char *args[]) {

  string line;
  fstream file;
  vector<Set> tenantV;
  Set items,
      desired,
      atLeastOne,
      moreThanOne,
      exactlyOne,
      missing;
  int tenants = 0;

  if (argc > 1) {
    file.open(args[1]);
    if (!file.is_open()) {
      getFile(&file);
    }
  } else {
    getFile(&file);
  }

  getline(file,line);
  parseToSet(line,&desired);
  while (getline(file,line)) {
    Set fill;
    fill.setName(extractName(&line));
    parseToSet(line,&fill);
    tenantV.push_back(fill);
    tenants++;
  }
  // get list of all items they have
  items = tenantV[0];
  for (int i = 1; i < tenants; i++) {
    items = setUnion(items,tenantV[i]);
  }

  // get list of all items they have at least one of
  atLeastOne = tenantV[0];
  for (int i = 1; i < tenants; i++) {
    atLeastOne = setUnion(atLeastOne,tenantV[i]);
  }

  // get list of all items they have more than one of
  for (int i = 1; i < tenants; i++) {
    Set tmp;
    tmp = intersection(tenantV[i-1],tenantV[i]);
    moreThanOne = setUnion(moreThanOne,tmp);
  }

  // get set of items they have exactly one of
  exactlyOne = difference(atLeastOne,moreThanOne);

  // get list of items they are missing
  missing = symdiff(desired,atLeastOne);

  items.setName("All Items");
  desired.setName("Desired Items");
  atLeastOne.setName("At Least One");
  moreThanOne.setName("More Than One");
  exactlyOne.setName("Exactly One");
  missing.setName("Missing");

  items.display();
  cout << endl;
  for (int i = 0; i != tenantV.size(); i++) {
    tenantV[i].display();
  }
  cout << endl << "-----------------------------------------------------------------------------------------------------" << endl;
  desired.display();
  cout << endl;
  atLeastOne.display();
  moreThanOne.display();
  exactlyOne.display();
  missing.display();

  return EXIT_SUCCESS;
}
