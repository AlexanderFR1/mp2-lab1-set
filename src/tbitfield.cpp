// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	MemLen=(len + sizeof(int)*8-1)/(sizeof(int)*8);//вычисляем колличество используемых 32-битных чисел
	pMem= new TELEM (MemLen);
	for (int i=0;i<MemLen;i++)
			pMem[i]=0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen=bf.BitLen;
	MemLen=bf.MemLen;
	pMem= new TELEM[MemLen];
	for (int i=0; i<MemLen;i++)
			pMem[i]=bf.pMem[i];
}

TBitField::~TBitField()//деструктор
{
	delete pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return n/(sizeof(int)*8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	int j,m;
	m=n%(sizeof(int)*8);
	j=1<<m;
	return j;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	pMem[GetMemIndex(n)]|=GetMemMask(n);//устанавливаем бит в 32-битном числе с соответствующей маской
}

void TBitField::ClrBit(const int n) // очистить бит
{
	pMem[GetMemIndex(n)]&=~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
  return pMem[GetMemIndex(n)] & GetMemMask(n);
  return 0;//pMem относится к классу TELEM, а функция относится к int. поэтому надо что-то вернуть
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	BitLen=bf.BitLen;
	if (MemLen!=bf.MemLen)
	{
		MemLen=bf.MemLen;
			delete pMem;
		pMem=new TELEM[MemLen];
	}
	for (int i=0;i<MemLen;i++)
		pMem[i]=bf.pMem[i];
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	int yes=1;
	if (BitLen!=bf.BitLen)
		yes=0;
	else
		for (int i=0;i<MemLen;i++)
		{
			if (pMem[i]!=bf.pMem[i])
			{
				yes=0;
				break;
			}
		}
  return yes;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	int yes=1;
	if (BitLen==bf.BitLen)
		yes=0;
	else
		for (int i=0;i<MemLen;i++)
		{
			if (pMem[i]==bf.pMem[i])
			{
				yes=0;
				break;
			}
		}
	return yes;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	TBitField tempMultitude(bf.BitLen);
	for (int i=0;i<bf.BitLen;i++)
		tempMultitude.pMem[i]=pMem[i];
	for (int i=0;i<bf.BitLen;i++)
		tempMultitude.pMem[i]|=bf.pMem[i];
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	TBitField tempMultitude(bf.BitLen);
	for (int i=0;i<bf.BitLen;i++)
		tempMultitude.pMem[i]=pMem[i];
	for (int i=0;i<bf.BitLen;i++)
		tempMultitude.pMem[i]&=bf.pMem[i];
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField tempMultitude(BitLen);
	for (int i=0;i<BitLen;i++)
		tempMultitude.pMem[i]= ~pMem[i];//каждый i-й элемент из tempMultitude присваивает отрицание из соотв. pMem[i]
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	char element;
	int count = 0;
	do
	{
		istr>>element;
	}
	while (element !=' ');
	while(1)
	{
		istr>>element;
		if (element=='0')
			bf.ClrBit(count++);
		else
			if (element=='1')
				bf.SetBit(count++);
		else
			break;
	}
		return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	int length = bf.GetLength();
	for (int i=0;i<length;i++)
	{
		if (bf.GetBit(i))//то есть, если при взятии значения бита получили не ноль,то выводим 1
			ostr<<'1';
		else
			ostr<<'0';
	}
	return ostr;
}
