#pragma once
#include "Object.h"
#include "Dendrite.h"


class Neuron : public Object
{
public:
	/* Constructor / Destructor */

	// 사전 조건: dendritesSize는 이전 뉴런과의 연결 개수
	Neuron(int dendritesSize);

	// Destructor
	~Neuron();

	/* Operations */

	// Boolean Function 계산
	double computeF();

	// Delta 계산
	double computeDelta();


	/* Accessers */

	// get f
	double getF();

	// get δ
	double getDelta();

	// get Dendrite
	Dendrite* getDendrite(int index);	


private:
	/* Attributes */
	double m_s;				// s
	double m_f;				// f (뉴런의 출력)
	double m_delta;			// δ
	Dendrite *m_dendrites;	// 다른 뉴런과의 연결을 나타내는 동적 배열 (W 벡터를 포함)
	Neuron *mp_next;		// 다음 층 뉴런 포인터

	/* Supports */
	bool mb_f;				// f 계산 여부
	bool mb_delta;			// δ 계산 여부
	int m_dendritesSize;	// 동적 배열 크기
};

