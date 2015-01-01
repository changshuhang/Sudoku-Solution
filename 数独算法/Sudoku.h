#pragma once
#include "Unit.h"
#include "stdlib.h"

class CSudoku
{
public:
	CSudoku(){}
	CSudoku(int lattice[9][9]);
	~CSudoku(){}
	
	bool StartCount();
private:
	CUnit m_lattice[9][9];			//��ʾ�������ӵľ���

	void getStartPos(int i, int j, int &s_i, int &s_j);			//��ȡi, j���ھŹ���ĳ�ʼ����
	int BitCount(int bit);			//������������ж��ٸ�1
};

