// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len < 0)
		throw "wrong data";
	BitLen = len;
	if (BitLen % 32 != 0) MemLen = BitLen / 32 + 1;
	else MemLen = BitLen / 32;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++) {
		pMem[i] = 0;
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[]pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return n / 32;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	int v = n % 32;
	TELEM tmp = 1;
	return tmp << v;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n < 0) || (n >= BitLen))
		throw "wrong data";
	int i = GetMemIndex(n);
	pMem[i] = pMem[i] | GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n < 0) || (n >= BitLen))
		throw "wrong data";
	int i = GetMemIndex(n);
	TELEM mask = GetMemMask(n);
	mask = ~mask;
	pMem[i] = pMem[i] & mask;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n < 0) || (n >= BitLen))
		throw "wrong data";
	int i = GetMemIndex(n);
	return pMem[i] & GetMemMask(n);
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (MemLen != bf.MemLen) {
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		delete[]pMem;
		pMem = new TELEM[MemLen];
	}
	BitLen = bf.BitLen;
	for (int i = 0; i < MemLen; i++) {
		pMem[i] = bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen)	return 0;
	for (int i = 0; i < MemLen - 1; i++) {
		if (pMem[i] != bf.pMem[i])	return 0;
	}
	for (int i = (MemLen - 1) * 32; i < BitLen; i++) {
		if (GetBit(i) != bf.GetBit(i))	return 0;
	}
	return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen)	return 1;
	for (int i = 0; i < MemLen - 1; i++) {
		if (pMem[i] != bf.pMem[i])	return 1;
	}
	for (int i = (MemLen - 1) * 32; i < BitLen; i++) {
		if (GetBit(i) != bf.GetBit(i))	return 1;
	}
	return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int maxBitLen = bf.BitLen;
	if (BitLen > bf.BitLen) maxBitLen = BitLen;
	TBitField tmp(maxBitLen);
	if (BitLen < bf.BitLen) {
		for (int i = 0; i < MemLen - 1; i++) tmp.pMem[i] = pMem[i];
		for (int i = (MemLen - 1) * 32; i < BitLen; i++) {
			if (GetBit(i)) tmp.SetBit(i);
		}
		for (int i = 0; i < tmp.MemLen; i++) {
			tmp.pMem[i] |= bf.pMem[i];
		}
	}
	else
	{
		for (int i = 0; i < bf.MemLen - 1; i++) tmp.pMem[i] = bf.pMem[i];
		for (int i = (bf.MemLen - 1) * 32; i < bf.BitLen; i++) {
			if (bf.GetBit(i)) tmp.SetBit(i);
		}
		for (int i = 0; i < tmp.MemLen; i++) {
			tmp.pMem[i] |= pMem[i];
		}
	}
	return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int maxBitLen = bf.BitLen;
	if (BitLen > bf.BitLen) maxBitLen = BitLen;
	TBitField tmp(maxBitLen);
	if (BitLen < bf.BitLen) {
		for (int i = 0; i < MemLen - 1; i++) tmp.pMem[i] = pMem[i];
		for (int i = (MemLen - 1) * 32; i < BitLen; i++) {
			if (GetBit(i)) tmp.SetBit(i);
		}
		for (int i = 0; i < tmp.MemLen; i++) {
			tmp.pMem[i] &= bf.pMem[i];
		}
	}
	else
	{
		for (int i = 0; i < bf.MemLen - 1; i++) tmp.pMem[i] = bf.pMem[i];
		for (int i = (bf.MemLen - 1) * 32; i < bf.BitLen; i++) {
			if (bf.GetBit(i)) tmp.SetBit(i);
		}
		for (int i = 0; i < tmp.MemLen; i++) {
			tmp.pMem[i] &= pMem[i];
		}
	}
	return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField tmp(BitLen);
	for (int i = 0; i < MemLen; i++) {
		tmp.pMem[i] = ~pMem[i];
	}
	return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	char c; int k = 0;
	do {
		istr >> c;
		if (c == '1')  bf.SetBit(k);
		if (c == '0')  bf.ClrBit(k);
		k++;
	} while ((c == '1') || (c == '0'));
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++) {
		if (bf.GetBit(i) != 0)
			ostr << 1;
		else ostr << 0;
	}
	return ostr;
}
