#!/bin/bash

NAME=wall

/usr/bin/fpc -dEVAL -XS -O2 -o$NAME grader.pas
