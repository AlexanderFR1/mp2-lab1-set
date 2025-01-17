// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(-1)
{
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(-1)
{
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(-1)
{
}

TSet::operator TBitField()
{
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	return BitField.GetBit(Elem);//если получим ненулевой, то вернёт true
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	BitField=s.BitField;
	MaxPower=s.MaxPower;
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	return BitField==s.BitField;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	return BitField!=s.BitField;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	return BitField|s.BitField;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	return BitField|Elem;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	return BitField|(~Elem);
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	return BitField&s.BitField;
}

TSet TSet::operator~(void) // дополнение
{
	return ~BitField;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	int currentElem;
	char symbol;
	do
	{
		istr>>symbol;
	}
	while (symbol!='{');
	do
	{
		istr>>currentElem;
		s.InsElem(currentElem);
		do 
		{
			istr>>symbol;
		}
		while ( (symbol!=',') && (symbol!='}') );
	}
	while (symbol!='}');
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	int size;
	char symbol;
	symbol=' ';
	ostr<<'{';
	size=s.GetMaxPower();
	for (int i=0;i<size;i++)
	{
		if ( s.IsMember(i) )
		{
			ostr<<symbol<<'x'<<i<<'='<<s.BitField.GetBit(i)<<' ';
			symbol=',';
		}
	}
	ostr<<'}';
	return ostr;
}
