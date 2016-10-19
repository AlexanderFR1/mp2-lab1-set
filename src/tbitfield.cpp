// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField :: TBitField (int len)
{
	if (len<0)
	{
		throw "negative value";
	}
	BitLen = len;
		MemLen = (len + sizeof (TELEM) * 8 - 1) / (sizeof (TELEM) * 8);
		pMem = new TELEM [MemLen];
		for (int i = 0; i < MemLen; i ++)
			pMem [i] = 0;

}

TBitField :: TBitField (const TBitField & bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM [MemLen];
	for (int i = 0; i < MemLen; i ++)
		pMem [i] = bf.pMem [i];

}

TBitField :: ~ TBitField ()
{
	delete [] pMem;
	pMem = NULL;
}

int TBitField :: GetMemIndex (const int n) const // индекс Мем для бита n
{
	return (n / (sizeof (TELEM) * 8));
}

TELEM TBitField :: GetMemMask (const int n) const // битовая маска для бита n
{
	return 1 << (n & (sizeof (TELEM) * 8 - 1));
}

// доступ к битам битового поля

int TBitField :: GetLength (void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField :: SetBit (const int n) // установить бит
{
	if (n<0)
	{
		throw "negative value";
	}
	if (n>BitLen)
	{
		throw "too large value";
	}
		pMem [GetMemIndex (n)] |= GetMemMask (n);
}

void TBitField :: ClrBit (const int n) // очистить бит
{
	if (n<0)
	{
		throw "negative value";
	}
	if (n>BitLen)
	{
		throw "too large value";
	}
		pMem [GetMemIndex (n)] &= ~GetMemMask (n);

}

int TBitField :: GetBit (const int n) const // получить значение бита
{
	if (n<0)
	{
		throw "negative value";
	}
	if (n>BitLen)
	{
		throw "too large value";
	}
		return pMem [GetMemIndex (n)] & GetMemMask (n);

}

// битовые операции

TBitField & TBitField :: operator = (const TBitField & bf) // присваивание
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	delete [] pMem;
	pMem = new TELEM [MemLen];
	for (int i = 0; i < MemLen; i ++)
		pMem [i] = bf.pMem [i];
	return * this;

}

int TBitField :: operator == (const TBitField & bf) const // сравнение
{
	if (BitLen == bf.BitLen)
    {
        int flag = 1;
        for (int i = 0; i < MemLen; i ++)
			if (pMem[i] != bf.pMem [i])
            {
                flag = 0;
                break;
            }
        return flag;
    }
    else
        return 0;
}

int TBitField :: operator != (const TBitField & bf) const // сравнение
{
  if (BitLen == bf.BitLen)
    {
        int flag = 0;
        for (int i = 0; i < MemLen; i ++)
			if (pMem[i] != bf.pMem[i])
            {
				flag = 1;
                break;
            }
			return flag;
    }
    else
		return 1;
}

TBitField TBitField :: operator | (const TBitField & bf) // операция "или"
{
	int len;
	if (BitLen > bf.BitLen)
		len = BitLen;
	else
		len = bf.BitLen;
	TBitField temp (len);
	for (int i = 0; i < temp.MemLen ; i ++)
		temp.pMem [i] = bf.pMem [i];
	int memoryLenTEMP;
	if (MemLen > temp.MemLen)
		memoryLenTEMP = temp.MemLen;
	else
		memoryLenTEMP = MemLen;
	for (int i = 0; i < memoryLenTEMP; i ++)
		temp.pMem [i] |= pMem [i]; // где "|=" - побитовое "ИЛИ" (OR), совмещённое с присваиванием
	return temp;
}

TBitField TBitField :: operator & (const TBitField & bf) // операция "и"
{
	int len;
	if (BitLen > bf.BitLen)
		len = BitLen;
	else
		len = bf.BitLen;
	TBitField temp (len);
	int memoryLenTEMP;
	if (MemLen > temp.MemLen)
		memoryLenTEMP = temp.MemLen;
	else
		memoryLenTEMP = MemLen;
	for (int i = 0; i < memoryLenTEMP ; i ++)
		temp.pMem [i] = bf.pMem [i];
	for (int i = 0; i < memoryLenTEMP; i ++)
		temp.pMem [i] &= pMem [i]; // где &= - побитовое "И" (AND), совмещённое с присваиванием
	for (int i = memoryLenTEMP; i < temp.MemLen; i ++)
		temp.pMem [i] = 0;
	return temp;
}

TBitField TBitField :: operator ~ (void) // отрицание
{
	TBitField bf = (*this);
    for (int i = 0; i < BitLen; i ++)
    {
        if (bf.GetBit (i))
            bf.ClrBit (i);
        else
            bf.SetBit (i);
    }
    return bf;
}
 
// ввод/вывод

istream & operator >> (istream & istr, TBitField & bf) // ввод
{
	int i = 0; 
	char symbol;
	do
		istr >> symbol;
	while (symbol != ' ');
	while (true)
	{
		istr >> symbol;
		if (symbol == '0')
			bf.ClrBit (i ++);
		else if (symbol == '1')
			bf.SetBit (i ++);
		else 
			break;
	}
	return istr;
}

 ostream & operator << (ostream & ostr, const TBitField & bf) // вывод
{
	int len = bf.GetLength ();
	for (int i = 0; i < len; i ++)
	{
		if (bf.GetBit (i))
			ostr << '1';
		else 
			ostr << '0';
	}
	return ostr;
}
