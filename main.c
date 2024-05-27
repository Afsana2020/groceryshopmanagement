#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Define colors
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BOLD    "\033[1m"

// Define maximum number of products
#define MAX_PRODUCTS 20

// Define structures
struct Product {
    int id;
    char productName[50];
    int quantity;
    int price;
    char date[12];
} p;

struct Employee {
    int id;
    char employeeName[50];
    char address[50];
    char dept[50];
    int salary;
} e;

struct InvoiceProduct {
    char productName[50];
    int quantity;
    int price;
};

struct Invoice {
    char customerName[50];
    char phoneNumber[15];
    char billDate[12];
    struct InvoiceProduct products[MAX_PRODUCTS];
    int productCount;
    float totalAmount;
    float change;
    float pay;
};

// Declare file pointers
FILE *fp;
FILE *fe;

// Function prototypes
void productManagement();
void addP();
void updateP();
void removeP();
int checkProductId(int id);
int checkProductName(char *name);
void del(int id);
void displayP();
void employeeManagement();
void addE();
void updateE();
void removeE();
void delemp(int id);
void displayE();
void bill();
void create();
void paymentdetails(struct Invoice invoice);
void all_Inv();
void search();
void displayInvoice(struct Invoice invoice);

int main()
{

    int ch;
    while(1){
        system("cls"); //clear screen

         printf(BOLD BLUE"\t\t\t\t\t --------------------------------------------\n"RESET);
    printf(BOLD BLUE"\t\t\t\t\t|                                            |\n"RESET);
    printf(BOLD BLUE "\t\t\t\t\t      ===== Store Management System =====          \n"RESET);
    printf(BOLD BLUE"\t\t\t\t\t|                                            |\n");
    printf(BOLD BLUE"\t\t\t\t\t --------------------------------------------\n\n"RESET);
        printf( "\n" );
        printf(GREEN "\t\t\t\t\t\t1. Products Management\n" RESET);
        printf(GREEN "\t\t\t\t\t\t2. Employee Management\n" RESET);
        printf(GREEN "\t\t\t\t\t\t3. Bill\n" RESET);
        printf(RED "\t\t\t\t\t\t0. Exit\n" RESET);

        printf("\n\n");
        printf(BOLD BLUE"\t\t\t\t\tEnter Your Choice: "RESET);
        scanf("%d", &ch);

        switch(ch){
        case 0:
            exit(0);
        case 1:
             productManagement();
             break;
        case 2:
             employeeManagement();
             break;
        case 3:
             bill();
             break;
         default:
            printf(RED "Invalid Choice.....\n\n" RESET);
        }

        printf("\n\nPress Any key to Continue..");
        getch();

    }
    return 0;
}

// product starts
void productManagement(){

    system("cls");
    int ch;


   printf(BOLD BLUE"\t\t\t\t\t --------------------------------------------\n"RESET);
    printf(BOLD BLUE"\t\t\t\t\t|                                            |\n"RESET);
    printf(BOLD BLUE "\t\t\t\t\t        ===== Products Management =====          \n"RESET);
    printf(BOLD BLUE"\t\t\t\t\t|                                            |\n");
    printf(BOLD BLUE"\t\t\t\t\t --------------------------------------------\n\n"RESET);
        printf( "\n" );
    printf(GREEN "\t\t\t\t\t\t1. Add products\n" RESET);
    printf(GREEN "\t\t\t\t\t\t2. Display Products\n" RESET);
    printf(GREEN "\t\t\t\t\t\t3. Update Products\n" RESET);
    printf(GREEN "\t\t\t\t\t\t4. Remove Products\n" RESET);
    printf(GREEN "\t\t\t\t\t\t5. Back\n" RESET);
    printf(RED "\t\t\t\t\t\t0. Exit\n\n" RESET);

    printf(BOLD BLUE"\n\t\t\t\t\tEnter Your Choice: "RESET);
    scanf("%d", &ch);


    switch(ch){
        case 0:
            exit(0);
        case 1:
             addP();
             break;

        case 2:
             displayP();
             break;

        case 3:
             updateP();
             break;
        case 4:
             removeP();
             break;
        case 5:
            return 0;
        default:
            printf("\t\t\t\t\tInvalid Choice.....\n\n") ;
    }
    }



