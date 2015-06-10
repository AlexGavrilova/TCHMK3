#!/usr/bin/python
import LongNum
import sys


def way(A, B, Mod, operation) :
zero = LongNum.LongNum("0")
Result = zero

if (Mod < zero) :
	print "Negative Mod!"
	return False, Result

if operation == '^' :
Result = LongNum.Pow(A, B, Mod)
return True, Result

if (Mod > zero) :
A = A % Mod
B = B % Mod

if operation == '+' :
Result = A + B

elif operation == '-' :
Result = A - B

elif operation == '*' :
Result = A * B

elif operation == '/' :
if B == zero :
print "Divid by zero"
return False, Result
Result = A / B

elif operation == '%' :
if (B == zero) :
print "Divid by zero"
return False, Result
Result = A % B

if (Mod > zero) :
Result = Result % Mod
while (Result < zero) :
	Result = Result + Mod

	return True, Result


	def main() :
if len(sys.argv) < 5 :
	print "Too few arguments!"

	return -1

if len(sys.argv) > 7:
print "Too many arguments!"
return -1

fileA = sys.argv[1]
operation = sys.argv[2]
fileB = sys.argv[3]
fileRes = sys.argv[4]
bin = False
ModFile = None

if len(sys.argv) == 6:
if sys.argv[5] == "-b" :
bin = True
else :
ModFile = sys.argv[5]

	if len(sys.argv) == 7 :
		bin = True;
	ModFile = sys.argv[6]

		A = LongNum.LongNum(0)
		B = LongNum.LongNum(0)
		Mod = LongNum.LongNum(0)

	if bin == True:
	A.OutBinFile(fileA)
		B.OutBinFile(fileB)
	if ModFile != None :
		Mod.OutBinFile(ModFile)
	else :
	A.OutFile(fileA)
	B.OutFile(fileB)
	if ModFile != None :
		Mod.OutFile(ModFile)

		isway, Result = way(A, B, Mod, operation)
	if not isway :
	sys.exit(-1)

	if bin == True :
		Result.InBinFile(fileRes)
	else :
	Result.InFile(fileRes)


	if __name__ == "__main__" :
		main()
