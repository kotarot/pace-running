# Makefile for pace-running

pacerun: pacerun.hpp pacerun.cpp
	g++ -Wall -O2 -o pacerun pacerun.cpp
