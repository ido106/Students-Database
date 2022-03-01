/************
* Ido Aharon
* 01
* ex5
*************/
#include "ex5.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

int validStr(char line[MAX_LINE], Classes allClasses[MAX_CLASSES], int numClasses);
int isCourseExist(char number[COURSE_NUM], Classes allClasses[MAX_CLASSES], int numClasses);
int findClasses(Classes academy[MAX_CLASSES], char courseNumber[COURSE_NUM], int numClasses);
int findStudent(Student** students, int studentsNum, char name[MAX_STUDENT_NAME]);
int alreadySigned(Student** allStudents, int studentsNum, char name[MAX_STUDENT_NAME]);
int firstDeleteCheck(char line[MAX_LINE], Classes allClasses[MAX_CLASSES], int numClasses);
int validForPrint(char line[MAX_LINE], int numClasses, Classes allClasses[MAX_CLASSES]);
Student** swap(Student** allStudents, int j);
int secondDeleteCheck(char line[MAX_LINE], Classes allclasses[MAX_CLASSES], int numClasses);
int thirdDeleteCheck(char line[MAX_LINE], Classes allclasses[MAX_CLASSES], int numClasses);
void printScoresMenu();
void printSumOrAverageGrade(Classes allClasses[MAX_CLASSES], int numClasses, int choice);
int returnMax(int a, int b);
void printMinMaxGrade(Classes allClasses[MAX_CLASSES], int numClasses, int choose);
int returnMin(int a, int b);
void printNumStudents(Classes allClasses[MAX_CLASSES], int numClasses);
void skipSpacesFromStart(char line[MAX_LINE], int* i);
void getName(int* i, int* j, char name[MAX_STUDENT_NAME], char line[MAX_LINE]);
void addStudent(int grade, int numClasses, int cIndex, Classes academy[MAX_CLASSES], char name[MAX_STUDENT_NAME]);
void updateStudentDetails(int cIndex, int grade, Classes academy[MAX_CLASSES], char name[MAX_STUDENT_NAME]);

/****************************************************
* Function Name: printMenu
* Input: none
* Output: none
* Function operation: function thats prints the menu
*****************************************************/
void printMenu() {
	printf("Please select an operation:\n\t0. Exit.\n\
\t1. Insert or update a class.\n\
\t2. Insert or update a student.\n\
\t3. Remove a student from classes.\n\
\t4. Print a class.\n\
\t5. Print all classes with their computed scores.\n\
\t6. Print the menu.\n");
}

/**************************************************************************************
* Function Name: findClasses
* Input: Classes academy[MAX_CLASSES], char courseNumber[COURSE_NUM], int numClasses
* Output: int
* Function operation: the function returns the class index or if not found returns -1
**************************************************************************************/
int findClasses(Classes academy[MAX_CLASSES], char courseNumber[COURSE_NUM], int numClasses) {
	int i;
	//check all classes
	for (i = 0; i < numClasses; i++) {
		if (strcmp(courseNumber, academy[i].courseNumber) == 0) {
			return i;
		}
	}
	return NOT_FOUND;
}

/*************************************************************************************************************
* Function Name: insertUpdateClass
* Input: Classes academy[MAX_CLASSES], int* numClasses
* Output: void
* Function operation: the function gets a request to update or add a class.
*					  the function checks the validity of the input string. if the string in not valid,
*					  the function doesn't do anything and prints an error message. if the request is valid,
*					  the function checks if the course is already exist. if it does, we only update the name
*					  of the course. otherwise, we add the course to the academy.
*************************************************************************************************************/
void insertUpdateClass(Classes academy[MAX_CLASSES], int* numClasses) {
	char courseNumber[COURSE_NUM], line[MAX_LINE], name[MAX_LINE];
	int i = 0, j = 0, index;
	// read the course details
	fgets(line, MAX_LINE, stdin);
	//remove newline
	line[strlen(line) - 1] = '\0';
	// skip spaces from the begining
	skipSpacesFromStart(line, &i);
	//check if all digits are numbers
	for (j = 0; j < COURSE_NUM - 1; j++) {
		if (!isdigit(line[i])) {
			printf("Error: invalid class number or name.\n");
			return;
		}
		courseNumber[j] = line[i++];
	}
	courseNumber[COURSE_NUM - 1] = '\0';
	//check if the number is longer than 5 digits
	if (line[i] != SPACE) {
		printf("Error: invalid class number or name.\n");
		return;
	}
	// skip spaces after the number
	while ((line[i] != '\0') && (line[i] == SPACE))
		i++;
	j = 0;
	//get the name
	while (line[i] != '\0') {
		//check if the name is invalid
		if (isalpha(line[i]) == 0 && isdigit(line[i]) == 0 && line[i] != SPACE) {
			printf("Error: invalid class number or name.\n");
			return;
		}
		name[j++] = line[i++];
	}
	name[j] = '\0';
	//check validity of name
	if (strlen(name) < 1 || strlen(name) > MAX_COURSE_NAME - 1) {
		printf("Error: invalid class number or name.\n");
		return;
	}
	//search for class
	index = findClasses(academy, courseNumber, *numClasses);
	//if found, only update the class.
	if (index != NOT_FOUND) {
		strcpy(academy[index].name, name);
		printf("Class \"%s %s\" updated.\n", academy[index].courseNumber, academy[index].name);
		return;
	}
	//if the academy is full, don't add the class.
	if (MAX_CLASSES == *numClasses) {
		printf("Unfortunately, there is no room for more classes.\n");
		return;
	}
	//if all checks are ok, add the class and print a message.
	strcpy(academy[*numClasses].name, name);
	strcpy(academy[*numClasses].courseNumber, courseNumber);
	printf("Class \"%s %s\" added.\n", courseNumber, name);
	//enlarge the count of classes by 1.
	(*numClasses)++;
}

