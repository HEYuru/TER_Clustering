#include <iostream>
#include <fstream>
#include <time.h>
#include "Node.hpp"
using namespace std;

int main(int argc, const char * argv[]) {
	double timeStart, timeEnd;
	Node node[N];
	char readBuffer[256];
	int i, pLen;
	int p[N] = { 0 };
	double tempX, tempY;
	

	cout << "Please type in the file name or name with path:";
	cin >> readBuffer;

	
	ifstream fileIn(readBuffer);

	//ifstream fileIn("dataConcav_a_b_a_N_ex1.txt");
	timeStart = clock();

	if (!fileIn.is_open()){
	
		cout << "File is Missing" << endl;
		exit(1);
	}
	//    fileIn.getline(readBuffer, 100);    
	//fileIn >> readBuffer;
	fileIn >> readBuffer;
	int length = atof(readBuffer);
	fileIn >> readBuffer;
	cout << length;
	for (i = 0; i < length; i++){
		fileIn >> readBuffer;             //Read x coordinates 
		tempX = atof(readBuffer);       //change type
		fileIn >> readBuffer;             //read y
		tempY = atof(readBuffer);       //change tyoe
		node[i].Set(tempX, tempY);      
	}

	cout << "Please type in how many types need to be cluster: ";
	int k;
	while (cin >> k){
		if (k>length){
			cout << "number of types should be smaller to nodes, please try again!" << endl;
		}
		else if (k <= 0){
			cout << "number of types should be posetive, please try again!" << endl;
		}
		else{
			break;
		}
	}

	cout << "Please the clustering measure:k-median " << endl;
	pLen = cluster2DParetoFront(p, node, k, 2, length);         //cluster2DParetoFront(int* Pr, Node node[], const int K, int pblm, const int length)

	
	for (i = 0; i < pLen; i++){
		cout << "type" << i / 2 + 1 << " is from node[" << p[i] + 1 << "] to node[" << p[i + 1] + 1 << "]" << endl;            
		i++;
	}
	cout << "type" << pLen / 2 + 1 << " is from node[" << 1 << "] to node[" << p[pLen - 2] << "]" << endl;
	fileIn.close();
	timeEnd = clock();
	cout << "Runtime is " << (timeEnd - timeStart) / 1000 << " Seconds" << endl;
	system("pause");
	return 0;
	
}


