target:
	g++ -c MT23064.cpp
	g++ -g -o debug1 MT23064.o
	g++ -O3 -o optimize1 MT23064.o
	./debug1