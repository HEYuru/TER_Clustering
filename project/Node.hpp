#ifndef Node_hpp
#define Node_hpp

#include <stdio.h>
#include<iostream>
#include<cmath>
#define N 100     //�����趨�������ǵø�********
using namespace std;


class Node{
	//    ��(Node)�������������������ɡ����캯������������
public:
	void Set(double locX, double locY);
	Node(double locX, double locY);
	Node();
	double getX();
	double getY();
	double getRange(Node Target);
private:
	double _x;
	double _y;
};

// �����Ǻ�������
void nodeSort(Node node[N], int length);
void getCiiPMedianProblem(double c[N][N], Node node[N]);
void getCiiPCenterProblem(double c[N][N], Node node[N]);
double getCiiPCenterAlgorithm(Node node[N], int i, int iNew);
int cluster2DParetoFront(int* Pr, Node node[], int K, int pblm, int length);
double noZeroMin(double A, double B);
double getKmediaFunc(Node node[], int i, int iNew);
void getKmedia(Node node[N], double c[N][N]);

double getKmeanFunc(Node node[], int i, int iNew);
void getKmean(Node node[N], double c[N][N]);

double min(double a, double b);
double max(double a, double b);


#endif /* Node_hpp */