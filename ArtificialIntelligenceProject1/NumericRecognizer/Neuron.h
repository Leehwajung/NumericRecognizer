#pragma once
#include "Object.h"
#include "Dendrite.h"


typedef Neuron* Layer;	// Layer is ARRAY of Neurons

/*
 * ���� (TLU)
 */
class Neuron : public Object
{
public:
	/* Constructor / Destructor */
	// Constructor
	Neuron();

	// Destructor
	~Neuron();


	/* Operations */
	// Boolean Function ���
	double computeF();

	// Delta ���
	double computeDelta();

	// �Է°� ���� (for Layer 0)
	void connect(int input[], int inputSize);

	// ���� ���̾�� ���� (for Other Layers)
	void connect(Layer layer, int layerSize);


	/* Mutators */
	// ���� ������ ����
	void connect(Neuron* nextNeuron);

private:
	// Dendrites ����
	// ���� ����: dendritesSize�� ���� �������� ���� ����
	void generateDendrites(int dendritesSize);


public:
	/* Accessers */
	// Get f
	double getF();

	// Get ��
	double getDelta();

	// Get Dendrite
	// ���� ����: index�� 1 �̻� DendritesSize ����!
	Dendrite* getDendrite(int index);

	// Get Dendrites Array Size
	int getDendritesSize();

	// Get Next Neuron
	Neuron* getNext();


private:
	/* Attributes */
	// ������ ������ ����
	double m_s = 0;						// s
	double m_f = 0;						// f (������ ���)
	double m_delta = 0;					// ��
	Dendrite *m_dendrites = nullptr;	// �ٸ� �������� ������ ��Ÿ���� ���� �迭 (W ���͸� ����)
	Neuron *mp_next = nullptr;			// ���� �� ���� ������


	/* Supports */
	bool mb_f = false;			// f ��� ����
	bool mb_delta = false;		// �� ��� ����
	int m_dendritesSize = 0;	// ���� �迭 ũ��
};

