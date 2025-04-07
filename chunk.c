#include <stdlib.h>

#include "chunk.h"

void initChunk(Chunk* chunk) {
    chunk->count = 0;
    chunk->capacity = 0;
    chunk->code = NULL;
    initValueArray(&chunk->constants);
    initLineArray(&chunk->lines);
}

void freeChunk(Chunk* chunk) {
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    freeLineArray(&chunk->lines);
    freeValueArray(&chunk->constants);
    initChunk(chunk);
}

void writeChunk(Chunk* chunk, uint8_t byte, int line) {
    if (chunk->capacity < chunk->count + 1) {
        int oldCapacity = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(oldCapacity);
        chunk->code = GROW_ARRAY(uint8_t, chunk->code, 
           oldCapacity, chunk->capacity); 
    }

    chunk->code[chunk->count] = byte;
    chunk->count++;

    updateLineArray(&chunk->lines, line);
}

int addConstant(Chunk* chunk, Value value) {
    writeValueArray(&chunk->constants, value);
    return chunk->constants.count - 1;
}

void writeConstant(Chunk* chunk, Value value, int line) {
    int index = addConstant(chunk, value);
    if (index <= 255) {
        writeChunk(chunk, OP_CONSTANT, line);
        writeChunk(chunk, index, line);
        return;
    }

    writeChunk(chunk, OP_CONSTANT_LONG, line);
    writeChunk(chunk, (index >> 16) & 0x00FF, line);
    writeChunk(chunk, (index >> 8) & 0x00FF, line);
    writeChunk(chunk, index & 0x00FF, line);
    
    return;

}
