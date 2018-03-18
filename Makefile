# Copyright (C) 2018 Nnmjywg

_target = ""

all:
	read _target
	make $_target

battleship-cxx:
	g++ -o Battleship main.cpp -std=c++11 -Wall -pedantic