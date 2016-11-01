#include <iostream>
#include <fstream>
#include "NeuralNetwork.h"
#include "initvals.h"

#define asciiToInt(c)	int((c) - 48)

using namespace std;


void main() {

	/*** 입력 신호 가져오기 ***/
	ifstream fin;
	fin.open("traindata.txt");
	if (fin.fail()) {
		cerr << "파일 열기 오류!" << endl;
	}

	// 모든 훈련 데이터를 가지고 있는 변수
	int **trainData;
	int *trainData_Addr[N_tr_examples];
	int trainData_Repo[N_tr_examples][N];
	int **d_tr;
	int *d_tr_Addr[N_tr_examples];
	int d_tr_Repo[N_tr_examples][m2];
	trainData = (int**)&trainData_Addr;
	d_tr = (int**)&d_tr_Addr;
	for (int i = 0; i < N_tr_examples; i++) {
		trainData_Addr[i] = &trainData_Repo[i][0];
		d_tr_Addr[i] = &d_tr_Repo[i][0];
	}

	// 모든 테스트 데이터를 가지고 있는 변수
	int testData[N_te_examples][N];
	int d_te[N_te_examples][m2];

	// 처음에 파일로부터 훈련 데이터를 읽어서 채움.
	char next;
	for (int i = 0; !fin.eof() && i < N_tr_examples; i++) {
		fin >> next;
		for (int j = 0; j < m2; j++) {
			d_tr[i][j] = 0;
		}
		d_tr[i][asciiToInt(next)] = 1;
		fin >> next;	// $
		for (int j = 0; j < N; j++) {
			fin >> next;
			trainData[i][j] = asciiToInt(next);
		}
	}
	
	NeuralNetwork nn(NLayer, M);
	nn.train(trainData, d_tr, N_tr_examples, N, m2);


	// 훈련 데이터 출력
	//for (int i = 0; i < N_tr_examples; i++) {
	//	for (int j = 0; j < N; j++) {
	//		cout << trainData[i][j];
	//	}
	//	cout << endl;
	//}


	//// 각 훈련 예를 이용하여 훈련하기 직전에 아래 두 변수를 채우고 시작함.
	//int intput[N];	// 입력 신호를 가지고 있는 변수 INPUT
	//// training data의 한 줄을 읽어서 이 변수를 채움.
	//int d[m2];		// 정답 레이블을 가지는 변수 D
	//// training data의 각 줄의 첫 숫자를 이용하여 이를 채움.
}