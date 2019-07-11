#include "Node.hpp"

void Node::Set(double locX, double locY){
	//    设定点坐标的函数
	_x = locX;
	_y = locY;
}

Node::Node(double locX, double locY){
	//    初始化点坐标
	_x = locX;
	_y = locY;
}

Node::Node(){
	//    初始化空点（用作暂存
	_x = 0;
	_y = 0;
}

double Node::getX(){
	//    获取点的x坐标
	return _x;
}

double Node::getY(){
	//    获取点的y坐标
	return _y;
}


double Node::getRange(Node Target){
	//    返回点对另外一个点的距离（由其中一个点调用即可
	//    return sqrt((_x-Target.getX())*(_x-Target.getX()) + (_y-Target.getY())*(_y-Target.getY()));
	return sqrt(pow((_x - Target.getX()), 2) + pow((_y - Target.getY()), 2));
}

void getCiiPMedianProblem(double c[N][N], Node node[N]){
	//    Algorithm 2: 计算p-median问题的c阵
	//    double cT[N][N] = {1000000};
	double d[N][N][N];
	int l, i, k, iNew;
	double minD;
	for (i = 0; i<N; i++) {
		for (iNew = 0; iNew < N; iNew++) {
			if (i <= iNew){
				c[i][iNew] = 0;
				for (l = i; l <= iNew; l++) {
					d[i][l][iNew] = 0;
				}
			}
		}
	}

	for (l = 0; l<N; l++){
		for (i = 0; i<N - l; i++) {
			for (k = i; k <= i + l; k++) {
				d[i][k][i + l] = d[i][k][i + l - 1] + node[i + l].getRange(node[k]);
			}
			minD = d[i][i + 1][i + l];
			for (k = i; k < i + l; k++){
				minD = noZeroMin(minD, d[i][k][i + l]);

			}
			c[i][i + l] = minD;
		}
	}
}

void getCiiPCenterProblem(double c[N][N], Node node[N]){
	//    Algorithm 1: 计算p-center问题的c阵，遍历每个点调用下面那个函数进行计算
	int i, j;
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			c[i][j] = getCiiPCenterAlgorithm(node, i, j);
		}
	}
}

double getCiiPCenterAlgorithm(Node node[N], int i, int iNew){
	//     Algorithm 1: 计算p-center问题的c阵
	if (i >= iNew) {
		return 0;
	}
	else{
		int idInf = i;
		int idSup = iNew;
		int  idMid;
		double valTemp, valTemp2;
		double valInf = node[i].getRange(node[iNew]);
		double valSup = node[i].getRange(node[iNew]);
		while ((idSup - idInf) > 2){    //Dichotomic search
			idMid = (idSup + idInf) / 2;
			valTemp = max(node[idMid].getRange(node[i]), node[idMid].getRange(node[iNew]));
			valTemp2 = max(node[idMid + 1].getRange(node[i]), node[idMid + 1].getRange(node[iNew]));
			if (valTemp == valTemp2) {
				idInf = idMid;
				valInf = valTemp;
				idSup = 1 + idMid;
				valSup = valTemp2;
			}
			if (valTemp < valTemp2) {
				idSup = idMid;
				valSup = valTemp2;
			}
			if (valTemp > valTemp2) {
				idInf = 1 + idMid;
				valInf = valTemp2;
			}
		}
		return min(valInf, valSup);
	}
}

double getKmeanFunc(Node node[], int i, int iNew){
	int temp, l, j;
	double meanX, meanY, range, sumLength = 0;
	Node nodeMean;
	if (iNew < i){
		temp = iNew;
		iNew = i;
		i = temp;
	}
	else if (i == iNew){
		return 0;
	}
	range = (double)(iNew - i + 1);

	for (l = i; l <= iNew; l++) {
		meanX = 0;
		meanY = 0;
		for (j = i; j <= iNew; j++) {
			meanX += node[j].getX();
			meanY += node[j].getY();
		}
		nodeMean.Set(meanX / range, meanY / range);
		sumLength += nodeMean.getRange(node[l])*nodeMean.getRange(node[l]);
	}
	return sumLength / range;
}

