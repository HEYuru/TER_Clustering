#ifndef Node_hpp
#define Node_hpp

#include <stdio.h>
#include<iostream>
#include<cmath>
#define N 100   //keep the N value lager then the number of points or nodes
using namespace std;


class Node{
	//    A Node class declaration that declares the composition, constructors, and other functions of the class 
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

// Function declaration 
void nodeSort(Node node[N], int length);

double getKmeanFunc(Node node[], int i, int iNew);
void getKmean(Node node[N], double c[N][N]);

void getKmedioids(Node node[N], double c[N][N]);
double getKmedioidsFunc(Node node[], int i, int iNew);

double getKmediaFunc(Node node[], int i, int iNew);
void getKmedia(Node node[N], double c[N][N]);

void getKcenterContinuous(Node node[N], double c[N][N]);
double getKcenterContinuousFunc(Node node[], int i, int iNew);

void getKcenterDiscrete(Node node[N], double c[N][N]);
double getKcenterDiscreteFunc(Node node[], int i, int iNew);

//void getCiiPMedianProblem(double c[N][N], Node node[N]);
//void getCiiPCenterProblem(double c[N][N], Node node[N]);
//double getCiiPCenterAlgorithm(Node node[N], int i, int iNew);

int cluster2DParetoFront(int* Pr, Node node[], int K, int pblm, int length);


double noZeroMin(double A, double B);
double min(double a, double b);
double max(double a, double b);


#endif /* Node_hpp */