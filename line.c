#include "line.h"
#include "memory.h"
#include <stdio.h>

int getLine(LineArray* array, int codeIndex) {
    int totalCodeCount = 0;

    for (int i = 0; i < array->count; i++) {
        totalCodeCount += array->lines[i].count;
        
        if (codeIndex < totalCodeCount) {
            return array->lines[i].lineNumber;
        }
    }

    return 0;
}

void initLineArray(LineArray* array) {
    array->capacity = 0;
    array->count = 0;
    array->lines = NULL;
}

void freeLineArray(LineArray* array) {
    FREE_ARRAY(Line, array->lines, array->count);
    initLineArray(array);
}

void writeLineArray(LineArray* array, int line) {
    if (array->capacity < array->count + 1) {
        int oldCapacity = array->capacity;
        array->capacity = GROW_CAPACITY(array->capacity);
        array->lines = GROW_ARRAY(Line, array->lines, oldCapacity, array->capacity);
    }

    array->count++;
    array->lines[array->count - 1].count = 1;
    array->lines[array->count - 1].lineNumber = line;
}

void updateLineArray(LineArray* array, int line) {
    if (array->capacity == 0) {
        writeLineArray(array, line);
        return;        
    }

    Line* lastLine = &array->lines[array->count - 1];
    if (lastLine->lineNumber != line) {
        writeLineArray(array, line);
        return;
    }

    lastLine->count++;

    return;
}
