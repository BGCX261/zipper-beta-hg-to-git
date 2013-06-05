# source files

SRC =  consolelib.cpp\
console/zipper.cpp

OBJ = $(patsubst %.cpp,obj/%.o,$(SRC))

OUT = libconsole.a

INCLUDES=-I../src \
         -I../../src

LIBS = -L/user/local/lib -L../../src/lib -lzipper -lm

#Compiler flags
CCFLAGS = -fPIC -g -Wall
LDFLAGS = rcs

#compiler
CCC = g++
AR=ar

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
	@mkdir -p lib
	$(AR) $(LDFLAGS) lib/$(OUT) $(OBJ)

clean:
	rm -f $(OBJ)
	rm -rf obj
	rm -rf lib
