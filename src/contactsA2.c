#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "../include/given.h"



int main(int argc, char *argv[]) {

    // check commland line arguments
    if (argc != 2) {
        printf("Incorrect amount of arguments\n");
        return -1;
    }
    
    // declare variables for file 
    char *fileName = argv[1]; 
    
    // open file to check for existing data
    FILE *file = fopen(fileName, "rb"); // opens an existing binary file to read
    
    // variable to store pos of contact
    long pos = 0;
    
    // check for files existence
    if (file == NULL) { 
        
        // if file doesnt exist, create a new one
        printf("File not found, creating new file\n");
        file = fopen(fileName, "wb+");
        
        if (file == NULL) {
            printf("Error creating file.\n");
            return -1;
        }

        // initialize the file with an empty head pos
        fwrite(&pos, sizeof(long), 1, file);
    } 
    
    // else read the head pos
    else {
        fread(&pos, sizeof(long), 1, file);
    }
    
    // close file as we are just checking its state
    fclose(file);

    // if the file empty (pos is 0), force user to create a contact first
    if (pos == 0) {
        
        // call createContacts function 
        createContacts(fileName);
    }
    
    // declare variables for menu and choices
    int choice; // variable for chice 
    int empId; // variable for employee id 
    int found; // variable for whether or not id is found

    // menu loop
    do {
        // display menu options
        printf("1 to print, 2 to search, 3 to create more, -1 to exit: ");
        scanf("%d", &choice);
        
        printf("\n"); // newline
        
        // validate user input
        if (choice < -1 || choice > 3) {
            printf("Invalid input, exiting program.\n");
            break;
        }

        // switch case to handle options
        switch (choice) {
            case 1:
                printf("\nPrinting Employee records saved on file:\n");
                
                // call readContacts to read the file
                readContacts(fileName);
                
                // break
                break;

            case 2:
                // do-while loop until valid employee ID is entered
                do {
                    // ask user 
                    printf("Enter the employee ID to search (1-9999): ");
                    scanf("%d", &empId);
                    
                    // if employee id is less than 1 or greater than 9999
                    if (empId < 1 || empId > 9999) {
                        printf("Error, invalid employee ID\n");
                    }
                } while (empId < 1 || empId > 9999);
                
                // call searchContacts to search for employee
                found = searchContacts(fileName, empId);
                
                // display result if not found
                if (!found) {
                    printf("No match found.\n");
                }
                
                // break
                break;

            case 3:
                // call createContacts to create new contacts
                createContacts(fileName);
                
                // break
                break;

            case -1:
                printf("\nExiting...\n");
                
                // break
                break;
        }
    } while (choice != -1); // loop until -1 is selected

    // return 0
    return 0;
}