void addP()
{
    system("cls");
    char myDate[12];
    char finishInput[2];
    time_t t= time(NULL);
    struct tm tm= *localtime(&t);
    sprintf(myDate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900);
    strcpy(p.date, myDate);

    fp = fopen("product.txt", "ab");
    printf(BOLD BLUE"\t\t\t\t\t --------------------------------------------\n"RESET);
    printf(BOLD BLUE"\t\t\t\t\t|                                            |\n"RESET);
    printf(BOLD BLUE"\t\t\t\t\t           ===== Add Products =====          \n"RESET);
    printf(BOLD BLUE"\t\t\t\t\t|                                            |\n"RESET);
    printf(BOLD BLUE"\t\t\t\t\t --------------------------------------------\n\n"RESET);
        printf( "\n" );

P: do{
    rewind(fp);
    printf(BOLD BLUE"\n\n\tEnter Product Id (Press 0 to back to Main menu):"RESET);
    scanf("%d", &p.id);

    if(p.id==0) {main(); }

    // Check if the product with the same ID already exists
    if (checkProductId(p.id)) {
        printf(RED "\n\tError: Product with ID %d already exists. Please enter a different ID.\n\n\n" RESET, p.id);
        fclose(fp);

         int c;
        printf(BOLD GREEN"\tPress 0 to try again\n"RESET);
        printf(BOLD GREEN"\tPress any other number to return to main menu\n"RESET);
        printf(BOLD BLUE"\n\tEnter Your choice:"RESET);
        scanf("%d",&c);
        if(c==0){goto P;}
        else{return;}
    }


    printf(BOLD BLUE"\tEnter Product Name: "RESET);
    fflush(stdin);
    gets(p.productName);

    // Check if the product with the same name already exists
    if (checkProductName(p.productName)) {
        printf(RED"\n\tError: Product with name %s already exists. Please enter a different name.\n\n"RESET, p.productName);
        fclose(fp);

        int c;
        printf(BOLD GREEN"\tPress 0 to try again\n"RESET);
        printf(BOLD GREEN"\tPress any other number to return to main menu\n"RESET);
        printf(BOLD BLUE"\n\tEnter Your choice:"RESET);
        scanf("%d",&c);
        if(c==0){goto P;}
        else{main();}
    }

    printf(BOLD BLUE"\tEnter Product Quantity: "RESET);
    fflush(stdin); //cleans buffer
    scanf("%d", &p.quantity);

    printf(BOLD BLUE"\tEnter product price: "RESET);
    fflush(stdin);
    scanf("%d", &p.price);
    fwrite(&p, sizeof(p), 1, fp);

    printf(GREEN"\n\tProducts Added Successfully...\n"RESET);

    printf(BOLD BLUE"\n\tDo you want to add another product? (Y/N): "RESET);
    scanf("%s", finishInput);
    printf("\n\n");
    }while (strcmp(finishInput, "Y") == 0 || strcmp(finishInput, "y") == 0);

    printf(BOLD GREEN"\n\tAll products are added...."RESET);

    fclose(fp);


}

// Function to check if the product with the given ID already exists
int checkProductId(int id)
{
    FILE *tempFile = fopen("product.txt", "rb");
    if (tempFile == NULL) {
        printf(RED"\n\tError: Unable to open product file.\n"RESET);
        return 0;
    }

    struct Product tempProduct;
    while (fread(&tempProduct, sizeof(tempProduct), 1, tempFile) == 1) {
        if (tempProduct.id == id) {
            fclose(tempFile);
            return 1;
        }
    }

    fclose(tempFile);
    return 0;
}

// Function to check if the product with the given name already exists
int checkProductName(char *name)
{
    FILE *tempFile = fopen("product.txt", "rb");
    if (tempFile == NULL) {
        printf("Error: Unable to open product file.\n");
        return 0;
    }

    struct Product tempProduct;
    while (fread(&tempProduct, sizeof(tempProduct), 1, tempFile) == 1) {
        if (strcmp(tempProduct.productName, name) == 0) {
            fclose(tempFile);
            return 1;
        }
    }

    fclose(tempFile);
    return 0;
}

void updateP()
{
    int id, f;
    char choice;
    system("cls");
    printf(BOLD BLUE"\t\t\t\t\t --------------------------------------------\n"RESET);
    printf(BOLD BLUE"\t\t\t\t\t|                                            |\n"RESET);
    printf(BOLD BLUE "\t\t\t\t\t          ===== Update Products =====          \n"RESET);
    printf(BOLD BLUE"\t\t\t\t\t|                                            |\n");
    printf(BOLD BLUE"\t\t\t\t\t --------------------------------------------\n\n"RESET);
    printf( "\n\n" );
    printf(BOLD BLUE"\t\tEnter Product Id to update(Press 0 to back to Main menu):"RESET);
    scanf("%d", &id);

    printf( "\n\n" );

    if(id==0) {return 0; }

    else{

    fp = fopen("product.txt", "rb+");
    if (fp == NULL) {
        printf(RED"Error: Unable to open product file.\n"RESET);
        return;
    }

    // Get the existing product details
   struct Product existingProduct;
    while (fread(&existingProduct, sizeof(existingProduct), 1, fp) == 1) {
        if (id == existingProduct.id) {
            f = 1;
            break;
        }
    }

    if (f == 1) {
        // Display existing product details
        printf("\n\t\tExisting Product Details:\n");
        printf("\t\tProduct Id: %d\n", existingProduct.id);
        printf("\t\tProduct Name: %s\n", existingProduct.productName);
        printf("\t\tProduct Quantity: %d\n", existingProduct.quantity);
        printf("\t\tProduct Price: %d\n", existingProduct.price);

        printf(BOLD BLUE"\n\t\tDo you want to update this product? (Y/N): "RESET);
        fflush(stdin);
        scanf("%c", &choice);

       decideP: if (choice == 'Y' || choice == 'y') {
            printf(BOLD BLUE"\n\t\tWhich attribute do you want to update?\n"RESET);
            printf("\t\t1. Quantity\n");
            printf("\t\t2. Price\n");
            printf(BOLD BLUE"\n\t\tEnter your choice: "RESET);
            fflush(stdin);
            scanf("%c", &choice);

            switch (choice) {
                case '1':
                    printf(BOLD BLUE"\t\tEnter new product Quantity: "RESET);
                    fflush(stdin);
                    scanf("%d", &existingProduct.quantity);
                    break;
                case '2':
                    printf(BOLD BLUE"\t\tEnter new price: "RESET);
                    fflush(stdin);
                    scanf("%d", &existingProduct.price);
                    break;
                default:
                    printf(RED"\t\tInvalid choice.\n"RESET);
                    fclose(fp);
                    return;
             }
                    // Prompt for further changes
                    printf(BOLD BLUE"\n\t\tDo you want to make more changes? (Y/N): "RESET);
                    fflush(stdin);
                    scanf("%c", &choice);
                    if (choice == 'Y' || choice == 'y') {
                        goto decideP;
                        return;
                    }


            // Update product details
            fseek(fp, -sizeof(existingProduct), SEEK_CUR);
            fwrite(&existingProduct, sizeof(existingProduct), 1, fp);
            fclose(fp);
            printf(GREEN"\n\t\tProduct Updated..."RESET);
        } else {
            printf(RED"\n\t\tUpdate operation cancelled."RESET);
        }
    }
    else {
        printf(RED"\n\n\t\tProduct Not Found! "RESET);
    }
}
}



