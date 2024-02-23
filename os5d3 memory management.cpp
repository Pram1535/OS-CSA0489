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

void worstFit(int size) {
    int index = -1;
    int max_size = -1;
    for (int i = 0; i < MAX_BLOCKS; ++i) {
        if (!memory[i].allocated && memory[i].size >= size && memory[i].size > max_size) {
            index = i;
            max_size = memory[i].size;
        }
    }

    if (index != -1) {
        memory[index].allocated = 1;
        printf("Memory allocated for process of size %d using worst fit at block %d\n", size, memory[index].id);
    } else {
        printf("Memory allocation failed for process of size %d using worst fit\n", size);
    }
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

    worstFit(250);
    worstFit(100);
    worstFit(350);
    worstFit(500);

    displayMemory();

    deallocateMemory(1);
    deallocateMemory(3);

    displayMemory();

    return 0;
}

