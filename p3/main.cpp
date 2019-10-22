/*
	 	  Name: 	Bowen Lyons
		 Title: 	p3
	  	   Due: 	August 6, 2019
   		Course: 	CSCE 2110
   Description:		This program simulates the spread of a disease based on the users input file.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <math.h>

using namespace std;

struct node
{
	string name; // name of this node
	int days; // counts the days passed in each state
	char state; // current state of the node
	bool known; // for searching through the nodes
	vector<node*> adjacent; // vector of pointers to adjacent nodes
};

vector<node*> graph; // the actual graph
vector<node*> cmp; // graph component
vector<vector<node*>> g;

// these functions count the number of the respective node status "s,e,i or r"
int sCount(vector<node*> adj);
int eCount(vector<node*> adj);
int iCount(vector<node*> adj);
int rCount(vector<node*> adj);

int getdist(string ip, string sp)
{
	int cluster, pos;
	for (unsigned int i = 0; i != g.size(); i++)
	{
		for (unsigned int j = 0; j != g[i].size(); j++)
		{
			if (g[i][j]->name == ip)
			{
				cluster = i;
				pos = j;
				g[i][j]->days = 0;
			} else {
				g[i][j]->days = -1;
			}
			g[i][j]->known = false;
		}
	}
	bool check = false;
	for (unsigned int i = 0; i != g[cluster].size(); i++)
	{
		if (g[cluster][i]->name == sp)
		{
			check = true;
		}
	}
	if (!check) // if they arent in the same cluster return -1 for not possible
	{
		return -1;
	}
	return g[cluster].size() / 3;
}

// component finder and printer
void dfs(int pos)
{
	graph[pos]->known = true;
	cmp.push_back(graph[pos]);
	for (unsigned int i = 0; i != graph[pos]->adjacent.size(); i++)
	{
		if (!graph[pos]->adjacent[i]->known)
		{
			string str = graph[pos]->adjacent[i]->name;
			str.erase(0,1);
			int n = stoi(str);
			dfs(n);
		}
	}
}
void findCmpts()
{
	for (unsigned int i = 0; i != graph.size(); i++)
	{
		if (!graph[i]->known)
		{
			cmp.clear();
			cmp.push_back(graph[i]);
			dfs(i);
			g.push_back(cmp);
		}
	}
}

int main(int argc, char **args)
{
	fstream file; // file opject
	string line; // use for opening/reading file information
	string popFile, pZero; // population file name, patient zero name
	int lPeriod, iPeriod; // latent and infectious periods
	vector<string> neighbors; // to store the nodes neighbors while creating the initial nodes
	vector<vector<node*>> cmpts; // graph seperated into a vector of node sets

	if (argc > 1) // check for command line file name open if present
	{
		file.open(args[1]);
	}

	while (!file.is_open()) // while file is not open ask for the file from user
	{
		cout << "Input valid file path: ";
		cin >> line;
		file.open(line);
	}

	// read and store info from the config file
	getline(file,line); // get the population file
	line.erase(0,line.find('=')+1); // delete all but the popfile name
	popFile = line;

	getline(file,line); // get the latent period
	line.erase(0,line.find('=')+1); // delete extra info
	lPeriod = stoi(line);

	getline(file,line); // get infectious period
	line.erase(0,line.find('=')+1); // delete extra info
	iPeriod = stoi(line);

	getline(file,line); // get patient zero
	line.erase(0,line.find('=')+1); // delete extra info
	pZero = line;

	file.close(); // close the config file

	file.open(popFile); // open the  population file
	
	while (getline(file,line)) // read the population file
	{
		// create a new node with the name from the file and initialize all members of the node struct
		node *n = new node;
		n->name = line.substr(0,line.find(':'));
		line.erase(0,line.find(':')+1);
		neighbors.push_back(line);
		n->days = 0;
		n->known = false;
		n->state = 's';
		graph.push_back(n);
	}

	file.close(); // close population file

	for (unsigned int i = 0; i != neighbors.size(); i++)
	{
		stringstream ss(neighbors[i]);
		while (getline(ss,line,','))
		{
			line.erase(0,1); // extract the number from the name and use as index for assigning the pointers
			int pos = stoi(line);
			graph[i]->adjacent.push_back(graph[pos]);
		}
	}
	g.clear();
	findCmpts();
	cout << "This graph contains " << g.size() << " components.\n";
	for (unsigned int i = 0; i != g.size(); i++)
	{
		cout << "Cluster " << i << "\n";
		int p = 0; 
		double avg = 0;
		for (unsigned int j = 0; j != g[i].size(); j++)
		{
			avg += g[i][j]->adjacent.size();
			p = j;
		}
		avg /= g[i].size();
		cout << "Total Population: " << p << " Average Degree: " << fixed << setprecision(2) << avg << endl;
	}

	// simulate the disease spreading
	// infect patient zero
	pZero.erase(0,1);
	int pz = stoi(pZero);
	graph[pz]->state = 'i';
	graph[pz]->days = 1;

	int day = 0;
	while (true) // loop increments "days" with every iteration
	{
		//print status of the graph
		cout << "Day:" << day << " Susceptible:" << sCount(graph) << " Latent:" << eCount(graph) << " Infectious:" << iCount(graph) << " Recovered:" << rCount(graph) << endl;
		// check for infection completion
		if (iCount(graph) == 0 && eCount(graph) == 0)
		{
			break;
		}
		// iterate through each node
		for (unsigned int i = 0; i != graph.size(); i++)
		{
			if (graph[i]->state == 's') // if it is susseptible and has an infectious node adjacent to it it becomes latent
			{
				for (unsigned int j = 0; j != graph[i]->adjacent.size(); j++)
				{
					if (graph[i]->adjacent[j]->state == 'i')
					{
						graph[i]->state = 'e';
						graph[i]->days = 0;
						break;
					}
				}
			} else if (graph[i]->state == 'e') // if it is latent check/increment the days passed
			{
				if (graph[i]->days == lPeriod)
				{
					graph[i]->state = 'i';
					graph[i]->days = 0;
				} else {
					graph[i]->days++;
				}
			} else if (graph[i]->state == 'i') // if it is infected check/increment the days passed
			{
				if (graph[i]->days == iPeriod)
				{
					graph[i]->state = 'r';
				} else {
					graph[i]->days++;
				}
			}
		}
		day++; // increment days
	}

	string ip, sp;
	cout << "Please enter the id for the infected person: ";
	cin >> ip;
	cout << "Please enter the id for the susceptible person: ";
	cin >> sp;

	int d = getdist(ip,sp);

	if (d == -1)
	{
		cout << "It is not possible to infect " << sp << " from " << ip << ".\n";
	} else {
		cout << "It would take " << d << " days to infect " << sp << ".\n";
	}

	return 0;
}

int sCount(vector<node*> adj)
{
	int ct = 0;
	for (unsigned int i = 0; i != adj.size(); i++)
	{
		if (adj[i]->state == 's')
		{
			ct++;
		}
	}
	return ct;
}
int eCount(vector<node*> adj)
{
	int ct = 0;
	for (unsigned int i = 0; i != adj.size(); i++)
	{
		if (adj[i]->state == 'e')
		{
			ct++;
		}
	}
	return ct;
}
int iCount(vector<node*> adj)
{
	int ct = 0;
	for (unsigned int i = 0; i != adj.size(); i++)
	{
		if (adj[i]->state == 'i')
		{
			ct++;
		}
	}
	return ct;
}
int rCount(vector<node*> adj)
{
	int ct = 0;
	for (unsigned int i = 0; i != adj.size(); i++)
	{
		if (adj[i]->state == 'r')
		{
			ct++;
		}
	}
	return ct;
}