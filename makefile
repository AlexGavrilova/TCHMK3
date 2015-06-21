all:
	swig -c++ -python longArifmetics.i
	g++ -c -w -std=c++11 longArifmetics.cpp
	g++ -c -w -std=c++11 longArifmetics_wrap.cxx -I/Library/Frameworks/Python.framework/Versions/2.7/include/python2.7
	g++ -lpython -dynamiclib longArifmetics.o longArifmetics_wrap.o -o longArifmetics.so 
