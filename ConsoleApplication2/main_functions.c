#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "main_functions.h"

char line[50];
char array_of_file[3][20] = { "ar_warehouse.txt" , "bz_warehouse.txt" , "sl_warehouse.txt" };
char ID[3][8] = { "WAR", "WBZ", "WSL" };
char car_sections[3][5] = { "ES","BWS","AS" };
char warehouse[3][20] = { "AR Warehouse (AR)","BZ Warehouse (BZ)","SL Warehouse (SL)" };

int car_menu() {
    int menu_choice1;
    printf("1. Armer (AR)\n");
    printf("2. Blaze (BZ)\n");
    printf("3. Silk (SL)\n");
    scanf_s(" %d", &menu_choice1);
    return menu_choice1;
}

void supplier_creation() {
    int i = 1;
    char line[100];
    char id_num[5]= "", ID[8] = "SUP";
    supp s,*node, *current= NULL, *head= NULL;
    FILE* fptr = fopen("supplier.txt", "a+");
    while (fgets(line, sizeof(line), fptr) != NULL) {
        ++i;
    }
    i = i + 1000;
    _itoa(i, id_num, 10);
    strcat(ID, id_num);
    printf("Enter company name: ");
    scanf("%[^\n]", s.name);
    rewind(stdin);
    printf("Enter contact number: ");
    scanf("%s", s.contact_num);
    rewind(stdin);   
    fprintf(fptr, "%s,%s,%s,NONE\n", ID, s.name, s.contact_num);
    fclose(fptr);
}

char* check_sup() {
    char sup_ID[8], line[50];
    printf("Enter your supplier ID: ");
    scanf("%s", sup_ID);
    rewind(stdin);
    FILE* fptr = fopen("supplier.txt", "r");
    while (fgets(line, sizeof(line), fptr) != NULL) {
        if (strstr(line, sup_ID) != NULL) {
            fclose(fptr);
            return sup_ID;
        }             
    }
    fclose(fptr);
    return "";
}
int section_menu() {
    int choice;
    printf("Which car sections would you like to register? Enter [1/2/3]\n");
    printf("1.  Engine Section (ES)\n");
    printf("2.  Body Work Section (BWS)\n");
    printf("3.  Air-con Section (AS)\n");
    scanf("%d", &choice);
    return choice;
}

void inventory_creation(char* x, parts**aop, supp*p)
{
    char sup_num[6], part_name[20], part_ID[8];
    int choice, y, amount, i=1;
    FILE* fptr, *fptr1;
    supp* head, *current;
    choice = car_menu()-1;
    y = section_menu();
    fptr = fopen(array_of_file[choice], "a+");   
    if (fptr == NULL) {
        printf("File does not exist!\n");
        return;
    }
    while (fgets(line, sizeof(line), fptr) != NULL) {
        ++i;
    }
    i = i + 1000;
    strcpy(part_ID, ID[choice]);
    _itoa(i, sup_num, 10);
    strcat(part_ID, sup_num);
    printf("Enter part name: ");
    scanf("%s", part_name);
    rewind(stdin);
    printf("Enter initial amount: ");
    scanf("%d", &amount);
    rewind(stdin);
    printf("The part ID for the part you just registered is %s\n", part_ID);
    fprintf(fptr, "%s,%s,%s,%s,%d,%d\n", part_ID, car_sections[y], part_name, x, amount, amount);
    fclose(fptr);
    current = p;
    head = p;
    while (p != NULL) {
        if (strcmp(p->sup_ID, x) == 0) {
            if (strcmp(p->parts_ID, "NONE")== 0) {
                strcpy(p->parts_ID, part_ID);
                strcat(p->parts_ID, " ");
                break;
            }
            else {
                strcat(p->parts_ID, part_ID);
                strcat(p->parts_ID, " ");
                break;
            }
        }
        p = p->next;
    }   
    fptr1 = fopen("supplier.txt", "w+");
    while (current != NULL) {
        fprintf(fptr1, "%s,%s,%s,%s\n", current->sup_ID, current->name, current->contact_num, current->parts_ID);
        current = current->next;
    }
    fclose(fptr1);
}