/***********************************************************************************
* Function Name: findStudent
* Input: Student** students, int studentsNum, char name[MAX_STUDENT_NAME]
* Output: int
* Function operation: the function returns the student index if found. if not, the
*					  function returns -1(NOT_FOUND).
***********************************************************************************/
int findStudent(Student** students, int studentsNum, char name[MAX_STUDENT_NAME]) {
	int i;
	for (i = 0; i < studentsNum; i++) {
		if (strcmp(name, students[i]->name) == 0) {
			return i;
		}
	}
	return NOT_FOUND;
}

/**********************************************************************************************************
* Function Name: insertUpdateStudent
* Input: Classes academy[MAX_CLASSES], int numClasses, Student** students
* Output: void
* Function operation: the function gets a request for insert or update a class. first, the function checks
*					  if the request is valid. meaning, if all classes are found and there is no problem
*					  with the name of the student, the name of the class or the grade.
*					  if there is a problem, the function prints an error message and doesn't do anything.
*					  if there is no problem, the function checks if the student is already signed
*					  to the course. if he does, the function only updates his grade.
*				      otherwise, the function add the new student to the class.
***********************************************************************************************************/
void insertUpdateStudent(Classes academy[MAX_CLASSES], int numClasses)
{
	char courseNumber[COURSE_NUM], name[MAX_STUDENT_NAME], line[MAX_LINE], * course = NULL, gradeStr[GRADELENGTH];
	// i is for line index, j is for name index,k is for courseNumber
	int grade, i = 0, j = 0, k = 0, classIndex;
	// read the course details
	fgets(line, MAX_LINE, stdin);
	// remove the new line from the end of the line
	line[strlen(line) - 1] = '\0';
	//check if the line is valid
	if (validStr(line, academy, numClasses) != 1)
	{
		printf("Error: invalid name, class number or grade.\n");
		return;
	}
	// skip spaces from the beginning
	skipSpacesFromStart(line, &i);
	// get the name of the student
	getName(&i, &j, name, line);
	//skip spaces
	skipSpacesFromStart(line, &i);
	// read the courses
	course = strtok(&line[i], ";");
	while (course != NULL) {
		//reset grade
		for (int g = 0; g <= 3; g++)
			gradeStr[g] = '\0';
		//skip the spaces, j is for substring index
		j = 0;
		skipSpacesFromStart(course, &j);
		// get the course number
		for (k = 0; k < COURSE_NUM - 1; k++) {
			courseNumber[k] = course[j++];
		}
		courseNumber[k] = '\0';
		//skip spaces and comma
		while ((course[j] != '\0') && ((course[j] == ',') || (course[j] == SPACE)))
			j++;
		k = 0;
		// get the grade
		while ((course[j] >= '0') && (course[j] <= '9')) {
			gradeStr[k++] = course[j++];
		}
		gradeStr[k] = '\0';
		//get the grade as int
		grade = atoi(gradeStr);
		//get the class index
		classIndex = findClasses(academy, courseNumber, numClasses);
		//if the student is found, only update his grade
		if (alreadySigned(academy[classIndex].allStudents, academy[classIndex].studentsNum, name) != NOT_FOUND)
			updateStudentDetails(classIndex, grade, academy, name);
		//if the student is not found, allocate a new memory from the heap and add him.
		else
			addStudent(grade, numClasses, classIndex, academy, name);
		course = strtok(NULL, ";");
	}
}

