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
	CUnit m_lattice[9][9];			//��ʾ�������ӵľ���

	void getStartPos(int i, int j, int &s_i, int &s_j);			//��ȡi, j���ھŹ���ĳ�ʼ����
	int BitCount(int bit);			//������������ж��ٸ�1
	void updataFill(int i, int j);	//����ָ�����ӵĿ������
};

