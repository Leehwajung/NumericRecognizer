#pragma once
#include "Object.h"
#include "Dendrite.h"


class Neuron : public Object
{
public:
	/* Constructor / Destructor */

	// ���� ����: dendritesSize�� ���� �������� ���� ����
	Neuron(int dendritesSize);

	// Destructor
	~Neuron();

	/* Operations */

	// Boolean Function ���
	double computeF();

	// Delta ���
	double computeDelta();


	/* Accessers */

	// get f
	double getF();

	// get ��
	double getDelta();

	// get Dendrite
	Dendrite* getDendrite(int index);	


private:
	/* Attributes */
	double m_s;				// s
	double m_f;				// f (������ ���)
	double m_delta;			// ��
	Dendrite *m_dendrites;	// �ٸ� �������� ������ ��Ÿ���� ���� �迭 (W ���͸� ����)
	Neuron *mp_next;		// ���� �� ���� ������

	/* Supports */
	bool mb_f;				// f ��� ����
	bool mb_delta;			// �� ��� ����
	int m_dendritesSize;	// ���� �迭 ũ��
};