/***********************************************************************************************************
* Function Name: addStudent
* Input: int grade,int numClasses,int cIndex, Classes academy[MAX_CLASSES],char name[MAX_STUDENT_NAME]
* Output: void
* Function operation: the function create a new student and add him into students array in the original
*					  struct. first the function mallocs size as the struct size, then reallocs the students
*					  array, add the malloced student into array and print a message. if the malloc or
*					  realloc fails, the function realeases all allocated memory and exit program.
*************************************************************************************************************/
void addStudent(int grade, int numClasses, int cIndex, Classes academy[MAX_CLASSES], char name[MAX_STUDENT_NAME]) {
	Student* newStudent = NULL;
	//if the malloc fails, release all allocated memory and exit
	newStudent = (Student*)malloc(sizeof(Student));
	if (newStudent == NULL) {
		freeAll(academy, numClasses);
		exit(1);
	}
	//insert grade
	newStudent->grade = grade;
	//insert name
	strcpy(newStudent->name, name);
	//enlarge students num by 1
	academy[cIndex].studentsNum++;
	//realloc place to the new students in students array
	academy[cIndex].allStudents = (Student**)realloc(academy[cIndex].allStudents,
									academy[cIndex].studentsNum * sizeof(Student*));
	//if realloc fails, release all allocated memory and exit
	if (academy[cIndex].allStudents == NULL) {
		freeAll(academy, numClasses);
		exit(1);
	}
	//set the pointer to the students array(add the student)
	academy[cIndex].allStudents[academy[cIndex].studentsNum - 1] = newStudent;
	//print a message
	printf("Student \"%s\" added to class \"%s %s\" with grade %d.\n", name, \
		academy[cIndex].courseNumber, academy[cIndex].name, grade);
}

/***********************************************************************************************************
* Function Name: updateStudentDetails
* Input: int cIndex,int grade,Classes academy[MAX_CLASSES], char name[MAX_STUDENT_NAME]
* Output: void
* Function operation: the function update the students details. first the function gets the student index
*					  within students array( with "already signed" function) and due to that index, changes
*					  his grade and print a message for it.
*************************************************************************************************************/
void updateStudentDetails(int cIndex, int grade, Classes academy[MAX_CLASSES], char name[MAX_STUDENT_NAME]) {
	Student** allStudents = academy[cIndex].allStudents;
	int found;
	//get the index of the student from students array
	found = alreadySigned(academy[cIndex].allStudents, academy[cIndex].studentsNum, name);
	//change the grade of the student
	allStudents[found]->grade = grade;
	//set the new array of students
	academy[cIndex].allStudents = allStudents;
	//print a message
	printf("Student \"%s\" updated on class \"%s %s\" with grade %d.\n", name, \
		academy[cIndex].courseNumber, academy[cIndex].name, grade);
}

/************************************************************************************************************
* Function Name: alreadySigned
* Input: Student** allStudents, int studentsNum, char name[MAX_STUDENT_NAME]
* Output: int
* Function operation: the function checks if the student is already signed to the course. if he does, the
*					  function returns his index in the student's array. if he doesn't, the function returns
*					  NOT_FOUND(-1)
*************************************************************************************************************/
int alreadySigned(Student** allStudents, int studentsNum, char name[MAX_STUDENT_NAME])
{
	//search for students in students array
	for (int i = 0; i < studentsNum; i++)
	{
		if (strcmp(allStudents[i]->name, name) == 0)
			return i;
	}
	return NOT_FOUND;
}


/***********************************************************************************
* Function Name: isCourseExist
* Input: char number[COURSE_NUM] , Classes allClasses[MAX_CLASSES],int numClasses
* Output: int(1 for found, -1 for not found)
* Function operation: the function checks if the course is found between the classes
*					  if it does, the function returns FOUND(1), else the function
*					  returns NOT_FOUND(-1)
************************************************************************************/
int isCourseExist(char number[COURSE_NUM], Classes allClasses[MAX_CLASSES], int numClasses) {
	for (int i = 0; i < numClasses; i++)
		if (strcmp(number, allClasses[i].courseNumber) == 0)
			return FOUND;
	return NOT_FOUND;
}

