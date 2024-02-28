#include <stdio.h>
#include <stdlib.h>

// Function to calculate absolute difference between two numbers
int absDiff(int a, int b) {
    return abs(a - b);
}

int main() {
    int tracks[] = {55, 58, 60, 70, 18};
    int numTracks = sizeof(tracks) / sizeof(tracks[0]);
    int headPosition;

    printf("Enter the initial head position: ");
    scanf("%d", &headPosition);

    int totalHeadMovement = 0;

    // FCFS (First Come First Serve) algorithm
    for (int i = 0; i < numTracks; ++i) {
        totalHeadMovement += absDiff(headPosition, tracks[i]);
        headPosition = tracks[i];
    }

    float averageHeadMovement = (float)totalHeadMovement / numTracks;

    printf("Average head movement: %.2f\n", averageHeadMovement);

    return 0;
}

