#!/bin/bash

NAME=wombats

/usr/bin/fpc -dEVAL -XS -O2 -o$NAME grader.pas
