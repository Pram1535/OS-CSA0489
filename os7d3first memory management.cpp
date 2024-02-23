#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 100

struct MemoryBlock {
    int id;
    int size;
    int allocated;
};

struct MemoryBlock memory[MAX_BLOCKS];

void initializeMemory() {
    for (int i = 0; i < MAX_BLOCKS; ++i) {
        memory[i].id = i + 1;
        memory[i].size = 0;
        memory[i].allocated = 0;
    }
}

void displayMemory() {
    printf("Memory Blocks:\n");
    printf("ID\tSize\tAllocated\n");
    for (int i = 0; i < MAX_BLOCKS; ++i) {
        printf("%d\t%d\t%s\n", memory[i].id, memory[i].size, memory[i].allocated ? "Yes" : "No");
    }
}

void firstFit(int size) {
    for (int i = 0; i < MAX_BLOCKS; ++i) {
        if (!memory[i].allocated && memory[i].size >= size) {
            memory[i].allocated = 1;
            printf("Memory allocated for process of size %d using first fit at block %d\n", size, memory[i].id);
            return;
        }
    }
    printf("Memory allocation failed for process of size %d using first fit\n", size);
}

void deallocateMemory(int blockId) {
    for (int i = 0; i < MAX_BLOCKS; ++i) {
        if (memory[i].id == blockId) {
            memory[i].allocated = 0;
            printf("Memory deallocated for block %d\n", blockId);
            return;
        }
    }
    printf("Block %d not found in memory\n", blockId);
}

int main() {
    initializeMemory();

    memory[0].size = 150;
    memory[1].size = 300;
    memory[2].size = 200;
    memory[3].size = 400;

    displayMemory();

    firstFit(250);
    firstFit(100);
    firstFit(350);
    firstFit(500);

    displayMemory();

    deallocateMemory(1);
    deallocateMemory(3);

    displayMemory();

    return 0;
}

