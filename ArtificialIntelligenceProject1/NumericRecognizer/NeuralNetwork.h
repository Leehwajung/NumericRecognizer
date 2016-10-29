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

	// Neural Network �Ʒ�
	void train();

	// Neural Network �׽�Ʈ
	void test();

	// ���� �ν� ����
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

