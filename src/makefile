main: main.o mysql.o
	g++ $^ -o $@ -lmysqlclient -L/usr/lib64 -g -std=c++11

main.o: main.cpp
	g++ -c $^ -g -std=c++11

mysql.o: mysql.cpp
	g++ -c $^ -g -std=c++11
