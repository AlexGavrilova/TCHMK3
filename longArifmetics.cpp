#include <stdio.h>
#include <math.h>
#include "longArifmetics.h"
#include <string.h>
#include <iostream>
#include <fstream>

using namespace std;
longNum::longNum()
{
    numMass = NULL;
    numMassSize = 0;
    longNumSign = '\0';
    base = 0;
}

//define the constructor of longNumber
longNum::longNum(const char* string)
{
    int stringSize = strlen(string);
    int curPos = 0;
    
    if(string[0] == '-')
    {
        this->longNumSign = '-';
        curPos = stringSize;
        stringSize -= 1;
    }
    else
    {
        this->longNumSign = '+';
        curPos = stringSize - 1;
    }
    
    this->base = 1000000000;
    if(!(stringSize % 9))
    {
        this->numMassSize = stringSize / 9;
    }
    else
    {
        this->numMassSize = (stringSize / 9 + 1);
    }
    
    this->numMass = new int[this->numMassSize];
    for(int i = 0; i < this->numMassSize; i++)
    {
        this->numMass[i] = 0;
    }
    
    for(int i = this->numMassSize; i > 0; i--)
    {
        if((curPos - 9) >= 0)
        {
            curPos -= 9;
            for(int j = 0; j < 9; j++)
            {
                this->numMass[i - 1] += (string[curPos + j] - 48)*(int)(pow((double)10, (9 - j - 1)));
            }
        }
        else
        {
            if(string[0] == '-')
            {
                for(int j = 1; j < curPos; j++)
                {
                    this->numMass[i - 1] += (string[j] - 48)*(int)(pow((double)10, (curPos - j - 1)));
                }
            }
            else
            {
                for(int j = 0; j < curPos; j++)
                {
                    this->numMass[i - 1] += (string[j] - 48)*(int)(pow((double)10, (curPos - j - 1)));
                }
            }
        }
    }
}

longNum::~longNum()
{
    if(this->numMass)
    {
        delete [] this->numMass;
    }
}

longNum& longNum::operator=(const longNum& rv)
{
    if(this->numMass)
    {
        delete [] this->numMass;
    }
    
    copylongNum(rv);
    return *this;
}

longNum& longNum::operator+(const longNum& rv)
{
    return sumOrSub(*this, rv, false, rv.longNumSign);
}

longNum& longNum::operator-(const longNum& rv)
{
    char tmpSecSign = '\0';
    if(rv.longNumSign == '-')
    {
        tmpSecSign = '+';
    }
    
    else
    {
        tmpSecSign = '-';
    }
    
    return sumOrSub(*this, rv, true, tmpSecSign);
}

longNum& longNum::operator*(const longNum& rv)
{
    longNum* resultNum = new longNum;
    resultNum->longNumSign = resSign('*', this->longNumSign, rv.longNumSign, this->numMass, rv.numMass, this->numMassSize, rv.numMassSize);
    resultNum->base = this->base;
    resultNum->numMass = multiplication(this->numMass, rv.numMass, resultNum->numMass, this->numMassSize, rv.numMassSize, resultNum->numMassSize, resultNum->base);
    return *resultNum;
}

longNum& longNum::operator/(const longNum& rv)
{
    longNum* resultNum = new longNum;
    resultNum->longNumSign = resSign('/', this->longNumSign, rv.longNumSign, this->numMass, rv.numMass, this->numMassSize, rv.numMassSize);
    resultNum->base = this->base;
    resultNum->numMass = dividing(this->numMass, rv.numMass, resultNum->numMass, this->numMassSize, rv.numMassSize, resultNum->numMassSize, false, resultNum->base);
    return *resultNum;
}

longNum& longNum::operator^(const longNum& rv)
{
    if(rv.longNumSign == '-')
    {
        cout << "Error! Power can't be negative!\n";
        return *this;
    }
    
    longNum* resultNum = new longNum;
    resultNum->longNumSign = this->longNumSign;
    resultNum->base = this->base;
    resultNum->numMass = involution(this->numMass, rv.numMass, resultNum->numMass, this->numMassSize, rv.numMassSize, resultNum->numMassSize, resultNum->base);
    return *resultNum;
}

longNum& longNum::operator%(const longNum& rv)
{
    if((rv.longNumSign == '-') || (this->longNumSign = '-'))
    {
        cout << "Error! Both values mast be positive!\n";
        return *this;
    }
    
    longNum* resultNum = new longNum;
    resultNum->longNumSign = '+';
    resultNum->base = this->base;
    resultNum->numMass = rest(this->numMass, rv.numMass, resultNum->numMass, this->numMassSize, rv.numMassSize, resultNum->numMassSize, resultNum->base);
    return *resultNum;
}

