#include <stdio.h>
#include <stdbool.h>

#define MAX_FRAMES 3

// Structure to represent a page frame
typedef struct {
    int page;
    bool used;
} Frame;

// Function to check if a page is present in a frame
bool isPagePresent(Frame frames[], int page) {
    for (int i = 0; i < MAX_FRAMES; ++i) {
        if (frames[i].page == page)
            return true;
    }
    return false;
}

// Function to find the index of the least recently used frame
int findLRU(Frame frames[]) {
    int index = 0;
    int min = frames[0].used;
    for (int i = 1; i < MAX_FRAMES; ++i) {
        if (frames[i].used < min) {
            min = frames[i].used;
            index = i;
        }
    }
    return index;
}

int main() {
    int pageSequence[] = {1, 2, 3, 2, 1, 5, 2, 1, 6, 2, 5, 6, 3, 1, 3, 6, 1, 2, 4};
    int numPages = sizeof(pageSequence) / sizeof(pageSequence[0]);
    int pageFaults = 0;

    Frame frames[MAX_FRAMES];
    for (int i = 0; i < MAX_FRAMES; ++i) {
        frames[i].page = -1;  // Initialize all frames as empty
        frames[i].used = 0;   // Initialize usage count for LRU
    }

    for (int i = 0; i < numPages; ++i) {
        int currentPage = pageSequence[i];
        if (!isPagePresent(frames, currentPage)) {
            ++pageFaults;
            int index = findLRU(frames);
            frames[index].page = currentPage;
        }
        for (int j = 0; j < MAX_FRAMES; ++j) {
            if (frames[j].page != -1)
                ++frames[j].used; // Increment usage count for all frames
        }
    }

    printf("Number of page faults using LRU: %d\n", pageFaults);

    return 0;
}

