#pragma once
#include "Neuron.h"


/*
 * Neural Network
 */
class NeuralNetwork
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
		const int inputSize, const double learningRate = C, const double trainTreshold = TrainingTreshold);

	// ���� Epoch�� �Ʒ�
	void trainEpoch(int** trainingData, int** d_tr, 
		const int dataSize, const int inputSize, const double learningRate = C);

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
	void updateWeights(double learningRate = C);


public:
	/* Mutator */
	// �α� ��� ����
	void setPrintingLog(bool set);
	

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


	/* Support */
	bool mb_logPrinting = false;
};