void removeP()
    {
    int id, f;
    system("cls");
    printf(BOLD BLUE"\t\t\t\t\t --------------------------------------------\n"RESET);
    printf(BOLD BLUE"\t\t\t\t\t|                                            |\n"RESET);
    printf(BOLD BLUE "\t\t\t\t\t           ===== Remove Products =====          \n"RESET);
    printf(BOLD BLUE"\t\t\t\t\t|                                            |\n");
    printf(BOLD BLUE"\t\t\t\t\t --------------------------------------------\n\n"RESET);
    printf( "\n" );
    printf(BOLD BLUE"\n\t\tEnter Product Id to remove(Press 0 to back to Main menu):"RESET);
    scanf("%d", &id);

    printf( "\n\n" );

    if(id==0) {return 0; }

    fp= fopen("product.txt", "rb");


     while(fread(&p, sizeof(p), 1, fp) == 1)
        {
            if(id== p.id)
            {
                f=1;
                fclose(fp);
                break;
            }
        }

        if(f==1){

            char choice;
            printf("\n\t\tProduct Details:\n");
            printf("\t\tProduct Id: %d\n", p.id);
            printf("\t\tProduct Name: %s\n", p.productName);
            printf("\t\tProduct Quantity: %d\n", p.quantity);
            printf("\t\tProduct Price: %d\n", p.price);

            printf(BOLD BLUE"\n\t\tDo you want to remove this product? (Y/N): "RESET);
            fflush(stdin);
            scanf("%c", &choice);

           if (choice == 'Y' || choice == 'y') {
            printf(GREEN"\n\t\tProduct Removed successfully...."RESET);
            del(id);
           }
           else{return;}
        }else{
            printf(RED"\n\n\t\tProduct Not Found! "RESET);
        }
    }

    void del(int id){
        int f=0;

        FILE *ft;
        fp =fopen("product.txt","rb");
        ft= fopen("temp.txt","wb");

        while(fread(&p, sizeof(p), 1, fp) == 1)
        {
            if(id==p.id)
            {
                f=1;
            }else{
                fwrite(&p, sizeof(p),1,ft);
            }
        }

        fclose(fp);
        fclose(ft);

        remove("product.txt");
        rename("temp.txt", "product.txt");

    }

// product ends here

// employee starts

void employeeManagement(){

    system("cls");
    int ch;

    printf(BOLD BLUE"\t\t\t\t\t --------------------------------------------\n"RESET);
    printf(BOLD BLUE"\t\t\t\t\t|                                            |\n"RESET);
    printf(BOLD BLUE "\t\t\t\t\t        ===== Employee Management =====          \n"RESET);
    printf(BOLD BLUE"\t\t\t\t\t|                                            |\n");
    printf(BOLD BLUE"\t\t\t\t\t --------------------------------------------\n\n"RESET);
        printf( "\n" );
    printf(GREEN "\t\t\t\t\t\t1. Add Employee\n" RESET);
    printf(GREEN "\t\t\t\t\t\t2. Display Employees\n" RESET);
    printf(GREEN "\t\t\t\t\t\t3. Update Employee\n" RESET);
    printf(GREEN "\t\t\t\t\t\t4. Remove Employee\n" RESET);
    printf(GREEN "\t\t\t\t\t\t5. Back\n" RESET);
    printf(RED "\t\t\t\t\t\t0. Exit\n\n" RESET);

    printf(BOLD BLUE"\n\n\t\t\t\t\tEnter Your Choice: "RESET);
    scanf("%d", &ch);


    switch(ch){
        case 0:
            exit(0);
        case 1:
             addE();
             break;

        case 2:
             displayE();
             break;

        case 3:
             updateE();
             break;
        case 4:
             removeE();
             break;
        case 5:
            return 0;
        default:
            printf(RED"\n\t\t\t\t\tInvalid Choice.....\n\n"RESET) ;
    }

}

