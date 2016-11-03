#include "NeuralNetwork.h"


NeuralNetwork::NeuralNetwork(const int width, const int layerSizes[])
	: m_width(width)
{
	// ���̾� ������ �����ϴ� ���� ���� ����
	m_layerSizes = new int[width];
	for (int i = 0; i < width; i++) {
		m_layerSizes[i] = layerSizes[i];
	}
	
	// ���̾ ������ �����ϰ� �� ������ ���� (Layer 0�� ���� ���� �Է°��̹Ƿ� �Է��� �� ����)
	m_neurons = new Layer[width];
	m_neurons[0] = new Neuron[layerSizes[0]];		// 0�� ���̾�
	for (int j = 1; j < width; j++) {				// j�� ���̾� (1�� �̻�)
		m_neurons[j] = new Neuron[layerSizes[j]];
		for (int i = 0; i < layerSizes[j - 1]; i++) {	// i��° ����
			m_neurons[j - 1][i].setAxon(layerSizes[j]);
		}
		// ��� ����ġ W ���͸� random number�� �ʱ�ȭ��.
		for (int i = 0; i < layerSizes[j]; i++) {		// i��° ����
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
	/*** �� ����(epoch)�� �Ʒ� ���� ***/
	for (int i = 0; i < dataSize; i++) {
		// i ��° �Ʒ� ������ ���� �Ʒ���.
		computeForward(trainingData[i], inputSize);
		computeBackward(d_tr[i]);	// updateWeights() �۾��� ������.
	}
}

double NeuralNetwork::getAvgSqErrorOfEpoch(int** trainingData, int** d_tr, 
	const int dataSize, const int inputSize)
{
	/*** �� Epoch �Ŀ� ��� ���� ��� ***/
	double sum_sq_error = 0;
	for (int t = 0; t < dataSize; t++) {
		// t ��° �Ʒ� ������ �̿��Ͽ� �ý����� ����� ���� error�� ����
		computeForward(trainingData[t], inputSize);	// t��° �Ʒ� ���� �����Ͽ� ����� ����
		// ���� ���� ����� �̿��Ͽ� ������ ����
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
	/*** �׽�Ʈ ���� ***/
	// �Ʒ��� ����� ���Ŀ� test data�� �̿��Ͽ� �ý����� ������ �����Ѵ�.
	int num_correct = 0;
	for (int t = 0; t < dataSize; t++) {

		int recValue = recognize(testData[t], inputSize);	// �׽�Ʈ ���� �����Ͽ� �ý��� ����� ���Ѵ�.

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
		if (isCorrect) {	// ����� �ùٸ��ٸ�
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
	// �Է°� ����
	// ��� ����ġ W ���͸� random number�� �ʱ�ȭ��.
	for (int i = 0; i < m_layerSizes[0]; i++) {
		m_neurons[0][i].connect(input, inputSize);
	}

	/*** Forward ��� ***/
	// �� ���� ���� s �� f�� ���
	for (int l = 0; l < m_width; l++) {	// �� L�� ���ؼ�,
		for (int i = 0; i < m_layerSizes[l]; i++) {	// �� L ���� ���� i�� ���Ͽ�
			m_neurons[l][i].computeF();				// s�� f�� ���
		}
	}
}

void NeuralNetwork::computeBackward(int d[])
{
	// �䱸�� ����
	for (int i = 0; i < getOutputSize(); i++) {
		getLastLayer()[i].connect(d[i]);
	}

	/*** Backward ��� ***/
	// �� ���� ���� delta�� ���
	for (int l = m_width - 1; l >= 0; l--) {	// �� L�� ���ؼ�,
		for (int i = 0; i < m_layerSizes[l]; i++) {	// �� ���� i�� ���Ͽ�
			m_neurons[l][i].computeDelta();			// delta�� ���
		}
	}

	/*** ����ġ ���� �۾� ***/
	updateWeights();
}

void NeuralNetwork::updateWeights()
{
	/*** ����ġ ���� �۾� ***/
	// �� ���� ���� ó��
	for (int l = 0; l < m_width; l++) {	// �� ��ȣ
		for (int i = 0; i < m_layerSizes[l]; i++) {	// ���� ��ȣ
			m_neurons[l][i].updateWeights();		// weight ����
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
