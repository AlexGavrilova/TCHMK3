#include "tchmk.h"

class ClassLN
{
    LongNumber num;
    public:
        ClassLN() {} 

        void ReadText(const char* filename);
        void WriteText(const char* filename);
        void ReadBin(const char* filename);
        void WriteBin(const char* filename);
        void ClearMemory();

        ClassLN& operator=(const ClassLN& rhv); 
        ClassLN operator+(ClassLN &right);
        ClassLN operator-(ClassLN &right);
        ClassLN operator*(ClassLN &right);
        ClassLN operator/(ClassLN &right);
        ClassLN operator%(ClassLN &right);

        friend ClassLN PowMod(ClassLN &base, ClassLN &exp, ClassLN &mod); 
};
