#ifndef Node_hpp
#define Node_hpp

#include <stdio.h>
#include<iostream>
#include<cmath>
#define N 500   //这里设定点数（记得改********
using namespace std;


class Node{
	//    点(Node)类声明，声明该类的组成、构造函数及其他函数
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

// 以下是函数声明
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