typedef struct parts {
    char ID[10];
    char sections[5];
    char name[20];
    char supplier_ID[10];
    int initialQuantity;
    int quantity;
    struct parts* next;
}parts;

typedef struct supp {
    char sup_ID[8];
    char name[30];
    char contact_num[15];
    char parts_ID[100];
    struct supp* next;
}supp;

void print_list(parts*);
void fetch_data(parts**);
supp* supplier_list();
void print_supp(supp*, char*);
void memory_free(parts* x);
int check_file(FILE* fptr);