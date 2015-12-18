# (C) 2015, Xiaofeng Gu, all rights reserved.

include ./makefile.inc

OBJS = $(SRC)/BSpline.o $(SRC)/InstaForwardCurve.o $(SRC)/Swap.o $(SRC)/BasisSwap.o $(SRC)/CurveStripper.o
OBJ_DEPS = BSpline.o InstaForwardCurve.o Swap.o BasisSwap.o CurveStripper.o
LINK_ARCHIVES = -lalglib

all: lib_dep test_BSpline TestInstaForwardCurve test_solver test_CurveStripper test_BasisSwap test_memFuncStaticVari

lib_dep:
	$(MAKE) -C ./ext_lib/alglib
	mkdir -p ./ext_lib/libs
	cp ./ext_lib/alglib/libalglib.a ./ext_lib/libs

test_CurveStripper: lib_dep test_CurveStripper.o $(OBJ_DEPS)
	mkdir -p bin
	$(CC) -o $(BIN)/test_CurveStripper $(SRC)/test_CurveStripper.o $(OBJS) $(LIBS) $(LINK_ARCHIVES)

test_solver: lib_dep test_solver.o $(OBJ_DEPS)
	mkdir -p bin
	$(CC) -o $(BIN)/test_solver $(SRC)/test_solver.o $(OBJS) $(LIBS) $(LINK_ARCHIVES)

test_BSpline: test_BSpline.o $(OBJ_DEPS)
	mkdir -p bin
	$(CC) -o $(BIN)/test_BSpline $(SRC)/test_BSpline.o $(OBJS) $(LIBS) $(LINK_ARCHIVES)

TestInstaForwardCurve: TestInstaForwardCurve.o $(OBJ_DEPS)
	mkdir -p bin
	$(CC) -o $(BIN)/TestInstaForwardCurve $(SRC)/TestInstaForwardCurve.o $(OBJS) $(LIBS) $(LINK_ARCHIVES)

test_BasisSwap:	test_BasisSwap.o
	mkdir -p bin
	$(CC) -o $(BIN)/test_BasisSwap $(SRC)/test_BasisSwap.o $(OBJS) $(LIBS) $(LINK_ARCHIVES)

test_memFuncStaticVari: test_memFuncStaticVari.o
	mkdir -p bin
	$(CC) -o $(BIN)/test_memFuncStaticVari $(SRC)/test_memFuncStaticVari.o $(OBJS) $(LIBS) $(LINK_ARCHIVES)

%.o: $(SRC)/%.cpp
	$(CC) $(CFLAGS) $(APPL_INCLUDES) -c -o $(SRC)/$@ $<

clean:
	rm -f $(BIN)/*
	rm -f $(SRC)/*.o
	rm -f lib/libs/*.a

clean-all: clean
	rm -f ext_lib/libs/*.a
	$(MAKE) -C ./ext_lib/alglib clean
