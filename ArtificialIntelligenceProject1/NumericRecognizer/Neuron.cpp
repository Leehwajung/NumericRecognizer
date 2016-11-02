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
	if (mp_axon) {
		delete[] mp_axon;
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
	/*** Backward ��� ***/
	m_delta = 0;

	// ���� �� ������ delta ���
	if (mb_desire) {
		m_delta = m_desire - getF();
	}

	// ���� �� ���� ���鿡 ���� delta ���
	else {
		for (int i = 1; i <= m_axonSize; i++) {
			m_delta += getNext(i)->getNucleus()->getDelta() * getNext(i)->getWeight();
		}
	}

	// delta ���
	m_delta *= getF() * (1 - getF());

	mb_delta = true;
	return m_delta;
}

void Neuron::updateWeights()
{
	/*** ����ġ ���� �۾� ***/
	for (int i = 0; i < m_dendritesSize; i++) {	// �ش� ���������� �� �����κ����� �Է� ��ȣ ��ȣ (dummy ��ȣ ����)
		m_dendrites[i].updateWeight();
	}
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
		m_dendrites[i].connect(&layer[i]);			// ���� ������� ����
		layer[i].connect(&m_dendrites[i]);	// ���� ������ ���� (���� ������ ���� ������ ���� ����)
	}
	m_dendrites[layerSize].connect(DUMMY);	// ���� �Է� ó����!
}

void Neuron::connect(int desire)
{
	m_desire = desire;
	mb_desire = true;
	m_axonArrSize = 1;
	if (mp_axon) {
		delete[] mp_axon;
		mp_axon = nullptr;
	}
}

void Neuron::connect(Dendrite* dendrite)
{
	if (dendrite) {
		mb_desire = false;
		if (m_axonSize >= m_axonArrSize) {
			setAxon(m_axonArrSize + 1);
			m_axonSize = m_axonArrSize - 1;
		}
		mp_axon[m_axonSize++] = dendrite;
	}
}

void Neuron::generateDendrites(int dendritesSize)
{
	if (m_dendrites) {
		delete[] m_dendrites;
		m_dendrites = nullptr;
		m_dendritesSize = 0;
		m_s = 0;
		m_f = 0;
		mb_f = false;
	}
	if (!m_dendrites && dendritesSize > 0) {
		m_dendrites = new Dendrite[dendritesSize];
		m_dendritesSize = dendritesSize;
		for (int i = 0; i < dendritesSize; i++) {
			m_dendrites[i].setNucleus(this);
		}
	}
}

void Neuron::setAxon(int size)
{
	if (mp_axon && m_axonArrSize != size) {
		delete[] mp_axon;
		mp_axon = nullptr;
		m_axonArrSize = 0;
		m_delta = 0;
		mb_delta = false;
		m_desire = 0;
		m_axonSize = 0;
	}
	if (!mp_axon && size > 0) {
		mp_axon = new Dendrite*[size];
		m_axonArrSize = size;
		m_axonSize = 0;
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
	if (index >= 1 && index <= m_dendritesSize) {
		return &m_dendrites[index - 1];
	}
	return nullptr;
}

int Neuron::getDendritesSize()
{
	return m_dendritesSize;
}

Dendrite* Neuron::getNext(int index)
{
	if (mp_axon && index >= 1 && index <= m_axonSize) {
		return mp_axon[index - 1];
	}
	return nullptr;
}

int Neuron::getAxonSize()
{
	return m_axonSize;
}
