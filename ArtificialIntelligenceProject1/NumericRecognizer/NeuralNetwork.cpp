#include "NeuralNetwork.h"


NeuralNetwork::NeuralNetwork(const int width, const int layerSizes[])
	: m_width(width)
{
	// 레이어 각각이 포함하는 뉴런 개수 설정
	m_layerSizes = new int[width];
	for (int i = 0; i < width; i++) {
		m_layerSizes[i] = layerSizes[i];
	}
	
	// 레이어별 뉴런을 생성하고 각 뉴런을 연결 (Layer 0는 이전 층이 입력값이므로 입력할 때 연결)
	m_neurons = new Layer[width];
	m_neurons[0] = new Neuron[layerSizes[0]];		// 0층 레이어
	for (int j = 1; j < width; j++) {				// j층 레이어 (1층 이상)
		m_neurons[j] = new Neuron[layerSizes[j]];
		for (int i = 0; i < layerSizes[j - 1]; i++) {	// i번째 뉴런
			m_neurons[j - 1][i].setAxon(layerSizes[j]);
		}
		// 모든 가중치 W 벡터를 random number로 초기화함.
		for (int i = 0; i < layerSizes[j]; i++) {		// i번째 뉴런
			m_neurons[j][i].connect(m_neurons[j - 1], layerSizes[j - 1]);
		}
	}
}

NeuralNetwork::~NeuralNetwork()
{
	if (m_neurons) {
		for (int i = 0; i < m_width; i++) {
			if (m_neurons[i]) {
				delete[] m_neurons[i];
			}
		}
		delete[] m_neurons;
	}
	if (m_layerSizes) {
		delete[] m_layerSizes;
	}
}

void NeuralNetwork::train(int** trainingData, int** d_tr, 
	const int dataSize, const int inputSize, const int outputSize)
{
	int *input = new int[inputSize];	// 입력 신호를 가지고 있는 변수 INPUT
	int *d = new int[outputSize];		// 정답 레이블을 가지는 변수 D

	/*** 한 에폭(epoch)의 훈련 과정 ***/
	for (int i = 0; i < dataSize; i++) {
		// i 번째 훈련 예제에 의한 훈련임.

		/*** 입력 신호 가져오기 ***/
		// trainingData의 한 줄을 읽어서 input 변수를 채움.
		for (int j = 0; j < inputSize; j++) {
			input[j] = trainingData[i][j];
		}

		// d_tr의 한 줄을 읽어서 d 변수를 채움.
		for (int j = 0; j < outputSize; j++) {
			d[j] = d_tr[i][j];
		}

		/*** 한 에폭(epoch)의 훈련 과정 ***/
		// 훈련 진행
		computeForward(input, inputSize);
		computeBackward(d, outputSize);		// updateWeights() 작업을 포함함.
	}

	delete[] input;
	delete[] d;
}

void NeuralNetwork::test(const int** testData, const int** d_te, 
	const int dataSize, const int inputSize, const int outputSize)
{
}

void NeuralNetwork::recognize()
{
}

void NeuralNetwork::computeForward(int input[], const int inputSize)
{
	// 입력값 설정
	// 모든 가중치 W 벡터를 random number로 초기화함.
	for (int i = 0; i < m_layerSizes[0]; i++) {
		m_neurons[0][i].connect(input, inputSize);
	}

	/*** Forward 계산 ***/
	// 각 층에 대한 s 및 f의 계산
	for (int l = 0; l < m_width; l++) {	// 층 L에 대해서,
		for (int i = 0; i < m_layerSizes[l]; i++) {	// 이 L 층의 뉴런 i에 대하여
			m_neurons[l][i].computeF();				// s와 f의 계산
		}
	}
}

void NeuralNetwork::computeBackward(int d[], const int dSize)
{
	// 요구값 설정
	for (int i = 0; i < m_layerSizes[m_width - 1]; i++) {
		m_neurons[m_width - 1][i].connect(d[i]);
	}

	/*** Backward 계산 ***/
	// 각 층에 대한 delta의 계산
	for (int l = m_width - 1; l >= 0; l--) {	// 층 L에 대해서,
		for (int i = 0; i < m_layerSizes[l]; i++) {	// 각 뉴런 i에 대하여
			m_neurons[l][i].computeDelta();			// delta의 계산
		}
	}

	/*** 가중치 갱신 작업 ***/
	updateWeights();
}

void NeuralNetwork::updateWeights()
{
	/*** 가중치 갱신 작업 ***/
	// 각 층에 대한 처리
	for (int l = 0; l < m_width; l++) {	// 층 번호
		for (int i = 0; i < m_layerSizes[l]; i++) {	// 뉴런 번호
			m_neurons[l][i].updateWeights();		// weight 갱신
		}
	}
}
