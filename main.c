/************
* Ido Aharon
* 01
* ex5
*************/

#include "ex5.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
	Classes academy[MAX_CLASSES];
	int numClasses = 0;
	char option, newLine;
	//reset all classes
	resetClasses(academy);
	//print the menu and scan the option
	printMenu();
	scanf(" %c", &option);
	//ignore spaces
	while (option == SPACE)
	{
		scanf("%c", &option);
	}
	while (option != '0')
	{
		//read newline
		scanf("%c", &newLine);
		switch (option)
		{
		case '1':insertUpdateClass(academy, &numClasses);
			break;
		case '2': insertUpdateStudent(academy, numClasses);
			break;
		case '3': deleteStudent(academy, numClasses);
			break;
		case '4':printStudents(academy, numClasses);
			break;
		case '5':printComputedScores(academy, numClasses);
			break;
		case '6':printMenu();
			break;
		default:
		{
			//if the option is not between 0-6 print error message.
			printf("Error: unrecognized operation.\n");
			break;
		}
		}
		if (option != '6')
			printf("Select the next operation (insert 6 for the entire menu):\n");
		scanf(" %c", &option);
		while (option == SPACE)
		{
			scanf("%c", &option);
		}
	}
	freeAll(academy, numClasses);
	return 0;
}
