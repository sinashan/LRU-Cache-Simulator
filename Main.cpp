/*
LRU Cache Simulator
3/4/19
Developers: Bruno E. Gracia Villalobos
			Ryan Walker
*/
#include <iostream>
#include <stdint.h>
#include <vector>		//array of cache sets
#include <list>			//for the cache sets
#include <iterator>		//iterating through lists
#include <algorithm>	//for find function
#include <unordered_map>
#include <utility>
#include "Cache.h"

using namespace G;
using namespace std;

//Returns a 4 byte vector with the lowest index at the MSB
/*vector<unsigned char> memBytes(unsigned int a)
{
	int size = sizeof(a);
	vector<unsigned char> address(sizeof(a));

	unsigned char temp;
	unsigned int tempint;
	unsigned char built;

	//To print an unsigned char in hex:
	//cout << (unsigned int)*memarray << endl;

	for(int i = 0; i < size; i++)
	{
		temp = (a>>(i*8)) & 0xFF;
		address.at(3-i) = temp;
		cout << "TEMP:" << temp << hex << endl;
//		cout << sizeof(address.at(i)) << endl;
//		cout << sizeof((a>>(i*8)) & 0xFF) << endl;
		cout << hex << ((a>>(i*8)) & 0xFF) << endl;
//		cout << "SIZE:" << address.size() << endl;
	}

	return address;
}

//Returns a char* array of bytes given an int
unsigned char* bytes(unsigned int &a)
{
	unsigned char* ret = (unsigned char*)malloc(sizeof(a));
	memcpy(ret, (unsigned char*)&a, sizeof(a));

	return ret;
}*/



/*Reads in cache config file*/
void readCacheConfig(int& cacheSize, int& blockSize, int& associativity) {
	/*VARIABLE DECLARATIONS*/
	ifstream file;
	string line;
	size_t found;
	string file_name;
	/*FLUSH COUT*/
	cout << flush;
	cout.flush();
	cout << dec;

	cout<<"Enter name of the file for cache parameters: ";
	cin>>file_name;


	/*Begin configuration file read*/
//	file.open("example.cfg", ios::in);
	file.open(file_name+".cfg", ios::in);

	if (file.is_open())
	{
		/*READ FIRST CONFIG LINE - CACHE SIZE */
		getline(file,line);
		found = line.find("=");
		cacheSize = stoi(line.substr(found+1, line.length()),nullptr,0);

		/*READ SECOND CONFIG LINE - BLOCK SIZE */
		getline(file, line);
		found = line.find("=");
		blockSize = stoi(line.substr(found+1, line.length()),nullptr,0);

		/*READ Third Config Line - ASSOCIATIVITY*/
		getline(file, line);
		found = line.find("=");
		associativity = stoi(line.substr(found+1, line.length()),nullptr,0);

	}

	file.close();
}

/*Sinashan: Reads in IO config file*/
void readConfig(int& nodes, vector<int>& VMs, string& cachingMode, string& SMC, string& resDistrib, string& migScheme, int& steps, int& reqSteps) {
	/*VARIABLE DECLARATIONS*/
	ifstream file;
	string file_name, line;
	int vm; //Sinashan: To keep number of VMs at each line
	/*FLUSH COUT*/
	cout << flush;
	cout.flush();
	cout << dec;

	cout<<"Enter name of the file for the HCI parameters: ";
	cin>>file_name;


	/*Begin configuration file read*/
//	file.open("example.cfg", ios::in);
	file.open(file_name+".cfg", ios::in);

	if (file.is_open())
	{
        file >> line;
        file >> nodes >> line;
        for(int i=0;i<nodes;i++)
        {
            file >> vm;
            VMs.push_back(vm);
        }

        file >> line >> cachingMode;
        file >> line >> SMC;
        file >> line >> resDistrib;
        file >> line >> migScheme;
        file >> line >> steps;
        file >> line >> reqSteps;

        /*Sinashan: Print out the config information on the screen*/
        cout << "Number of Nodes: " << nodes << endl;
        for(int i=0;i<VMs.size();i++)
            cout << "Node " << i+1 << " has " << VMs[i] << " virtual machines." << endl;
        cout << "Caching mode is set to " << cachingMode << endl;
        cout << "Split Mirrored Cache (SMC) is " << SMC << endl;
        if(resDistrib == "Traffic") cout << "Resources will be distributed in a way to minimize network traffic." << endl;
        else if(resDistrib == "Load") cout << "Resources will be distributed in a way to balance load." << endl;
        if(migScheme == "Gradual") cout << "Migration scheme is gradual." << endl;
        else if(migScheme == "Instant") cout << "Migration scheme is instant." << endl;
        cout << "Cache metrics checked after every " << reqSteps << " requests, in a total of " << steps << " steps." << endl;
	}

	file.close();
}

/*Sinashan: Assigning initial cache values to each VM*/
void initializeCache(vector<int>& m_VMs, vector<vector<int> >& m_vmCacheSize, int cSize, int bSize, int assoc){
    int numBlocks, temp, i, j, sum;
    for(i=0;i<m_VMs.size();i++){
        numBlocks = cSize / bSize;
        temp = numBlocks / m_VMs[i];
        sum = 0;
        for(j=0;j<m_VMs[i];j++){

        }
    }

}

int main(int argc, char** argv)
{
	int cacheSize,blockSize,associativiy;    //Sinashan: Just changed names for clarity!
	int nodes, steps,reqSteps;
	string cachingMode, SMC, resDistrib, migScheme; //Sinashan: HCIConfig file
	vector<int> VMs;    //Sinashan: VMs per node
	vector<vector<int> > vmCacheSize; //Sinashan: A vector to store cache sizes for each VM

    readConfig(nodes,VMs,cachingMode,SMC,resDistrib,migScheme,steps,reqSteps);  //Sinashan: Read in HCI config file
	readCacheConfig(cacheSize,blockSize,associativiy);	//Sinashan: Read in cache configuration values from file

    initializeCache(VMs,vmCacheSize,cacheSize,blockSize,associativiy);

    for(int i=0;i<vmCacheSize.size();i++){
        for(int j=0;j<vmCacheSize[i].size();j++){
            cout << vmCacheSize[i][j] << endl;
        }
        cout << endl;
    }
	/*Instantiate cache class with config file params*/
	Cache cache2(cacheSize,blockSize,associativiy);
	cache2.readMemory(); //Sinashan: Workload's name
	cache2.testMem();

	return 0;
}
