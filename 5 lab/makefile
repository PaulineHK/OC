all:1 2 3 0
1:5_1_1.o
	g++ -o 1 5_1_1.o -lpthread
5_1_1.o:5_1_1.cpp
	g++ -c 5_1_1.cpp
2:5_1_2.o
	g++ -o 2 5_1_2.o -lpthread
5_1_2.o:5_1_2.cpp
	g++ -c 5_1_2.cpp

3:5_2.o
	g++ -o 3 5_2.o -lpthread
5_2.o:5_2.cpp
	g++ -c 5_2.cpp

0:5_origin.o
	g++ -o 0 5_origin.o -lpthread
5_origin.o:5_origin.cpp
	g++ -c 5_origin.cpp
clean:
	rm -f *.o
	rm -f 
	
