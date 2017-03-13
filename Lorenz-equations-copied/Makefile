all:
	/usr/bin/g++ -Wall -fPIC -o "Lorenz.o" "Lorenz.cpp" && chmod +x Lorenz.o && ./Lorenz.o && gnuplot < lorenz_ode_commands.txt
clean:
	rm Lorenz.o
