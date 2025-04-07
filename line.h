#ifndef clox_line_h
#define clox_line_h

#include "common.h"
#include "memory.h"

typedef struct {
    int count;
    int lineNumber;
} Line;

typedef struct {
    int capacity;
    int count;
    Line* lines;
} LineArray;

int getLine(LineArray* array, int codeIndex);
void initLineArray(LineArray* array);
void freeLineArray(LineArray* array);
void writeLineArray(LineArray* array, int line);
void updateLineArray(LineArray* array, int line);


#endif