#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 100
#define MAX_FILENAME_LENGTH 50

// Structure to represent a file
typedef struct {
    char name[MAX_FILENAME_LENGTH];
} File;

// Structure to represent a directory
typedef struct {
    char name[MAX_FILENAME_LENGTH];
    File files[MAX_FILES];
    int numFiles;
} Directory;

// Function to create a new directory
Directory createDirectory(char *name) {
    Directory dir;
    strcpy(dir.name, name);
    dir.numFiles = 0;
    return dir;
}

// Function to add a file to a directory
void addFileToDirectory(Directory *dir, char *filename) {
    if (dir->numFiles < MAX_FILES) {
        strcpy(dir->files[dir->numFiles].name, filename);
        dir->numFiles++;
        printf("File '%s' added to directory '%s'.\n", filename, dir->name);
    } else {
        printf("Cannot add file. Directory '%s' is full.\n", dir->name);
    }
}

// Function to display the contents of a directory
void displayDirectory(Directory dir) {
    printf("Contents of directory '%s':\n", dir.name);
    if (dir.numFiles == 0) {
        printf("Empty\n");
    } else {
        for (int i = 0; i < dir.numFiles; ++i) {
            printf("%s\n", dir.files[i].name);
        }
    }
}

int main() {
    Directory cseDirectory = createDirectory("CSE");
    addFileToDirectory(&cseDirectory, "A");
    addFileToDirectory(&cseDirectory, "B");
    addFileToDirectory(&cseDirectory, "C");
    displayDirectory(cseDirectory);

    return 0;
}

