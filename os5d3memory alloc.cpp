#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 100

struct memory_block {
    int id, size, allocated;
};

void initialize_memory(struct memory_block *blocks, int num_blocks) {
    for (int i = 0; i < num_blocks; i++) {
        blocks[i].id = i;
        blocks[i].size = rand() % 100 + 1;
        blocks[i].allocated = 0;
    }
}

void display_memory(struct memory_block *blocks, int num_blocks) {
    printf("Memory Blocks:\nID\tSize\tAllocated\n");
    for (int i = 0; i < num_blocks; i++)
        printf("%d\t%d\t%s\n", blocks[i].id, blocks[i].size, blocks[i].allocated ? "Yes" : "No");
    printf("\n");
}

void allocate(struct memory_block *blocks, int num_blocks, int size, const char *fit) {
    int index = -1, extrema = fit[0] == 'b' ? 0 : 1;
    for (int i = 0; i < num_blocks; i++) {
        if (!blocks[i].allocated && blocks[i].size >= size && (
            (extrema && blocks[i].size > blocks[index].size) || (!extrema && blocks[i].size < blocks[index].size)))
            index = i;
    }
    if (index != -1) {
        blocks[index].allocated = 1;
        printf("%s Fit: Allocated block %d of size %d\n", fit, blocks[index].id, size);
    } else
        printf("%s Fit: Unable to allocate block of size %d\n", fit, size);
}

int main() {
    struct memory_block blocks[MAX_BLOCKS];
    int num_blocks = 10, allocation_size = 50;

    initialize_memory(blocks, num_blocks);
    display_memory(blocks, num_blocks);

    allocate(blocks, num_blocks, allocation_size, "First");
    allocate(blocks, num_blocks, allocation_size, "Best");
    allocate(blocks, num_blocks, allocation_size, "Worst");

    display_memory(blocks, num_blocks);

    return 0;
}

