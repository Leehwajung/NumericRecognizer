#include <iostream>
#include <fstream>
#include "NeuralNetwork.h"
#include "initvals.h"

#define asciiToInt(c)	((c) - 48)
#define TRAINDATA	"traindata.txt"
#define TESTDATA	"testdata.txt"


using namespace std;

// Load Data from File
void loadDataFromFile(const char* fileName, int** trainingData, int** d_tr,
	const int dataSize, const int inputSize, const int outputSize);


void main() {

	/*** 입력 신호 가져오기 ***/
	// 모든 훈련 데이터를 가지고 있는 변수
	int *trainData[N_tr_examples];
	int *trainData_Repo = new int[N_tr_examples * N];
	int *d_tr[N_tr_examples];
	int *d_tr_Repo = new int[N_tr_examples * m2];
	for (int i = 0; i < N_tr_examples; i++) {
		trainData[i] = &trainData_Repo[i * N];
		d_tr[i] = &d_tr_Repo[i * m2];
	}

	// 처음에 파일로부터 훈련 데이터를 읽어서 채움.
	loadDataFromFile(TRAINDATA, trainData, d_tr, N_tr_examples, N, m2);

	// 모든 테스트 데이터를 가지고 있는 변수
	int *testData[N_te_examples];
	int *testData_Repo = new int[N_te_examples * N];
	int *d_te[N_te_examples];
	int *d_te_Repo = new int[N_te_examples * m2];
	for (int i = 0; i < N_te_examples; i++) {
		testData[i] = &testData_Repo[i * N];
		d_te[i] = &d_te_Repo[i * m2];
	}

	// 처음에 파일로부터 테스트 데이터를 읽어서 채움.
	loadDataFromFile(TESTDATA, testData, d_te, N_te_examples, N, m2);
	
	// 훈련 및 테스트
	char command;
	do {
		cout << "### Start Test ###" << endl;
		NeuralNetwork nn(NLayer, M);	// 1회 테스트마다 새롭게 생성
		nn.setPrintingLog(false);
		for (int i = 0; i < NLayer; i++) {
			cout << "Layer " << i << " Neurons: " << M[i] << endl;
		}
		cout << "Learning Rate: " << C << endl;
		cout << "Epochs: " << nn.train(trainData, d_tr, N_tr_examples, N) << endl;
		cout << "Test Accuracy: " << nn.test(testData, d_te, N_te_examples, N) * 100 << '%' << endl;
		cout << "### Test Finished ###" << endl << endl;

		cout << "Enter 'y' to retest. ";
		cin >> command;
		cout << endl << endl;
	} while (command == 'y' || command == 'Y');

	// 할당 해제
	delete[] trainData_Repo;
	delete[] d_tr_Repo;
	delete[] testData_Repo;
	delete[] d_te_Repo;
}

void loadDataFromFile(const char* fileName, int** input, int** desire, 
	const int dataSize, const int inputSize, const int outputSize)
{
	/*** 입력 신호 가져오기 ***/
	// 파일 입력 스트림
	ifstream fin;
	fin.open(fileName);
	if (fin.fail()) {
		cerr << "파일 열기 오류!" << endl;
		exit(1);
	}

	// 처음에 파일로부터 테스트 데이터를 읽어서 채움
	char next;
	for (int i = 0; !fin.eof() && i < dataSize; i++) {
		for (int j = 0; j < outputSize; j++) {
			desire[i][j] = 0;
		}
		fin >> next;		// desire
		desire[i][asciiToInt(next)] = 1;
		fin >> next;		// $
		for (int j = 0; j < inputSize; j++) {
			fin >> next;	// input
			input[i][j] = asciiToInt(next);
		}
	}

	fin.close();
}
