/************
* Ido Aharon
* 01
* ex5
*************/

#define MAX_CLASSES 5
#define MAX_LINE 200
#define COURSE_NUM 6
#define MAX_COURSE_NAME 31
#define MAX_STUDENT_NAME 21
#define SPACE ' '
#define NOT_FOUND -1
#define FOUND 1
#define INVALIDCHECK -1
#define VALIDCHECK 1
#define GRADELENGTH 4

/******************************************************************************
* The struct is build from 4 variables: the course num, the name of the course,
* the students count and a pointer to a list of all students in class.
*******************************************************************************/
typedef struct
{
	char courseNumber[COURSE_NUM];
	char name[MAX_COURSE_NAME];
	int studentsNum;
	struct Student** allStudents;
} Classes;


//Struct for student: every student has a name and a grade
typedef struct
{
	char name[MAX_STUDENT_NAME];
	int grade;
}Student;

void insertUpdateClass(Classes academy[MAX_CLASSES], int* numClasses);
void insertUpdateStudent(Classes academy[MAX_CLASSES], int numClasses);
void printMenu();
void printStudents(Classes allClasses[MAX_CLASSES], int numOfClasses);
void deleteStudent(Classes allClasses[MAX_CLASSES], int numClasses);
void freeAll(Classes allClasses[MAX_CLASSES], int numClasses);
void printComputedScores(Classes allClasses[MAX_CLASSES], int numClasses);
void resetClasses(Classes allClasses[MAX_CLASSES]);
