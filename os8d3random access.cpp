#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define FILENAME "employees.dat"

struct Employee { int id; char name[MAX_NAME_LENGTH]; float salary; };

void addEmployee() {
    struct Employee emp;
    FILE *file = fopen(FILENAME, "ab");
    if (!file) { printf("Error!\n"); exit(1); }
    printf("Enter ID, Name, and Salary: ");
    scanf("%d ", &emp.id);
    fgets(emp.name, MAX_NAME_LENGTH, stdin);
    scanf("%f", &emp.salary);
    fwrite(&emp, sizeof(struct Employee), 1, file);
    fclose(file);
}

void updateEmployee() {
    int targetId;
    struct Employee emp;
    FILE *file = fopen(FILENAME, "r+b");
    if (!file) { printf("Error!\n"); exit(1); }
    printf("Enter ID to update: ");
    scanf("%d", &targetId);
    while (fread(&emp, sizeof(struct Employee), 1, file) == 1) {
        if (emp.id == targetId) {
            printf("Enter new Name and Salary: ");
            fgets(emp.name, MAX_NAME_LENGTH, stdin);
            scanf("%f", &emp.salary);
            fseek(file, -sizeof(struct Employee), SEEK_CUR);
            fwrite(&emp, sizeof(struct Employee), 1, file);
            fclose(file);
            return;
        }
    }
    printf("Not found!\n");
    fclose(file);
}

void displayEmployees() {
    struct Employee emp;
    FILE *file = fopen(FILENAME, "rb");
    if (!file) { printf("Error!\n"); exit(1); }
    while (fread(&emp, sizeof(struct Employee), 1, file) == 1) {
        printf("%d %s %.2f\n", emp.id, emp.name, emp.salary);
    }
    fclose(file);
}

int main() {
    int choice;
    do {
        printf("1. Add\n2. Update\n3. Display\n4. Exit\n");
        scanf("%d", &choice);
        switch (choice) {
            case 1: addEmployee(); break;
            case 2: updateEmployee(); break;
            case 3: displayEmployees(); break;
            case 4: printf("Exiting.\n"); break;
            default: printf("Invalid!\n");
        }
    } while (choice != 4);
    return 0;
}

