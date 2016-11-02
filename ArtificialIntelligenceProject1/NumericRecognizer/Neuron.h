#pragma once
#include "Object.h"
#include "Dendrite.h"


typedef Neuron* Layer;	// Layer is ARRAY of Neurons

/*
 * ���� (TLU, Sigmoid Unit)
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

	// �䱸�Ǵ� �� ���� (for Layer LAST)
	void connect(int desire);

	// ���� ������ ���� (for Other Layers)
	void connect(Dendrite* dendrite);


private:
	/* Mutators */
	// Dendrites ����
	// ���� ����: dendritesSize�� ���� �������� ���� ����
	void generateDendrites(int dendritesSize);

public:
	// Set Axon Array S
	void setAxon(int size);


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

	// Get Dendrite of Next Neuron
	// ���� ����: index�� 1 �̻� AxonSize ����!
	Dendrite* getNext(int index);

	// Get Axon Array Size
	int getAxonSize();


private:
	/* Attributes */
	// ������ ������ ����
	double m_s = 0;						// s
	double m_f = 0;						// f (������ ���)
	double m_delta = 0;					// ��
	int m_desire = 0;					// d
	Dendrite *m_dendrites = nullptr;	// ���� �� �������� ������ ��Ÿ���� ���� �迭 (W ���͸� ����)
	Dendrite **mp_axon = nullptr;		// ���� �� �������� ���� �������� ���� �迭


	/* Supports */
	bool mb_f = false;			// f ��� ����
	bool mb_delta = false;		// �� ��� ����
	bool mb_desire = false;		// ���� ���� ������� ����
	int m_dendritesSize = 0;	// ���� ������ ���� ���� �迭 ũ��
	int m_axonArrSize = 0;		// ���� ������ ���� ���� �迭 ũ��
	int m_axonSize = 0;			// ���� ���� ����� ��� ����
};

