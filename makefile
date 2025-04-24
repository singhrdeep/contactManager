bin/contactManager: contacts.o createContacts.o readContacts.o searchContacts.o
	gcc -Wall -std=c99 contacts.o createContacts.o readContacts.o searchContacts.o -o bin/contactManager

contacts.o: src/contactsA2.c include/given.h
	gcc -Wall -std=c99 -c src/contacts.c

createContacts.o: src/createContacts.c include/given.h
	gcc -Wall -std=c99 -c src/createContacts.c

readContacts.o: src/readContacts.c include/given.h
	gcc -Wall -std=c99 -c src/readContactsA2.c

searchContacts.o: src/searchContacts.c include/given.h
	gcc -Wall -std=c99 -c src/searchContacts.c
clean:
	rm *.o bin/myContacts *.db
