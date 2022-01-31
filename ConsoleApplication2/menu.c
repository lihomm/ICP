#include "main.h"
#include "menu.h"
#include "main_functions.h"
#include "loop.h"


void menu() {
    unsigned int choice;
    parts* aop[3];
    supp* x = NULL, *head;
    fetch_data(aop);   
    x = supplier_list();
    char ID[8] = "";

    do {
        printf("----- AUTOMOBILE PARTS INVENTORY MANAGEMENT SYSTEM -----\n"
            "----- 1. Supplier Account Creation                 -----\n"
            "----- 2. Inventory Creation                        -----\n"
            "----- 3. Inventory Update                          -----\n"
            "----- 4. Inventory Checking                        -----\n"
            "----- 5. Searching                                 -----\n"
            "----- 6. Exit                                      -----\n");
        printf("Enter your choice : ");
        scanf_s("%d", &choice);
        rewind(stdin);
        switch (choice) {
        case 1:
            supplier_creation();
            x = supplier_list();
            if (x == NULL) {
                printf("fuck u");
            }
            break;
        case 2:
            strcpy(ID, check_sup());
            if (strcmp(ID, "") != 0) {
                printf("%s\n", ID);
                printf("Welcome to Inventory Creation System. Which of these models would you like to access? Enter [1/2/3]\n");
                inventory_creation(ID,aop,x);
            }
            else
                printf("Supplier ID does not exist.\n");
            break;
        case 3:
            if (check_sup() != NULL) {
                printf("Welcome to Inventory Update System. Which of these models would you like to access? Enter [1/2/3]\n");
                inventory_update(aop);
            }
            else
                printf("Supplier ID does not exist.\n");
            break;
        case 4:
            inventory_checking(aop);
            break;
        case 5:
            searching(x);
            break;
        case 6:
            break;
        default:
            printf("Invalid Input! Please enter again.\n");
        }  
    } while (choice != 6);
    for (int i = 0; i < 3; i++) {
        memory_free(aop[i]);
    }
}