#include "linked_list.h"

int car_menu();
void supplier_creation();
void inventory_creation(char*, parts** aop, supp* p);
void inventory_update(parts**);
void inventory_checking(parts**);
void searching(supp* x);
char* check_sup();
int section_menu();
void print_list2(parts**, int);
void line_search(FILE* fptr, char* ID);