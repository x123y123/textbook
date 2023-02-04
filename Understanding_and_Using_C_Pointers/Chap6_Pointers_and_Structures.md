# Chap 6: Pointers and Structures

In structures, the pointers provide the glue that ties elements together in such like a node of a `linked list` or `tree`.

## How to declare a structure?
* using `struct`:
```c
struct _person {
    char* firstName;
    char* lastName;
    char* title;
    unsigned int age;
}

```
* using `typedef struct`:
```c
typedef struct _person {
    char* firstName;
    char* lastName;
    char* title;
    unsigned int age;
} Person;

Person person;
```
## How can we use pointer to a structure?
> use points-to operator(`->`)

* Example: (using `points-to operator`)
```c
Person *ptrPerson;
ptrPerson = (Person*) malloc(sizeof(Person));
ptrPerson->firstName = (char*) malloc(strlen("Tom")+1);
strcpy(ptrPerson->firstName, "Tom");
ptrPerson->age = 23;
```

* Example: (using `dereference + dot operator`)
```c
Person *ptrPerson;
ptrPerson = (Person*) malloc(sizeof(Person));
(*ptrPerson).firstName = (char*) malloc(strlen("Tom")+1);
strcpy((*ptrPerson).firstName, "Tom");
(*ptrPerson).age = 23;
```


