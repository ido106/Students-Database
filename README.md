# Students Database
In this assignment we will implement a course management system using *dynamic allocation*.  
### Introduction
The system will support the following actions:  
1) Exit
2) Create a new course or update an existing course
3) Registration of a new student for courses with his grades or update existing grades
4) Delete an existing student from courses
5) Print a course with its registered students
6) Print all courses in the system with the following options:  
  a) average grade in the course  
  b) maximal grade in the course  
  c) minimal grade in the course  
  d) sum of the grades in the course  
  e) number of students in the course  
7) Reprint the menu

The system starts when there is no information about any course or student.  
The system supports up to five courses in total, and unlimited number of students in every course.  

<p align="left">
  <img 
    width="300"
    height="133"
    src="https://user-images.githubusercontent.com/92651125/156233288-4cd9813b-060c-4549-89b7-8d35d7f60a8c.png"
  >
</p>

### Creating a new course or updating an existing course
Each course has a unique number and a name. The system receives the required information and add the course to the system. If the course already exists, the name of the course is updated to the new name.
If the course is inserted for the first time, the next message will be printed:  
```Class "89210 Advanced Programming 1" added.```  
If the course is not entered for the first time, the next message will be printed:  
```Class "89210 Advanced Programming 1" updated.```

### Registration of a new student
Each student has a name and a list containing course numbers and grades.  
The system will receive a student and a list of grades, and sign the student to the courses.  
If the student already exists in the system, the grades are being updated (can be a combined message).  
Example:  
```
Student "Israel Israeli" added to class "89210 Advanced Programming 1" with grade 100.
Student "Israel Israeli" updated on class "89110 Computer Science 101" with grade 95.
```  
If the input is invalid, the message ```Error: invalid name, class number or grade.``` is printed.

### Delete an existing student
The system receives a student name and course numbers, and deletes the students registration from those courses.  
Example:  
Input:  
```Israel Israeli: 89210, 89211```  
Output:  
```
Student "Israel Israeli" removed from class "89210 Advanced Programming 1".
Student "Israel Israeli" removed from class "89211 Advanced Programming 2".
```
If the input is invalid, the message ```Error: invalid name or class number``` is printed.  
If the student is not registered to one of the courses, the request is not executed and the message ```Error: student is not a member of class "89211 Advanced Programming 2".``` is printed.

### Print a course with its students
The system receives a course number and prints the registered students in the course with their grades.  
```
Class "89210 Advanced Programming 1" students:
Israel Israeli, 100
Yaakov Yaakovi, 95
Ariel Arieli, 98
```

### Print all courses with the computed scores
The following menu is printed:  
<p align="left">
  <img 
    width="270"
    height="139"
    src="https://user-images.githubusercontent.com/92651125/156240426-e6057b0f-222f-4142-8c87-6965b4edf5f9.png"
  >
</p>
The system prints all the courses with their computed scores.  
Example (for input 'e'):  
```
90210 Advanced Programming 1, 355
Class "89110 Computer Science 101" has no students.
89211 Advanced Programming 2, 342
```
