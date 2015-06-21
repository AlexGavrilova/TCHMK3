#ifndef t4mk_2_longArifmetics_h
#define t4mk_2_longArifmetics_h
class longNum
{
private:
    //Hidden elements and functions
    int base;
    int* numMass;
    int numMassSize;
    char longNumSign;
    
    int* readFIle(char* fileIn, int base, int& arrSize, char& numberSign);
    bool writeFile(int* numMass, char numSign, int numMassSize, char* resFileName, int base);
    char resSign(char operation, char firstSign, char secSign, int* firstArr, int* secArr, int firstArrSize, int secArrSize);
    void toMaxMin(int* firstArr, int* secArr, int firstArrSize, int secArrSize, int** maxArr, int** minArr, int& maxArrSize, int& minArrSize);
    int* deleteNulls(int* arrYesNulls, int& arrSize);
    int* convertToInt(long long int ArrElem, int* longArr, int& longArrSize, int base);
    int* copyMass(int* newMas, int* oldMas, int& newMasSize, int oldMasSize);
    
    void copylongNum(const longNum& rhv);
    
    //Arithmetic operation
    longNum& sumOrSub(const longNum& lhv, const longNum& rhv, bool isSub, char tmpSecSign);
    
    int* addition(int* firstArr, int* secArr, int* resArr, int firstArrSize, int secArrSize, int& resArrSize, int base);
    int* substraction(int* firstArr, int* secArr, int* resArr, int firstArrSize, int secArrSize, int& resArrSize, int base);
    int* multiplication(int* firstArr, int* secArr, int* resArr, int firstArrSize, int secArrSize, int& resArrSize, int base);
    int* divOnDigit(int* firstArr, int digit, int* resArr, int firstArrSize, int& resArrSize, int& tail, bool isRem, int base);
    int* dividing(int* firstArr, int* secArr, int* resArr, int firstArrSize, int secArrSize, int& resArrSize, bool isRem, int base);
    int* involution(int* firstArr, int* secArr, int* resArr, int firstArrSize, int secArrSize, int& resArrSize, int base);
    int* rest(int* firstArr, int* secArr, int* resArr, int firstArrSize, int secArrSize, int& resArrSize, int base);
    
public:
    //Constructor
    longNum();
    longNum(const char* string);
    
    //Destructor
    ~longNum();
    
    //operators overloading
    longNum& operator=(const longNum& rv);
    longNum& operator+(const longNum& rv);
    longNum& operator-(const longNum& rv);
    longNum& operator*(const longNum& rv);
    longNum& operator/(const longNum& rv);
    longNum& operator^(const longNum& rv);
    longNum& operator%(const longNum& rv);
    bool operator==(const longNum& rv);
    bool operator!=(const longNum& rv);
    bool operator>=(const longNum& rv);
    bool operator<=(const longNum& rv);
    bool operator>(const longNum& rv);
    bool operator<(const longNum& rv);
    
    //Other functions
    bool read(char* inFileName, int base);
    bool write(char* outFileName);
};

#endif
