#include <stdio.h>

#include "debug.h"
#include "value.h"

void disassembleChunk(Chunk* chunk, const char* name) {
    printf("== %s ==\n", name);

    for (int offset = 0; offset < chunk->count;) {
        offset = disassembleInstruction(chunk, offset);
    }

    printf("\nPress Enter to continue...");
    getchar();
}

static int simpleInstruction(const char* name, int offset) {
    printf("%s\n ", name);
    return offset + 1;
}

static int constantInstruction(const char* name, Chunk* chunk, int offset) {
    uint8_t constant = chunk->code[offset + 1];
    printf("%-16s %4d '", name, constant);
    printValue(chunk->constants.values[constant]);
    printf("'\n");
    return offset + 2;
}

static int constantLongInstruction(const char* name, Chunk* chunk, int offset) {
    uint8_t byte1 = chunk->code[offset + 1];
    uint8_t byte2 = chunk->code[offset + 2];
    uint8_t byte3 = chunk->code[offset + 3];

    int index = ((int) byte1 << 16) | ((int) byte2 << 8) | (int) byte3;

    printf("%-16s %4d '", name, index);
    printValue(chunk->constants.values[index]);
    printf("'\n");
    return offset + 4;

}

int disassembleInstruction(Chunk* chunk, int offset) {
    printf("%04d ", offset);
    int lineNumber = getLine(&chunk->lines, offset);
    printf("%4d ", lineNumber); 

    uint8_t instruction = chunk->code[offset];
    switch (instruction) {
        case OP_CONSTANT:
            return constantInstruction("OP_CONSTANT", chunk, offset);
        case OP_CONSTANT_LONG:
            return constantLongInstruction("OP_CONSTANT_LONG", chunk, offset);
        case OP_RETURN: 
            return simpleInstruction("OP_RETURN", offset);
        default:
            printf("Unknown opcode %d\n", instruction);
            return offset + 1;
    }
}
