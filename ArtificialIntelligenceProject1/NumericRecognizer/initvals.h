#pragma once
#include "global.h"


/*** ������ ���� ***/
// NN ����
#define NLayer	3		// Layer �� ��
#define MLayerSize	65	// Max Layer Size (��, Layer�� ���� �� �ִ� �ִ� ���� ��)

// 0, 1, 2 ���� ������ ��: ��� (m0, m1, m2)�� ������.
#define m0	3
#define m1	2
#define m2	3
const int M[NLayer] = { m0, m1, m2 };

// �Է� ��ȣ�� ��: N
#define N	(64 + DUMMY)	// Dummy Input 1 ����.

// ������ ����
#define N_tr_examples	600	// �Ʒ� ������ ����
#define N_te_examples	90	// �׽�Ʈ ������ ����

// �н���
#define C	0.5

// �Ʒ� �Ӱ�ġ
#define TrainingTreshold	0.001