void inventory_update(parts** aop)
{
    parts temp, * head, * current;
    int choice, x, y, z, i;
    char part_ID[8];
    FILE* fptr;
    choice = car_menu()-1;
    printf("Enter the part ID to be updated: ");
    scanf("%s", part_ID);
    printf("Please select the operation to be performed: Enter [1/2]\n");
    printf("1.  Receiving from suppliers (Increase Quantity)\n");
    printf("2.  Providing to assembly sections (Decrease quantity)\n");
    scanf("%d", &x);
    if (x != 1 && x != 2) {
        printf("Invalid input\n");
        return;
    }
    printf("Enter quantity to add/remove %s:", part_ID);
    scanf("%d", &z);
    if (z < 0) {
        printf("Negative value!");
        return;
    }
    head = aop[choice];
    current = head; 
    while (current != NULL) {
        printf("%d", current->quantity);
        current = current->next;
    }
    while (current != NULL) {
        if (strcmp(current->ID, part_ID) == 0) {
            switch (x) {
            case 1:
                current->quantity += z;

                break;
            case 2:
                if (current->quantity < z) {
                    printf("Insufficient parts in warehouse.");
                    return;
                }
                else {
                    current->quantity -= z;
                }
                break;
            }
        }
        current = current->next;
    }
    fptr = fopen("ar_warehouse.txt", "w");


        
}

void inventory_checking(parts**aop)
{
    int choice, warehouse_choice,j;
    FILE* fptr;
    parts* head, *current;
    printf("Welcome to Inventory Checking System. Which of these models would you like to access? Enter [1/2]\n");
    printf("1.  Total available quantity of all parts\n");
    printf("2.  Records of all parts that has stock quantity less than 10 units in each warehouse\n");
    scanf("%d", &choice);
    if (choice == 1) {
        for (int i = 0; i < 3; i++) {
            head = aop[i];
            current = head;
            printf("------------------------\n");
            printf("%s\n", warehouse[i]);
            print_list(aop[i]);
            printf("------------------------\n");
        }
    }
    else if (choice == 2) {
        warehouse_choice = car_menu();      
        print_list2(aop, warehouse_choice - 1);
    }
}

void print_list2(parts**aop, int x) {
    parts* head, *current;
    head = aop[x];
    current = head;
    if (current->ID == NULL) {
        printf("No records available.");
    }
    while (current != NULL) {
        if (current->quantity < 10) {
            printf("\n------------------------\n");
            printf("Part ID: %s\n", current->ID);
            printf("Warehouse Section: %s\n", current->sections);
            printf("Part Name: %s\n", current->name);
            printf("Supplier ID: %s\n", current->supplier_ID);
            printf("Initial Quantity: %d\n", current->initialQuantity);
            printf("Current Quantity: %d\n", current->quantity);
            printf("------------------------\n");
        }
        current = current->next;
    }
}

void searching(supp* x)
{   
    FILE* fptr;
    char ID[8], line[50];
    int choice;
    printf("Welcome to Search System.\n");
    printf("1.  Search Part ID\n");
    printf("2.  Search Supplier ID\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    switch (choice) {
    case 1:
        printf("Enter the part ID: ");
        scanf("%s", ID);
        if (strstr(ID, "WAR") != NULL) {
            fptr = fopen("ar_warehouse.txt", "r");
            line_search(fptr, ID);
        }
        else if (strstr(ID, "WBZ") != NULL) {
            fptr = fopen("bz_warehouse.txt", "r");
            line_search(fptr, ID);
        }
        else if (strstr(ID, "WSL") != NULL) {
            fptr = fopen("sl_warehouse.txt", "r");
            line_search(fptr, ID);
        }
        else
            printf("No record available.\n");
        break;
    case 2:
        printf("Enter supplier ID: ");
        scanf("%s", ID);
        print_supp(x, ID);
    break;
    }
}    


void line_search(FILE*fptr, char*ID) {
    parts x;
    while (fscanf(fptr, "%[^,],%[^,],%[^,],%[^,],%d,%d\n", x.ID, x.sections, x.name, x.supplier_ID, &x.initialQuantity, &x.quantity) != EOF) {
        if (strcmp(x.ID, ID) == 0) {
            printf("\nPart ID: %s\n", x.ID);
            printf("Warehouse Section: %s\n", x.sections);
            printf("Part Name: %s\n", x.name);
            printf("Supplier ID: %s\n", x.supplier_ID);
            printf("Initial Quantity: %d\n", x.initialQuantity);
            printf("Current QUantity: %d\n\n", x.quantity);
        }
    }
    fclose(fptr);
}