void getKmean(Node node[N], double c[N][N]){
	int i, j;
	for (i = 0; i < N; i++){
		for (j = 0; j < N; j++){
			if (i >= j) {
				c[i][j] = 0;
			}
			else {
				c[i][j] = getKmeanFunc(node, i, j);
			}
		}
	}
}



int cluster2DParetoFront(int* Pr, Node node[], const int K, int pblm, const int length){
	//    Algorithm 3: 依照不同问题(pblm)的c阵计算C阵，遍历查找C阵对应的坐标
	//    写入Pr矩阵中，返回该矩阵的有效长度。
	//    pblm = 0 P-median,  pblm = 1 P-center pblm = 2 K-media   pblm = 3 K-mean
	double c[N][N];
	double C[N][N];
	int PLen = 0;
	int i, j, k;
	double minC;
	nodeSort(node, length);
	if (pblm == 0) {
		getCiiPMedianProblem(c, node);
	}
	else if (pblm == 1){
		getCiiPCenterProblem(c, node);
	}
	else if(pblm == 2){
		 getKmedia(node, c);
	}
	else{
		getKmean(node, c);
	}
	for (i = 0; i < length; i++) {
		k = 0;
		C[i][k] = getKmediaFunc(node, k, i);// c[i][k];
		for (k = 1; k < K; k++) {
			minC = 0;
			for (j = 1; j < i; j++) {
				minC = noZeroMin(minC, C[j - 1][k - 1] + c[j][i]);
			}
			C[i][k] = minC;
		}
	}
	i = length - 1;
	int iNew = i;
	for (k = K - 1; k >= 0; k--){
		for (j = 1; j <= i; j++){
			if (C[i][k] == (C[j - 1][k - 1] + getKmeanFunc(node, j, i))){
				Pr[PLen] = j;
				Pr[PLen + 1] = i;
				PLen = PLen + 2;
				iNew = j - 1;
				continue;
			}
		}
		i = iNew;
	}
	return PLen;
}

void nodeSort(Node node[], int length){
	//    点排序算法（冒泡法
	int i, j;
	Node temp;
	for (j = 0; j < length - 1; j++){
		for (i = 0; i < length - 1 - j; i++)
		{
			if (node[i].getX() > node[i + 1].getX())
			{
				temp = node[i];
				node[i].Set(node[i + 1].getX(), node[i + 1].getY());
				node[i + 1].Set(temp.getX(), temp.getY());
			}
		}
	}
}

void getKmedia(Node node[N], double c[N][N]){
	int i, j;
	for (i = 0; i < N; i++){
		for (j = 0; j < N; j++){
			if (i >= j) {
				c[i][j] = 0;
			}
			else {
				c[i][j] = getKmediaFunc(node, i, j);
			}
		}
	}
}

double getKmediaFunc(Node node[], int i, int iNew){
	int jT, lT;
	lT = i;
	double temp, minSum = 0;
	for (jT = i; jT <= iNew; jT++) {
		minSum += node[jT].getRange(node[lT]);
	}

	//    cout<<minSum<<endl;
	for (lT = 1; lT < iNew; lT++) {
		temp = 0;
		for (jT = i; jT <= iNew; jT++) {
			temp += node[jT].getRange(node[lT]);
		}
		minSum = min(temp, minSum);
	}

	return minSum;
}
double noZeroMin(double A, double B){
	//    判断非零最小值
	if (abs(A)<1e-16) {
		return B;
	}
	else if (abs(B)<1e-16) {
		return A;
	}
	else {
		return min(A, B);
	}
}

double min(double a, double b){
	return a<b ? a : b;
}
double max(double a, double b){
	return a>b ? a : b;
}


