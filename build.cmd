@echo off
cls

cmake -G "MinGW Makefiles" . && make && granny

del *.cmake  Makefile