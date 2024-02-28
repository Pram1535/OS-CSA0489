#include <stdio.h>
#include <stdbool.h>

#define MAX_FRAMES 3

// Function to find the index of the page that will not be used for the longest time in the future
int findOptimalIndex(int pages[], int n, int frame[], int frameSize, int index) {
    int res = -1, farthest = index;
    for (int i = 0; i < frameSize; ++i) {
        int j;
        for (j = index; j < n; ++j) {
            if (frame[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
        if (j == n)
            return i;
    }
    return (res == -1) ? 0 : res;
}

// Function to perform page replacement using the OPT algorithm
void optimalPageReplacement(int pages[], int n, int frameSize) {
    int frame[frameSize];
    bool isPresent[frameSize];

    for (int i = 0; i < frameSize; ++i) {
        frame[i] = -1;
        isPresent[i] = false;
    }

    int pageFaults = 0;

    for (int i = 0; i < n; ++i) {
        if (!isPresent[i]) {
            int j;
            if (pageFaults < frameSize) {
                frame[pageFaults] = pages[i];
                isPresent[i] = true;
                ++pageFaults;
            } else {
                j = findOptimalIndex(pages, n, frame, frameSize, i + 1);
                isPresent[j] = false;
                isPresent[i] = true;
                frame[j] = pages[i];
                ++pageFaults;
            }
        }
    }

    printf("Number of page faults using OPT: %d\n", pageFaults);
}

int main() {
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    int numPages = sizeof(pages) / sizeof(pages[0]);
    int numFrames = 3;

    optimalPageReplacement(pages, numPages, numFrames);

    return 0;
}

