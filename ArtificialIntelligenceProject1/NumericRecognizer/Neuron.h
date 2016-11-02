#pragma once
#include "Object.h"
#include "Dendrite.h"


typedef Neuron* Layer;	// Layer is ARRAY of Neurons

/*
 * 뉴런 (TLU, Sigmoid Unit)
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
	// Boolean Function 계산
	double computeF();

	// Delta 계산
	double computeDelta();

	// 입력값 설정 (for Layer 0)
	void connect(int input[], int inputSize);

	// 이전 레이어와 연결 (for Other Layers)
	void connect(Layer layer, int layerSize);

	// 요구되는 값 설정 (for Layer LAST)
	void connect(int desire);

	// 다음 뉴런와 연결 (for Other Layers)
	void connect(Dendrite* dendrite);


private:
	/* Mutators */
	// Dendrites 생성
	// 사전 조건: dendritesSize는 이전 뉴런과의 연결 개수
	void generateDendrites(int dendritesSize);

public:
	// Set Axon Array S
	void setAxon(int size);


	/* Accessers */
	// Get f
	double getF();

	// Get δ
	double getDelta();

	// Get Dendrite
	// 사전 조건: index는 1 이상 DendritesSize 이하!
	Dendrite* getDendrite(int index);

	// Get Dendrites Array Size
	int getDendritesSize();

	// Get Dendrite of Next Neuron
	// 사전 조건: index는 1 이상 AxonSize 이하!
	Dendrite* getNext(int index);

	// Get Axon Array Size
	int getAxonSize();


private:
	/* Attributes */
	// 뉴런의 데이터 구조
	double m_s = 0;						// s
	double m_f = 0;						// f (뉴런의 출력)
	double m_delta = 0;					// δ
	int m_desire = 0;					// d
	Dendrite *m_dendrites = nullptr;	// 이전 층 뉴런과의 연결을 나타내는 동적 배열 (W 벡터를 포함)
	Dendrite **mp_axon = nullptr;		// 다음 층 뉴런과의 연결 포인터의 동적 배열


	/* Supports */
	bool mb_f = false;			// f 계산 여부
	bool mb_delta = false;		// δ 계산 여부
	bool mb_desire = false;		// 최종 층의 노드인지 여부
	int m_dendritesSize = 0;	// 이전 층과의 연결 동적 배열 크기
	int m_axonArrSize = 0;		// 다음 층과의 연결 동적 배열 크기
	int m_axonSize = 0;			// 다음 층과 연결된 노드 개수
};