/*************************************************************************************************************
* Function Name: validStr
* Input: char line[MAX_LINE], Classes allClasses[MAX_CLASSES], int numClasses
* Output: int(1 for valid, -1 for not valid)
* Function operation: the function checks if the input string is valid due to user's rules.first the function
*					  checks if the name of the student is longer than possible or contain invalid chars.
*					  then, function checks if the course num and grade is valid, and if the course exist in
*					  the system. if one of the checks above failed. the function returns -1(INVALIDCHECK)
*					  else, the function returns 1 (VALIDCHECK)
**************************************************************************************************************/
int validStr(char line[MAX_LINE], Classes allClasses[MAX_CLASSES], int numClasses) {
	char* course1, tempLine[MAX_LINE], name[MAX_LINE], number[MAX_LINE], grade[MAX_LINE];
	//indexes for loops
	int i = 0, j = 0, k = 0, z = 0, q = 0, lastindex = strlen(line) - 1;
	while (line[lastindex] == SPACE)
		line[lastindex--] = '\0';
	//check if there is no ; at the end
	if (line[strlen(line) - 1] != ';')
		return INVALIDCHECK;
	strcpy(tempLine, line);
	// skip spaces from the begining
	skipSpacesFromStart(tempLine, &i);
	// get the name of the student
	getName(&i, &j, name, tempLine);
	//check if there is no two dots
	if (line[i - 1] != ':')
		return INVALIDCHECK;
	//check if the name contains too many letters
	if (strlen(name) < 1 || strlen(name) > MAX_STUDENT_NAME - 1)
		return INVALIDCHECK;
	//check if the name contains invalid chars
	for (k = 0; k < strlen(name); k++)
		if (isalpha(name[k]) == 0 && name[k] != SPACE)
			return INVALIDCHECK;
	course1 = strtok(&tempLine[i], ";");
	while (course1 != NULL) {
		//reset number
		for (int n = 0; n <= 4; n++)
			number[n] = '\0';
		//use this indexes for substring,grade and number
		z = 0;
		k = 0;
		q = 0;
		//ignore spaces from beginning
		skipSpacesFromStart(course1, &k);
		//get number
		while (course1[k] != ',' && course1[k] != '\0') {
			number[q++] = course1[k++];
		}
		number[q] = '\0';
		//check if number is longer than 5 digits and go on
		if (strlen(number) > 5 || strlen(number) < 1)
			return INVALIDCHECK;
		//if the course does not exist return INVALID(-1)
		if (isCourseExist(number, allClasses, numClasses) != FOUND)
			return INVALIDCHECK;
		//skip the ,
		k++;
		//ignore spaces
		while (course1[k] == SPACE)
			k++;
		while (course1[k] != '\0')
			grade[z++] = course1[k++];
		grade[z] = '\0';
		//check if there is no number
		if (strlen(grade) < 1)
			return INVALIDCHECK;
		//if the grade is 0 continue. else, check if the grade is valid.
		if (strcmp(grade, "0") != 0 && (atoi(grade) == 0 || strlen(grade) > 3 || atoi(grade) > 100 || atoi(grade) < 0))
			return INVALIDCHECK;
		course1 = strtok(NULL, ";");
	}
	return VALIDCHECK;
}

/******************************************************************************************************
* Function Name: deleteStudent
* Input: Classes allClasses[MAX_CLASSES],int numClasses
* Output: void
* Function operation: the function gets a request to delete a student from one or few courses. first,
*					  the function checks if the request is valid due to user's rules of string.
*					  the second check is whether or not the student is signed to the class or not.
*					  the third is to check if the request is to delete the user from all courses.
*					  if one of the above is true, the function prints an error message and exit.
*					  otherwise, the function removes the student from all asked classes.
********************************************************************************************************/
void deleteStudent(Classes allClasses[MAX_CLASSES], int numClasses) {
	Student** allStudents = NULL;
	char name[MAX_STUDENT_NAME], line[MAX_LINE], classNumber[COURSE_NUM];
	//index i is for line, j for student name
	int i = 0, j = 0, lastIndex, classIndex, studentIndex, n;
	fgets(line, MAX_LINE, stdin);
	//remove new line
	line[strlen(line) - 1] = '\0';
	lastIndex = strlen(line) - 1;
	//remove all spaces from end
	while (line[lastIndex] == SPACE)
		line[lastIndex--] = '\0';
	//delete last comma if exist
	if (line[lastIndex] == ',')
		line[lastIndex] = '\0';
	//continue only if all check are valid
	if (firstDeleteCheck(line, allClasses, numClasses) == INVALIDCHECK ||
		secondDeleteCheck(line, allClasses, numClasses) == INVALIDCHECK ||
		thirdDeleteCheck(line, allClasses, numClasses) == INVALIDCHECK)
		return;
	//skip spaces
	while (line[i] == SPACE)
		i++;
	//get name
	while (line[i] != ':')
		name[j++] = line[i++];
	name[j] = '\0';
	//skip the :
	i++;
	//continue till the end of the line
	while (line[i] != '\0')
	{
		//skip spaces
		while (line[i] == SPACE)
			i++;
		//get class number
		for (j = 0; j <= 4; j++)
			classNumber[j] = line[i++];
		classNumber[COURSE_NUM - 1] = '\0';
		classIndex = findClasses(allClasses, classNumber, numClasses);
		allStudents = allClasses[classIndex].allStudents;
		studentIndex = findStudent(allStudents, allClasses[classIndex].studentsNum, name);
		printf("Student \"%s\" removed from class \"%s %s\".\n", name, allClasses[classIndex].courseNumber, \
			allClasses[classIndex].name);
		//erase student
		for (n = studentIndex; n < allClasses[classIndex].studentsNum - 1; n++)
		{
			allStudents[n]->grade = allStudents[n + 1]->grade;
			strcpy(allStudents[n]->name, allStudents[n + 1]->name);
		}
		//free last student
		free(allStudents[n]);
		//copy new array
		allClasses[classIndex].allStudents = allStudents;
		//subtract one student from counting
		allClasses[classIndex].studentsNum--;
		//skip the ,
		i++;
	}
}

