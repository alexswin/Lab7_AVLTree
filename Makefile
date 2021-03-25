TARGETS = avlLab
CC = g++
CCFLAGS = -std=c++11 -g
avlLab: main.cpp AVLInterface.h NodeInterface.h AVL.h AVL.cpp Node.h Node.cpp
	$(CC) $(CCFLAGS) -o avlLab main.cpp AVL.cpp Node.cpp
clean: 
	rm avlLab