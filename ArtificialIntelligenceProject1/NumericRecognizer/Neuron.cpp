#include "Neuron.h"


Neuron::Neuron(int dendritesSize)
	: m_dendritesSize(dendritesSize), mb_f(false), mb_delta(false)
{
	m_dendrites = new Dendrite[dendritesSize];
}

Neuron::~Neuron()
{
	if (m_dendrites != nullptr) {
		delete[] m_dendrites;
	}
}

double Neuron::computeF()
{
	mb_f = true;
	return m_f;
}

double Neuron::computeDelta()
{
	mb_delta = true;
	return m_delta;
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
	if (index > 0 && index < m_dendritesSize) {
		return &m_dendrites[index];
	}
	return nullptr;
}
