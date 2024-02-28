#include <stdio.h>
#include <stdlib.h>

// Function to calculate the absolute difference between two numbers
int absDiff(int a, int b) {
    return abs(a - b);
}

int main() {
    int numTracks = 9;
    int tracks[] = {55, 58, 60, 70, 18, 90, 150, 160, 18};

    printf("Track position: ");
    for (int i = 0; i < numTracks; ++i) {
        printf("%d ", tracks[i]);
    }
    printf("\n");

    int initialHeadPosition;
    printf("Enter the initial head position: ");
    scanf("%d", &initialHeadPosition);

    int totalHeadMovement = 0;

    // FCFS algorithm
    for (int i = 0; i < numTracks; ++i) {
        totalHeadMovement += absDiff(initialHeadPosition, tracks[i]);
        initialHeadPosition = tracks[i];
    }

    float averageHeadMovement = (float)totalHeadMovement / numTracks;

    printf("Average head movement: %.2f\n", averageHeadMovement);

    return 0;
}

