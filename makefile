all: 
	swig -c++ -python Long.i
	g++ -fPIC -c LongNum.cpp
	g++ -fPIC -c LongNum_wrap.cxx -I/usr/include/python2.7
	g++ -shared LongNum.o BigNumb_wrap.o -o _LongNum.so
	rm LongNum.o LongNum_wrap.cxx LongNum_wrap.o
	
windows32:
	swig -c++ -python Long.i
	g++ -c LongNum.cpp
	g++ -c LongNum_wrap.cxx -IC:\Python27\include
	g++ LongNum.o LongNum_wrap.o -Ic:\python27\include -Lc:\python27\libs -lpython27 -shared -o _LongNum.pyd
	del LongNum.o LongNum_wrap.cxx LongNum_wrap.o
	
windows64:
	swig -c++ -python Long.i
	C:\TDM-GCC-64\bin\g++ -c LongNum.cpp
	C:\TDM-GCC-64\bin\g++ -c LongNum_wrap.cxx -IC:\Python27\include
	C:\TDM-GCC-64\bin\g++ LongNum.o LongNum_wrap.o -Ic:\python27\include -Lc:\python27\libs -lpython27 -shared -o _LongNum.pyd
	del LongNum.o LongNum_wrap.cxx LongNum_wrap.o
