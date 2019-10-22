/*************************************************
 *	Title: proj3	Author: Bowen Lyons	           *
 *	Course: 3110	Due: 06/21/19		               *
 *************************************************
 * This program creates an efficient Hopscotch	 *
 * Hash table with a menu interface to allow the *
 * user to store integers.			                 *
 *************************************************
 */

#include <iostream>
#include <stdlib.h>
#include <map>

#define TABLE_SIZE 17
#define MAX_DIST 4

void printMenu();
int menu();
int hash(int);

using namespace std;

int main(int argc, char *args[])
{
	int choice = 0;
	while (choice != 5)
	{
		choice = menu();
		if (choice == 1)
		{
      //call insert value
      int val;
      cout << "Enter positive integer value to insert into Hopscotch Hash Table: ";
      cin >> val;
      cout << val << " " << hash(val) << endl;
			continue;
		}
		if (choice == 2)
		{
			//call delete value
			int val;
			cout << "Enter positive integer value to delete from Hopscotch Hash Table: ";
			cin >> val;
			continue;
		}
		if (choice == 3)
		{
			//call search value
			int val;
			cout << "Enter positive integer to search for in Hopscotch Hash Table: ";
			cin >> val;
			continue;
		}
		if (choice == 4)
		{
			//call output table
			continue;
		}
	}
	cout << "Program terminated by user...\n";
	return EXIT_SUCCESS;
}

int hash(int value)
{
	return (value % TABLE_SIZE);
}

void printMenu()
{
	cout << "HOPSCOTCH HASH MENU:\n1 - Insert Value\n2 - Delete Value\n3 - Search Value\n";
	cout << "4 - Output Table\n5 - Exit Program\nEnter operation to perform: ";
}

int menu()
{
	int choice;
	while (1)
	{
		printMenu();
		cin >> choice;
		if (choice > 0 && choice < 6)
		{
			break;
		}
		else
		{
			cout << "ERROR: Please select operation between 1 and 5, inclusively.\n";
			continue;
		}
	}
	return choice;
}