/******************************************************************************************************
* Function Name: firstDeleteCheck
* Input: char line[MAX_LINE]
* Output: int(1 for valid, -1 for not valid)
* Function operation: the function checks if the delete request is valid. if the name of the students
*					  contains invalid chars, too long, too short. the function returns NOT_VALID(-1)
*					  if all checks are passed, the function returns VALID(1)
*******************************************************************************************************/
int firstDeleteCheck(char line[MAX_LINE], Classes allClasses[MAX_CLASSES],int numClasses) {
	char tempLine[MAX_LINE], name[MAX_LINE], number[MAX_LINE];
	//i for line index, j for name and number index
	int i = 0, j = 0, z = 0;
	//reset array
	for (int i = 0; i < MAX_LINE; i++)
		number[i] = '\0';
	//check if the line still contains comma at end
	if (line[strlen(line) - 1] == ',')
	{
		printf("Error: invalid name or class number.\n");
		return INVALIDCHECK;
	}
	strcpy(tempLine, line);
	// skip spaces from the begining
	skipSpacesFromStart(tempLine, &i);
	// get the name of the student
	getName(&i, &j, name, line);
	//check if the line doesn't contain two dots
	if (line[i-1] != ':')
	{
		printf("Error: invalid name or class number.\n");
		return INVALIDCHECK;
	}
	//check if the name contains too many letters
	if (strlen(name) < 1 || strlen(name) > 20)
	{
		printf("Error: invalid name or class number.\n");
		return INVALIDCHECK;
	}
	//check if the name contains invalid chars
	for (int k = 0; k < strlen(name); k++)
		if (isalpha(name[k]) == 0 && isdigit(name[k]) == 0 && name[k] != SPACE)
		{
			printf("Error: invalid name or class number.\n");
			return INVALIDCHECK;
		}
	//check if there is no course num
	if(line[i]=='\0')
	{
		printf("Error: invalid name or class number.\n");
		return INVALIDCHECK;
	}
	while (line[i] != '\0') {
		//reset j index for number index and reset number
		j = 0;
		while (number[j] != '\0')
			number[j++] = '\0';
		j = 0;
		//skip spaces
		while ((tempLine[i] != '\0') && (tempLine[i] == SPACE))
			i++;
		//get and check the number
		for (int k = 0; k <= 4; k++) {
			//check if the number is valid
			if (isdigit(line[i]) == 0)
			{
				printf("Error: invalid name or class number.\n");
				return INVALIDCHECK;
			}
			else
				number[j++] = line[i++];
		}
		//check if the course exist
		if(findClasses(allClasses,number,numClasses)==NOT_FOUND)
		{
			printf("Error: invalid name or class number.\n");
			return INVALIDCHECK;
		}
		//the next letter must be a comma, only if we are not in the end of the string.
		if (line[i] != ',' && line[i + 1] != '\0')
		{
			printf("Error: invalid name or class number.\n");
			return INVALIDCHECK;
		}
		//go to next number
		i++;
	}
	return VALIDCHECK;
}

/******************************************************************************************************
* Function Name: secondDeleteCheck
* Input: char line[MAX_LINE],Classes allclasses[MAX_CLASSES],int numClasses
* Output: int(1 for valid, -1 for not valid)
* Function operation: the function checks if the student is signed to all included classes. if he does
*					  not, the function print an error message and returns -1. if the student is signed
*				      to all included classes, the function returns -1.
*******************************************************************************************************/
int secondDeleteCheck(char line[MAX_LINE], Classes allclasses[MAX_CLASSES], int numClasses) {
	// i is index for line, j for student name
	int i = 0, j = 0, classIndex;
	char classNumber[COURSE_NUM], studentName[MAX_STUDENT_NAME];
	//we already know that the string itself is valid, so skip all spaces till name
	while (line[i] == SPACE)
		i++;
	//get the name
	while (line[i] != ':')
	{
		studentName[j++] = line[i++];
	}
	studentName[j] = '\0';
	//skip the :
	i++;
	//check all possibilities till the end of the line
	while (line[i] != '\0')
	{
		//skip spaces
		while (line[i] == SPACE)
			i++;
		for (j = 0; j <= 4; j++)
			classNumber[j] = line[i++];
		classNumber[COURSE_NUM - 1] = '\0';
		classIndex = findClasses(allclasses, classNumber, numClasses);
		if (findStudent(allclasses[classIndex].allStudents, allclasses[classIndex].studentsNum, studentName) == NOT_FOUND)
		{
			printf("Error: student is not a member of class \"%s %s\".\n", allclasses[classIndex].courseNumber\
				, allclasses[classIndex].name);
			return INVALIDCHECK;
		}
		//skip the comma and continue
		i++;
	}
	return VALIDCHECK;
}

