include ../../makefile.inc

CPP_FILES := $(wildcard *.cpp)
OBJ_FILES := $(notdir $(CPP_FILES:.cpp=.o))

all: $(OBJ_FILES)
	$(ARC) $(ARCFLAGS) libalglib.a $(OBJ_FILES)

%.o: %.cpp
	$(CC) $(CFLAGS) $(LIB_INCLUDES) -c -o $@ $<

clean:
	rm -f libalglib.a
	rm -f *.o
