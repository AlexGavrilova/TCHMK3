import ClassLN
import sys
import os

if len(sys.argv) < 5 or len(sys.argv) > 7:
        print "You must be enter more than 5 and fewer than 7 arguments. For example:"
	print "<file_a> <[ + | - | x | / | % | ^ ]> <file_b> <file_result> <file_module>"
	print "or:"
	print "<file_a> <[ + | - | x | / | % | ^ ]> <file_b> <file_result> <file_module> <-b>"
	sys.exit(0)

bin = 0

if len(sys.argv) == 5:
    if sys.argv[2][0] == '^' :
            print "You must be enter module file"
            sys.exit(0)

if len(sys.argv) == 6:
    if sys.argv[5] == "-b":
        bin = 1
    else:
        bin = 0
    if bin == 0:
        if sys.argv[2][0] != '^':
            print "Bad argument: ", sys.argv[5]
            sys.exit(0)
        else:
            if not os.path.isfile(sys.argv[5]):
                print "Module file not found: ", sys.argv[5]
	        sys.exit(0)

if len(sys.argv) == 7:
    if sys.argv[6] == "-b":
        bin = 1;
    else:
        print "What this: ", sys.argv[6]
        sys.exit(0)
    if sys.argv[2][0] != '^':
        print "Bad argument: ", sys.argv[5]
        sys.exit(0)
    else:
        if not os.path.isfile(sys.argv[5]):
            print "Module file not found: ", sys.argv[5]
	    sys.exit(0)

if not os.path.exists(sys.argv[1]):
    print "File not found: ", sys.argv[1]
    sys.exit(0)

if not os.path.isfile(sys.argv[3]):
    print "File not found: ", sys.argv[3]
    sys.exit(0)

if ((len(sys.argv[2]) > 1 or sys.argv[2][0] == '\0') or sys.argv[2][0] != '+' and sys.argv[2][0] != '-' and sys.argv[2][0] != 'x' and sys.argv[2][0] != '/' and sys.argv[2][0] != '%' and sys.argv[2][0] != '^'):
    print "Bad operation: ", sys.argv[2][0]
    sys.exit(0) 

a = ClassLN.ClassLN()
b = ClassLN.ClassLN()

if bin == 1:
    a.ReadBin(sys.argv[1])
    b.ReadBin(sys.argv[3])
else:
    a.ReadText(sys.argv[1])
    b.ReadText(sys.argv[3])    

result = ClassLN.ClassLN()

if sys.argv[2][0] == '+':
    result = a + b
if sys.argv[2][0] == '-':
    result = a - b
if sys.argv[2][0] == 'x':
    result = a * b
if sys.argv[2][0] == '/':
    result = a / b
if sys.argv[2][0] == '%':
    result = a % b    
if sys.argv[2][0] == '^':
    c = ClassLN.ClassLN()
    if bin == 1:
	c.ReadBin(sys.argv[5])
    else:
	c.ReadText(sys.argv[5])
    result = ClassLN.PowMod(a, b, c)

if bin == 1:
    result.WriteBin(sys.argv[4])
else:
    result.WriteText(sys.argv[4])
