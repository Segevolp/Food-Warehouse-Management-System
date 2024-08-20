all: clean compile link

compile:
	g++ -std=c++11 -g -Wall -Weffc++ -c -o bin/main.o src/main.cpp
	g++ -std=c++11 -g -Wall -Weffc++ -c -o bin/AddActions.o src/AddActions.cpp
	g++ -std=c++11 -g -Wall -Weffc++ -c -o bin/BaseActions.o src/BaseActions.cpp
	g++ -std=c++11 -g -Wall -Weffc++ -c -o bin/Customer.o src/Customer.cpp
	g++ -std=c++11 -g -Wall -Weffc++ -c -o bin/Order.o src/Order.cpp
	g++ -std=c++11 -g -Wall -Weffc++ -c -o bin/PrintActions.o src/PrintActions.cpp
	g++ -std=c++11 -g -Wall -Weffc++ -c -o bin/StepActions.o src/StepActions.cpp
	g++ -std=c++11 -g -Wall -Weffc++ -c -o bin/Volunteer.o src/Volunteer.cpp
	g++ -std=c++11 -g -Wall -Weffc++ -c -o bin/WareHouse.o src/WareHouse.cpp
	g++ -std=c++11 -g -Wall -Weffc++ -c -o bin/WareHouseActions.o src/WareHouseActions.cpp

link:
	g++ -o bin/warehouse bin/main.o bin/AddActions.o bin/BaseActions.o bin/Customer.o bin/Order.o bin/PrintActions.o bin/StepActions.o bin/Volunteer.o bin/WareHouse.o bin/WareHouseActions.o

clean:
#powershell Remove-Item -Force bin/*
	rm -f bin/*

valgrind:
	valgrind --leak-check=full --show-reachable=yes -s bin/warehouse /home/users/bsc/olpak/Desktop/spl1/SPL1/src/configFileExample.txt