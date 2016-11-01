#include <iostream>
#include <fstream>
#include "NeuralNetwork.h"
#include "initvals.h"

#define asciiToInt(c)	int((c) - 48)

using namespace std;


void main() {

	/*** �Է� ��ȣ �������� ***/
	ifstream fin;
	fin.open("traindata.txt");
	if (fin.fail()) {
		cerr << "���� ���� ����!" << endl;
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

	// ��� �׽�Ʈ �����͸� ������ �ִ� ����
	int testData[N_te_examples][N];
	int d_te[N_te_examples][m2];

	// ó���� ���Ϸκ��� �Ʒ� �����͸� �о ä��.
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


	// �Ʒ� ������ ���
	//for (int i = 0; i < N_tr_examples; i++) {
	//	for (int j = 0; j < N; j++) {
	//		cout << trainData[i][j];
	//	}
	//	cout << endl;
	//}


	//// �� �Ʒ� ���� �̿��Ͽ� �Ʒ��ϱ� ������ �Ʒ� �� ������ ä��� ������.
	//int intput[N];	// �Է� ��ȣ�� ������ �ִ� ���� INPUT
	//// training data�� �� ���� �о �� ������ ä��.
	//int d[m2];		// ���� ���̺��� ������ ���� D
	//// training data�� �� ���� ù ���ڸ� �̿��Ͽ� �̸� ä��.
}