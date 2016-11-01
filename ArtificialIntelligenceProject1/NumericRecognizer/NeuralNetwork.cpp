#include "NeuralNetwork.h"


NeuralNetwork::NeuralNetwork(const int width, const int layerSizes[])
	: m_width(width)
{
	// 레이어 각각이 포함하는 뉴런 개수 설정
	m_layerSizes = new int[width];
	for (int i = 0; i < width; i++) {
		m_layerSizes[i] = layerSizes[i];
	}
	
	// 레이어별 뉴런을 생성하고 각 뉴런을 연결
	m_neurons = new Layer[width];
	m_neurons[0] = new Neuron[layerSizes[0]];	// Layer 0
	for (int j = 1; j < width; j++) {
		m_neurons[j] = new Neuron[layerSizes[j]];
		// 모든 가중치 W 벡터를 random number로 초기화함.
		for (int i = 0; i < layerSizes[j]; i++) {
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

	for (int i = 0; i < dataSize; i++) {
		// i 번째 훈련 예제에 의한 훈련임.

		// trainingData의 한 줄을 읽어서 input 변수를 채움.
		for (int j = 0; j < inputSize; j++) {
			input[j] = trainingData[i][j];
		}

		// d_tr의 한 줄을 읽어서 d 변수를 채움.
		for (int j = 0; j < outputSize; j++) {
			d[j] = d_tr[i][j];
		}

		inputData(input, inputSize);

		computeForward();
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

void NeuralNetwork::inputData(int data[], const int size)
{
	// 모든 가중치 W 벡터를 random number로 초기화함.
	for (int i = 0; i < m_layerSizes[0]; i++) {
		m_neurons[0][i].connect(data, size);
	}
}

void NeuralNetwork::computeForward()
{
	/*** Forward 계산 ***/
	// 각 층에 대한 s 및 f의 계산
	for (int l = 0; l < m_width; l++) {	// 층 L에 대해서,
		for (int i = 0; i < m_layerSizes[l]; i++) {	// 이 L 층의 뉴런 i에 대하여
			// s와 f의 계산
			m_neurons[l][i].computeF();
		}
	}
}

void NeuralNetwork::computeBackward()
{
}

void NeuralNetwork::updateWeight()
{
}