void addE()
{

    system("cls");
    struct Employee newEmployee;
    int idExists;

    printf(BOLD BLUE"\t\t\t\t\t --------------------------------------------\n"RESET);
    printf(BOLD BLUE"\t\t\t\t\t|                                            |\n"RESET);
    printf(BOLD BLUE"\t\t\t\t\t           ===== Add Employee =====          \n"RESET);
    printf(BOLD BLUE"\t\t\t\t\t|                                            |\n"RESET);
    printf(BOLD BLUE"\t\t\t\t\t --------------------------------------------\n\n"RESET);
    printf( "\n" );

     fe = fopen("employee.txt", "ab");
    if (fe == NULL)
    {
        printf(RED"\n\t\tError: Unable to open employee file.\n"RESET);
        return;
    }


    do
    {
        rewind(fe);
        idExists = 0;
        printf(BOLD BLUE"\t\tEnter Employee Id(Press 0 to back to Main menu):"RESET);
        scanf("%d", &newEmployee.id);
        if(newEmployee.id==0) {return 0; }

        // Check if the entered ID already exists
        FILE *tempFile = fopen("employee.txt", "rb");
        if (tempFile != NULL)
        {
            struct Employee tempEmployee;
            while (fread(&tempEmployee, sizeof(tempEmployee), 1, tempFile) == 1)
            {
                if (newEmployee.id == tempEmployee.id)
                {
                    printf(RED"\n\t\tError: Employee with the same ID already exists. Please enter a unique ID.\n\n\n"RESET);
                    idExists = 1;
                    break;
                }
            }
            fclose(tempFile);
        }

    } while (idExists);

    printf(BOLD BLUE"\n\t\tEnter Employee's Name: "RESET);
    fflush(stdin);
    gets(newEmployee.employeeName);

    printf(BOLD BLUE"\n\t\tEnter Employee's Address: "RESET);
    fflush(stdin);
    gets(newEmployee.address);

    printf(BOLD BLUE"\n\t\tEnter Employee's Department: "RESET);
    fflush(stdin);
    gets(newEmployee.dept);

    printf(BOLD BLUE"\n\t\tEnter Employee's salary: "RESET);
    fflush(stdin);
    scanf("%d", &newEmployee.salary);

    printf(BOLD GREEN"\n\t\tNew employee is hired successfully..."RESET);

    fwrite(&newEmployee, sizeof(newEmployee), 1, fe);

    fclose(fe);

}

void displayE()
    {

    system("cls");


    printf(BOLD BLUE"\t\t\t\t\t --------------------------------------------\n"RESET);
    printf(BOLD BLUE"\t\t\t\t\t|                                            |\n"RESET);
    printf(BOLD BLUE"\t\t\t\t\t           ===== Employee List =====          \n"RESET);
    printf(BOLD BLUE"\t\t\t\t\t|                                            |\n"RESET);
    printf(BOLD BLUE"\t\t\t\t\t --------------------------------------------\n\n"RESET);
        printf( "\n\n\n" );
        printf(BOLD BLUE"   %-10s %-30s %-30s %-30s %-30s\n" , "Id", "Employee Name", "Department", "Salary", "Address"RESET);
        printf(BOLD BLUE"------------------------------------------------------------------------------------------------------------------------\n\n"RESET);

        fe = fopen("employee.txt", "rb");

        while(fread(&e, sizeof(e), 1, fe) == 1)
        {
            printf(BOLD GREEN"   %-10d  %-30s %-30s %-30d %-30s\n"RESET, e.id,e.employeeName,e.dept,e.salary, e.address);
        }

        fclose(fe);
        printf(RESET);

    }

