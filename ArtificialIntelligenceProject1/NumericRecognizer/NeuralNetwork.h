#pragma once
#include "Object.h"
#include "Neuron.h"


/*
 * Neural Network
 */
class NeuralNetwork : public Object
{
public:
	/* Constructor / Destructor */
	// Constructor
	NeuralNetwork(const int width, const int layerSizes[]);

	// Destructor
	~NeuralNetwork();


	/* Operations */

	// Neural Network �Ʒ�
	void train(int** trainingData, int** d_tr, const int dataSize, const int inputSize, const int outputSize);

	// Neural Network �׽�Ʈ
	void test(const int** testData, const int** d_te, const int dataSize, const int inputSize, const int outputSize);

	// ���� �ν� ����
	void recognize();

private:
	// Forward Propagation (Forward ���)
	void computeForward(int input[], const int inputSize);

	// Backward Propagation (Backward ���)
	void computeBackward(int d[], const int dSize);

	// Weight Update
	void updateWeights();


private:
	/* Attribute */
	Neuron **m_neurons = nullptr;


	/* Supports */
	int m_width = 0;
	int *m_layerSizes = nullptr;
};

