#include "ClassLN.h"

void ClassLN::ReadText(const char* filename)
{
    ClassLN res;
    res.num = ReadTextFile(filename);
    *this = res;
}

void ClassLN::ReadBin(const char* filename)
{
    ClassLN res;
    res.num = ReadBinFile(filename);
    *this = res;
}

void ClassLN::WriteText(const char* filename)
{
    WriteTextFile(filename, this->num);
}

void ClassLN::WriteBin(const char* filename)
{
    WriteBinFile(filename, this->num);
}

void ClassLN::ClearMemory()
{
    free((*this).num.pointer);
}

ClassLN& ClassLN::operator=(const ClassLN& rhv)
{
    this->num = copy(rhv.num);
    return *this;
}

ClassLN ClassLN::operator+(ClassLN &right)
{
    ClassLN res;
    res.num = ADD(this->num, right.num);
    return res;
}

ClassLN ClassLN::operator-(ClassLN &right)
{
    ClassLN res;
    res.num = SUB(this->num, right.num);
    return res;;
}

ClassLN ClassLN::operator*(ClassLN &right)
{
    ClassLN res;
    res.num = MUL(this->num, right.num);
    return res;
}

ClassLN ClassLN::operator/(ClassLN &right)
{
    ClassLN res;
    res.num = DIV(this->num, right.num, 1);
    return res;
}

ClassLN ClassLN::operator%(ClassLN &right)
{
    ClassLN res;
    res.num = DIV(this->num, right.num, 2);
    return res;
}

ClassLN PowMod(ClassLN &base, ClassLN &exp, ClassLN &mod)
{
    ClassLN res;
    res.num = DEGREE(base.num, exp.num, mod.num);
    return res;
}
