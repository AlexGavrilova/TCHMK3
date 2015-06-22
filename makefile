all:
	swig -c++ -python ClassLN.i
	g++ -c -w -std=c++11 ClassLN.cpp
	g++ -c -w -std=c++11 tchmk.cpp
	g++ -c -w -std=c++11 longNumber_wrap.cxx -I/Library/Frameworks/Python.framework/Versions/2.7/include/python2.7
	g++ -lpython -dynamiclib ClassLN.o tchmk.o ClassLN_wrap.o -o _ClassLN.so 
