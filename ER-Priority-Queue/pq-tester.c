#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "emalloc.h"

#define MAX_LINE_LEN 5000

void inccounter(Patient *p, void *arg) {
    int *ip = (int *)arg;
    (*ip)++;
}


void print_word(Patient *p, void *arg) {
    char *fmt = (char *)arg;
    printf(fmt, p->name, p->birth_year, p->priority);
}


void dump(Patient *list) {
    int len = 0;

    apply(list, inccounter, &len);    
    printf("Number of patients: %d\n", len);

    apply(list, print_word, "%s,%d,%d\n");
}

//Tokenize a line of input and initialize a patient pointer
Patient *tokenize_line(char *line) {
    char *token = strtok(line, ",\n");
    // Check for empty input lines or if dequeue is the input
    if (strcmp(token, "dequeue") == 0 || token == NULL){ 
        return NULL;
    }
    else { 
        //Initialize patient pointer from the input line
        Patient *patient = (Patient *)emalloc(sizeof(Patient));
        patient->name = strdup(strtok(NULL, ","));
        patient->birth_year = atoi(strtok(NULL, ","));
        patient->priority = atoi(strtok(NULL, ","));

        return patient;
    }
}
    
    
//Reads input lines from stdin and processes them
Patient *read_lines(Patient *list) {
    char line[MAX_LINE_LEN];
    //Read input from stdin 
    while(fgets(line, sizeof(line), stdin) != NULL) {
        //Call helper function to interpret the lines as patient pointers.
        Patient *patient = tokenize_line(line);
        //If patient exists, add it to the list according to its priority ranking, if not (incase of dequeue), remove the front of the line
        if (patient != NULL) {
            list = add_with_priority(list, patient);
        } else {
            list = remove_front(list);
        }
    }
    return list;
}

// Helper function to deallocate memory used by the patient list.
void deallocate_memory(Patient *list) {
    while (list != NULL) {
        Patient *temp = list;
        list = list->next;

        free(temp->name);
        
        free(temp);
    }

}  

int main(int argc, char *argv[]) {
    /* DO NOT CHANGE THE MAIN FUNCTION. YOU HAVE TO IMPLEMENT YOUR
        CODE TO FOLLOW THE SEQUENCE OF INSTRUCTIONS BELOW. */
    Patient *list = NULL;

    if (argc != 1) {
            printf("Usage: %s\n", argv[0]);
            printf("Should receive no parameters\n");
            printf("Read from the stdin instead\n");
            exit(1);
    }

    list = read_lines(list);
 
    dump(list);
    
    deallocate_memory(list);

    exit(0); 
}
