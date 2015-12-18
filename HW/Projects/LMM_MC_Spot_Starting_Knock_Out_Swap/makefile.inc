# (C) 2015, Xiaofeng Gu, all rights reserved.

APPL_INCLUDES = -I./include -I./lib/include -I ./ext_lib/
LIB_INCLUDES = -I../../include -I../../../ext_lib/
CFLAGS = -Wall -O2 -std=c++11
ARCFLAGS = -cvq
CC = g++
ARC = ar
SRC = src
LIBS = -L./lib/libs -L./ext_lib/libs
BIN = ./bin
MAKE = make