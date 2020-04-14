#!/bin/sh

g++ -std=c++11 -o grader grader.cpp lang.cpp && cat grader.in.1 | ./grader
