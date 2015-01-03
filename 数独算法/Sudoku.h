#pragma once

#include <stack>
#include <stdlib.h>
#include "Unit.h"
using namespace std;



class CSudoku
{
public:
	CSudoku(){}
	CSudoku(int lattice[9][9]);
	~CSudoku(){}

	int getDigit(int i, int j);

	bool StartCount();

private:
	enum Flag
	{
		normal = 0,
		notonly,
		nosln
	};

	class CCache		//����״̬
	{
	public:
		CCache(CUnit lattice[9][9], int i, int j, int digit);

		CUnit m_lattice[9][9];
		int m_i;
		int m_j;
		int m_digit;
	};
private:
	CUnit m_lattice[9][9];			//��ʾ�������ӵľ���
	stack<CCache> m_cache;			//�洢����״̬��ջ

	void getStartPos(int i, int j, int &s_i, int &s_j);			//��ȡi, j���ھŹ���ĳ�ʼ����
	int BitCount(int bit);			//������������ж��ٸ�1
	void updataFill(int i, int j);	//����ָ�����ӵĿ������
};

