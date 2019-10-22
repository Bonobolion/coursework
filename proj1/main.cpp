/*
  Name: Bowen Lyons
  Class: CSCE 3110
  Due: 11:59pm on May 29, 2019
  Purpose: Write a complete C++ program to implement multiplication operations
    and perform an analysis with respect to theoretical and experimental
    runtime complexity.
*/

#include <iostream>
#include <chrono>
#include <unistd.h>

using namespace std;

#define MAXINT 2147483647

int multiply(int,int);
int bitMultiply(int,int);
string binstr(int);
void printNums(int,int,int);
void isOverflow(int);

int main(int argc, char *args[]) {

  int input1   = -1,
      input2   = -1,
      result;

  long int sAvg = 0,
           nAvg = 0;

  do {
    cout << "Enter first positive integer: ";
    cin >> input1;
  } while (input1 <= 0);

  do {
    cout << "Enter second positive integer: ";
    cin >> input2;
  } while (input2 <= 0);

  for (int i = 1; i < 11; i++) {
    cout << "Multiplication using only ADDITION:\n";
    auto strt = chrono::steady_clock::now();
    result = multiply(input1,input2);
    isOverflow(result);
    auto stop = chrono::steady_clock::now();
    long int s = (long int)chrono::duration_cast<chrono::seconds>(stop - strt).count();
    long int n = (long int)chrono::duration_cast<chrono::nanoseconds>(stop - strt).count();
    sAvg += (s / 10);
    nAvg += (n / 10);
    cout << "Product: " << result << "\nPass " << i << ": " << s << " seconds " << n << " nanoseconds\n";
  }
  cout << "Average: " << sAvg << " seconds " << nAvg << " nanoseconds\n";
  sAvg = 0;
  nAvg = 0;
  for (int i = 1; i < 11; i++) {
    cout << "Multiplication using only ADDITION and BIT SHIFTS:\n";
    auto strt = chrono::steady_clock::now();
    result = bitMultiply(input1,input2);
    isOverflow(result);
    auto stop = chrono::steady_clock::now();
    long int s = (long int)chrono::duration_cast<chrono::seconds>(stop - strt).count();
    long int n = (long int)chrono::duration_cast<chrono::nanoseconds>(stop - strt).count();
    sAvg += (s / 10);
    nAvg += (n / 10);
    cout << "Product: " << result << "\nPass " << i << ": " << s << " seconds " << n << " nanoseconds\n";
  }
  cout << "Average: " << sAvg << " seconds " << nAvg << " nanoseconds\n";

  return EXIT_SUCCESS;
}
// will return the product of op1 and op2 using addition
int multiply(int op1, int op2) {
  int prod = 0,
      mplr = (op1 < op2) ? op1 : op2,
      mcnd = (op1 > op2) ? op1 : op2;
  for (int i = 0; i < mplr; i++) {
    prod += mcnd;
  }
  return prod;
}
// will return the product of op1 and op2 using bit shifts and addition
int bitMultiply(int op1, int op2) {
  int prod = 0; // initialize product
  while (op2 > 0) {  // while op2 is larger than 0
    if ( op2 & 1 ) { // if op2 is odd
      prod += op1; // add op1 to prod
    }
    op1 = op1 << 1; // double op1
    op2 = op2 >> 1; // half op2
  }
  return prod; // return product
}
// returns a string containing the binary number
string binstr(int num) {
  string str = ""; // initialize empty string
  for (int i = 15; i >= 0; i--) { // loop to examine bits
    if ( num & (1 << i) ) { // if encounter 1
      str += "1"; // append a 1 to string
    } else {
      str += "0"; // else append a 0
    }
  }
  return str; // return the binary integer string
}

// displays base 2 and base 10 numbers
void printNums(int input1, int input2, int result) {
  cout << binstr(input1) << " (" << input1 << ") * " << binstr(input2) << " (" << input2 << ") = " << binstr(result) << " (" << result << ")\n";
}

void isOverflow(int result) {
  if ( result <= 0 || result > MAXINT ) {
    cout << "Error: Product results in integer overflow.\n";
    exit(EXIT_FAILURE);
  }
}
