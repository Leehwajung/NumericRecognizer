#pragma once
#include "Object.h"


class Neuron;

class Dendrite : public Object
{
public:
	/* Constructor / Destructor */

	// Constructor
	Dendrite();

	// Destructor
	~Dendrite();


	/* Mutators */

	// �ʱ� �Է°� ���� (����)
	// ���� ����: input�� �ʱ� �Է� ������
	// ���� ����: ���� ������ ���� (nullptr)
	void connect(double input);

	// ���� ���� ����
	// ���� ����: prevNeuron�� ������ ���� ����
	// ���� ����: �Է� �����ʹ� prevNeuron�� f
	void connect(Neuron* prevNeuron);


	/* Accessers */

	// get X
	double getInput();

	// get W
	double getWeight();


private:
	/* Attributes */
	double m_X;			// X (�Է°� ����, ���� ���)
	double m_W;			// W (����ġ ����, Weight)
	Neuron *mp_prev;	// ���� �� ���� ������
};

