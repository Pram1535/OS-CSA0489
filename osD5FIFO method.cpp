#include <stdio.h>
#include <stdbool.h>

// Function prototypes
int findPageFaults(int pageReference[], int n, int numFrames);

int main() {
    // Test case parameters
    int numFrames = 3;
    int pageReference[] = {4, 1, 2, 4, 3, 2, 1, 5};
    int n = sizeof(pageReference) / sizeof(pageReference[0]);

    // Calculate and print the number of page faults
    int pageFaults = findPageFaults(pageReference, n, numFrames);
    printf("Number of page faults: %d\n", pageFaults);

    return 0;
}

int findPageFaults(int pageReference[], int n, int numFrames) {
    int pageFaults = 0;
    int frames[numFrames];
    bool pagePresent[numFrames];
    int framePointer = 0;

    // Initialize pagePresent array to false and frames array to -1
    for (int i = 0; i < numFrames; i++) {
        pagePresent[i] = false;
        frames[i] = -1;
    }

    // Iterate through the page reference sequence
    for (int i = 0; i < n; i++) {
        int currentPage = pageReference[i];
        bool pageFound = false;

        // Check if the page is already in the frame
        for (int j = 0; j < numFrames; j++) {
            if (frames[j] == currentPage) {
                pageFound = true;
                break;
            }
        }

        // If page not found, it's a page fault
        if (!pageFound) {
            pageFaults++;

            // Replace the oldest page using FIFO
            frames[framePointer] = currentPage;
            framePointer = (framePointer + 1) % numFrames;
        }
    }

    return pageFaults;
}

