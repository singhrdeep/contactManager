#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "../include/given.h"


/* Task 3 */
int searchContacts(char *fileName, int keyId) {

	// open file in binary read mode
	FILE *file = fopen(fileName, "rb");

	// check if file opened successfully
	if (file == NULL) {
		printf("error opening file\n");
		return -1;
	}

	// declare struct to search contacts
	struct contact searchContact;

	// declare variables
	int empId; // employee id
	long pos; // position
	int found = 0; // variable to check if its found

	// move to start of file
	fseek(file, 0, SEEK_SET);

	// check if file contains any contacts, if not tell user
	if (fread(&pos, sizeof(long), 1, file) != 1 || pos == 0) {
		printf("no contacts found.\n");
		fclose(file);
		return 0;
	}

	// do-while loop to loop through contacts to find a match
	do {

		// move to the current contacts pos and read data
		fseek(file, pos, SEEK_SET);
		if (fread(&searchContact, sizeof(struct contact), 1, file) != 1) {
			printf("error reading contact data.\n");
			break;
		}

		// move to employee ID pos and read it
		fseek(file, searchContact.empIdPosn, SEEK_SET);
		fread(&empId, sizeof(int), 1, file);

		// check if employee ID matches search key
		if (empId == keyId) {

			// set flag to 1 to indicate match found
			found = 1;

			// print header
			printf("************************************************************\n");
			printf("employee ID: %d\n", empId);

			// dynamically allocate memory for contact details
			char *firstName = malloc(50 * sizeof(char));
			char *lastName = malloc(50 * sizeof(char));
			char *email = malloc(100 * sizeof(char));

			// read and print first name
			if (searchContact.firstNamePosn > 0) {
			    
			    // move to pos and read name into variable
				fseek(file, searchContact.firstNamePosn, SEEK_SET); 
				fgets(firstName, 50, file); 

				// check if first name is empty
				if (firstName[0] != '\n' && firstName[0] != '\0') {
					printf("first name: %s\n", firstName);
				}

				// else print and continue
				else {
					printf("first name: not entered\n");
				}
			}

			// read and print last name
			if (searchContact.lastNamePosn > 0) {
			    
			    // move to pos and read name into variable
				fseek(file, searchContact.lastNamePosn, SEEK_SET);
				fgets(lastName, 50, file);

				// check if last name is empty
				if (lastName[0] != '\n' && lastName[0] != '\0') {
					printf("last name: %s\n", lastName);
				}

				// else print and skip
				else {
					printf("last name: not entered\n");
				}
			}

			// read and print email
			if (searchContact.emailPosn > 0) {
			    
			    // move to pos and read name into variable
				fseek(file, searchContact.emailPosn, SEEK_SET);
				fgets(email, 100, file);

				// check if email is empty
				if (email[0] != '\n' && email[0] != '\0') {
					printf("email: %s\n", email);
				}

				// else print and skip
				else {
					printf("email: not entered\n");
				}
			}

			// print footer
			printf("************************************************************\n\n");

			// free allocated memory before breaking out of loop
			free(firstName);
			free(lastName);
			free(email);

			// exit loop if match found
			break;
		}

		// move to next contact
		pos = searchContact.next;

	} while (pos != 0);  // continue until no more contacts

	// if no contact was found, print message
	if (!found) {
		printf("no match found.\n");
	}

	// close file
	fclose(file);

	// return result
	return found;
}
