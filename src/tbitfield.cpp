//tbitfield
// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле
// for commit
#include "tbitfield.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);

#define size sizeof(TELEM) * 8

TBitField::TBitField(int len)
{
    if (len < 0)
        throw length_error("negative length");
    BitLen = len;
    MemLen = ceil(double (len) / size);
    pMem = new TELEM[MemLen]();
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
    delete[] pMem;
    pMem = nullptr;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    if (n >= BitLen)
        throw length_error("index bit out of range");
    if (n < 0)
        throw length_error("negative length");
    int MemIndex = n / size;
    return MemIndex;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    if (n >= BitLen)
        throw length_error("index bit out of range");
    if (n < 0)
        throw length_error("negative length");
    return (1 << (n % size));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n >= BitLen)
        throw length_error("index bit out of range");
    if (n < 0)
        throw length_error("negative length");
    pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] | GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n >= BitLen)
        throw length_error("index bit out of range");
    if (n < 0)
        throw length_error("negative length");
    int MemIndex = GetMemIndex(n);
    int ShiftIndex = GetMemMask(n);
    pMem[MemIndex] = pMem[MemIndex] & (~ShiftIndex);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n >= BitLen)
        throw length_error("index bit out of range");
    if (n < 0)
        throw length_error("negative length");
    return (pMem[GetMemIndex(n)] & GetMemMask(n)) != 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (this != &bf) {
        delete[] pMem;
        BitLen = bf.BitLen;
        MemLen = bf.MemLen;
        pMem = new TELEM[MemLen];
        for (int i = 0; i < MemLen; i++)
            pMem[i] = bf.pMem[i];
    }
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (BitLen != bf.BitLen)
        return 0;
    for (int i = 0; i < MemLen; i++)
        if (pMem[i] != bf.pMem[i])
            return 0;
    return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    if (BitLen != bf.BitLen)
        return 1;
    for (int i = 0; i < MemLen; i++)
        if (pMem[i] != bf.pMem[i])
            return 1;
    return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    int mn = min(MemLen, bf.MemLen);
    TBitField Result(max(BitLen, bf.BitLen));
    for (int i = 0; i < mn; i++)
        Result.pMem[i] = pMem[i] | bf.pMem[i];
    if (MemLen > bf.MemLen) {
        for (int i = mn; i < max(MemLen, bf.MemLen); i++)
            Result.pMem[i] = pMem[i];
    }
    else {
        for (int i = mn; i < max(MemLen, bf.MemLen); i++)
            Result.pMem[i] = bf.pMem[i];
    }
    return Result;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    TBitField Result(max(BitLen, bf.BitLen));
    for (int i = 0; i < min(MemLen, bf.MemLen); i++)
        Result.pMem[i] = pMem[i] & bf.pMem[i];
    return Result;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField Result(*this);
    for (int i = 0; i < Result.GetLength(); i++) {
        if (GetBit(i) == 1)
            Result.ClrBit(i);
        else Result.SetBit(i);
    }
    return Result;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    string Input;
    istr >> Input;
    for (int i = 0; i < bf.MemLen; i++)
        bf.pMem[i] = 0;
    for (int i = 0; i < bf.GetLength(); i++)
        if (Input[i] == '1')
            bf.SetBit(i);
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = 0; i < bf.BitLen; i++)
        ostr << bf.GetBit(i);
    return ostr;
}
