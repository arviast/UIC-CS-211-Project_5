ajamsr2proj5: ajamsr2proj5_1.o
	g++ -o ajamsr2proj5 ajamsr2proj5_1.o

ajamsr2proj5_1.o: ajamsr2proj5_1.cpp ajamsr2proj5.h
	g++ -c ajamsr2proj5_1.cpp