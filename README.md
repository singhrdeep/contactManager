
# contactManager – Binary File Contact Manager in C

`contactManager` is a command-line program written in C that lets users create, store, and retrieve contact records using a custom binary file format. It supports persistent contact storage using file offsets and dynamic memory for flexible string input.

This project was originally developed at the University of Guelph to help illustrate foundational programming and machine learning concepts in C. While it was built in an academic setting, it has been adapted for public sharing and broader learning.
---

## Features

- Stores contacts with employee ID, first name, last name, and email
- Dynamically allocates memory for all string fields
- Writes contact records with offset-based linking in a binary file
- Can search, retrieve, and re-append to the file across multiple runs
- Menu-driven interface with multiple operational modes

---

## Requirements

- GCC compiler (C99 standard)
- Make utility

---

## Folder Structure

```
contactManager/
├── bin/           # Compiled executable
├── include/       # Header files (given.h)
├── src/           # Source files
└── makefile       # Build instructions
```

---

## Build Instructions

To compile the project:

```bash
make
```

To clean object files and executables:

```bash
make clean
```

---

## Run Instructions

To run the program:

```bash
./bin/contactManager contactsList.db
```

The database file `contactsList.db` will be created if it doesn’t exist.

---

## Functionality

- **Create Contact:** Prompt the user for employee details and append to the binary file.
- **Read All Contacts:** Print all stored records in order.
- **Search Contact:** Look up a contact by employee ID.
- **Persistent Storage:** All data remains after program exit.

---

## License

This project is provided as-is for educational use. No license is currently specified.