/******************************************************************************************************
* Function Name: thirdDeleteCheck
* Input: char line[MAX_LINE], Classes allclasses[MAX_CLASSES], int numClasses
* Output: int(1 for valid, -1 for not valid)
* Function operation: the function checks if the user is trying to delete the student from all the
*					  classes he is signed to. if this is the situation, the function prints an error
*					  message and returns -1. if the user is asking to delete the student
*					  from a partial amount of courses, the checking succeed and the function returns 1.
********************************************************************************************************/
int thirdDeleteCheck(char line[MAX_LINE], Classes allclasses[MAX_CLASSES], int numClasses) {
	Student* currentStudent = NULL;
	char stuName[MAX_STUDENT_NAME];
	// i is index for line, j for student name
	int signedSum = 0, askedSum = 1, i = 0, j = 0;
	//skip spaces
	while (line[i] == SPACE)
		i++;
	//get name
	while (line[i] != ':')
		stuName[j++] = line[i++];
	stuName[j] = '\0';
	//skip the :
	i++;
	//at this place i know we removed the comma at the end of the line
	while (line[i] != '\0')
	{
		if (line[i] == ',')
			askedSum++;
		i++;
	}
	//continue checking how many courses the student is really signed to
	for (int n = 0; n < numClasses; n++)
	{
		for (int z = 0; z < allclasses[n].studentsNum; z++)
		{
			currentStudent = allclasses->allStudents[z];
			if (strcmp(currentStudent->name, stuName) == 0)
			{
				signedSum++;
			}
		}
	}
	//if the number of asked courses is equal to the sum the student already signed, print error
	if (askedSum >= signedSum)
	{
		printf("Error: student cannot be removed from all classes.\n");
		return INVALIDCHECK;
	}
	//if all check are good return 1
	return VALIDCHECK;
}

/******************************************************************************************************
* Function Name: printStudents
* Input: Classes allClasses[MAX_CLASSES],int numOfClasses
* Output: none
* Function operation: the function gets a request to print a list of students. first, it checks if the
*					  request is valid. the request has to contain only 1 course number that exists in
*					  the system. if the number is invalid or doesn't exist, or there is no students in
*					  class, the function prints a message and doesn't do anything. else, the function
*					  do bubble sort to all students in class with their names and prints them by order
*******************************************************************************************************/
void printStudents(Classes allClasses[MAX_CLASSES], int numOfClasses) {
	char line[MAX_LINE], classNumber[COURSE_NUM];
	//get all students
	Student** allStudents = NULL;
	// i index for line, j-n index for bubble sort, j also for number.
	int i = 0, j = 0, n, classIndex;
	fgets(line, MAX_LINE, stdin);
	//remove the newline
	line[strlen(line) - 1] = '\0';
	//check if the line is valid
	if (validForPrint(line, numOfClasses, allClasses) != VALIDCHECK)
		return;
	// skip spaces
	while (line[i] == SPACE && line[i] != '\0')
		i++;
	//get number
	for (j = 0; j < COURSE_NUM - 1; j++)
		classNumber[j] = line[i++];
	classNumber[j] = '\0';
	//find the requested class
	classIndex = findClasses(allClasses, classNumber, numOfClasses);
	allStudents = allClasses[classIndex].allStudents;
	//bubble sort with students name
	n = allClasses[classIndex].studentsNum;
	for (i = 0; i < n - 1; i++)
		// Last i elements are already in place    
		for (j = 0; j < n - i - 1; j++)
			if (strcmp(allStudents[j]->name, allStudents[j + 1]->name) > 0)
				allStudents = swap(allStudents, j);
	//print all students
	printf("Class \"%s %s\" students:\n", allClasses[classIndex].courseNumber, allClasses[classIndex].name);
	for (i = 0; i < allClasses[classIndex].studentsNum; i++)
		printf("%s, %d\n", allStudents[i]->name, allStudents[i]->grade);
}

/******************************************************************************************************
* Function Name: swap
* Input: Student** allStudents, int j
* Output: Student**
* Function operation: the function gets an index within the allStudents array, and switches between
*					  the student in the j,j+1 indexes and returns the new array.
*******************************************************************************************************/
Student** swap(Student** allStudents, int j)
{
	//move to first student to a temp pointer
	Student* temp = allStudents[j];
	//switch between the pointers
	allStudents[j] = allStudents[j + 1];
	allStudents[j + 1] = temp;
	//return new array
	return allStudents;
}

