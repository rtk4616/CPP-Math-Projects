all:
	/usr/bin/g++ -Wall -fPIC -o "example" "example.cpp" -I/usr/include/qt -I/usr/include/qt/QtCore -I/usr/include/qt/QtGui -I/usr/include/qt/QtWidgets
clean:
	rm example
