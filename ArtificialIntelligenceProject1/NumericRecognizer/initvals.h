#pragma once


// Dummy Input
#define Dummy	1

// Layer
#define NLayer	3		// Layer �� ��
#define MLayerSize	65	// Max Layer Size (��, Layer�� ���� �� �ִ� �ִ� ���� ��)

// 0, 1, 2 ���� ������ ��: ��� (m0, m1, m2)�� ������.
#define m0	3
#define m1	2
#define m2	3

// �Է� ��ȣ�� ��: N
#define N	(64 + Dummy)	// Dummy Input 1 ����.

// ����Ÿ ����
#define N_tr_examples	600	// �Ʒ� ����Ÿ ����
#define N_te_examples	90	// �׽�Ʈ ����Ÿ ����
