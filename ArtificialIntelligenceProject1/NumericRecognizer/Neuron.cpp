#include "Neuron.h"

#include <cmath>
#include "global.h"


Neuron::Neuron()
{
}

Neuron::~Neuron()
{
	if (m_dendrites) {
		delete[] m_dendrites;
	}
}

double Neuron::computeF()
{
	/*** Forward ��� ***/
	// s �� ���
	m_s = 0;
	for (int i = 0; i < m_dendritesSize; i++) {	// ������ ������ ��¸��ٰ� �Է��� ��.
		m_s += m_dendrites[i].getInput() * m_dendrites[i].getWeight();	// ���� �Է� ó���� ���Ե�!
	}

	// f �� ���
	m_f = 1 / (1 + exp(-m_s));

	mb_f = true;
	return m_f;
}

double Neuron::computeDelta()
{
	mb_delta = true;
	return m_delta;
}

void Neuron::connect(int input[], int inputSize)
{
	if (m_dendritesSize < inputSize) {
		generateDendrites(inputSize);
	}
	for (int i = 0; i < inputSize; i++) {
		m_dendrites[i].connect(input[i]);
	}
}

void Neuron::connect(Layer layer, int layerSize)
{
	if (m_dendritesSize <= layerSize) {
		generateDendrites(layerSize + 1);	// �� ���� ������ ���� ������.
	}
	for (int i = 0; i < layerSize; i++) {
		m_dendrites[i].connect(&layer[i]);	// ���� ������� ����
		layer[i].connect(this);				// ���� ������ ���� (���� ������ ���� ������ ���� ����)
	}
	m_dendrites[layerSize].connect(DUMMY);	// ���� �Է� ó����!
}

void Neuron::connect(Neuron* nextNeuron)
{
	mp_next = nextNeuron;
}

void Neuron::generateDendrites(int dendritesSize)
{
	if (m_dendrites) {
		delete[] m_dendrites;
		m_dendrites = nullptr;
		m_dendritesSize = 0;
	}
	if (!m_dendrites && dendritesSize > 0) {
		m_dendrites = new Dendrite[dendritesSize];
		m_dendritesSize = dendritesSize;
	}
}

double Neuron::getF()
{
	if (mb_f) {
		return m_f;
	}
	else {
		return computeF();
	}
}

double Neuron::getDelta()
{
	if (m_delta) {
		return m_delta;
	}
	else {
		return computeDelta();
	}
}

Dendrite* Neuron::getDendrite(int index)
{
	if (index > 1 && index <= m_dendritesSize) {
		return &m_dendrites[index - 1];
	}
	return nullptr;
}

int Neuron::getDendritesSize()
{
	return m_dendritesSize;
}

Neuron * Neuron::getNext()
{
	return mp_next;
}
