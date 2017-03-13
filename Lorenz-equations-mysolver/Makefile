# Requires support for C++ 11
# GCC 4.8 fails
# GCC 6.2 and 6.3 succeeds
all:
	/usr/bin/g++ -std=c++11 -pipe -Wall -fPIC -o "lorenz.o" "lorenz.cpp"
	chmod +x lorenz.o
	./lorenz.o
clean:
	rm lorenz.o
