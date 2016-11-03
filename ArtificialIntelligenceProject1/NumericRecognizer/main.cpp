#include <iostream>
#include <fstream>
#include "NeuralNetwork.h"
#include "initvals.h"

#define asciiToInt(c)	((c) - 48)

using namespace std;


void main() {

	/*** �Է� ��ȣ �������� ***/
	ifstream finTraining;
	finTraining.open("traindata.txt");
	if (finTraining.fail()) {
		cerr << "���� ���� ����!" << endl;
		exit(1);
	}

	// ��� �Ʒ� �����͸� ������ �ִ� ����
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

	// ó���� ���Ϸκ��� �Ʒ� �����͸� �о ä��.
	char next;
	for (int i = 0; !finTraining.eof() && i < N_tr_examples; i++) {
		for (int j = 0; j < m2; j++) {
			d_tr[i][j] = 0;
		}
		finTraining >> next;		// desire
		d_tr[i][asciiToInt(next)] = 1;
		finTraining >> next;		// $
		for (int j = 0; j < N; j++) {
			finTraining >> next;	// input
			trainData[i][j] = asciiToInt(next);
		}
	}


	/*** �׽�Ʈ ������ �������� ***/
	ifstream finTest;
	finTest.open("testdata.txt");
	if (finTest.fail()) {
		cerr << "���� ���� ����!" << endl;
		exit(1);
	}

	// ��� �׽�Ʈ �����͸� ������ �ִ� ����
	int **testData;
	int *testData_Addr[N_te_examples];
	int testData_Repo[N_te_examples][N];
	int **d_te;
	int *d_te_Addr[N_te_examples];
	int d_te_Repo[N_te_examples][m2];
	testData = (int**)&testData_Addr;
	d_te = (int**)&d_te_Addr;
	for (int i = 0; i < N_te_examples; i++) {
		testData_Addr[i] = &testData_Repo[i][0];
		d_te_Addr[i] = &d_te_Repo[i][0];
	}

	// ó���� ���Ϸκ��� �׽�Ʈ �����͸� �о ä��.
	for (int i = 0; !finTest.eof() && i < N_te_examples; i++) {
		for (int j = 0; j < m2; j++) {
			d_te[i][j] = 0;
		}
		finTest >> next;		// desire
		d_te[i][asciiToInt(next)] = 1;
		finTest >> next;		// $
		for (int j = 0; j < N; j++) {
			finTest >> next;	// input
			testData[i][j] = asciiToInt(next);
		}
	}
	
	// �Ʒ� �� �׽�Ʈ
	NeuralNetwork nn(NLayer, M);
	cout << nn.train(trainData, d_tr, N_tr_examples, N) << endl;
	cout << nn.test(testData, d_te, N_te_examples, N) << endl;
}