#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "../include/given.h"


/* Task 2 */
int readContacts(char *fileName) {

	// open file in read-binary mode
	FILE *file = fopen(fileName, "rb");

	// check if the file opened successfully
	if (file == NULL) {
		printf("error opening file\n");
		return -1;
	}

	// declare struct to read contacts
	struct contact readContact;

	// declare variables
	char readString[100]; // buffer to read strings
	int empId; // emplyoee id
	long pos; // pos of contacts
	long contacts[100]; // array to store contact pos
	int contactCount = 0; // contact count

	// move to start of file
	fseek(file, 0, SEEK_SET);

	// check if file contains any data, if not, return 0
	if (fread(&pos, sizeof(long), 1, file) != 1 || pos == 0) { // checks if val 0 or failed
		printf("no contacts found.\n");
		fclose(file);
		return 0;
	}

	// store contact pos in an array
	while (pos != 0 && contactCount < 100) {
		contacts[contactCount] = pos;
		contactCount++;

		// move to current contact pos and read struct
		fseek(file, pos, SEEK_SET);
		if (fread(&readContact, sizeof(struct contact), 1, file) != 1) {
			printf("error reading data.\n");
			fclose(file);
			return -1;
		}

		pos = readContact.next; // move to next contact
	}

	// for loop to print contacts in correct order
	for (int i = contactCount - 1; i >= 0; i--) {
		
		// seek to current pos
		fseek(file, contacts[i], SEEK_SET);
		
		// to handle if reading fails
		if (fread(&readContact, sizeof(struct contact), 1, file) != 1) {
			printf("error reading data.\n");
			continue;
		}

		// read employee id
		fseek(file, readContact.empIdPosn, SEEK_SET);
		fread(&empId, sizeof(int), 1, file);

		// print contact details
		printf("************************************************************\n");
		printf("Employee id: %d\n", empId);

        /*
		** strcspn() **

		Source: https://www.w3schools.com/c/ref_string_strcspn.php

		Explaination: strcspn() is a C function that searches a string for
		the first occurrence of any character from a given set and returns the index of that
		character, if no match is found, it returns the length of the string.
		*/

		// read and print first name
		if (readContact.firstNamePosn > 0) {
			fseek(file, readContact.firstNamePosn, SEEK_SET);
			fgets(readString, sizeof(readString), file);
			
			readString[strcspn(readString, "\n")] = 0; // remvoe newline using strcspn

            // check if readstring contains characters
			if (strlen(readString) > 0) {
				printf("First Name: %s\n", readString);
			}

            // else set to nothing
			else {
				printf("First Name: \n");
			}
		}

        // else set to nothing
		else {
			printf("First Name: \n");
		}
    
		// read and print last name
		if (readContact.lastNamePosn > 0) {
			
			// move file pointer to pos and read into readString
			fseek(file, readContact.lastNamePosn, SEEK_SET);
			fgets(readString, sizeof(readString), file);
			
			readString[strcspn(readString, "\n")] = 0; // remove newline using strcspn 

            // check if readstring contains characters
			if (strlen(readString) > 0) {
				printf("Last Name: %s\n", readString);
			}
		}
        // else set to nothing
		else {
			printf("Last Name: \n");
		}

		// read and print email
		if (readContact.emailPosn > 0) {
		    
		    // move file pointer to pos and read into readString
			fseek(file, readContact.emailPosn, SEEK_SET);
			fgets(readString, sizeof(readString), file);
			
			readString[strcspn(readString, "\n")] = 0; // remove newline using strcspn

            // check if readstring contains characters
			if (strlen(readString) > 0) {
				printf("Email: %s\n", readString);
			} 
			
			// else set to nothing
			else {
				printf("Email: \n");
			}
		} 
		// else set to nothing
		else {
			printf("Email: \n");
		}

		// print header
		printf("************************************************************\n\n");
	}

	// close file
	fclose(file);

	// return
	return 0;
}