bool longNum::operator==(const longNum& rv)
{
    if(resSign('+', this->longNumSign, rv.longNumSign, this->numMass, rv.numMass, this->numMassSize, rv.numMassSize) == '=')
    {
        return true;
    }
    
    return false;
}

bool longNum::operator!=(const longNum& rv)
{
    if(resSign('+', this->longNumSign, rv.longNumSign, this->numMass, rv.numMass, this->numMassSize, rv.numMassSize) == '=')
    {
        return false;
    }
    
    return true;
}

bool longNum::operator>=(const longNum& rv)
{
    char tempSecSign = '\0';
    
    if(rv.longNumSign == '+')
    {
        tempSecSign = '-';
    }
    else
    {
        tempSecSign = '+';
    }
    
    if(resSign('+', this->longNumSign, tempSecSign, this->numMass, rv.numMass, this->numMassSize, rv.numMassSize) == '-')
    {
        return false;
    }
    
    return true;
}

bool longNum::operator<=(const longNum& rv)
{
    char tempSecSign = '\0';
    
    if(rv.longNumSign == '+')
    {
        tempSecSign = '-';
    }
    else
    {
        tempSecSign = '+';
    }
    
    if(resSign('+', this->longNumSign, tempSecSign, this->numMass, rv.numMass, this->numMassSize, rv.numMassSize) == '+')
    {
        return false;
    }
    
    return true;
}

bool longNum::operator>(const longNum& rv)
{
    char tempSecSign = '\0';
    
    if(rv.longNumSign == '+')
    {
        tempSecSign = '-';
    }
    else
    {
        tempSecSign = '+';
    }
    
    if(resSign('+', this->longNumSign, tempSecSign, this->numMass, rv.numMass, this->numMassSize, rv.numMassSize) == '+')
    {
        return true;
    }
    
    return false;
}

bool longNum::operator<(const longNum& rv)
{
    char tempSecSign = '\0';
    
    if(rv.longNumSign == '+')
    {
        tempSecSign = '-';
    }
    else
    {
        tempSecSign = '+';
    }
    
    if(resSign('+', this->longNumSign, tempSecSign, this->numMass, rv.numMass, this->numMassSize, rv.numMassSize) == '-')
    {
        return true;
    }
    
    return false;
}

bool longNum::read(char* inFileName, int base)
{
    numMass = readFIle(inFileName, base, longNum::numMassSize, longNum::longNumSign);
    if(!numMass)
    {
        return false;
    }
    longNum::base = base;
    return true;
}

bool longNum::write(char* outFileName)
{
    return writeFile(longNum::numMass, longNum::longNumSign, longNum::numMassSize, outFileName, longNum::base);
}

//function to read bigNumber from file
int* longNum::readFIle(char* fileIn, int base, int& arrSize, char& numberSign)
{
    int* numMass = NULL;
    
    ifstream fp;
    
    if (base == 1000000000)
    {
        fp.open(fileIn, ios::in);
    }
    else if (base == 256)
    {
        fp.open(fileIn, ios::in | ios::binary);
    }
    
    if (fp.fail())
    {
        cout << "Unable to open the file. Error!\n";
        return numMass;
    }
    
    fp.seekg(0, fp.end);
    int fileSize = fp.tellg();
    int curPos = 0;
    
    if(base == 1000000000) //define array_size depending on num system base
    {
        fp.seekg(0, fp.beg);
        if(fp.get() == '-')
        {
            numberSign = '-';
            curPos = fileSize;
            fileSize -= 1;
        }
        else
        {
            numberSign = '+';
            curPos = fileSize;
        }
        
        if(!(fileSize % 9))
        {
            arrSize = fileSize / 9;
        }
        else
        {
            numberSign = '+';
            curPos = fileSize;
            arrSize = fileSize / 9 + 1;
        }
    }
    else if(base == 256)
    {
        numberSign = '+';
        curPos = fileSize;
        arrSize = fileSize;
    }
    
    numMass = new int[arrSize];
    for(int i = 0; i < arrSize; i++)
    {
        numMass[i] = 0;
    }
    
    if(base == 1000000000) //not binary - 10^9 num system
    {
        
        for(int i = arrSize; i > 0; i--)
        {
            if((curPos - 9) >= 0) //if not the last 9 symbols
            {
                curPos -= 9;
                fp.seekg(curPos, fp.beg);
                for(int j = 0; j < 9; j++) //to 10^9 num system (int border)
                {
                    numMass[i - 1] += (fp.get() - 48)*(int)(pow((double)10, (9 - j - 1)));
                }
            }
            else //if the last 9 symbols -> check sign, read reminded
            {
                fp.seekg(0, fp.beg);
                if(fp.get() == '-')
                {
                    fp.seekg(1, fp.beg);
                    for(int j = 1; j < curPos; j++)
                    {
                        numMass[i - 1] += (fp.get() - 48)*(int)(pow((double)10, (curPos - j - 1)));
                    }
                }
                else
                {
                    fp.seekg(0, fp.beg);
                    for(int j = 0; j < curPos; j++)
                    {
                        numMass[i - 1] += (fp.get() - 48)*(int)(pow((double)10, (curPos - j - 1)));
                    }
                }
            }
        }
    }
    else if(base == 256) //if binary - read as it is
    {
        fp.seekg(0, fp.beg);
        for(int i = arrSize; i > 0; i--)
        {
            numMass[i - 1] = fp.get();
        }
    }
    
    fp.close();
    printf("The big number is successfully read from file.\n");
    return numMass;
}

