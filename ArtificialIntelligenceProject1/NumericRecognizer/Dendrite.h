#pragma once
#include "Object.h"


class Neuron;

/*
 * 수상돌기 (뉴런 간 연결, weight)
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
	// 초기 입력값 전달 (설정)
	// 사전 조건: input는 초기 입력 데이터
	// 사후 조건: 이전 뉴런은 없음 (nullptr)
	void connect(double input);

	// 이전 뉴런 연결
	// 사전 조건: prevNeuron는 연결한 이전 뉴런
	// 사후 조건: 입력 데이터는 prevNeuron의 f
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
	double m_X = 0;				// X (입력값 벡터, 이전 출력)
	double m_W = 0;				// W (가중치 벡터, Weight)
	Neuron *mp_nucleus;			// 뉴런 본체
	Neuron *mp_prev = nullptr;	// 이전 층 뉴런 포인터


	/* Supports */
	bool mb_connected = false;
	static bool mb_setRandomSeed;
};

