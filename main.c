#include <stdio.h>
#include "datatype.h"
#include "function.h"

int main() {
    Student students[100];
    int studentCount = 0, choice, subChoice,a;
    loadStudents(students, &studentCount);
    Teacher teachers[100];
    int teacherCount = 0;
    loadTeachers(teachers, &teacherCount);
    do {
        mainMenu();
        scanf("%d", &choice);
        if (choice == 1) {
            do {
                studentMenu();
                scanf("%d", &subChoice);
                switch (subChoice) {
                    case 1: inputStudent(students, &studentCount); break;
                    case 2: displayStudents(students, studentCount); break;
                    case 3: searchStudent(students, studentCount); break;
                    case 4: displayStudents(students, studentCount); editStudent(students, studentCount); break;
                    case 5: displayStudents(students, studentCount); deleteStudent(students, &studentCount); break;
                    case 6: sortMenu(students, studentCount); break;
                    case 7: resetStudents(students, &studentCount); break;
                    case 0: break;
                    default: printf("Invalid choice! Please try again.\n");
                }
            } while (subChoice != 0);
        } else if (choice == 2) {
            do {
                teacherMenu();
                scanf("%d", &subChoice);
                switch (subChoice) {
                    case 1: inputTeacher(teachers, &teacherCount); break;
                    case 2: displayTeachers(teachers, teacherCount); break;
                    case 3: searchTeacher(teachers, teacherCount); break;
                    case 4: displayTeachers(teachers, teacherCount); editTeacher(teachers, teacherCount); break;
                    case 5: displayTeachers(teachers, teacherCount); deleteTeacher(teachers, &teacherCount); break;
                    case 6: resetTeachers(teachers, &teacherCount); break;
                    case 0: break;
                    default: printf("Invalid choice! Please try again.\n");
                }
            } while (subChoice != 0);
        } else if (choice == 0) {
            printf("Exiting Program...\n");
        } else {
            printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 0); 
    return 0;
}