//function to write bigNumber to file
bool longNum::writeFile(int* numMass, char numSign, int numMassSize, char* resFileName, int base)
{
    ofstream fp;
    if (base == 1000000000)
    {
        fp.open(resFileName, ios::out);
    }
    else if (base == 256)
    {
        fp.open(resFileName, ios::out | ios::binary);
    }
    
    if (fp.fail())
    {
        return false;
    }
    
    if(base == 1000000000) //not binary - 10^9 num system
    {
        if(numSign == '-')
        {
            fp << numSign;
        }
        for(int i = 0; i < numMassSize; i++)
        {
            if(i)
            {
                for(int j = 0; j < 9; j++)
                {
                    if(numMass[i] < (int)pow((double)10, j))
                    {
                        fp << 0;
                    }
                }
            }
            fp << numMass[i];
        }
    }
    
    else if(base == 256) //if binary
    {
        for(int i = numMassSize; i > 0; i--)
        {
            fp.put(numMass[i - 1]);
        }
    }
    
    fp.close();
    printf("The big number is successfully written to file.\n");
    return true;
}

//function to define the sign of the result
char longNum::resSign(char operation, char firstSign, char secSign, int* firstArr, int* secArr, int firstArrSize, int secArrSize)
{
    if(operation == '+')
    {
        if(firstArrSize > secArrSize) //if 1st num is longer - its sign
        {
            return firstSign;
        }
        else if(firstArrSize < secArrSize) //if 2nd num is longer - its sign
        {
            return secSign;
        }
        
        else //if 1st and 2nd lengths are equal - compare symbol by symbol
        {
            for(int i = 0; i < firstArrSize; i++)
            {
                if(firstArr[i] > secArr[i])
                {
                    return firstSign;
                }
                
                else if(firstArr[i] < secArr[i])
                {
                    return secSign;
                }
            }
        }
        
        return '=';
    }
    
    if(operation == '*' || operation == '/')
    {
        if(firstSign != secSign)
        {
            return '-';
        }
        else
        {
            return '+';
        }
    }
    
    return firstSign;
}

