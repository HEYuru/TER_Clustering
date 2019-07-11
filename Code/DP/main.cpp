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

	//    ��ȡ�ļ�
	cout << "Please type in the file name or name with path:";
	cin >> readBuffer;
	//    ��ȡ�ļ�
	//    ifstream fileIn("dataConcav_a_b_a_N_ex1.txt");
	ifstream fileIn(readBuffer);

	//ifstream fileIn("dataConcav_a_b_a_N_ex1.txt");
	timeStart = clock();

	if (!fileIn.is_open()){
		//        ����ļ������ڣ������˳�
		cout << "File is Missing" << endl;
		exit(1);
	}


	fileIn >> readBuffer;
	int length = atof(readBuffer);
	fileIn >> readBuffer;

	for (i = 0; i < length; i++){
		fileIn >> readBuffer;             //��ȡx����
		tempX = atof(readBuffer);       //ת��Ϊ��������
		fileIn >> readBuffer;             //��ȡy����
		tempY = atof(readBuffer);       //ת��Ϊ��������
		node[i].Set(tempX, tempY);      //�趨�������
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


	pLen = cluster2DParetoFront(p, node, k, 2, length);         //���÷��ຯ�����з��࣬���ִ���������


	for (i = 0; i < pLen; i++){
		cout << "type" << i / 2 + 1 << " is from node[" << p[i] + 1 << "] to node[" << p[i + 1] + 1 << "]" << endl;            //������
		i++;
	}
	cout << "type" << pLen / 2 + 1 << " is from node[" << 1 << "] to node[" << p[pLen - 2] << "]" << endl;
	fileIn.close();
	timeEnd = clock();
	cout << "Runtime is " << (timeEnd - timeStart) / 1000 << " Seconds" << endl;
	system("pause");
	return 0;

}