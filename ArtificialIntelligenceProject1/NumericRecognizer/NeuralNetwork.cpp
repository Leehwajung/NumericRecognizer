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
	const int dataSize, const int inputSize, const int outputSize, const double trainTreshold)
{
	int epoch = 0;
	double avg_sq_error = 0;
	do {
		trainEpoch(trainingData, d_tr, dataSize, inputSize, outputSize);
		avg_sq_error = getAvgSqErrorOfEpoch(trainingData, d_tr, dataSize, inputSize, outputSize);
		epoch++;
	} while (avg_sq_error > trainTreshold);
	return epoch;
}

void NeuralNetwork::trainEpoch(int** trainingData, int** d_tr,
	const int dataSize, const int inputSize, const int outputSize)
{
	/*** �� ����(epoch)�� �Ʒ� ���� ***/
	for (int i = 0; i < dataSize; i++) {
		// i ��° �Ʒ� ������ ���� �Ʒ���.
		computeForward(trainingData[i], inputSize);
		computeBackward(d_tr[i], outputSize);		// updateWeights() �۾��� ������.
	}
}

double NeuralNetwork::getAvgSqErrorOfEpoch(int** trainingData, int** d_tr, 
	const int dataSize, const int inputSize, const int outputSize)
{
	/*** �� Epoch �Ŀ� ��� ���� ��� ***/
	double sum_sq_error = 0;
	for (int t = 0; t < dataSize; t++) {
		// t ��° �Ʒ� ������ �̿��Ͽ� �ý����� ����� ���� error�� ����
		computeForward(trainingData[t], inputSize);	// t��° �Ʒ� ���� �����Ͽ� ����� ����
		// ���� ���� ����� �̿��Ͽ� ������ ����
		for (int i = 0; i < outputSize; i++) {
			double sub = d_tr[t][i] - m_neurons[outputSize - 1][i].getF();
			sum_sq_error += sub * sub;
		}
	}
	return sum_sq_error / (dataSize * outputSize);	// avg_sq_error
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

void NeuralNetwork::computeBackward(int d[], const int dSize)
{
	// �䱸�� ����
	for (int i = 0; i < m_layerSizes[m_width - 1]; i++) {
		m_neurons[m_width - 1][i].connect(d[i]);
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