//function to  define what number is bigger
void longNum::toMaxMin(int* firstArr, int* secArr, int firstArrSize, int secArrSize, int** maxArr, int** minArr, int& maxArrSize, int& minArrSize)
{
    if(firstArrSize > secArrSize) //if 1st num is longer - 1st-max, 2nd-min
    {
        maxArrSize = firstArrSize;
        *maxArr = new int[maxArrSize];
        for(int i = 0; i < maxArrSize; i++)
        {
            (*maxArr)[i] = firstArr[i];
        }
        minArrSize = secArrSize;
        *minArr = new int[minArrSize];
        for(int i = 0; i < minArrSize; i++)
        {
            (*minArr)[i] = secArr[i];
        }
    }
    
    else if(firstArrSize < secArrSize) //if 2nd num is longer - 1st-min, 2nd-max
    {
        maxArrSize = secArrSize;
        *maxArr = new int[maxArrSize];
        for(int i = 0; i < maxArrSize; i++)
        {
            (*maxArr)[i] = secArr[i];
        }
        minArrSize = firstArrSize;
        (*minArr) = new int[minArrSize];
        for(int i = 0; i < minArrSize; i++)
        {
            (*minArr)[i] = firstArr[i];
        }
    }
    
    else //if lengths are equal - compare symbol by symbol
    {
        for(int i = 0; i < firstArrSize; i++)
        {
            if(firstArr[i] > secArr[i]) //if 1st num [i] is bigger - 1st-max, 2nd-min
            {
                maxArrSize = firstArrSize;
                *maxArr = new int[maxArrSize];
                for(int i = 0; i < maxArrSize; i++)
                {
                    (*maxArr)[i] = firstArr[i];
                }
                minArrSize = secArrSize;
                *minArr = new int[minArrSize];
                for(int i = 0; i < minArrSize; i++)
                {
                    (*minArr)[i] = secArr[i];
                }
                break;
            }
            
            else if(firstArr[i] < secArr[i]) //if 2nd num [i] is bigger - 1st-min, 2nd-max
            {
                maxArrSize = secArrSize;
                *maxArr = new int[maxArrSize];
                for(int i = 0; i < maxArrSize; i++)
                {
                    (*maxArr)[i] = secArr[i];
                }
                minArrSize = firstArrSize;
                *minArr = new int[minArrSize];
                for(int i = 0; i < minArrSize; i++)
                {
                    (*minArr)[i] = firstArr[i];
                }
                break;
            }
            
            else
            {
                maxArrSize = firstArrSize;
                *maxArr = new int[maxArrSize];
                for(int i = 0; i < maxArrSize; i++)
                {
                    (*maxArr)[i] = firstArr[i];
                }
                minArrSize = secArrSize;
                *minArr = new int[minArrSize];
                for(int i = 0; i < minArrSize; i++)
                {
                    (*minArr)[i] = secArr[i];
                }
                break;
            }
        }
    }
}

//function to cut head nulls
int* longNum::deleteNulls(int* arrYesNulls, int& arrSize)
{
    int nullValues = 0;
    int* arrdeleteNulls = NULL;
    
    for(int i = 0; i < arrSize; i++)
    {
        if(arrYesNulls[i] == 0)
        {
            nullValues++;
        }
        else
        {
            break;
        }
    }
    
    arrSize -= nullValues;
    if(!arrSize)
    {
        arrSize = 1;
        arrdeleteNulls = new int[arrSize];
        arrdeleteNulls[0] = 0;
    }
    
    else
    {
        arrdeleteNulls = new int[arrSize];
        for(int i = 0; i < arrSize; i++)
        {
            arrdeleteNulls[i] = arrYesNulls[i + nullValues];
        }
    }
    
    delete [] arrYesNulls;
    return arrdeleteNulls;
}

//function to convert long long num to 2 ints (integer and residue)
int* longNum::convertToInt(long long int ArrElem, int* longArr, int& longArrSize, int base)
{
    longArrSize = 2;
    longArr = new int[longArrSize];
    for(int i = 0; i < longArrSize; i++)
    {
        longArr[i] = 0;
    }
    
    longArr[0] = (int)(ArrElem / (long long int)base);
    longArr[1] = (int)(ArrElem % (long long int)base);
    
    return deleteNulls(longArr, longArrSize);
}
//function to copy arrays (nums)
int* longNum::copyMass(int* newMas, int* oldMas, int& newMasSize, int oldMasSize)
{
    if(newMas != NULL)
    {
        delete [] newMas;
    }
    newMasSize = oldMasSize;
    newMas = new int[newMasSize];
    for(int i = 0; i < newMasSize; i++)
    {
        newMas[i] = oldMas[i];
    }
    
    delete [] oldMas;
    return deleteNulls(newMas, newMasSize);
}

void longNum::copylongNum(const longNum& rhv)
{
    this->base = rhv.base;
    this->longNumSign = rhv.longNumSign;
    this->numMass = copyMass(this->numMass, rhv.numMass, this->numMassSize, rhv.numMassSize);
}

longNum& longNum::sumOrSub(const longNum& lhv, const longNum& rhv, bool isSubmit, char tmpSecSign)
{
    char realOperation = '+';
    longNum* Result = new longNum;
    Result->base = lhv.base;
    
    Result->longNumSign = resSign('+', lhv.longNumSign, tmpSecSign, lhv.numMass, rhv.numMass, lhv.numMassSize, rhv.numMassSize);
    
    if(lhv.longNumSign != tmpSecSign)
    {
        realOperation = '-';
    }
    
    switch(realOperation)
    {
        case '+':
            Result->numMass = addition(lhv.numMass, rhv.numMass, Result->numMass, lhv.numMassSize, rhv.numMassSize, Result->numMassSize, Result->base);
            break;
        case '-':
            Result->numMass = substraction(lhv.numMass, rhv.numMass, Result->numMass, lhv.numMassSize, rhv.numMassSize, Result->numMassSize, Result->base);
            break;
    }
    
    return *Result;
}

