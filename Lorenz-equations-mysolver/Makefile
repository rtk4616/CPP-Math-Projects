# Requires support for C++ 11
# Clang 3.3 and later, as well as GCC 4.7 and later have at least experimental support for C++11
all:
	/usr/bin/g++ -std=c++11 -pipe -Wall -fPIC -o "lorenz.o" "lorenz.cpp"
	chmod +x lorenz.o
	./lorenz.o
clean:
	rm lorenz.o
