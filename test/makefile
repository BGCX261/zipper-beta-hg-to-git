# source files

SRC = testrunner.cpp

OBJ = $(patsubst %.cpp,obj/%.o,$(SRC))

OUT = zippertest

#include directories
INCLUDES = -I../src \
           -Ithird-party/cppunit-1.12.1/include

#library paths
LIBS = -L/user/local/lib -Lthird-party/cppunit-1.12.1/src/cppunit/.libs -L../zipper-lib/lib -lzipper -lcppunit -lm

#Compiler flags
CCFLAGS = -fPIC -g -Wall
LDFLAGS = rcs

#compiler
CCC = g++

default: $(OUT)

$(OBJ): | obj

obj:
	@echo creating objects directory $@
	@mkdir -p $@
	@mkdir -p $(patsubst %/, $@/%, $(sort $(dir $(SRC))))

obj/%.o : %.cpp
	$(CCC) $(INCLUDES) $(CCFLAGS) -c $< -o $@

#archive the library
$(OUT):$(OBJ)
	$(CCC) -o $(OUT) $(CCFLAGS) $(OBJ) $(LIBS)

clean:
	rm -f $(OBJ)
	rm -f $(OUT)
	rm -rf obj
