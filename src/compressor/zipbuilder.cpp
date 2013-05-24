#include <stdlib.h>
#include <string.h>

#include "zipbuilder.h"

ZipBuilder::ZipBuilder() {
    this->inputPaths = 0;
    this->fileHeaders = 0;
}

ZipBuilder::ZipBuilder(char** input, int inputSize) {
    this->inputPaths = explorePaths(input, inputSize);
    this->fileHeaders = new list<Path>();
}

ZipBuilder::ZipBuilder(const ZipBuilder& other) {
    this->inputPaths=other.inputPaths;
    this->fileHeaders=other.fileHeaders;
}

ZipBuilder::~ZipBuilder() {
    if (this->fileHeaders)
        delete fileHeaders;
    if (this->inputPaths)
        delete inputPaths;
}

void ZipBuilder::buildZipFile(ostream outputStream){
    
}


