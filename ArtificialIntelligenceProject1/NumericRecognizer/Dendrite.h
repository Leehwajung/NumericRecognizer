#pragma once
#include "Object.h"


class Neuron;

/*
 * ���󵹱� (���� �� ����, weight)
 */
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

	// Update W
	void updateWeight(double w);

	// Set Nucleus
	void setNucleus(Neuron* nucleus);


	/* Accessers */
	// Get X
	double getInput();

	// Get W
	double getWeight();

	// Get Nucleus
	Neuron* getNucleus();


private:
	/* Attributes */
	double m_X = 0;				// X (�Է°� ����, ���� ���)
	double m_W = 0;				// W (����ġ ����, Weight)
	Neuron *mp_nucleus;			// ���� ��ü
	Neuron *mp_prev = nullptr;	// ���� �� ���� ������


	/* Supports */
	bool mb_connected = false;
	static bool mb_setRandomSeed;
};

