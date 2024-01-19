#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "emalloc.h"
#include "list.h"


Patient *new_patient(char *name, int birth_year, int priority) {
    assert( name != NULL);

    Patient *temp = (Patient *)emalloc(sizeof(Patient));

    temp->name       = strdup(name);
    temp->birth_year = birth_year;
    temp->priority   = priority;
    temp->next       = NULL;

    return temp;
}


Patient *add_front(Patient *list, Patient *new) {
    new->next = list;
    return new;
}


Patient *add_end(Patient *list, Patient *new) {
    Patient *curr;

    if (list == NULL) {
        new->next = NULL;
        return new;
    }

    for (curr = list; curr->next != NULL; curr = curr->next);
    curr->next = new;
    new->next = NULL;
    return list;
}

//Adds a new patient to the linked list by priority order
Patient *add_with_priority(Patient *list, Patient *new) {
    //If the list is empty or the new patient has higher priority, insert the new patient at the front of the list.
    if (list == NULL || list->priority > new->priority) {
        new->next = list;
        return new;
    }
    //Traverse the list to find correct position for new patient based on priority.
    Patient *curr = list;
    while (curr->next != NULL && curr->next->priority <= new->priority) {
        curr = curr->next;
    }
    //Insert the new patient into list
    new->next = curr->next;
    curr->next = new;

    return list;
}

Patient *peek_front(Patient *list) {
    return list;
}


Patient *remove_front(Patient *list) {
    if (list == NULL) {
        return NULL;
    }

    return list->next;
}


void apply(Patient *list,
           void (*fn)(Patient *list, void *),
           void *arg)
{
    for ( ; list != NULL; list = list->next) {
        (*fn)(list, arg);
    }
}