//Update Employee

    void updateE()
{
    int id, f;
    char choice;

    system("cls");
    printf(BOLD BLUE"\t\t\t\t\t --------------------------------------------\n"RESET);
    printf(BOLD BLUE"\t\t\t\t\t|                                            |\n"RESET);
    printf(BOLD BLUE "\t\t\t\t\t          ===== Update Employee =====          \n"RESET);
    printf(BOLD BLUE"\t\t\t\t\t|                                            |\n");
    printf(BOLD BLUE"\t\t\t\t\t --------------------------------------------\n\n"RESET);
    printf( "\n\n" );
    printf(BOLD BLUE"\t\tEnter Employee Id to update(Press 0 to back to Main menu):"RESET);
    scanf("%d", &id);

    printf( "\n\n" );

    if(id==0) {return 0; }



    else{

    fe = fopen("employee.txt", "rb+");
    if (fe == NULL) {
        printf(RED"Error: Unable to open employee file.\n"RESET);
        return;
    }

    // Get the existing employee details
   struct Employee existingE;
    while (fread(&existingE, sizeof(existingE), 1, fe) == 1) {
        if (id == existingE.id) {
            f = 1;
            break;
        }
    }

    if (f == 1) {
        // Display existing Employee details
            printf(GREEN"\n\t\tEmployee Found!\n"RESET);
            printf(BOLD BLUE"\n\n\t\tEmployee Details:\n\n"RESET);
            printf("\t\tID: %d\n", existingE.id);
            printf("\t\tName: %s\n", existingE.employeeName);
            printf("\t\tDepartment: %s\n", existingE.dept);
            printf("\t\tAddress: %s\n", existingE.address);
            printf("\t\tSalary: %d\n", existingE.salary);


        printf(BOLD BLUE"\n\t\tDo you want to update this product? (Y/N): "RESET);
        fflush(stdin);
        scanf("%c", &choice);

       decideE: if (choice == 'Y' || choice == 'y') {

                printf(BOLD BLUE"\n\n\t\tSelect field to update:\n"RESET);
                printf("\n\t\t1. Department\n");
                printf("\t\t2. Address\n");
                printf("\t\t3. Salary\n");
                printf("\t\t4. Cancel\n");
                printf(BOLD BLUE"\n\t\tEnter your choice: "RESET);
                fflush(stdin);
               scanf("%c", &choice);

            switch (choice) {
                case '1':
                    printf(BOLD BLUE"\t\tEnter new department: "RESET);
                    fflush(stdin);
                    gets(existingE.dept);
                    break;
                case '2':
                    printf(BOLD BLUE"\t\tEnter new Address: "RESET);
                    fflush(stdin);
                    gets(existingE.address);
                    break;
                 case '3':
                    printf(BOLD BLUE"\t\tEnter new Salary: "RESET);
                    fflush(stdin);
                    scanf("%d", &existingE.salary);
                    break;
                 case '4':
                    printf(RED"\n\t\tUpdate canceled.\n"RESET);
                    fclose(fe);
                    return;
                default:
                    printf(RED"\t\tInvalid choice.\n"RESET);
                    fclose(fp);
                    return;
             }
                    // Prompt for further changes
                    printf(BOLD BLUE"\n\t\tDo you want to make more changes? (Y/N): "RESET);
                    fflush(stdin);
                    scanf("%c", &choice);
                    if (choice == 'Y' || choice == 'y') {
                        goto decideE;
                        return;
                    }


            // Update employee details
            fseek(fe, -sizeof(existingE), SEEK_CUR);
            fwrite(&existingE, sizeof(existingE), 1, fe);
            fclose(fe);
            printf(GREEN"\n\t\tEmployee Updated..."RESET);
        } else {
            printf(RED"\n\t\tUpdate operation cancelled."RESET);
        }
    }
    else {
        printf(RED"\n\n\t\tEmployee Not Found! "RESET);
    }
}
}








void removeE()
    {

    system("cls");
    int f;
    int id;
    char ch;

    system("cls");
    printf(BOLD BLUE"\t\t\t\t\t --------------------------------------------\n"RESET);
    printf(BOLD BLUE"\t\t\t\t\t|                                            |\n"RESET);
    printf(BOLD BLUE "\t\t\t\t\t          ===== Fire an Employee =====          \n"RESET);
    printf(BOLD BLUE"\t\t\t\t\t|                                            |\n");
    printf(BOLD BLUE"\t\t\t\t\t --------------------------------------------\n\n"RESET);
    printf( "\n\n" );
    printf(BOLD BLUE"\t\tEnter Employee Id to fire(Press 0 to back to Main menu):"RESET);
    scanf("%d", &id);

    printf( "\n\n" );

    if(id==0) {return 0; }



    fe = fopen("employee.txt", "rb");
    if (fe == NULL)
    {
        printf(RED"\n\t\tError: Unable to open employee file.\n"RESET);
        return;
    }



         while(fread(&e, sizeof(e), 1, fe) == 1)
        {
            if(id== e.id)
            {
                f=1;
                fclose(fe);
                break;
            }
        }

        if(f==1){

            char choice;
            printf("\n\t\tEmployee Details:\n");
            printf("\t\tEmployee Id: %d\n", e.id);
            printf("\t\tEmployee Name: %s\n", e.employeeName);
            printf("\t\tDepartment: %s\n", e.dept);
            printf("\t\tSalary: %d\n", e.salary);
            printf("\t\tAddress: %s\n", e.address);

            printf(BOLD BLUE"\n\t\tDo you want to fire this employee? (Y/N): "RESET);
            fflush(stdin);
            scanf("%c", &choice);

            if (choice == 'Y' || choice == 'y') {
            printf(GREEN"\n\t\tEmployee is fired successfully...."RESET);
            delemp(id);
            }
            else{return;}
        }else{
            printf(RED"\n\n\t\tEmployee with this name does not exist! "RESET);
        }
    }

void delemp(int id){
        int f=0;

        FILE *ft;
        fe =fopen("employee.txt","rb");
        ft= fopen("etemp.txt","wb");

        while(fread(&e, sizeof(e), 1, fe) == 1)
        {
            if(id==e.id)
            {
                f=1;
            }else{
                fwrite(&e, sizeof(e),1,ft);
            }
        }

        fclose(fe);
        fclose(ft);

        remove("employee.txt");
        rename("etemp.txt", "employee.txt");

    }

// employee ends here

//bill

