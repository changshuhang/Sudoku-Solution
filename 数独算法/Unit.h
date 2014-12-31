#pragma once
#define NO_FILL -1
#define ALL_FILL -2
#define ERROR -3

int GetBin(int digital);
int GetDigital(int bin);

class CUnit
{
public:
	int m_fill;			//��ʾ�������
	int m_dig;			//���������0��ʾʲô��û��

	CUnit();

	CUnit &operator =(int dig);
	bool operator ==(int dig);
};