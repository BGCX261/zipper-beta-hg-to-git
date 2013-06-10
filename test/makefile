# source files

SRC = interface/interfacetest.cpp \
      compressor/fileheadertest.cpp \
      utils/fileutilstest.cpp \
      utils/crctest.cpp \
      utils/dateconvertertest.cpp \
      struct/treetest.cpp \
      decompressor/decompressortest.cpp \
      testrunner.cpp 

OBJ = $(patsubst %.cpp,obj/%.o,$(SRC))

OUT = zippertest

#include directories
INCLUDES = -I../src \
           -Ithird-party/cppunit-1.12.1/include

#library paths
LIBS = -L/user/local/lib -Lthird-party/cppunit-1.12.1/src/cppunit/.libs -L../src/lib -lzipper -lcppunit -lm

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

# build tests
build-tests: .build-tests-post

.build-tests-pre:
# Add your pre 'build-tests' code here...

.build-tests-post: .build-tests-impl
# Add your post 'build-tests' code here...


# run tests
test: .test-post

.test-pre:
# Add your pre 'test' code here...

.test-post: .test-impl
# Add your post 'test' code here...
