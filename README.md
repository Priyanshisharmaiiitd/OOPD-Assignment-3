# OOPD-Assignment-3
This is for oopd assignment 3
These are the commands that I have used to create the makefile
1)g++ -c MT23064.cpp
MT23064.cpp is the name of my source file in c++
We are using g++ compiler to compile our source file
-c flag means we are generating only the object file , which is the intermediate step in compilation process
2)g++ -g -o debug1 MT23064.cpp
We are using g++compiler to create an executable file named debug1, -g means we are adding debugging information , so that we can run debugger on it and -o specifies the output executable file's name
3)g++  -O3 -o optimize1 MT23064.o
We are using g++compiler to link the MT23064.o object file and create an executable file named as optimize1, -O3 means high level of optimization in the code is done, and -o flag specifies the output executable file's name
4)./debug1
We are running the executable file created in previour step and ./ means that executable file is in the current directory.
