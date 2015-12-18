# (C) 2015, Xiaofeng Gu, all rights reserved.

include ./makefile.inc

OBJ_DEPS = GaussianRVGenerator.o BrownianMotionGenerator.o LIBORMarketModel1F.o Rates.o Swap.o
OBJS = $(addprefix $(SRC)/, $(OBJ_DEPS))

LINK_ARCHIVES = 

all: test_GaussianRVGenerator test_eigen test_BrownianMotionGenerator test_vec test_LIBORMarketModel1F test_Swap

lib_dep:
	$(MAKE) -C ./ext_lib/alglib
	mkdir -p ./ext_lib/libs
	cp ./ext_lib/alglib/libalglib.a ./ext_lib/libs

test_GaussianRVGenerator: test_GaussianRVGenerator.o $(OBJ_DEPS)
	mkdir -p bin
	$(CC) -o $(BIN)/$@ $(SRC)/$< $(OBJS) $(LIBS) $(LINK_ARCHIVES)

test_eigen: test_eigen.o $(OBJ_DEPS)
	mkdir -p bin
	$(CC) -o $(BIN)/$@ $(SRC)/$< $(OBJS) $(LIBS) $(LINK_ARCHIVES)

test_BrownianMotionGenerator: test_BrownianMotionGenerator.o $(OBJ_DEPS)
	mkdir -p bin
	$(CC) -o $(BIN)/$@ $(SRC)/$< $(OBJS) $(LIBS) $(LINK_ARCHIVES)

test_LIBORMarketModel1F: test_LIBORMarketModel1F.o $(OBJ_DEPS)
	mkdir -p bin
	$(CC) -o $(BIN)/$@ $(SRC)/$< $(OBJS) $(LIBS) $(LINK_ARCHIVES)

test_vec: test_vec.o $(OBJ_DEPS)
	mkdir -p bin
	$(CC) -o $(BIN)/$@ $(SRC)/$< $(OBJS) $(LIBS) $(LINK_ARCHIVES)

test_Swap: test_Swap.o $(OBJ_DEPS)
	mkdir -p bin
	$(CC) -o $(BIN)/$@ $(SRC)/$< $(OBJS) $(LIBS) $(LINK_ARCHIVES)

%.o: $(SRC)/%.cpp
	$(CC) $(CFLAGS) $(APPL_INCLUDES) -c -o $(SRC)/$@ $<

clean:
	rm -f $(BIN)/*
	rm -f $(SRC)/*.o
	rm -f lib/libs/*.a

clean-all: clean
	rm -f ext_lib/libs/*.a

