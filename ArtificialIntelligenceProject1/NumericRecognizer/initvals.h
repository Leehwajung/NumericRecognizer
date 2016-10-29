#pragma once


// Dummy Input
#define Dummy	1

// Layer
#define NLayer	3		// Layer 의 수
#define MLayerSize	65	// Max Layer Size (즉, Layer가 가질 수 있는 최대 뉴론 수)

// 0, 1, 2 층의 뉴론의 수: 상수 (m0, m1, m2)로 선언함.
#define m0	3
#define m1	2
#define m2	3

// 입력 신호의 수: N
#define N	(64 + Dummy)	// Dummy Input 1 포함.

// 데이타 개수
#define N_tr_examples	600	// 훈련 데이타 개수
#define N_te_examples	90	// 테스트 데이타 개수