void bill(){

    system("cls");
    int ch;

    printf(BOLD BLUE"\t\t\t\t\t --------------------------------------------\n"RESET);
    printf(BOLD BLUE"\t\t\t\t\t|                                            |\n"RESET);
    printf(BOLD BLUE "\t\t\t\t\t             ===== Billing =====          \n"RESET);
    printf(BOLD BLUE"\t\t\t\t\t|                                            |\n");
    printf(BOLD BLUE"\t\t\t\t\t --------------------------------------------\n\n"RESET);
    printf(GREEN "\t\t\t\t\t\t1. Create Invoice\n" RESET);
    printf(GREEN "\t\t\t\t\t\t2. Display All Invoices\n" RESET);
    printf(GREEN "\t\t\t\t\t\t3. Search Invoice\n" RESET);
    printf(GREEN "\t\t\t\t\t\t4. Back\n" RESET);
    printf(RED "\t\t\t\t\t\t0. Exit\n\n" RESET);

    printf(BOLD BLUE"\n\n\t\t\t\t\tEnter Your Choice: "RESET);
    scanf("%d", &ch);


    switch(ch){
        case 0:
            exit(0);
        case 1:
             create();
             break;

        case 2:
             all_Inv();
             break;

        case 3:
             search();
             break;
        case 4:
            return 0;
        default:
            printf(RED"\n\t\t\t\t\tInvalid Choice.....\n\n"RESET) ;
    }
}

