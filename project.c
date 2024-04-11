#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 100

struct Student {
    int id;
    char name[50];
    int age;
};

struct Student students[MAX_STUDENTS];
int studentCount = 0;

// Function to add a new student
void addStudent(struct Student *newStudent) {
    if (studentCount >= MAX_STUDENTS) {
        printf("Cannot add more students. Student limit reached.\n");
        return;
    }

    // Prompting user to input student details
    printf("Enter student ID: ");
    scanf("%d", &(newStudent->id));

    printf("Enter student name: ");
    scanf("%s", newStudent->name);

    printf("Enter student age: ");
    scanf("%d", &(newStudent->age));

    // Adding new student to the array of students
    students[studentCount++] = *newStudent;
    printf("Student added successfully.\n");
}

// Function to display all students
void displayStudents() {
    if (studentCount == 0) {
        printf("No students to display.\n");
        return;
    }

    // Displaying header for the table
    printf("ID\tName\tAge\n");
    // Displaying each student's details
    for (int i = 0; i < studentCount; i++) {
        printf("%d\t%s\t%d\n", students[i].id, students[i].name, students[i].age);
    }
}

// Function to search for a student by ID
void searchStudent(int id) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            // Printing details of the found student
            printf("\nID: %d\nName: %s\nAge: %d\n", students[i].id, students[i].name, students[i].age);
            return;
        }
    }
    printf("Student with ID %d not found.\n", id);
}

// Function to delete a student by ID
void deleteStudent(int id) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            // Shifting array elements to remove the student
            for (int j = i; j < studentCount - 1; j++) {
                students[j] = students[j + 1];
            }
            studentCount--;
            printf("\nStudent with ID %d deleted successfully.\n", id);
            return;
        }
    }
    printf("\nStudent with ID %d not found.\n", id);
}

// Function to save student data to a file
void saveDataToFile(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("\nError opening file %s for writing.\n", filename);
        return;
    }

    // Writing each student's data to the file
    for (int i = 0; i < studentCount; i++) {
        fprintf(file, "%d %s %d\n", students[i].id, students[i].name, students[i].age);
    }

    fclose(file);
    printf("Data saved to %s successfully.\n", filename);
}

// Function to load student data from a file
void loadDataFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file %s for reading.\n", filename);
        return;
    }

    // Reading student data from the file
    while (fscanf(file, "%d %s %d", &students[studentCount].id, students[studentCount].name, &students[studentCount].age) != EOF) {
        studentCount++;
    }

    fclose(file);
    printf("Data loaded from %s successfully.\n", filename);
}

int main() {
    int choice, id;
    struct Student newStudent;

    char filename[] = "student_data.txt";

    // Load student data from file when the program starts
    loadDataFromFile(filename);

    // Main menu loop
    do {
        printf("\nStudent Management System\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student by ID\n");
        printf("4. Delete Student by ID\n");
        printf("5. Save Data to File\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent(&newStudent); // Add a new student
                break;
            case 2:
                displayStudents(); // Display all students
                break;
            case 3:
                printf("Enter student ID to search: ");
                scanf("%d", &id);
                searchStudent(id); // Search for a student by ID
                break;
            case 4:
                printf("Enter student ID to delete: ");
                scanf("%d", &id);
                deleteStudent(id); // Delete a student by ID
                break;
            case 5:
                saveDataToFile(filename); // Save data to file
                break;
            case 6:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 6.\n");
        }
    } while (choice != 6);

    return 0;
}
