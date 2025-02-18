
typedef struct{
	int day;
	int month;
	int year;
} date;

typedef struct {
    int id;
    char name[50];
    char email[50];
    int phone[15];
    date dayofbirth;
    char industry[50];
    int gender;
} Student;

typedef struct {
    int id;
    char name[50];
    char email[50];
    int phone[15];
    date dayofbirth;
    char industry[50];
    int gender;
} Teacher;
