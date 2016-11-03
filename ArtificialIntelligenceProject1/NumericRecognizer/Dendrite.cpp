#include "Dendrite.h"

#include <iostream>	// for srand(), rand() and RAND_MAX
#include <ctime>	// for time()
#include "Neuron.h"


bool Dendrite::mb_setRandomSeed = false;

Dendrite::Dendrite()
{
	/*** ����ġ ������ �ʱ�ȭ ***/
	if (!mb_setRandomSeed) {	// Initial Random Number Generation
		srand(unsigned int(time(NULL)));
		mb_setRandomSeed = true;
	}
	int sign = 1;
	if (rand() % 2) {
		sign = -1;
	}
	m_W = sign * (double(rand()) / double(RAND_MAX));	// ����ġ W ���͸� Random Number�� �ʱ�ȭ��.
	mp_prev = nullptr;
}

Dendrite::~Dendrite()
{
}

void Dendrite::updateWeight(double learningRate)
{
	/*** ����ġ ���� �۾� ***/
	m_W += learningRate * getNucleus()->getDelta() * getInput();	// dummy input�� ���� ��굵 �Բ� ����.
}

void Dendrite::connect(double input)
{
	m_X = input;
	mp_prev = nullptr;
	mb_connected = true;
}

void Dendrite::connect(Neuron* prevNeuron)
{
	m_X	= 0;	// dummy
	if (prevNeuron) {
		mp_prev = prevNeuron;
		mb_connected = true;
	}
	else {
		mp_prev = nullptr;
		mb_connected = false;
	}
}

double Dendrite::getInput()
{
	if (mp_prev) {
		return mp_prev->getF();	// �� ���� ������ ����� �Է��� ��.
	}
	else {
		return m_X;
	}
}

double Dendrite::getWeight()
{
	return m_W;
}

Neuron * Dendrite::getNucleus()
{
	return mp_nucleus;
}

void Dendrite::setNucleus(Neuron* nucleus)
{
	mp_nucleus = nucleus;
}
