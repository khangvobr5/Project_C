#include <stdio.h>
#include <string.h>
#include "datatype.h"
#include "function.h"

//QUAN LY SINH VIEN

//luu file danh sach hoc sinh vao file student.txt 
void saveStudents(Student students[], int count) {
    FILE *file = fopen("students.txt", "wb"); 
    if (file == NULL) {
        printf("Loi: Khong the mo file de ghi\n");
        return;
    }
    
    fwrite(&count, sizeof(int), 1, file);
    fwrite(students, sizeof(Student), count, file);
    
    fclose(file);
    printf("Du lieu da duoc luu vao file\n");
}
//xuat file danh sach hoc sinh trong file student.txt
void loadStudents(Student students[], int *count) {
    FILE *file = fopen("students.txt", "rb");
    if (file == NULL) {
        printf("Loi: Khong the mo file hoac file trong\n");
        return;
    }
    
    fread(count, sizeof(int), 1, file);//doc so luong sinh vien
    fread(students, sizeof(Student), *count, file);
    
    fclose(file);
    printf("Du lieu da duoc tai tu file\n");
}
//menu chinh
void mainMenu() {
    printf("*** Student Management System Using C ***\n");
    printf("CHOOSE YOUR ROLE\n");
    printf("========================\n");
    printf("[1] Student\n");
    printf("[2] Teacher\n");
    printf("[0] Exit the Program\n");
    printf("========================\n");
    printf("Enter Your Choice: ");
}
//menu con
void studentMenu() {
    printf("***Student Management Menu***\n");
    printf("[1] Add A New Student\n");
    printf("[2] Show All Students\n");
    printf("[3] Search A Student\n");
    printf("[4] Edit A Student\n");
    printf("[5] Delete A Student\n");
    printf("[6] Sort Students\n");
    printf("[7] Reset Student List\n");
    printf("[0] Back to Main Menu\n");
    printf("Enter Your Choice: ");
}
//menu sort
void sortMenu(students, studentCount){
	int i,j,a;
	printf("***Sort Menu***\n");
	printf("[1] Sort StudentsAtoZ\n");
    printf("[2] Sort StudentsZtoA\n");
    printf("[0] Back to Main Menu\n");
    printf("Enter Your Choice: ");
    scanf("%d",&a);
    switch(a){
    	case 1:
    		sortStudentsAtoZ(students, studentCount);
    		break;
    	case 2:
    		sortStudentsZtoA(students, studentCount);
    		break;
    	case 3:
    		break;
	}
    
}
//nhap thong tin sinh vien
void inputStudent(Student students[], int *count) {
    if (*count >= 100) {
        printf("Student list is full!\n");
        return;
    }
    Student newStudent;
    int isDuplicate;
//Id Student
    do {
        isDuplicate = 0;
        printf("Enter Student ID: ");
        scanf("%d", &newStudent.id);
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        int i;
        for ( i = 0; i < *count; i++) {
            if (students[i].id == newStudent.id) {
                printf("ID already exists. Please enter a different ID.\n");
                isDuplicate = 1;
                break;
            }
        }
        char str[20];
        sprintf(str, "%d", newStudent.id);
        if (strlen(str) == 0 || newStudent.id < 0) {
            printf("Error.\n");
            isDuplicate = 1;
        }
    } while (isDuplicate);
//Name Student
    do {
        isDuplicate = 0;
        printf("Enter Student Name: ");
        fgets(newStudent.name, sizeof(newStudent.name), stdin);
        newStudent.name[strcspn(newStudent.name, "\n")] = '\0';
        if (strlen(newStudent.name) == 0) {
            printf("Error.\n");
            isDuplicate = 1;
        }
    } while(isDuplicate);
//Gmail Student
    do {
        isDuplicate = 0;
        printf("Enter Student Email: ");
        scanf("%s", newStudent.email);
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        int i;
        for ( i = 0; i < *count; i++) {
            if (strcmp(students[i].email, newStudent.email) == 0) {
                printf("Email already exists. Please enter a different email.\n");
                isDuplicate = 1;
                break;
            }
        }
        if (strlen(newStudent.email) < 0) {
            printf("Error.\n");
            isDuplicate = 1;
        }
        if (strstr(newStudent.email, "@gmail.com.") == NULL) {
            printf("Error.\n");
            isDuplicate = 1;
        }
    } while (isDuplicate);
//DateOfBirth Student
    do {
        isDuplicate = 0;
        printf("Enter Student Date of Birth (dd mm yyyy): ");
        int result = scanf("%d %d %d", &newStudent.dayofbirth.day, &newStudent.dayofbirth.month, &newStudent.dayofbirth.year);
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        if (result != 3) {
            printf("Error. Date of Birth should be in format dd mm yyyy.\n");
            isDuplicate = 1;
            while (getchar() != '\n');
        }
        if (newStudent.dayofbirth.day>31||newStudent.dayofbirth.day<1){
        	printf("Error.\n");
            isDuplicate = 1;
		} else if(newStudent.dayofbirth.month>12||newStudent.dayofbirth.month<1){
			printf("Error.\n");
            isDuplicate = 1;
		} else if(newStudent.dayofbirth.year<1||newStudent.dayofbirth.year>9999){
			printf("Error.\n");
            isDuplicate = 1;
		}
    } while (isDuplicate);
//Phone Student
    do {
        isDuplicate = 0;
        printf("Enter Phone Number: ");
        scanf(" %s", newStudent.phone);
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        int i;
        for ( i = 0; i < *count; i++) {
            if (strcmp(students[i].phone, newStudent.phone) == 0) {
                printf("Phone number already exists. Please enter a different phone number.\n");
                isDuplicate = 1;
                break;
            }
        }
        if (strlen(newStudent.phone) < 10||strlen(newStudent.phone)>10) {
            printf("Error.\n");
            isDuplicate = 1;
        }
    } while (isDuplicate);
//Industry Student
    do {
        isDuplicate = 0;
        printf("Enter Industry: ");
        scanf("%s", newStudent.industry);
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        if (strlen(newStudent.industry) < 1) {
            printf("Error.\n");
            isDuplicate = 1;
        }
    } while (isDuplicate);
//Gender Student
    int tempgenderStudent;
    do {
        printf("Enter Student Gender (0: Male, 1: Female): ");
        scanf("%d", &tempgenderStudent);
    } while (tempgenderStudent != 0 && tempgenderStudent != 1);
    newStudent.gender = tempgenderStudent;
    
    students[(*count)++] = newStudent;
    saveStudents(students, *count);
    printf("Student added successfully!\n");
}
// hien thi bang liet ke danh sach sinh vien
void displayStudents(Student students[], int count) {
    if (count == 0) {
        printf("No students found!\n");
        return;
    }
    printf("========================================================================================================================================\n");
    printf("| %-5s | %-20s | %-28s | %-16s | %-15s | %-20s | %-10s |\n", "ID", "Name", "Email", "Date of Birth", "Phone", "Industry", "Gender");
    int i;
    for ( i = 0; i < count; i++) {
        printf("----------------------------------------------------------------------------------------------------------------------------------------\n");
        printf("| %-5d | %-20s | %-28s | %02d/%02d/%04d       | %-15s | %-20s | %-10s |\n",
            students[i].id,
            students[i].name,
            students[i].email,
            students[i].dayofbirth.day,
            students[i].dayofbirth.month,
            students[i].dayofbirth.year,
            students[i].phone,
            students[i].industry,
            (students[i].gender == 0) ? "Male" : "Female");
    }
    printf("========================================================================================================================================\n");
}
// tim kiem sinh vien theo ten co chuc nang tim kiem gan dung
void searchStudent(Student students[], int count) {
    char keyword[50];
    printf("Enter the name from the first letter of the name: ");
	scanf("%s", keyword);
    printf("LIST OF STUDENTS HAVE NAME '%s'\n", keyword);
    printf("========================================================================================================================================\n");
    printf("| %-5s | %-20s | %-28s | %-16s | %-15s | %-20s | %-10s |\n", "ID", "Name", "Email", "Date of Birth", "Phone", "Industry", "Gender");
    printf("----------------------------------------------------------------------------------------------------------------------------------------\n");
    int found = 0,i;
    for ( i = 0; i < count; i++) {
        if(strstr(students[i].name, keyword) != NULL) {
            printf("| %-5d | %-20s | %-28s | %02d/%02d/%04d       | %-15s | %-20s | %-10s |\n",
            students[i].id,
            students[i].name,
            students[i].email,
            students[i].dayofbirth.day,
            students[i].dayofbirth.month,
            students[i].dayofbirth.year,
            students[i].phone,
            students[i].industry,
            (students[i].gender == 0) ? "Male" : "Female");
            found = 1;
    		printf("========================================================================================================================================\n");
        }
    }
    if (!found) {
        printf("No students found with the given name keyword.\n");
    }
}
//chinh sua thong tin sinh vien theo id
void editStudent(Student students[], int count) {
	int isDuplicate;
    int id;
    printf("Enter ID to edit: ");
    scanf("%d", &id);
    fflush(stdin); // Clear the input buffer
    // Search for the student by ID
    int i;
    for ( i = 0; i < count; i++) {
        if (students[i].id == id) {
        	printf("========================================================================================================================================\n");
    		printf("| %-5s | %-20s | %-28s | %-16s | %-15s | %-20s | %-10s |\n", "ID", "Name", "Email", "Date of Birth", "Phone", "Industry", "Gender");
    		printf("----------------------------------------------------------------------------------------------------------------------------------------\n");
        	printf("| %-5d | %-20s | %-28s | %02d/%02d/%04d       | %-15s | %-20s | %-10s |\n",
            students[i].id,
            students[i].name,
            students[i].email,
            students[i].dayofbirth.day,
            students[i].dayofbirth.month,
            students[i].dayofbirth.year,
            students[i].phone,
            students[i].industry,
            (students[i].gender == 0) ? "Male" : "Female");
        	printf("========================================================================================================================================\n");
            // Input new student name
            do{
           	isDuplicate=0;
            printf("Enter Student Name: ");
            fgets(students[i].name, sizeof(students[i].name), stdin);
            students[i].name[strcspn(students[i].name, "\n")] = '\0';// Remove the trailing newline
            if (strlen(students[i].name) == 0) {
            printf("Error.\n");
            isDuplicate = 1;
        	}
			} while (isDuplicate);
            // Input new student email
            do {
        	isDuplicate = 0;
        	printf("Enter Student Email: ");
        	scanf("%s", students[i].email);
        	int c;
        	while ((c = getchar()) != '\n' && c != EOF);
        	if (strlen(students[i].email) < 0) {
            printf("Error.\n");
            isDuplicate = 1;
        	}
        	if (strstr(students[i].email, "@gmail.com.") == NULL) {
            printf("Error.\n");
            isDuplicate = 1;
       		}
    		} while (isDuplicate);
            // Input dateofbirth
            do {
        	isDuplicate = 0;
       		printf("Enter Student Date of Birth (dd mm yyyy): ");
        	int result = scanf("%d %d %d", &students[i].dayofbirth.day, &students[i].dayofbirth.month, &students[i].dayofbirth.year);
        	int c;
        	while ((c = getchar()) != '\n' && c != EOF);
        	if (result != 3) {
            printf("Error. Date of Birth should be in format dd mm yyyy.\n");
            isDuplicate = 1;
            while (getchar() != '\n');
        	}
        	if (students[i].dayofbirth.day>31||students[i].dayofbirth.day<1){
        	printf("Error.\n");
            isDuplicate = 1;
			} else if(students[i].dayofbirth.day>12||students[i].dayofbirth.day<1){
			printf("Error.\n");
            isDuplicate = 1;
			} else if(students[i].dayofbirth.day<1||students[i].dayofbirth.day>9999){
			printf("Error.\n");
            isDuplicate = 1;
			}
    		} while (isDuplicate);
            // Input new student phone
            do {
        	isDuplicate = 0;
        	printf("Enter Phone Number: ");
        	scanf(" %s", students[i].phone);
        	int c;
        	while ((c = getchar()) != '\n' && c != EOF);
        	if (strlen(students[i].phone) < 10||strlen(students[i].phone)>10) {
            printf("Error.\n");
            isDuplicate = 1;
        	}
    		} while (isDuplicate);
            // Input new student industry
            do {
        	isDuplicate = 0;
        	printf("Enter Industry: ");
        	scanf("%s", students[i].industry);
        	int c;
        	while ((c = getchar()) != '\n' && c != EOF);
        	if (strlen(students[i].industry) < 1) {
            printf("Error.\n");
            isDuplicate = 1;
        	}
    		} while (isDuplicate);
            // Input new Student Gender
            int tempgenderStudentEd;
    		do {
        	printf("Enter Student Gender (0: Male, 1: Female): ");
        	scanf("%d", &tempgenderStudentEd);
    		} while (tempgenderStudentEd != 0 && tempgenderStudentEd != 1);
    		students[i].gender = tempgenderStudentEd;
            // Save the updated student list
            saveStudents(students, count);
            printf("Student information updated!\n");
            return;
        }
}
    // If the student is not found
    printf("Student not found!\n");
}
//xoa sinh vien khoi danh sach theo id
void deleteStudent(Student students[], int *count) {
    int id;
    printf("Enter ID to delete: ");
    scanf("%d", &id);
    int i,j;
    for ( i = 0; i < *count; i++) {
        if (students[i].id == id) {
            for ( j = i; j < *count - 1; j++) {
                students[j] = students[j + 1];
            }
            (*count)--;
            saveStudents(students, *count);
            printf("Student deleted successfully!\n");
            return;
        }
    }
    printf("Student not found!\n");
}
//sap xep sinh vien theo ten tu a-z bang sap xep bb sort
void sortStudentsAtoZ(Student students[], int count) {
	int i,j;
    for ( i = 0; i < count - 1; i++) {
        for ( j = i + 1; j < count; j++) {
            if (students[i].id > students[j].id) {
                Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
    saveStudents(students, count);
    printf("Students sorted successfully!\n");
}
//sap xep sinh vien theo ten tu z->a bang sap xep bb sort
void sortStudentsZtoA(Student students[], int count) {
	int i,j;
    for ( i = 0; i < count - 1; i++) {
        for ( j = i + 1; j < count; j++) {
            if (students[i].id < students[j].id) {
                Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
    saveStudents(students, count);
    printf("Students sorted successfully!\n");
}
//lam moi danh sach sinh vien
void resetStudents(Student students[], int *count) {
    *count = 0;
    saveStudents(students, *count);
    printf("Student list has been reset!\n");
}

//QUAN LY GIAO VIEN

void teacherMenu() {
    printf("\n--- Teacher Management ---\n");
    printf("1. Add Teacher\n");
    printf("2. Display Teachers\n");
    printf("3. Search Teacher\n");
    printf("4. Edit Teacher\n");
    printf("5. Delete Teacher\n");
    printf("6. Reset Teachers\n");
    printf("0. Back to Main Menu\n");
    printf("Enter your choice: ");
}
//luu danh sach hoc sinh vao file student.txt 
void saveTeachers(Teacher teachers[], int count) {
    FILE *file = fopen("teacher.txt", "wb"); 
    if (file) {
        fwrite(&count, sizeof(int), 1, file);
        fwrite(teachers, sizeof(Teacher), count, file);
        fclose(file);
    }
}
//doc danh sach hoc sinh trong file student.txt
void loadTeachers(Teacher teachers[], int *count) {
    FILE *file = fopen("teacher.txt", "rb");
    if (file) {
        fread(count, sizeof(int), 1, file);
        fread(teachers, sizeof(Teacher), *count, file);
        fclose(file);
    }
}
//nhap thong tin giao vien
void inputTeacher(Teacher teachers[], int *count) {
    if (*count >= 100) {
        printf("Teacher list is full!\n");
        return;
    }
    Teacher newTeacher;
    int isDuplicate;
//Id Teacher
    do {
        isDuplicate = 0;
        printf("Enter Teacher ID: ");
        scanf("%d", &newTeacher.id);
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        int i;
        for ( i = 0; i < *count; i++) {
            if (teachers[i].id == newTeacher.id) {
                printf("ID already exists. Please enter a different ID.\n");
                isDuplicate = 1;
                break;
            }
        }
        char str[20];
        sprintf(str, "%d", newTeacher.id);
        if (strlen(str) == 0 || newTeacher.id <= 0) {
            printf("Error.\n");
            isDuplicate = 1;
        }
    } while (isDuplicate);
//Name Teacher
    do {
        isDuplicate = 0;
        printf("Enter Teacher Name: ");
        fgets(newTeacher.name, sizeof(newTeacher.name), stdin);
        newTeacher.name[strcspn(newTeacher.name, "\n")] = '\0';
        if (strlen(newTeacher.name) == 0) {
            printf("Error.\n");
            isDuplicate = 1;
        }
    } while(isDuplicate);
//Gmail Teacher
    do {
        isDuplicate = 0;
        printf("Enter Teacher Email: ");
        scanf("%s", newTeacher.email);
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        int i;
        for ( i = 0; i < *count; i++) {
            if (strcmp(teachers[i].email, newTeacher.email) == 0) {
                printf("Email already exists. Please enter a different email.\n");
                isDuplicate = 1;
                break;
            }
        }
        if (strlen(newTeacher.email) == 0) {
            printf("Error.\n");
            isDuplicate = 1;
        }
        if (strstr(newTeacher.email, "@gmail.com.") == NULL) {
            printf("Error.\n");
            isDuplicate = 1;
        }
    } while (isDuplicate);
//DateOfBirth Teacher
    do {
        isDuplicate = 0;
        printf("Enter Student Date of Birth (dd mm yyyy): ");
        int result = scanf("%d %d %d", &newTeacher.dayofbirth.day, &newTeacher.dayofbirth.month, &newTeacher.dayofbirth.year);
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        if (result != 3) {
            printf("Error. Date of Birth should be in format dd mm yyyy.\n");
            isDuplicate = 1;
            while (getchar() != '\n');
        }
        if (newTeacher.dayofbirth.day>31||newTeacher.dayofbirth.day<1){
        	printf("Error.\n");
            isDuplicate = 1;
			} else if(newTeacher.dayofbirth.day>12||newTeacher.dayofbirth.day<1){
			printf("Error.\n");
            isDuplicate = 1;
			} else if(newTeacher.dayofbirth.day<1||newTeacher.dayofbirth.day>9999){
			printf("Error.\n");
            isDuplicate = 1;
			}
    } while (isDuplicate);
//Phone Teacher
    do {
        isDuplicate = 0;
        printf("Enter Phone Number: ");
        scanf(" %s", newTeacher.phone);
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        int i;
        for ( i = 0; i < *count; i++) {
            if (strcmp(teachers[i].phone, newTeacher.phone) == 0) {
                printf("Phone number already exists. Please enter a different phone number.\n");
                isDuplicate = 1;
                break;
            }
            if (strlen(newTeacher.phone) < 10||strlen(newTeacher.phone)>10) {
            printf("Error.\n");
            isDuplicate = 1;
        	}
        }
        if (strlen(newTeacher.phone) < 1) {
            printf("Error.\n");
            isDuplicate = 1;
        }
    } while (isDuplicate);
//Industry Teacher
    do {
        isDuplicate = 0;
        printf("Enter Industry: ");
        scanf("%s", newTeacher.industry);
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        if (strlen(newTeacher.industry) < 1) {
            printf("Error.\n");
            isDuplicate = 1;
        }
    } while (isDuplicate);
//Gender Teacher
    int tempgenderteacher;
    do {
        printf("Enter Teacher Gender (0: Male, 1: Female): ");
        scanf("%d", &tempgenderteacher);
    } while (tempgenderteacher != 0 && tempgenderteacher != 1);
    newTeacher.gender = tempgenderteacher;
    
    teachers[(*count)++] = newTeacher;
    saveTeachers(teachers, *count);
    printf("Teacher added successfully!\n");
}
// hien thi bang liet ke danh sach giao vien
void displayTeachers(Teacher teachers[], int count) {
    if (count == 0) {
        printf("No teachers found!\n");
        return;
    }
    printf("========================================================================================================================================\n");
    printf("| %-5s | %-20s | %-28s | %-16s | %-15s | %-20s | %-10s |\n", "ID", "Name", "Email", "Date of Birth", "Phone", "Industry", "Gender");
    int i;
    for ( i = 0; i < count; i++) {
        printf("----------------------------------------------------------------------------------------------------------------------------------------\n");
        printf("| %-5d | %-20s | %-28s | %02d/%02d/%04d       | %-15s | %-20s | %-10s |\n",
            teachers[i].id,
            teachers[i].name,
            teachers[i].email,
            teachers[i].dayofbirth.day,
            teachers[i].dayofbirth.month,
            teachers[i].dayofbirth.year,
            teachers[i].phone,
            teachers[i].industry,
            (teachers[i].gender == 0) ? "Male" : "Female");
    }
    printf("========================================================================================================================================\n");
}
//tim kiem giao vien theo ten gan dung
void searchTeacher(Teacher teachers[], int count) {
    char keyword[50];
    printf("Enter the name from the first letter of the name: ");
	scanf("%s", keyword);
    printf("LIST OF TEACHER HAVE NAME '%s'\n", keyword);
    printf("========================================================================================================================================\n");
    printf("| %-5s | %-20s | %-28s | %-16s | %-15s | %-20s | %-10s |\n", "ID", "Name", "Email", "Date of Birth", "Phone", "Industry", "Gender");
    printf("----------------------------------------------------------------------------------------------------------------------------------------\n");
    int found = 0,i;
    for ( i = 0; i < count; i++) {
        if(strstr(teachers[i].name, keyword) != NULL) {
            printf("| %-5d | %-20s | %-28s | %02d/%02d/%04d       | %-15s | %-20s | %-10s |\n",
            teachers[i].id,
            teachers[i].name,
            teachers[i].email,
            teachers[i].dayofbirth.day,
            teachers[i].dayofbirth.month,
            teachers[i].dayofbirth.year,
            teachers[i].phone,
            teachers[i].industry,
            (teachers[i].gender == 0) ? "Male" : "Female");
            found = 1;
    		printf("========================================================================================================================================\n");
        }
    }
    if (!found) {
        printf("No teachers found with the given name keyword.\n");
    }
}
//chinh sua thong tin giao vien theo id
void editTeacher(Teacher teachers[], int count) {
    int id,isDuplicate;
    printf("Enter ID to edit: ");
    scanf("%d", &id);
    fflush(stdin);
    int i;
    for ( i = 0; i < count; i++) {
        if (teachers[i].id == id) {
        	printf("========================================================================================================================================\n");
    		printf("| %-5s | %-20s | %-28s | %-16s | %-15s | %-20s | %-10s |\n", "ID", "Name", "Email", "Date of Birth", "Phone", "Industry", "Gender");
    		printf("----------------------------------------------------------------------------------------------------------------------------------------\n");
        	printf("| %-5d | %-20s | %-28s | %02d/%02d/%04d       | %-15s | %-20s | %-10s |\n",
            teachers[i].id,
            teachers[i].name,
            teachers[i].email,
            teachers[i].dayofbirth.day,
            teachers[i].dayofbirth.month,
            teachers[i].dayofbirth.year,
            teachers[i].phone,
            teachers[i].industry,
            (teachers[i].gender == 0) ? "Male" : "Female");
            printf("========================================================================================================================================\n");
//Id Teacher
			do {
           	isDuplicate=0;
            printf("Enter Student New Name: ");
            fgets(teachers[i].name, sizeof(teachers[i].name), stdin);
            teachers[i].name[strcspn(teachers[i].name, "\n")] = '\0';// Remove the trailing newline
            if (strlen(teachers[i].name) == 0) {
            printf("Error.\n");
            isDuplicate = 1;
        	}
			} while (isDuplicate);
//Name Teacher
			do {
        	isDuplicate = 0;
        	printf("Enter Teacher New Email: ");
        	scanf("%s", teachers[i].email);
        	int c;
        	while ((c = getchar()) != '\n' && c != EOF);
        	if (strlen(teachers[i].email) < 0) {
            printf("Error.\n");
            isDuplicate = 1;
        	}
        	if (strstr(teachers[i].email, "@gmail.com.") == NULL) {
            printf("Error.\n");
            isDuplicate = 1;
       		}
    		} while (isDuplicate);
//DateOfBirth Teacher
			do {
        	isDuplicate = 0;
       		printf("Enter Teacher New Date of Birth (dd mm yyyy): ");
        	int result = scanf("%d %d %d", &teachers[i].dayofbirth.day, &teachers[i].dayofbirth.month, &teachers[i].dayofbirth.year);
        	int c;
        	while ((c = getchar()) != '\n' && c != EOF);
        	if (result != 3) {
            printf("Error. Date of Birth should be in format dd mm yyyy.\n");
            isDuplicate = 1;
            while (getchar() != '\n');
        	}
        	if (teachers[i].dayofbirth.day>31||teachers[i].dayofbirth.day<1){
        	printf("Error.\n");
            isDuplicate = 1;
			} else if(teachers[i].dayofbirth.day>12||teachers[i].dayofbirth.day<1){
			printf("Error.\n");
            isDuplicate = 1;
			} else if(teachers[i].dayofbirth.day<1||teachers[i].dayofbirth.day>9999){
			printf("Error.\n");
            isDuplicate = 1;
			}
    		} while (isDuplicate);
//Phone Teacher
			do {
        	isDuplicate = 0;
        	printf("Enter Phone New Number: ");
        	scanf(" %s", teachers[i].phone);
        	int c;
        	while ((c = getchar()) != '\n' && c != EOF);
        	if (strlen(teachers[i].phone) < 10||strlen(teachers[i].phone)>10) {
            printf("Error.\n");
            isDuplicate = 1;
        	}
    		} while (isDuplicate);
//Industry Teacher
			do {
        	isDuplicate = 0;
        	printf("Enter New Industry: ");
        	scanf("%s", teachers[i].industry);
        	int c;
        	while ((c = getchar()) != '\n' && c != EOF);
        	if (strlen(teachers[i].industry) < 1) {
            printf("Error.\n");
            isDuplicate = 1;
        	}
    		} while (isDuplicate);
//Gender Teacher	
			int tempgenderTeacherEd;
			do {
        	printf("Enter Teacher New Gender (0: Male, 1: Female): ");
        	scanf("%d", &tempgenderTeacherEd);
    		} while (tempgenderTeacherEd != 0 && tempgenderTeacherEd != 1);
    		teachers[i].gender = tempgenderTeacherEd;
			saveTeachers(teachers, count);
            printf("Teacher information updated!\n");
            return;
        }
    }
    printf("Teacher not found!\n");
}
//xoa giao vien khoi danh sach theo id
void deleteTeacher(Teacher teachers[], int *count) {
    int id,i,j;
    printf("Enter ID to delete: ");
    scanf("%d", &id);
    for ( i = 0; i < *count; i++) {
        if (teachers[i].id == id) {
            for ( j = i; j < *count - 1; j++) {
                teachers[j] = teachers[j + 1];
            }
            (*count)--;
            saveTeachers(teachers, *count);
            printf("Teacher deleted successfully!\n");
            return;
        }
    }
    printf("Teacher not found!\n");
}
//lam moi danh sach giao vien 
void resetTeachers(Teacher teachers[], int *count) {
    *count = 0;
    saveTeachers(teachers, *count);
    printf("Teacher list has been reset!\n");
}