//function of summarising (+)
int* longNum::addition(int* firstArr, int* secArr, int* resArr, int firstArrSize, int secArrSize, int& resArrSize, int base)
{
    int* moreNumArr = NULL;
    int* lessNumArr = NULL;
    int moreNumArrSize = 0;
    int lessNumArrSize = 0;
    
    toMaxMin(firstArr, secArr, firstArrSize, secArrSize, &moreNumArr, &lessNumArr, moreNumArrSize, lessNumArrSize);
    resArrSize = moreNumArrSize + 1;
    resArr = new int[resArrSize];
    
    for(int i = 0; i < resArrSize; i++)
    {
        resArr[i] = 0;
    }
    
    for(int i = resArrSize; i > 1; i--) //add starting from the end
    {
        if((resArrSize - i) < lessNumArrSize) //if shorter num hasn't been completely added yet
        {
            resArr[i - 1] += (moreNumArr[moreNumArrSize - (resArrSize - i) - 1] + lessNumArr[lessNumArrSize - (resArrSize - i) - 1]);
        }
        
        else //if shorter number has already been completely added
        {
            resArr[i - 1] += moreNumArr[moreNumArrSize - (resArrSize - i) - 1];
        }
        
        resArr[i - 2] += resArr[i - 1] / base; //saving integer part and the residue
        resArr[i - 1] %= base;
    }
    
    delete [] moreNumArr;
    delete [] lessNumArr;
    return deleteNulls(resArr, resArrSize);
}

//function sub (-)
int* longNum::substraction(int* firstArr, int* secArr, int* resArr, int firstArrSize, int secArrSize, int& resArrSize, int base)
{
    int* moreNumArr = NULL;
    int* lessNumArr = NULL;
    int moreNumArrSize = 0;
    int lessNumArrSize = 0;
    int credit = 0;
    int newSub = 0;
    
    toMaxMin(firstArr, secArr, firstArrSize, secArrSize, &moreNumArr, &lessNumArr, moreNumArrSize, lessNumArrSize);
    resArrSize = moreNumArrSize;
    
    resArr = new int[resArrSize];
    
    for(int i = 0; i < resArrSize; i++)
    {
        resArr[i] = 0;
    }
    
    for(int i = resArrSize; i > 0; i--) //sub starting from the end
    {
        if((resArrSize - i) < lessNumArrSize) //if shorter num hasn't been completely subbed yet
        {
            newSub = moreNumArr[moreNumArrSize - (resArrSize - i) - 1] - lessNumArr[lessNumArrSize - (resArrSize - i) - 1] - credit;
        }
        
        else //if shorter number has already been completely subbed
        {
            newSub = moreNumArr[moreNumArrSize - (resArrSize - i) - 1] - credit;
        }
        
        if(newSub < 0) //if there is overflow
        {
            resArr[i - 1] = newSub + base;
            credit = 1;
        }
        else
        {
            resArr[i - 1] = newSub;
            credit = 0;
        }
        
    }
    
    delete [] moreNumArr;
    delete [] lessNumArr;
    return deleteNulls(resArr, resArrSize);
}

//function mul (*)
int* longNum::multiplication(int* firstArr, int* secArr, int* resArr, int firstArrSize, int secArrSize, int& resArrSize, int base)
{
    long long int* resArrLong = NULL;
    resArrSize = firstArrSize + secArrSize + 1;
    resArr = new int[resArrSize];
    resArrLong = new long long int[resArrSize];
    
    for(int i = 0; i < resArrSize; i++)
    {
        resArrLong[i] = 0;
        resArr[i] = 0;
    }
    
    for(int i = firstArrSize; i > 0; i--) //mul as by columns
    {
        for(int j = secArrSize; j > 0; j--)
        {
            resArrLong[i + j] += (long long int)(firstArr[i - 1]) * (long long int)(secArr[j - 1]);
        }
    }
    
    for(int i = resArrSize; i > 1; i--) //mul as by columns
    {
        resArrLong[i - 2] += resArrLong[i - 1] / base;
        resArrLong[i - 1] %= base;
    }
    
    for(int i = 0; i < resArrSize; i++)
    {
        resArr[i] = (int)resArrLong[i];
    }
    
    delete [] resArrLong;
    
    return deleteNulls(resArr, resArrSize);
}