/******************************************************************************************************
* Function Name: validForPrint
* Input: char line[MAX_LINE],int numClasses, Classes allClasses[MAX_CLASSES]
* Output: int(1 for valid,-1 for invalid)
* Function operation: the function gets a request line for printing students. the function checks:
*					  1) if the number is valid, contain exactly 5 digits
*					  2)if the class really exist 3) if there is no students in class
*					  if one of the above happens, the function prints an error message and return
*					  -1. else, the function returns 1.
*******************************************************************************************************/
int validForPrint(char line[MAX_LINE], int numClasses, Classes allClasses[MAX_CLASSES]) {
	char classNumber[COURSE_NUM];
	int i = 0, classIndex;
	//skip spaces
	while (line[i] == SPACE && line[i] != '\0')
		i++;
	//check if all letters are digits
	for (int j = 0; j <= 4; j++) {
		if (isdigit(line[i]) == 0) {
			printf("Error: invalid class number.\n");
			return INVALIDCHECK;
		}
		else {
			classNumber[j] = line[i++];
		}
	}
	classNumber[COURSE_NUM - 1] = '\0';
	//check if the number is longer than 5 digits.
	if (line[i] != '\0')
	{
		printf("Error: invalid class number.\n");
		return INVALIDCHECK;
	}
	//check if the class exists
	if (findClasses(allClasses, classNumber, numClasses) == NOT_FOUND)
	{
		printf("Error: invalid class number.\n");
		return INVALIDCHECK;
	}
	//check if there is no students in the class
	classIndex = findClasses(allClasses, classNumber, numClasses);
	if (allClasses[classIndex].studentsNum == 0)
	{
		printf("Class \"%s %s\" has no students.\n", allClasses[classIndex].courseNumber, allClasses[classIndex].name);
		return INVALIDCHECK;
	}
	return VALIDCHECK;
}

/************************************************************************************************************
* Function Name: printComputedScores
* Input: Classes allClasses[MAX_CLASSES],int numClasses
* Output: void
* Function operation: the function gets a request to print a comptued score as the user's asking. the options
*					  are: a) average grade b) maximal grade c) minimal grade d)sum e)count 0) return to main
*					  menu.
*************************************************************************************************************/
void printComputedScores(Classes allClasses[MAX_CLASSES], int numClasses) {
	char choose;
	//if the num of classes is 0 don't do anything
	if (numClasses == 0) {
		printf("Error: there are no classes.\n");
		return;
	}
	//print the menu
	printScoresMenu();
	scanf(" %c", &choose);
	switch (choose)
	{
	case 'a': printSumOrAverageGrade(allClasses, numClasses, 2);
		break;
	case 'b': printMinMaxGrade(allClasses, numClasses, 1);
		break;
	case 'c': printMinMaxGrade(allClasses, numClasses, 2);
		break;
	case 'd': printSumOrAverageGrade(allClasses, numClasses, 1);
		break;
	case 'e': printNumStudents(allClasses, numClasses);
		break;
	case '0': return;
		break;
	default:
		printf("Error: unrecognized operation.\n");
		break;
	}
}

/********************************************************************************
* Function Name: printScoresMenu
* Input: none
* Output: void
* Function operation: the function prints the menu for the computed scores menu
********************************************************************************/
void printScoresMenu() {
	printf("Please select the aggregation method:\n\
\ta. Average Grade.\n\
\tb. Maximal Grade.\n\
\tc. Minimal Grade.\n\
\td. Sum.\n\
\te. Count.\n\
\t0. Return to the main menu.\n");
}

/*****************************************************************************************************
* Function Name: printSumOrAverageGrade
* Input: Classes allClasses[MAX_CLASSES],int numClasses,int choice
* Output: void
* Function operation: the function get a request to print the sum or the average of the students grade.
*					  if the user want to print the Sum, the input choice will be 1. if the user want
*					  to print the average, the input choice will be 2. operation: the function reading
*					  all existed classes, calculating the sum of every class grade with a "for" loop.
*					  if the user asked to print the average, before printing the function divides the
*					  sum of grade.
*******************************************************************************************************/
void printSumOrAverageGrade(Classes allClasses[MAX_CLASSES], int numClasses, int choice) {
	//pointer to student list
	Student** allStudents = NULL;
	int grade = 0, numStudents;
	//run all classes
	for (int i = 0; i < numClasses; i++)
	{
		grade = 0;
		//take the right list and students sum
		allStudents = allClasses[i].allStudents;
		numStudents = allClasses[i].studentsNum;
		//check if there is no students in class
		if (numStudents == 0) {
			printf("Class \"%s %s\" has no students.\n", allClasses[i].courseNumber, allClasses[i].name);
			continue;
		}
		//run a loop for all current students
		for (int j = 0; j < numStudents; j++)
		{
			//add all grades of class
			grade = grade + allStudents[j]->grade;
		}
		// if the user chose to calculate average divide by num of students.
		if (choice == 2)
			grade = grade / numStudents;
		//print sum or average grade
		printf("%s %s, %d\n", allClasses[i].courseNumber, allClasses[i].name, grade);
	}
}

