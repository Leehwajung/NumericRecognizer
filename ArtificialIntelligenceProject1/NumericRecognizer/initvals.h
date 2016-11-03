#pragma once
#include "global.h"


/*** 데이터 구조 ***/
// NN 구조
#define NLayer	3		// Layer 의 수
#define MLayerSize	65	// Max Layer Size (즉, Layer가 가질 수 있는 최대 뉴런 수)

// 0, 1, 2 층의 뉴런의 수: 상수 (m0, m1, m2)로 선언함.
#define m0	3
#define m1	2
#define m2	3
const int M[NLayer] = { m0, m1, m2 };

// 입력 신호의 수: N
#define N	(64 + DUMMY)	// Dummy Input 1 포함.

// 데이터 개수
#define N_tr_examples	600	// 훈련 데이터 개수
#define N_te_examples	90	// 테스트 데이터 개수

// 학습률
#define C	0.5

// 훈련 임계치
#define TrainingTreshold	0.001
