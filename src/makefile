# source files

INCLUDES = -I../third-party/bzip2-1.0.6

SRC = compressor/fileheader.cpp \
      compressor/zipbuilder.cpp\
      utils/fileutils.cpp \
      utils/crc32.cpp \
      utils/dateconverter.cpp \
      decompressor/decompressor.cpp \
      struct/node.cpp \
      struct/tree.cpp \
      encryption/blowfish.cpp\
      log/LoggerManager.cpp \
      log/FileLogger.cpp \
      log/ConsoleLogger.cpp \
      log/Logger.cpp \
      algorithms/algorithms.cpp \
      zipperlib.cpp

OBJ = $(patsubst %.cpp,obj/%.o,$(SRC))

OUT = libzipper.a


#library paths
LIBS = -L/user/local/lib -lm 

#Compiler flags
CCFLAGS = -fPIC -g -Wall
LDFLAGS = rcs

#compiler
CCC = g++
AR = ar

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
