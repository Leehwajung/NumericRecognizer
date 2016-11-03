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

int NeuralNetwork::train(int** trainingData, int** d_tr,
	const int dataSize, const int inputSize, const double trainTreshold)
{
	int epoch = 0;
	double avg_sq_error = 0;
	do {
		trainEpoch(trainingData, d_tr, dataSize, inputSize);
		avg_sq_error = getAvgSqErrorOfEpoch(trainingData, d_tr, dataSize, inputSize);
		epoch++;
	} while (avg_sq_error > trainTreshold);
	return epoch;
}

void NeuralNetwork::trainEpoch(int** trainingData, int** d_tr,
	const int dataSize, const int inputSize)
{
	/*** 한 에폭(epoch)의 훈련 과정 ***/
	for (int i = 0; i < dataSize; i++) {
		// i 번째 훈련 예제에 의한 훈련임.
		computeForward(trainingData[i], inputSize);
		computeBackward(d_tr[i]);	// updateWeights() 작업을 포함함.
	}
}

double NeuralNetwork::getAvgSqErrorOfEpoch(int** trainingData, int** d_tr, 
	const int dataSize, const int inputSize)
{
	/*** 한 Epoch 후에 평균 에러 계산 ***/
	double sum_sq_error = 0;
	for (int t = 0; t < dataSize; t++) {
		// t 번째 훈련 예제를 이용하여 시스템의 출력을 구해 error를 구함
		computeForward(trainingData[t], inputSize);	// t번째 훈련 예를 투입하여 출력을 구함
		// 최종 층의 출력을 이용하여 에러를 구함
		for (int i = 0; i < getOutputSize(); i++) {
			double sub = d_tr[t][i] - getLastLayer()[i].getF();
			sum_sq_error += sub * sub;
		}
	}
	return sum_sq_error / (dataSize * getOutputSize());	// avg_sq_error
}

double NeuralNetwork::test(int** testData, int** d_te,
	const int dataSize, const int inputSize)
{
	/*** 테스트 과정 ***/
	// 훈련이 종료된 이후에 test data를 이용하여 시스템의 성능을 측정한다.
	int num_correct = 0;
	for (int t = 0; t < dataSize; t++) {

		int recValue = recognize(testData[t], inputSize);	// 테스트 예를 투입하여 시스템 출력을 구한다.

		bool isCorrect = true;
		for (int i = 0; i < getOutputSize(); i++) {
			if (i == recValue) {
				if (d_te[t][i] != 1) {
					isCorrect = false;
					break;
				}
			}
			else {
				if (d_te[t][i] != 0) {
					isCorrect = false;
					break;
				}
			}
		}
		if (isCorrect) {	// 결과가 올바르다면
			num_correct++;
		}
	}
	return (double) num_correct / dataSize;	// accuracy
}

int NeuralNetwork::recognize(int* data, int dataSize)
{
	computeForward(data, dataSize);	// 

	double maxF = getLastLayer()[0].getF();
	int maxIndex = 0;
	for (int i = 1; i < getOutputSize(); i++) {
		double f = getLastLayer()[i].getF();
		if (maxF < f) {
			maxF = f;
			maxIndex = i;
		}
	}

	return maxIndex;
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

void NeuralNetwork::computeBackward(int d[])
{
	// 요구값 설정
	for (int i = 0; i < getOutputSize(); i++) {
		getLastLayer()[i].connect(d[i]);
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

int NeuralNetwork::getOutputSize()
{
	return m_layerSizes[m_width - 1];
}

Layer& NeuralNetwork::getLastLayer()
{
	return m_neurons[m_width - 1];
}
