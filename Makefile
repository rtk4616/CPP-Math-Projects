#CPPFLAGS = -I/usr/include/qt -I/usr/include/qt/QtCore -I/usr/include/qt/QtDBus -I/usr/include/qt/QtGui -I/usr/include/qt/QtWidgets -I/usr/include/qt/QtUiTools -I/usr/include/qt/QtX11Extras -I/usr/include/qt/QtNetwork -I/usr/include/qt/QtXml -I/usr/include/qt/QtXmlPatterns
all:
	/usr/bin/g++ -Wall -fPIC -o "example" "example.cpp" && ./example
	/usr/bin/g++ -Wall -fPIC -o "simppenadj" "simppenadj.cpp" && ./simppenadj
clean:
	rm example
	rm simppenadj
