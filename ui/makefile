# source files

SRC = src/main.cpp \

OBJ = $(patsubst %.cpp,obj/%.o,$(SRC))

OUT = zipper

INCLUDES=-I ../src \
         -I src/console \
	 -I ../third-party/bzip2-1.0.6

LIBS = -L/user/local/lib -L../src/lib -L src/lib -lconsole -lzipper -lm \
       -L../third-party/bzip2-1.0.6 -lbz2

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

.PHONY: clean    
clean:
	rm -f $(OBJ)
	rm -f $(OUT)
	rm -rf obj
	
