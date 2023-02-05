/* structure list it may can avoid some malloc/free overhead */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define LIST_SIZE   10

typedef struct _person { 
    char* firstName;
    char* lastName; 
    char* title; 
    unsigned int age;
} Person;

Person *list[LIST_SIZE];

void initializeList() 
{
    for(int i=0; i<LIST_SIZE; i++) {
        list[i] = NULL;
    }
}

void initializePerson(Person *person, const char* fn, const char* ln, const char* title, unsigned int age) 
{
    person->firstName = (char*) malloc(strlen(fn) + 1); 
    strcpy(person->firstName, fn);
    person->lastName = (char*) malloc(strlen(ln) + 1); 
    strcpy(person->lastName, ln);
    person->title = (char*) malloc(strlen(title) + 1); 
    strcpy(person->title, title);
    person->age = age;
}

void deallocatePerson(Person *person) 
{ 
    free(person->firstName); 
    free(person->lastName); 
    free(person->title);
}

void displayPerson(Person *person)
{
    printf("%s\n", person->firstName);
    printf("%s\n", person->lastName);
    printf("%s\n", person->title);
    printf("%d\n", person->age);
}

Person *getPerson() 
{
    for(int i=0; i<LIST_SIZE; i++) {
        if(list[i] != NULL) { 
            Person *ptr = list[i]; 
            list[i] = NULL;
            return ptr;
        } 
    }
    Person *person = (Person*)malloc(sizeof(Person));
    return person; 
}

Person *returnPerson(Person *person) 
{ 
    for(int i=0; i<LIST_SIZE; i++) {
        if(list[i] == NULL) { 
            list[i] = person; 
            return person;
        } 
    }
    deallocatePerson(person); 
    free(person);
    return NULL;
}

int main()
{
     initializeList();
     Person *ptrPerson;
     ptrPerson = getPerson();
     initializePerson(ptrPerson,"Ralph","Fitsgerald","Mr.",35);
     displayPerson(ptrPerson);
     returnPerson(ptrPerson);
}
