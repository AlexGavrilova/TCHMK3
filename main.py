import sys
import longArifmetics
import functions

functions.PrintStart()

paramsNum = len(sys.argv)

if not functions.checkParam(paramsNum, sys.argv):
	sys.exit(-1)

inFile1 = sys.argv[1]
operation = sys.argv[2][0]
inFile2 = sys.argv[3]
resFile = sys.argv[4]
base = 0
isModule = False

if (paramsNum == 5):
	base = 1000000000

if (paramsNum == 6):
	if (sys.argv[5] == "-b"):
		base = 256
		binKey = sys.argv[5]
	else:
		base = 1000000000
		moduleFile = sys.argv[5]
		isModule = True

if (paramsNum == 7):
	if (sys.argv[5] == "-b"):
			base = 256
			binKey = sys.argv[5]
			moduleFile = sys.argv[6]
			isModule = True
	else:
		print "Too many arguments. Error!"
		sys.exit(-1)
		
firstNum = longArifmetics.longNum()
secNum = longArifmetics.longNum()
resultNum = longArifmetics.longNum()

if not firstNum.read(inFile1, base):
		print "An error occured in reading the first number!"
		sys.exit(-1)
if not secNum.read(inFile2, base):
		print "An error occured in reading the second number!"
		sys.exit(-1)
		
if operation == "+": 
	resultNum = firstNum + secNum
elif operation == "-":
	resultNum = firstNum - secNum
elif operation == "m":
	resultNum = firstNum * secNum
elif operation == "/":
	resultNum = firstNum / secNum
elif operation == "^":
	resultNum = firstNum ^ secNum
elif operation == "r":
	resultNum = firstNum % secNum
	
if isModule:
	modlongNum = longArifmetics.longNum()
	resModlongNum = longArifmetics.longNum()
	if not modlongNum.Read(moduleFile, base):
		print "An error occured in reading the module!"
		sys.exit(-1)
		
	resModlongNum = resultNum % modlongNum;
	resModlongNum.write(resFile)
else:
	resultNum.write(resFile)
