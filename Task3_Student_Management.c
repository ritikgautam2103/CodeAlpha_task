#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "students.dat"

typedef struct {
    int rollNo;
    char name[50];
    int age;
    char course[50];
    float marks;
} Student;

void addStudent(void);
void displayStudents(void);
void searchStudent(void);
void updateStudent(void);
void deleteStudent(void);

int main(void) {
    int choice;

    do {
        printf("\n===== Student Management System =====\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: printf("Exiting...\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 6);

    return 0;
}

void addStudent(void) {
    FILE *fp;
    Student s;

    fp = fopen(FILE_NAME, "ab");
    if (fp == NULL) {
        printf("Unable to open file.\n");
        return;
    }

    printf("Enter Roll Number: ");
    scanf("%d", &s.rollNo);

    printf("Enter Name: ");
    scanf(" %49[^\n]", s.name);

    printf("Enter Age: ");
    scanf("%d", &s.age);

    printf("Enter Course: ");
    scanf(" %49[^\n]", s.course);

    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(Student), 1, fp);
    fclose(fp);

    printf("Student added successfully.\n");
}

void displayStudents(void) {
    FILE *fp;
    Student s;

    fp = fopen(FILE_NAME, "rb");
    if (fp == NULL) {
        printf("No student records found.\n");
        return;
    }

    printf("\n%-8s %-25s %-6s %-20s %-8s\n",
           "Roll", "Name", "Age", "Course", "Marks");
    printf("---------------------------------------------------------------------\n");

    while (fread(&s, sizeof(Student), 1, fp) == 1) {
        printf("%-8d %-25s %-6d %-20s %-8.2f\n",
               s.rollNo, s.name, s.age, s.course, s.marks);
    }

    fclose(fp);
}

void searchStudent(void) {
    FILE *fp;
    Student s;
    int roll, found = 0;

    printf("Enter Roll Number to search: ");
    scanf("%d", &roll);

    fp = fopen(FILE_NAME, "rb");
    if (fp == NULL) {
        printf("No student records found.\n");
        return;
    }

    while (fread(&s, sizeof(Student), 1, fp) == 1) {
        if (s.rollNo == roll) {
            printf("\nStudent Found\n");
            printf("Roll Number: %d\n", s.rollNo);
            printf("Name       : %s\n", s.name);
            printf("Age        : %d\n", s.age);
            printf("Course     : %s\n", s.course);
            printf("Marks      : %.2f\n", s.marks);
            found = 1;
            break;
        }
    }

    fclose(fp);

    if (!found)
        printf("Student not found.\n");
}

void updateStudent(void) {
    FILE *fp;
    Student s;
    int roll, found = 0;

    printf("Enter Roll Number to update: ");
    scanf("%d", &roll);

    fp = fopen(FILE_NAME, "rb+");
    if (fp == NULL) {
        printf("No student records found.\n");
        return;
    }

    while (fread(&s, sizeof(Student), 1, fp) == 1) {
        if (s.rollNo == roll) {
            printf("Enter New Name: ");
            scanf(" %49[^\n]", s.name);

            printf("Enter New Age: ");
            scanf("%d", &s.age);

            printf("Enter New Course: ");
            scanf(" %49[^\n]", s.course);

            printf("Enter New Marks: ");
            scanf("%f", &s.marks);

            fseek(fp, -(long)sizeof(Student), SEEK_CUR);
            fwrite(&s, sizeof(Student), 1, fp);

            found = 1;
            printf("Student updated successfully.\n");
            break;
        }
    }

    fclose(fp);

    if (!found)
        printf("Student not found.\n");
}

void deleteStudent(void) {
    FILE *fp, *temp;
    Student s;
    int roll, found = 0;

    printf("Enter Roll Number to delete: ");
    scanf("%d", &roll);

    fp = fopen(FILE_NAME, "rb");
    if (fp == NULL) {
        printf("No student records found.\n");
        return;
    }

    temp = fopen("temp.dat", "wb");
    if (temp == NULL) {
        fclose(fp);
        printf("Unable to create temporary file.\n");
        return;
    }

    while (fread(&s, sizeof(Student), 1, fp) == 1) {
        if (s.rollNo == roll) {
            found = 1;
        } else {
            fwrite(&s, sizeof(Student), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.dat", FILE_NAME);

    if (found)
        printf("Student deleted successfully.\n");
    else
        printf("Student not found.\n");
}
