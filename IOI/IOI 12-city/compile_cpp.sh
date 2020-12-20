#!/bin/bash

NAME=city

/usr/bin/g++ -DEVAL -Wall -static -O2 -o $NAME grader.cpp $NAME.cpp