//function divide bigNum on digit
int* longNum::divOnDigit(int* firstArr, int digit, int* resArr, int firstArrSize, int& resArrSize, int& tail, bool isRem, int base)
{
    if(!digit)
    {
        printf("Dividing to the zero. Error!\n");
        return firstArr;
    }
    
    resArrSize = firstArrSize;
    resArr = new int[resArrSize];
    for(int i = 0; i < resArrSize; i++)
    {
        resArr[i] = 0;
    }
    
    int remain = 0;
    long long int curDiver = 0;
    for(int i = 0; i < firstArrSize; i++)
    {
        //current numerator
        curDiver = (long long int)remain * (long long int)base + (long long int)firstArr[i];
        resArr[i] = (int)(curDiver / (long long int)digit); //current result
        remain = (int)(curDiver % (long long int)digit); //current residue
    }
    
    tail = remain; //last residue
    return deleteNulls(resArr, resArrSize);
}

//function divide bigNum on bigNum (/)
int* longNum::dividing(int* firstArr, int* secArr, int* resArr, int firstArrSize, int secArrSize, int& resArrSize, bool isRem, int base)
{
    int remain = 0;
    if(secArrSize == 1) //if 2nd num is digit
    {
        resArr = divOnDigit(firstArr, secArr[0], resArr, firstArrSize, resArrSize, remain, isRem, base);
        if(isRem) //if need residue
        {
            delete [] resArr;
            resArr = new int[1];
            resArr[0] = remain;
            return resArr;
        }
        else
        {
            return resArr;
        }
    }
    
    if(firstArrSize == 1) //if 1st num is digit
    {
        resArrSize = 1;
        resArr = new int[resArrSize];
        
        if(secArrSize == 1)
        {
            if(secArr[0])
            {
                resArr[0] = firstArr[0] / secArr[0];
                return resArr;
            }
            else
            {
                printf("Dividing to the zero. Error!\n");
                return firstArr;
            }
        }
        else
        {
            resArr[0] = 0;
            return resArr;
        }
    }
    
    resArrSize = firstArrSize - secArrSize + 1;
    resArr = new int[resArrSize];
    for(int i = 0; i < resArrSize; i++)
    {
        resArr[i] = 0;
    }
    
    int* rest = NULL;
    int* substr = NULL;
    int* submit = NULL;
    int* difference = NULL;
    long long int* newRem = NULL;
    long long int* NewSecArr = NULL;
    int restSize = 0;
    int substrSize = 0;
    int difSize = 0;
    restSize = firstArrSize + 1;
    rest = new int[restSize];
    submit = new int[restSize];
    newRem = new long long int[restSize];
    NewSecArr = new long long int[secArrSize];
    for(int i = 0; i < restSize; i++)
    {
        rest[i] = 0;
        newRem[i] = 0;
        submit[i] = 0;
    }
    
    for(int i = 0; i < secArrSize; i++)
    {
        NewSecArr[i] = 0;
    }
    
    int helpValue = 0; //dividing cuts to halfs
    if(!((base / 2) % secArr[0]))
    {
        helpValue = ((base / 2) / secArr[0]);
    }
    
    else
    {
        helpValue = ((base / 2) / secArr[0]) + 1;
    }
    
    for(int i = 1; i < restSize; i++)
    {
        rest[i] = firstArr[i - 1];
    }
    
    for(int i = 0; i < secArrSize; i++)
    {
        NewSecArr[i] = (long long int)secArr[i] * (long long int)helpValue;
    }
    
    int* newLimit = NULL;
    newLimit = new int[1];
    int* newRemInt = NULL;
    int* NewSecArrInt = NULL;
    int* MulArr = NULL;
    int* secMulArr = NULL;
    int* thirdMulArr = NULL;
    int* sumArr = NULL;
    int* baseArr = NULL;
    int* relation = NULL;
    baseArr = new int[1];
    baseArr[0] = base;
    int MulArrSize = 0;
    int secMulArrSize = 0;
    int thirdMulArrSize = 0;
    int sumArrSize = 0;
    int newRemIntSize = 0;
    int NewSecArrIntSize = 0;
    int relationSize = 0;
    
    for(int i = 0; i < resArrSize; i++)
    {
        for(int j = 0; j < restSize; j++)
        {
            newRem[j] = (long long int)rest[j] * (long long int)helpValue;
        }
        
        newRemInt = convertToInt(newRem[i], newRemInt, newRemIntSize, base);
        MulArr = multiplication(newRemInt, baseArr, MulArr, newRemIntSize, 1, MulArrSize, base); //mulArr=residue*helpValue*base
        delete [] newRemInt;
        newRemInt = convertToInt(newRem[i + 1], newRemInt, newRemIntSize, base);
        sumArr = addition(MulArr, newRemInt, sumArr, MulArrSize, newRemIntSize, sumArrSize, base); //sumArr=residue*helpValue*base + newRem[i]
        delete [] newRemInt;
        relation = divOnDigit(sumArr, (int)NewSecArr[0], relation, sumArrSize, relationSize, remain, false, base); //relation = residue*helpValue*base + newRem[i-1]*helpValue / secArr[i]*helpValue
        
        if(relationSize > 1)
        {
            newLimit[0] = (base - 1);
        }
        else
        {
            newLimit[0] = relation[0];
        }
        
        delete [] relation;
        
        do
        {
            delete [] MulArr;
            delete [] sumArr;
            
            NewSecArrInt = convertToInt(NewSecArr[1], NewSecArrInt, NewSecArrIntSize, base);
            MulArr = multiplication(NewSecArrInt, newLimit, MulArr, NewSecArrIntSize, 1, MulArrSize, base);
            delete [] NewSecArrInt;
            
            newRemInt = convertToInt(newRem[i], newRemInt, newRemIntSize, base);
            secMulArr = multiplication(newRemInt, baseArr, secMulArr, newRemIntSize, 1, secMulArrSize, base);
            delete [] newRemInt;
            newRemInt = convertToInt(newRem[i + 1], newRemInt, newRemIntSize, base);
            sumArr = addition(secMulArr, newRemInt, sumArr, secMulArrSize, newRemIntSize, sumArrSize, base); //newRem[i]*base+newRem[i]
            delete [] newRemInt;
            delete [] secMulArr;
            NewSecArrInt = convertToInt(NewSecArr[0], NewSecArrInt, NewSecArrIntSize, base);
            secMulArr = multiplication(NewSecArrInt, newLimit, secMulArr, NewSecArrIntSize, 1, secMulArrSize, base); //newSecArr[0]*newLimit
            delete [] NewSecArrInt;
            thirdMulArr = substraction(sumArr, secMulArr, thirdMulArr, sumArrSize, secMulArrSize, thirdMulArrSize, base); //newRem[i]*base+newRem[i] - newSecArr[0]*newLimit
            delete [] sumArr;
            delete [] secMulArr;
            secMulArr = multiplication(thirdMulArr, baseArr, secMulArr, thirdMulArrSize, 1, secMulArrSize, base); //(newRem[i]*base+newRem[i] - newSecArr[0]*newLimit) * base
            delete [] thirdMulArr;
            newRemInt = convertToInt(newRem[i + 2], newRemInt, newRemIntSize, base);
            sumArr = addition(secMulArr, newRemInt, sumArr, secMulArrSize, newRemIntSize, sumArrSize, base); //(newRem[i]*base+newRem[i] - newSecArr[0]*newLimit) * base + newRem[i+2]
            delete [] secMulArr;
            delete [] newRemInt;
            
            if(resSign('+', '+', '-', MulArr, sumArr, MulArrSize, sumArrSize) == '+')
            {
                newLimit[0]--; //decrease the limit while mulArr is bigger than SumArr
            }
        }while(resSign('+', '+', '-', MulArr, sumArr, MulArrSize, sumArrSize) == '+');
        
        delete [] MulArr;
        delete [] sumArr;
        substr = multiplication(secArr, newLimit, substr, secArrSize, 1, substrSize, base); //delitel*newLimit
        for(int j = 0; j < (i + 1 - (substrSize - secArrSize)); j++)
        {
            submit[j] = 0;
        }
        for(int j = (i + 1 - (substrSize - secArrSize)); j < (secArrSize + 1 + i); j++)
        {
            submit[j] = substr[j - i - 1 + (substrSize - secArrSize)]; //4islo proverka
        }
        for(int j = (secArrSize + 1 + i); j < restSize; j++)
        {
            submit[j] = 0;
        }
        
        if(resSign('+', '+', '-', rest, submit, restSize, restSize) == '-') //ostatok>proverki
        {
            newLimit[0]--; //decrease the limit
            
            delete [] substr;
            
            substr = multiplication(secArr, newLimit, substr, secArrSize, 1, substrSize, base); //secArr*newLimit
            for(int j = 0; j < (i + 1 - (substrSize - secArrSize)); j++)
            {
                submit[j] = 0;
            }
            for(int j = (i + 1 - (substrSize - secArrSize)); j < (secArrSize + 1 + i); j++)
            {
                submit[j] = substr[j - i - 1 + (substrSize - secArrSize)]; //4islo proverka
            }
            for(int j = (secArrSize + 1 + i); j < restSize; j++)
            {
                submit[j] = 0;
            }
        }
        
        difference = substraction(rest, submit, difference, restSize, restSize, difSize, base); //ostatok-proverka
        resArr[i] = newLimit[0]; //result[i]=newLimit
        for(int i = restSize; i > (restSize - difSize); i--)
        {
            rest[i - 1] = difference[difSize - (restSize - i) - 1]; //change the residue
        }
        for(int i = (restSize - difSize); i > 0; i--)
        {
            rest[i - 1] = 0;
        }
        delete [] difference;
        delete [] substr;
    }
    
    delete [] submit;
    delete [] newRem;
    delete [] NewSecArr;
    delete [] newLimit;
    delete [] baseArr;
    
    if(isRem)
    {
        delete [] resArr;
        resArr = deleteNulls(rest, restSize);
        resArrSize = restSize;
        return resArr;
    }
    else
    {
        delete [] rest;
        return deleteNulls(resArr, resArrSize);
    }
}

