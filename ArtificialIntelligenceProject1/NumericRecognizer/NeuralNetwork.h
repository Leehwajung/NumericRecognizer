#pragma once
#include "Object.h"
#include "Layer.h"


class NeuralNetwork : public Object
{
public:
	/* Constructor / Destructor */

	// Constructor
	NeuralNetwork();

	// Destructor
	~NeuralNetwork();


	/* Operations */

	// Neural Network 훈련
	void train();

	// Neural Network 테스트
	void test();

	// 숫자 인식 수행
	void recognize();

private:
	// Forward Propagation
	void computeForward();

	// Backward Propagation
	void computeBackward();

	// Weight Update
	void updateWeight();


private:
	/* Attribute */
	Layer *m_layers;
};