void create() {
    system("cls");
    displayP();

    // Initialize invoice
    printf("\n\n");
    printf(BOLD BLUE "\t\t\t\t\t --------------------------------------------\n" RESET);
    printf(BOLD BLUE "\t\t\t\t\t|                                            |\n" RESET);
    printf(BOLD BLUE "\t\t\t\t\t         ===== Create an Invoice =====          \n" RESET);
    printf(BOLD BLUE "\t\t\t\t\t|                                            |\n" RESET);
    printf(BOLD BLUE "\t\t\t\t\t --------------------------------------------\n\n" RESET);
    printf("\n\n");

    struct Invoice invoice;
    invoice.productCount = 0;
    invoice.totalAmount = 0;

    // Get customer details
    printf(BOLD BLUE "\n\t\tEnter Customer Name: " RESET);
    fflush(stdin);
    gets(invoice.customerName);

    printf(BOLD BLUE "\n\t\tEnter Phone Number: " RESET);
    fflush(stdin);
    scanf("%s", invoice.phoneNumber);

    // Get current date
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(invoice.billDate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    // Get product details and calculate total amount
    char finishInput[2];

    do {
        int id;
        int quantity;

        printf(BOLD BLUE "\n\t\tEnter Product ID: " RESET);
        scanf("%d", &id);

        printf(BOLD BLUE "\n\t\tEnter Quantity: " RESET);
        scanf("%d", &quantity);

        // Check if the product exists in the file
        fp = fopen("product.txt", "rb+");
        if (fp == NULL) {
            printf(RED "/n/t/tError: Unable to open product file.\n" RESET);
            return;
        }

        int found = 0;
        while (fread(&p, sizeof(p), 1, fp) == 1) {
            if (id == p.id) {
                found = 1;
                if (p.quantity >= quantity) {
                    // Add product to invoice
                    strcpy(invoice.products[invoice.productCount].productName, p.productName);
                    invoice.products[invoice.productCount].quantity = quantity;
                    invoice.products[invoice.productCount].price = p.price;
                    invoice.totalAmount += p.price * quantity;
                    invoice.productCount++;
                    // Update product quantity
                    p.quantity -= quantity;
                    fseek(fp, -sizeof(p), SEEK_CUR);
                    fwrite(&p, sizeof(p), 1, fp);
                    break;
                } else {
                    printf(RED "\n\t\tError: Insufficient quantity in stock for %d.\n" RESET, id);
                }
            }
        }
        fclose(fp);

        if (!found) {
            printf(RED "\n\t\tError: Product %d not found.\n" RESET, id);
        }

        printf(BOLD BLUE "\n\t\tDo you want to add another product? (Y/N): " RESET);
        fflush(stdin);
        scanf("%s", finishInput);
    } while (strcmp(finishInput, "Y") == 0 || strcmp(finishInput, "y") == 0);

    // Write invoice to file
    FILE *invoiceFile = fopen("invoice.txt", "a");
    if (invoiceFile == NULL) {
        printf(RED "\n\t\tError: Unable to open invoice file.\n" RESET);
        return;
    }

    // Write invoice details along with product information
    fprintf(invoiceFile, "%s,%s,%s,%.2f", invoice.customerName, invoice.phoneNumber, invoice.billDate, invoice.totalAmount);
    for (int i = 0; i < invoice.productCount; i++) {
        fprintf(invoiceFile, ",%s,%d,%d", invoice.products[i].productName, invoice.products[i].quantity, invoice.products[i].price);
    }
    fprintf(invoiceFile, "\n");

    paymentdetails(invoice);


    // Close file
    fclose(invoiceFile);
}

void paymentdetails(struct Invoice invoice)
{
payM:
     printf(BOLD BLUE"\n\n\t\tPayment details:\n\n"RESET);
     printf(BOLD GREEN"\t\t\Total Amount: %.2f\n\n"RESET, invoice.totalAmount);
     printf(BOLD BLUE"\t\tEnter payment by customer: "RESET);
     scanf("%f",&invoice.pay);

     if(invoice.pay<invoice.totalAmount)
     {
         printf(BOLD RED"\t\t\Payment is not enough......\n\t\tPay again....."RESET);
         goto payM;
     }
     else{
     invoice.change=invoice.pay-invoice.totalAmount;
     printf(BOLD GREEN"\n\t\tPayment Complete........\n"RESET);
     printf(BOLD BLUE"\n\t\tCreate Invoice?(Y/N): "RESET);
     char in;
     fflush(stdin);
     scanf(" %c",&in);
     if(in=='y'||in=='Y') { displayInvoice(invoice);}
     }


}

// Function to display invoice
void displayInvoice(struct Invoice invoice) {
    system("cls");

    printf("\n\n");
    printf(BOLD CYAN"\t\t\t\t=================================================\n"RESET);
    printf(BOLD CYAN"\t\t\t\t-------------------------------------------------\n"RESET);
    printf(BOLD CYAN"\t\t\t\t|                                               |\n"RESET);
    printf(BOLD CYAN"\t\t\t\t            ======= Invoice =======        \n"RESET);
    printf(BOLD CYAN"\t\t\t\t|                                               |\n"RESET);
    printf(BOLD CYAN"\t\t\t\t-------------------------------------------------\n"RESET);
    printf("\n");
    printf("\t\t\t\tCustomer Name: %s\n", invoice.customerName);
    printf("\t\t\t\tPhone Number: %s\n", invoice.phoneNumber);
    printf("\t\t\t\tBill Date: %s\n\n", invoice.billDate);
    printf(BOLD CYAN"\t\t\t\t-------------------------------------------------\n"RESET);
    printf(BOLD CYAN"\t\t\t\t%-30s %-10s %-10s\n", "Product Name", "Quantity", "Price"RESET);
    printf(BOLD CYAN"\t\t\t\t-------------------------------------------------\n"RESET);
    for (int i = 0; i < invoice.productCount; i++) {
        printf("\t\t\t\t%-30s %-10d %-10d\n", invoice.products[i].productName, invoice.products[i].quantity,
               invoice.products[i].price);
    }
    printf(BOLD CYAN"\t\t\t\t-------------------------------------------------\n"RESET);
    printf("\t\t\t\tTotal Amount: \t\t\t\t%.2f\n", invoice.totalAmount);
    printf("\t\t\t\tPaid Amount: \t\t\t\t%.2f\n", invoice.pay);
    printf(BOLD CYAN"\t\t\t\t-------------------------------------------------\n"RESET);
    printf(BOLD CYAN"\t\t\t\t-------------------------------------------------\n"RESET);
    printf("\t\t\t\tChange: \t\t\t\t%.2f\n", invoice.change);
    printf(BOLD CYAN"\t\t\t\t=================================================\n"RESET);
    printf("\n\n\n");
    printf(BOLD GREEN"\t\t\t\t\t   Thanks for buying from us!   \n"RESET);
    printf(BOLD CYAN"\t\t\t\t=================================================\n"RESET);

}

// Function to display products
void displayP() {
    system("cls");
    printf(BOLD BLUE "\t\t\t\t\t --------------------------------------------\n" RESET);
    printf(BOLD BLUE "\t\t\t\t\t|                                            |\n" RESET);
    printf(BOLD BLUE "\t\t\t\t\t           ===== Products List =====          \n" RESET);
    printf(BOLD BLUE "\t\t\t\t\t|                                            |\n" RESET);
    printf(BOLD BLUE "\t\t\t\t\t --------------------------------------------\n\n" RESET);
    printf("\n\n\n");
    printf(BOLD BLUE "   %-10s %-30s %-30s %-30s %s\n", "Id", "Product Name", "Quantity", "Price", "Date" RESET);
    printf(BOLD BLUE "-----------------------------------------------------------------------------------------------------------------------\n\n" RESET);

    fp = fopen("product.txt", "rb");
    if (fp == NULL) {
        printf(RED "\n\t\tError: Unable to open product file.\n" RESET);
        return;
    }

    while (fread(&p, sizeof(p), 1, fp) == 1) {

            printf(GREEN "   %-10d %-30s %-30d %-30d %s\n" RESET, p.id, p.productName, p.quantity, p.price, p.date);

    }

    fclose(fp);
}


void all_Inv() {
    system("cls");
    FILE *invoiceFile = fopen("invoice.txt", "r");
    printf("\n\n");
        printf(BOLD GREEN"\t\t\t\t-------------------------------------------------\n"RESET);
        printf(BOLD GREEN"\t\t\t\t|                                               |\n"RESET);
        printf(BOLD GREEN"\t\t\t\t        ======== List of Invoices ========        \n"RESET);
        printf(BOLD GREEN"\t\t\t\t|                                               |\n"RESET);
        printf(BOLD GREEN"\t\t\t\t-------------------------------------------------\n"RESET);
        printf("\n");
         printf("\n\n========================================================================================================================");
        printf("\n========================================================================================================================\n\n");

    if (invoiceFile == NULL) {
        printf("Error: Unable to open invoice file.\n");
        return;
    }

    int i=1;
    char line[1000];
    while (fgets(line, sizeof(line), invoiceFile)) {
        struct Invoice invoice;
        invoice.productCount = 0;
        invoice.totalAmount = 0;

        char *token = strtok(line, ",");
        strcpy(invoice.customerName, token);

        token = strtok(NULL, ",");
        strcpy(invoice.phoneNumber, token);

        token = strtok(NULL, ",");
        strcpy(invoice.billDate, token);

        token = strtok(NULL, ",");
        invoice.totalAmount = atof(token);

        printf("\n\n");
        printf(BOLD CYAN"\t\t\t\t=================================================\n"RESET);
        printf(BOLD CYAN"\t\t\t\t-------------------------------------------------\n"RESET);
        printf(BOLD CYAN"\t\t\t\t|                                               |\n"RESET);
        printf(BOLD CYAN"\t\t\t\t          ======== Invoice %d ========        \n"RESET,i);
        printf(BOLD CYAN"\t\t\t\t|                                               |\n"RESET);
        printf(BOLD CYAN"\t\t\t\t-------------------------------------------------\n"RESET);
        printf("\n");
        printf("\t\t\t\tCustomer Name: %s\n", invoice.customerName);
        printf("\t\t\t\tPhone Number: %s\n", invoice.phoneNumber);
        printf("\t\t\t\tBill Date: %s\n\n", invoice.billDate);

        printf(BOLD CYAN"\t\t\t\t        ======= Purchased Products =======        \n"RESET);
        while ((token = strtok(NULL, ",")) != NULL) {
            struct InvoiceProduct product;
            strcpy(product.productName, token);

            token = strtok(NULL, ",");
            product.quantity = atoi(token);

            token = strtok(NULL, ",");
            product.price = atoi(token);

            printf("\t\t\t\t%-30s %-10d %-10d\n", product.productName, product.quantity, product.price);

            invoice.products[invoice.productCount++] = product;
        }
        printf(BOLD CYAN"\t\t\t\t-------------------------------------------------\n"RESET);
        printf(BOLD CYAN"\t\t\t\t-------------------------------------------------\n"RESET);
        printf("\t\t\t\tTotal Amount: \t\t\t\t%.2f\n", invoice.totalAmount);




        printf(BOLD CYAN"\t\t\t\t=================================================\n\n"RESET);
        printf("\n\n========================================================================================================================");
        printf("\n========================================================================================================================\n\n");
        i++;
    }

    fclose(invoiceFile);
}

void search() {
    system("cls");

        printf("\n\n");
        printf(BOLD BLUE"\t\t\t\t-------------------------------------------------\n"RESET);
        printf(BOLD BLUE"\t\t\t\t|                                               |\n"RESET);
        printf(BOLD BLUE"\t\t\t\t        ======== Search Invoice ========        \n"RESET);
        printf(BOLD BLUE"\t\t\t\t|                                               |\n"RESET);
        printf(BOLD BLUE"\t\t\t\t-------------------------------------------------\n"RESET);
        printf("\n");
        printf("========================================================================================================================\n\n");

    char searchName[50];
    printf(BOLD BLUE"\n\t\t\t\tEnter customer name to search invoices: "RESET);
    fflush(stdin);
    gets(searchName);

    FILE *invoiceFile = fopen("invoice.txt", "r");
    if (invoiceFile == NULL) {
        printf(RED"\n\n\t\t\t\tError: Unable to open invoice file.\n"RESET);
        return;
    }

    char line[1000];
    int i=1,f=0;
    while (fgets(line, sizeof(line), invoiceFile)) {
        struct Invoice invoice;
        invoice.productCount = 0;
        invoice.totalAmount = 0;

        char *token = strtok(line, ",");
        strcpy(invoice.customerName, token);

        if (strcmp(invoice.customerName, searchName) == 0) {
            f=1;
            printf(BOLD CYAN"\n\t\t\t\t =================== Invoice %d ===================\n\n"RESET,i);
            printf("\t\t\t\tCustomer Name: %s\n", invoice.customerName);

            token = strtok(NULL, ",");
            strcpy(invoice.phoneNumber, token);
            printf("\t\t\t\tPhone Number: %s\n", invoice.phoneNumber);

            token = strtok(NULL, ",");
            strcpy(invoice.billDate, token);
            printf("\t\t\t\tBill Date: %s\n", invoice.billDate);

            token = strtok(NULL, ",");
            invoice.totalAmount = atof(token);



            printf(BOLD CYAN"\n\t\t\t\t================== Product List ==================\n"RESET);
            while ((token = strtok(NULL, ",")) != NULL) {
                struct InvoiceProduct product;
                strcpy(product.productName, token);

                token = strtok(NULL, ",");
                product.quantity = atoi(token);

                token = strtok(NULL, ",");
                product.price = atoi(token);

                printf("\t\t\t\t%-30s %-10d %-10d\n", product.productName, product.quantity, product.price);

                invoice.products[invoice.productCount++] = product;
            }
            printf(BOLD CYAN"\t\t\t\t-------------------------------------------------\n"RESET);

            printf("\t\t\t\tTotal Amount: \t\t\t\t%.2f\n", invoice.totalAmount);

            printf(BOLD CYAN"\t\t\t\t=================================================\n"RESET);

            printf("\n\n========================================================================================================================");
            printf("========================================================================================================================\n\n");
        }
        i++;
    }

    if(f==0){printf(RED"\n\n\t\t\t\tNot found!"RESET);}


    fclose(invoiceFile);
}


//bill ends here