//function ^
int* longNum::involution(int* firstArr, int* secArr, int* resArr, int firstArrSize, int secArrSize, int& resArrSize, int base)
{
    resArr = new int[1];
    resArr[0] = 1;
    resArrSize = 1;
    int* oneArr = NULL;
    oneArr = new int[1];
    oneArr[0] = 1;
    int* tempQuotArr = NULL;
    int tempQuotArrSize = 0;
    int* tempMulArr = NULL;
    int tempMulArrSize = 0;
    int* tempSubArr = NULL;
    int tempSubArrSize = 0;
    int* tempFirstArr = NULL;
    int tempFirstArrSize = 0;
    int* tempSecArr = NULL;
    int tempSecArrSize = 0;
    int remain = 0;
    
    tempFirstArrSize = firstArrSize;
    tempFirstArr = new int[tempFirstArrSize];
    for(int i = 0; i < tempFirstArrSize; i++)
    {
        tempFirstArr[i] = firstArr[i];
    }
    tempSecArrSize = secArrSize;
    tempSecArr = new int[tempSecArrSize];
    for(int i = 0; i < tempSecArrSize; i++)
    {
        tempSecArr[i] = secArr[i];
    }
    
    while(!((tempSecArrSize == 1) && (tempSecArr[0] == 0)))
    {
        tempQuotArr = divOnDigit(tempSecArr, 2, tempQuotArr, tempSecArrSize, tempQuotArrSize, remain, false, base);
        if(!remain) //if delitsa na 2 umnozaem na tekushcii
        {
            tempSecArr = copyMass(tempSecArr, tempQuotArr, tempSecArrSize, tempQuotArrSize);
            tempMulArr = multiplication(tempFirstArr, tempFirstArr, tempMulArr, tempFirstArrSize, tempFirstArrSize, tempMulArrSize, base);
            tempFirstArr = copyMass(tempFirstArr, tempMulArr, tempFirstArrSize, tempMulArrSize);
        }
        else //esli net umnozaem na pervoe chislo
        {
            tempSubArr = substraction(tempSecArr, oneArr, tempSubArr, tempSecArrSize, 1, tempSubArrSize, base);
            tempSecArr = copyMass(tempSecArr, tempSubArr, tempSecArrSize, tempSubArrSize);
            tempMulArr = multiplication(tempFirstArr, resArr, tempMulArr, tempFirstArrSize, resArrSize, tempMulArrSize, base);
            resArr = copyMass(resArr, tempMulArr, resArrSize, tempMulArrSize);
        }
    }
    
    tempMulArr = multiplication(tempFirstArr, resArr, tempMulArr, tempFirstArrSize, resArrSize, tempMulArrSize, base);
    resArr = copyMass(resArr, tempMulArr, resArrSize, tempMulArrSize);
    
    delete [] oneArr;
    delete [] tempSecArr;
    delete [] tempFirstArr;
    return resArr;
}

int* longNum::rest(int* firstArr, int* secArr, int* resArr, int firstArrSize, int secArrSize, int& resArrSize, int base)
{
    resArr = dividing(firstArr, secArr, resArr, firstArrSize, secArrSize, resArrSize, true, base);
    return resArr;
}
