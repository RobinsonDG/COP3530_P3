all: compile remove

compile:
	g++ src/*.cpp -o output/project3.exe

remove:
	del output/*.exe