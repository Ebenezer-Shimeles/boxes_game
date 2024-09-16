@echo off
cls

cmake -G "MinGW Makefiles" . && make && granny

del *.cmake CMakeCache.txt Makefile