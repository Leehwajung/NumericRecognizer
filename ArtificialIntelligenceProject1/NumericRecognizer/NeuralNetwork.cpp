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

void NeuralNetwork::train(int** trainingData, int** d_tr, 
	const int dataSize, const int inputSize, const int outputSize)
{
	int *input = new int[inputSize];	// �Է� ��ȣ�� ������ �ִ� ���� INPUT
	int *d = new int[outputSize];		// ���� ���̺��� ������ ���� D

	for (int i = 0; i < dataSize; i++) {
		// i ��° �Ʒ� ������ ���� �Ʒ���.

		// trainingData�� �� ���� �о input ������ ä��.
		for (int j = 0; j < inputSize; j++) {
			input[j] = trainingData[i][j];
		}

		// d_tr�� �� ���� �о d ������ ä��.
		for (int j = 0; j < outputSize; j++) {
			d[j] = d_tr[i][j];
		}

		inputData(input, inputSize);

		computeForward();
		computeBackward();
		updateWeights();
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
	// ��� ����ġ W ���͸� random number�� �ʱ�ȭ��.
	for (int i = 0; i < m_layerSizes[0]; i++) {
		m_neurons[0][i].connect(data, size);
	}
}

void NeuralNetwork::computeForward()
{
	/*** Forward ��� ***/
	// �� ���� ���� s �� f�� ���
	for (int l = 0; l < m_width; l++) {	// �� L�� ���ؼ�,
		for (int i = 0; i < m_layerSizes[l]; i++) {	// �� L ���� ���� i�� ���Ͽ�
			m_neurons[l][i].computeF();				// s�� f�� ���
		}
	}
}

void NeuralNetwork::computeBackward()
{
	/*** Backward ��� ***/
	// �� ���� ���� delta�� ���
	for (int l = m_width - 1; l >= 0; l--) {	// �� L�� ���ؼ�,
		for (int i = 0; i < m_layerSizes[l]; i++) {	// �� ���� i�� ���Ͽ�
			m_neurons[l][i].computeDelta();			// delta�� ���
		}
	}
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
