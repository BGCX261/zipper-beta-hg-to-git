# source files

SRC = console/consoletest.cpp \
      testrunner.cpp 

OBJ = $(patsubst %.cpp,obj/%.o,$(SRC))

OUT = consoletest

#include directories
INCLUDES = -I../src/console \
           -I../../test/third-party/cppunit-1.12.1/include\
           -I../../src

#library paths
LIBS = -L/user/local/lib -L../../test/third-party/cppunit-1.12.1/src/cppunit/.libs -L../../src/lib -L../src/lib -lconsole -lzipper -lcppunit -lm

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
