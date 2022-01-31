#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "menu.h"
int choice=0;

int loop(){
	rewind(stdin);
	printf("\nDo you still want to use the service? [1/2]\n");
	printf("1. Yes\n");
	printf("2. No\n");
	printf("Enter choice: ");
	scanf_s("%d", &choice);
	return (choice == 1);
}