/*****************************************************************************************************
* Function Name: printMinMaxGrade
* Input: Classes allClasses[MAX_CLASSES],int numClasses,int choice
* Output: void
* Function operation: the function get a request to print the min or the max students grade.
*					  if the user want to print the max, the input choice will be 1. if the user want
*					  to print the min, the input choice will be 2. operation: function runs all
*					  classes. if there is no students, the function prints it and exit. else, the
*					  function calculate the min/max grade with a "for" loop and print the result.
*******************************************************************************************************/
void printMinMaxGrade(Classes allClasses[MAX_CLASSES], int numClasses, int choice) {
	int grade, numStudents;
	//pointer to student list
	Student** allStudents = NULL;
	//run all classes
	for (int i = 0; i < numClasses; i++)
	{
		grade = 0;
		//take the right list and students sum
		allStudents = allClasses[i].allStudents;
		numStudents = allClasses[i].studentsNum;
		//check if there is no students in class
		if (numStudents == 0) {
			printf("Class \"%s %s\" has no students.\n", allClasses[i].courseNumber, allClasses[i].name);
			continue;
		}
		//set the first number as the grade of the first student
		grade = allStudents[0]->grade;
		//check if the student asked minumum or maximum grade,if the choice is 1 return max
		if (choice == 1)
		{
			//compare between every two students grade
			for (int j = 0; j < numStudents - 1; j++)
			{
				//calculate max grade
				grade = returnMax(grade, allStudents[j + 1]->grade);
			}
		}
		//if the choice is 2 return min
		else
		{
			//compare between every two students grade
			for (int j = 0; j < numStudents - 1; j++)
			{
				//calculate max grade
				grade = returnMin(grade, allStudents[j + 1]->grade);
			}
		}
		//print result
		printf("%s %s, %d\n", allClasses[i].courseNumber, allClasses[i].name, grade);
	}
}

/***************************************************************************
* Function Name: returnMax
* Input: int a, int b
* Output: int (bigger int)
* Function operation: the function gets two ints and returns the bigger int
****************************************************************************/
int returnMax(int a, int b) {
	if (a > b)
		return a;
	return b;
}

/***************************************************************************
* Function Name: returnMin
* Input: int a, int b
* Output: int (smaller int)
* Function operation: the function gets two ints and returns the smaller int
****************************************************************************/
int returnMin(int a, int b) {
	if (a < b)
		return a;
	return b;
}

/*******************************************************************************
* Function Name: printNumStudents
* Input: Classes allClasses[MAX_CLASSES], int numClasses
* Output: void
* Function operation: the function prints the sum of every class in the academy.
********************************************************************************/
void printNumStudents(Classes allClasses[MAX_CLASSES], int numClasses) {
	//run all classes
	for (int i = 0; i < numClasses; i++)
	{
		//check if the class is empty and print a message if it is.
		if (allClasses[i].studentsNum == 0) {
			printf("Class \"%s %s\" has no students.\n", allClasses[i].courseNumber, allClasses[i].name);
			continue;
		}
		printf("%s %s, %d\n", allClasses[i].courseNumber, allClasses[i].name, allClasses[i].studentsNum);
	}
}

/*******************************************************************************
* Function Name: freeAll
* Input: Classes allClasses[MAX_CLASSES], int numClasses
* Output: void
* Function operation: the function releases all allocated memory from memory.
********************************************************************************/
void freeAll(Classes allClasses[MAX_CLASSES], int numClasses) {
	//run all classes
	for (int i = 0; i < numClasses; i++)
	{
		//release all students contents
		for (int j = allClasses[i].studentsNum-1; j >=0; j--)
		{
			free(allClasses[i].allStudents[j]);
		}
		allClasses[i].allStudents = NULL;
	}
}

/***********************************************************
* Function Name: resetClasses
* Input: Classes allClasses[MAX_CLASSES]
* Output: void
* Function operation: the function resets all Classes array
************************************************************/
void resetClasses(Classes allClasses[MAX_CLASSES]) {
	for (int i = 0; i < MAX_CLASSES; i++)
	{
		allClasses[i].courseNumber[0] = '\0';
		allClasses[i].name[0] = '\0';
		allClasses[i].allStudents = NULL;
		allClasses[i].studentsNum = 0;
	}
}

/*****************************************************************************************
* Function Name: skipSpaces
* Input: char line[MAX_LINE], int *index
* Output: void
* Function operation: the function returns the index of the array after "deleting" spaces
******************************************************************************************/
void skipSpacesFromStart(char line[MAX_LINE], int* i) {
	while (line[*i] != '\0' && line[*i] == SPACE)
		(*i)++;
}

/*****************************************************************************************
* Function Name: getName
* Input: int *i, int *j, char name[MAX_STUDENT_NAME], char line[MAX_LINE]
* Output: void
* Function operation: the function set the real name into char array and changes the index
*					  by its address.
******************************************************************************************/
void getName(int* i, int* j, char name[MAX_STUDENT_NAME], char line[MAX_LINE]) {
	while ((line[*i] != '\0') && (line[*i] != ':'))
	{
		name[*j] = line[*i];
		(*j)++;
		(*i)++;
	}
	//insert end of line in name
	name[*j] = '\0';
	//skip the :
	(*i)++;
}

