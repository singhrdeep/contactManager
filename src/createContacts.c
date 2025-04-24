#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "../include/given.h"


/* Task 1 */
void createContacts(char *fileName) {

	// open file in read+write mode 
	FILE *file = fopen(fileName, "r+b");

	// if file does not exist, create a new one
	if (file == NULL) {
		file = fopen(fileName, "w+b"); // w+b creates a new file if it doesnt exist
		if (file == NULL) {
			printf("error creating file\n");
			return;
		}
		// initialize file with empty pos
		long emptyPos = 0;
		fwrite(&emptyPos, sizeof(long), 1, file);
	}

	// declare empty struct to store contact
	struct contact newContact = {0, 0, 0, 0, 0};

	// dynamically allocate memory for contact details
	char *firstName = malloc(50 * sizeof(char));
	char *lastName = malloc(50 * sizeof(char));
	char *email = malloc(100 * sizeof(char));

	// declare input variables
	int empId; // employee id
	char choice[10]; // for choice
	long pos = 0; // for current pos of file

	// move to start of file and read pos
	fseek(file, 0, SEEK_SET);
	fread(&pos, sizeof(long), 1, file);

	// infinite loop to allow user to enter multiple contacts
	while (1) {
	    
		// ask user if they want to enter a new contact
		printf("\ndo you wish to enter a new contact? (Yes or No?): ");
		scanf("%s", choice);

		// validate input (only exit if exactly "No")
		if (strcmp(choice, "No") == 0) {
			break;
		}

		/*
		** getchar() **
		
		Source: https://www.geeksforgeeks.org/clearing-the-input-buffer-in-cc/

		Explaination: getchar() is a function that is commonly used for handling user
		input, and it is also used to clear input buffers. This means that when you
		use scanf(), a newline character is left in the buffer after input, and with
		getchar(), you can use it to clear it before reading other input.
		*/
		
		// clear input buffer using getChar
		while (getchar() != '\n');

		// ask for employee ID and validate
		printf("enter employee ID (1-9999): ");
		if (scanf("%d", &empId) != 1 || empId < 1 || empId > 9999) {
			printf("invalid employee ID. skipping entry.\n");
			while (getchar() != '\n'); // clear input buffer using getchar
			continue;
		}

		// clear input buffer using getchar
		while (getchar() != '\n');

		/*
		** strcspn() **

		Source: https://www.w3schools.com/c/ref_string_strcspn.php

		Explaination: strcspn() is a C function that searches a string for
		the first occurrence of any character from a given set and returns the index of that
		character, if no match is found, it returns the length of the string.
		*/

		// get input for first name 
		printf("first name: ");
		fgets(firstName, 50, stdin);
		firstName[strcspn(firstName, "\n")] = 0; // remove newline using strcspn

		// get input for first name 
		printf("last name: ");
		fgets(lastName, 50, stdin);
		lastName[strcspn(lastName, "\n")] = 0; // remove newline using strcspn

		// get input for first name 
		printf("email: ");
		fgets(email, 100, stdin);
		email[strcspn(email, "\n")] = 0; // remove newline using strcspn

		// store pos of new contact
		fseek(file, 0, SEEK_END);
		long contactPos = ftell(file); // store new pos inside declared variable
		fwrite(&newContact, sizeof(struct contact), 1, file); // write to file

		// store and write employee ID
		newContact.empIdPosn = ftell(file); // store new contact pos
		fwrite(&empId, sizeof(int), 1, file); // write to file 

		// store and write first name
		if (strlen(firstName) > 0) {
			newContact.firstNamePosn = ftell(file); // store file pos 
			fwrite(firstName, strlen(firstName) + 1, 1, file); // write to file and include null terminator 
		}

		// else set to 0
		else {
			newContact.firstNamePosn = 0;
		}

		// store and write last name
		if (strlen(lastName) > 0) {
			newContact.lastNamePosn = ftell(file); // store file pos 
			fwrite(lastName, strlen(lastName) + 1, 1, file); // write to file and include null terminator 
		}

		// else set to 0
		else {
			newContact.lastNamePosn = 0;
		}

		// store and write email
		if (strlen(email) > 0) {
			newContact.emailPosn = ftell(file); // store file pos 
			fwrite(email, strlen(email) + 1, 1, file); // write to file and include null terminator 
		}

		// else set to 0
		else {
			newContact.emailPosn = 0;
		}

		// update next pointer
		newContact.next = pos;
		pos = contactPos;

		// update the contact with correct values
		fseek(file, contactPos, SEEK_SET); // update file 
		fwrite(&newContact, sizeof(struct contact), 1, file); // write to file 

		// update the head pos at start of file
		fseek(file, 0, SEEK_SET);
		fwrite(&pos, sizeof(long), 1, file); // write to file 
	}

	// free allocated memory
	free(firstName);
	free(lastName);
	free(email);

	// close file
	fclose(file);
}
