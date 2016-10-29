#include "Dendrite.h"
#include <iostream>

#include "Neuron.h"


Dendrite::Dendrite()
{
	m_W = double(rand()) / double(RAND_MAX);
	mp_prev = nullptr;
}

Dendrite::~Dendrite()
{
}

void Dendrite::connect(double input)
{
	m_X = input;
	mp_prev = nullptr;
}

void Dendrite::connect(Neuron* prevNeuron)
{
	m_X = 0;
	mp_prev = prevNeuron;
}

double Dendrite::getInput()
{
	if (mp_prev != nullptr) {
		return mp_prev->getF();
	}
	else {
		return m_X;
	}
}

double Dendrite::getWeight()
{
	return m_W;
}
