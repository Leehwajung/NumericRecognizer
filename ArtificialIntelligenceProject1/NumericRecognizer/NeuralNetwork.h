#pragma once
#include "Object.h"
#include "Neuron.h"

#define DefaultTrainTreshold	0.001


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
	// Neural Network �Ʒ� (Training Part)
	int train(int** trainingData, int** d_tr, const int dataSize, 
		const int inputSize, const double trainTreshold = DefaultTrainTreshold);

	// ���� Epoch�� �Ʒ�
	void trainEpoch(int** trainingData, int** d_tr, 
		const int dataSize, const int inputSize);

	// ���� Epoch�� ��� ���� ���
	double getAvgSqErrorOfEpoch(int** trainingData, 
		int** d_tr, const int dataSize, const int inputSize);

	// Neural Network �׽�Ʈ
	// �Ʒ��� ����� ���Ŀ� test data�� �̿��Ͽ� �ý����� ������ �����Ѵ�.
	double test(int** testData, int** d_te, const int dataSize, const int inputSize);

	// ���� �ν� ����
	int recognize(int* data, int dataSize);

private:
	// Forward Propagation (Forward ���)
	// ��� ������ s, f�� ���������� ����Ѵ�.
	void computeForward(int input[], const int inputSize);

	// Backward Propagation (Backward ���)
	// ��� ������ delta�� ���������� ����Ѵ�.
	void computeBackward(int d[]);

	// Weight Update
	// ��� ������ weights�� delta�� �̿��Ͽ� �����Ѵ�.
	void updateWeights();


public:
	/* Accessors */
	// Get Output Size
	// ��� ������ ������ ������ ���̾��� ���� ������ ����.
	int getOutputSize();

	// Get Last Layer
	Layer& getLastLayer();


private:
	/* Attributes */
	Neuron **m_neurons = nullptr;	// ����
	int m_width = 0;				// ���̾� ����
	int *m_layerSizes = nullptr;	// ���̾ ���� ����
};

