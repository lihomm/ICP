#define _CRT_SECURE_NO_WARNINGS
#include "menu.h"
#include "linked_list.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void fetch_data(parts**aop) {
    parts* currentPtr = NULL, * node, temp;
    int x = 1; 
    FILE* fptr;
    for (int i = 0; i < 3; i++)
        aop[i] = NULL;
    for(;x<4;x++){
        if (x == 1) {
            fptr = fopen("ar_warehouse.txt", "r");
        }
        else if (x == 2) {
            fptr = fopen("bz_warehouse.txt", "r");
        }
        else if (x == 3) {
            fptr = fopen("sl_warehouse.txt", "r");
        }
        else
            return;
        if (fptr == NULL) {
            printf("Error opening file");
            return;
        }
        if (check_file(fptr) == 0) {
            return;
        }
        while (fscanf(fptr, "%[^,],%[^,],%[^,],%[^,],%d,%d\n", temp.ID, temp.sections, temp.name, temp.supplier_ID, &temp.initialQuantity, &temp.quantity) != EOF) {
            node = (parts*)malloc(sizeof(parts));
            strcpy(node->ID, temp.ID);
            strcpy(node->sections, temp.sections);
            strcpy(node->name, temp.name);
            strcpy(node->supplier_ID, temp.supplier_ID);
            node->initialQuantity = temp.initialQuantity;
            node->quantity = temp.quantity;
            if (aop[x - 1] == NULL) {
                currentPtr = aop[x - 1] = node;
            }
            else
                currentPtr = currentPtr->next = node;
            currentPtr->next = NULL;
        }     
        fclose(fptr);
    } 
}

int check_file(FILE*fptr) {
    long size;
    fseek(fptr, 0, SEEK_END);
    size = ftell(fptr);
    fseek(fptr, 0, SEEK_SET);
    if (0 == size) {
        printf("File is empty\n");
        return 0;
    }
    return 1;
}

supp* supplier_list () {
    supp* currentPtr = NULL, * node, *x= NULL, temp;
    FILE* fptr;
    fptr = fopen("supplier.txt", "r"); 
    if (fptr == NULL) {
        printf("File does not exist.");
        return;
    }
    if (check_file(fptr) == 0) {
        return NULL;
    }
    while (fscanf(fptr, "%[^,],%[^,],%[^,],%[^\n]\n", temp.sup_ID, temp.name, temp.contact_num, temp.parts_ID) != EOF) {
        node = (supp*)malloc(sizeof(supp));
        strcpy(node->sup_ID, temp.sup_ID);
        strcpy(node->name, temp.name);
        strcpy(node->contact_num, temp.contact_num);
        strcpy(node->parts_ID, temp.parts_ID);
        if (x == NULL)
            currentPtr = x = node;
        else
            currentPtr = currentPtr->next = node;
        currentPtr->next = NULL;
    }

    fclose(fptr);
    return x;
}

void print_supp(supp* x, char*y) {
    while (x != NULL) {
        if (strcmp(x->sup_ID, y)== 0) {
            printf("\nSupplier ID: %s\n", x->sup_ID);
            printf("Company Name: %s\n", x->name);
            printf("Contact Number: %s\n", x->contact_num);
            printf("Parts ID Supplied: %s\n\n", x->parts_ID);
            break;
        }
        x = x->next;
    }
}

void print_list(parts* z) {
    while (z != NULL) {
        printf("\nPart ID: %s\n", z->ID);
        printf("Warehouse Section: %s\n", z->sections);
        printf("Part Name: %s\n", z->name);
        printf("SUpplier ID: %s\n", z->supplier_ID);
        printf("Initial Quantity: %d\n", z->initialQuantity);
        printf("Current Quantity: %d\n\n", z->quantity);
        z = z->next;
    }
}

void memory_free(parts* x) {
    parts* current = x; 
    while (current != NULL) {
        current = x->next;
        free(x);
        x = current;
    }
}
