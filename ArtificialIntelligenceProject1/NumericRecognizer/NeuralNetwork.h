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
	// Neural Network 훈련 (Training Part)
	int train(int** trainingData, int** d_tr, const int dataSize, 
		const int inputSize, const double trainTreshold = DefaultTrainTreshold);

	// 단일 Epoch의 훈련
	void trainEpoch(int** trainingData, int** d_tr, 
		const int dataSize, const int inputSize);

	// 단일 Epoch의 평균 에러 계산
	double getAvgSqErrorOfEpoch(int** trainingData, 
		int** d_tr, const int dataSize, const int inputSize);

	// Neural Network 테스트
	// 훈련이 종료된 이후에 test data를 이용하여 시스템의 성능을 측정한다.
	double test(int** testData, int** d_te, const int dataSize, const int inputSize);

	// 숫자 인식 수행
	int recognize(int* data, int dataSize);

private:
	// Forward Propagation (Forward 계산)
	// 모든 뉴런의 s, f를 순방향으로 계산한다.
	void computeForward(int input[], const int inputSize);

	// Backward Propagation (Backward 계산)
	// 모든 뉴런의 delta를 역방향으로 계산한다.
	void computeBackward(int d[]);

	// Weight Update
	// 모든 뉴런의 weights를 delta를 이용하여 갱신한다.
	void updateWeights();


public:
	/* Accessors */
	// Get Output Size
	// 출력 데이터 개수는 마지막 레이어의 뉴런 개수와 같음.
	int getOutputSize();

	// Get Last Layer
	Layer& getLastLayer();


private:
	/* Attributes */
	Neuron **m_neurons = nullptr;	// 뉴런
	int m_width = 0;				// 레이어 개수
	int *m_layerSizes = nullptr;	// 레이어별 뉴런 개수
};

