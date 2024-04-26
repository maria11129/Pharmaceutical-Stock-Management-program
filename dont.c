#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>

#define ENTER 13
#define BKSP 8
#define SPACE 32
#define TAB 9
#define DATE_LENGTH 11
#define MAX_MEDS 1000
#define MAX_NAME_LENGTH 60
#define MAX_BRAND_LENGTH 60
#define MIN_YEAR 2000

typedef struct {
    char medication_name[MAX_NAME_LENGTH];
    int available_quantity;
    int unit_price;
    int manufacturing_date[3]; // dd/mm/yy
    int expiry_date[3]; // dd/mm/yy
    char medication_brand[MAX_BRAND_LENGTH];
    int productid;
} med_info;

void append_to_file(const char *filename, const char *data) {
    FILE *fp = fopen(filename, "a");
    if (fp == NULL) {
        printf("Error opening file for appending.\n");
        return;
    }
    fprintf(fp, "%s\n", data);
    fclose(fp);
}

void wel_come(void);
void title(void);
void login();
void menu(void);
void title(void);
void deleteproduct();
void gotoxy(short x, short y)
{
	COORD pos ={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}

void add_item();
void read_item();
void search_and_select_medication(FILE *fp);
void search_item();
void edit_item();

med_info st;

void wel_come(void)

{
	time_t t;
	time(&t);
	printf("                                                                                                         \n");
	printf("---------------------------------------------------------------------------------------------------------\n");
	printf("\t\t\t\t\t%s",ctime(&t));
	printf("---------------------------------------------------------------------------------------------------------\n");
	printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
	printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
	printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
	printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
	printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
	printf("|\t\t\t\t==================================\t\t\t\t\t\t|\n");
	printf("|\t\t\t\t|\t     WELCOME TO \t |\t\t\t\t\t\t|\n");
	printf("|\t\t\t\t|\tPRODUCT MGMT SYSTEM\t |\t\t\t\t\t\t|\n");
	printf("|\t\t\t\t==================================\t\t\t\t\t\t|\n");
	printf("|\t\t\t\t            Address      \t\t\t\t\t\t\t|\n");
	printf("|\t\t\t\t\t     Number\t\t\t\t\t\t\t\t|\n");
	printf("|\t\t\t\t      \"WE BELIEVE IN QUALITY\"\t\t\t\t\t\t\t|\n");
	printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
	printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
	printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
	printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
	printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
	printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
	printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
	printf("|Press any key to continue.........\t\t\t\t\t\t\t\t\t\t|\n");

	printf("---------------------------------------------------------------------------------------------------------\n");

getch();
system("cls");
}

void login()
{

int a=0,i=0;
    char uname[10],c=' ';
    char pword[10],code[10];
    char user[10]="user";
    char pass[10]="pass";
    do
{

    printf("\n  ========================  LOGIN   ========================  ");
    printf(" \n                        USERNAME:-");
	scanf("%s", &uname);
	printf(" \n                        PASSWORD:-");
	while(i<10)
	{
	    pword[i]=getch();
	    c=pword[i];
	    if(c==13) break;
	    else printf("*");
	    i++;
	}
	pword[i]='\0';
	//char code=pword;
	i=0;
	//scanf("%s",&pword);
		if(strcmp(uname,"user")==0 && strcmp(pword,"pass")==0)
	{
	printf("  \n\n\n       WELCOME TO PHARMACEUTICAL STOCK MANAGEMENT SYSTEM !!!! LOGIN IS SUCCESSFUL");
	printf("\n\n\n\t\t\t\tPress any key to continue...");
	getch();//holds the screen
	break;
	}
	else
	{
		printf("\n        SORRY !!!!  LOGIN IS UNSUCESSFUL");
		a++;

		getch();//holds the screen

	}
}
	while(a<=2);
	if (a>2)
	{
		printf("\nSorry you have entered the wrong username and password for four times!!!");

		getch();

		}
		system("cls");
		menu();
}


void menu(void)
{
	int choice;
	system("cls");
	main:
	printf("\n======================== PHARMACEUTICAL STOCK MANAGEMENT SYSTEM ========================");
	printf("                                                                                          ");
	printf("                                                                                          ");
	printf("\n\t\tPress <1> Add medicine");
	printf("\n\t\tPress <2> Delete medicine");
	printf("\n\t\tPress <3> Search medicine");
	printf("\n\t\tPress <4> Show stock");
	printf("\n\t\tPress <5> Edit medecine");
	printf("\n\t\tPress <6> Exit!");

	printf("\n\n\t\tEnter your choice[1-6]");
	scanf("%i", &choice);

	system("cls");

	switch(choice)
	{
		case 1:
			add_item();
			break;
		case 2:
			deleteproduct();
			break;
		case 3:
			search_item();
			break;
		case 4:
			read_item();
			break;
		case 5:
			edit_item();
			break;
		case 6:
			printf("System Exit");
			exit(0);
			break;


		default:
			printf("Invalid Choice! System Exit\n");
			getch();
	}

}

void add_item() {
    int index, valid;
    char c;
    FILE *fp;
    med_info item; // Changed from 'st' to 'item'

    do {
        system("cls");
        printf("============ Enter Product Detail ============\n");
        int ID;
        fp = fopen("NextFile.bin", "r"); // Open in read mode to check if file exists
        if (fp != NULL) {
            fclose(fp);
            printf("\nProduct Code\t :");
            scanf("%i", &ID);
            fp = fopen("NextFile.bin", "r+"); // Reopen in read/write mode to check for existing product codes
            while (fscanf(fp, "%s %s %i %i %i %i/%i/%i %i/%i/%i %s",
                          item.medication_name, item.medication_brand, &item.available_quantity, &item.unit_price, &item.productid,
                          &item.manufacturing_date[0], &item.manufacturing_date[1], &item.manufacturing_date[2],
                          &item.expiry_date[0], &item.expiry_date[1], &item.expiry_date[2], item.medication_brand) != EOF) {
                if (ID == item.productid) {
                    printf("\n\tTHE PRODUCT CODE ALREADY EXISTS.\n");
                    fclose(fp); // Close the file after checking

                }
            }
            fseek(fp, 0, SEEK_END); // Move the file pointer to the end of the file for appending
            item.productid = ID;
        } else {
            item.productid = ID;
        }

        // Initialize medication details
        strcpy(item.medication_name, "Default Name");
        item.available_quantity = 0;
        item.unit_price = 0;
        item.manufacturing_date[0] = 26; // Day
        item.manufacturing_date[1] = 4;  // Month
        item.manufacturing_date[2] = 2024; // Year
        item.expiry_date[0] = 26; // Day
        item.expiry_date[1] = 4;  // Month
        item.expiry_date[2] = 2026; // Year

        // Additional input code for product name, company, price, quantity, etc.

        char data[100];
        sprintf(data, "%s %s %i %i %i %i/%i/%i %i/%i/%i %s", item.medication_name, item.medication_brand, item.available_quantity, item.unit_price, item.productid,
                item.manufacturing_date[0], item.manufacturing_date[1], item.manufacturing_date[2],
                item.expiry_date[0], item.expiry_date[1], item.expiry_date[2], item.medication_brand);
        append_to_file("NextFile.bin", data);
        printf("\nPress 'Enter' to add more items and any other key to go to the main menu");
    } while ((c = getchar()) == '\r');
    menu();
}

void search_and_select_medication(FILE *fp) {
    printf("\n");

    printf("Enter the name to search or the first letter of the medication you want to find: ");
    char target[40];
    fflush(stdin);
    gets(target);

    if (strlen(target) == 1) { // search by first letter
        char first_letter = toupper(target[0]);
        int found_count = 0;

        printf("\nFound medications:\n");
        printf("Name\tAvailable Quantity\tUnit Price\tMnf Date\t\tExp Date\t\tBrand\n");

        med_info m;
        while (fscanf(fp, "%s %s %i %i %i %i/%i/%i %i/%i/%i %s",
                      m.medication_name, m.medication_brand, &m.available_quantity, &m.unit_price, &m.productid,
                      &m.manufacturing_date[0], &m.manufacturing_date[1], &m.manufacturing_date[2],
                      &m.expiry_date[0], &m.expiry_date[1], &m.expiry_date[2], m.medication_brand) != EOF) {
            if (m.medication_name[0] == first_letter) {
                char manufacturing_date_str[DATE_LENGTH], expiry_date_str[DATE_LENGTH];
                sprintf(manufacturing_date_str, "%02d/%02d/%04d", m.manufacturing_date[0], m.manufacturing_date[1], m.manufacturing_date[2]);
                sprintf(expiry_date_str, "%02d/%02d/%04d", m.expiry_date[0], m.expiry_date[1], m.expiry_date[2]);
                printf("%-15s\t%-18d\t%-10d\t%-12s\t%-12s\t%-20s\n",
                       m.medication_name,
                       m.available_quantity,
                       m.unit_price,
                       manufacturing_date_str,
                       expiry_date_str,
                       m.medication_brand);
                found_count++;
            }
        }

        if (found_count == 0) {
            printf("No medication found starting with '%c'.\n", first_letter);
        }
    } else { // search by name
        int found = 0;
        med_info m;
        while (fscanf(fp, "%s %s %i %i %i %i/%i/%i %i/%i/%i %s",
                      m.medication_name, m.medication_brand, &m.available_quantity, &m.unit_price, &m.productid,
                      &m.manufacturing_date[0], &m.manufacturing_date[1], &m.manufacturing_date[2],
                      &m.expiry_date[0], &m.expiry_date[1], &m.expiry_date[2], m.medication_brand) != EOF) {
            if (strcmp(target, m.medication_name) == 0) {
                found = 1;
                char manufacturing_date_str[DATE_LENGTH], expiry_date_str[DATE_LENGTH];
                sprintf(manufacturing_date_str, "%02d/%02d/%04d", m.manufacturing_date[0], m.manufacturing_date[1], m.manufacturing_date[2]);
                sprintf(expiry_date_str, "%02d/%02d/%04d", m.expiry_date[0], m.expiry_date[1], m.expiry_date[2]);
                printf("\nRecord found\n");
                printf("Name\t\t:%s\nAvailable Quantity\t:%d\nUnit Price\t:%d\nMnf Date\t:%s\nExp Date\t:%s\nBrand\t:%s\n",
                       m.medication_name,
                       m.available_quantity,
                       m.unit_price,
                       manufacturing_date_str,
                       expiry_date_str,
                       m.medication_brand);
            }
        }

        if (!found) {
            printf("No record found\n");
        }
    }

    printf("\nPress any key to go to Main Menu!");
    while((getch()) =='\r');
    menu();
}

void deleteproduct() {
    char target[MAX_NAME_LENGTH];
    int found = 0;
    FILE *sourceFile, *tempFile;

    if ((sourceFile = fopen("NextFile.bin", "rb")) == NULL) {
        printf("NO RECORD ADDED.\n");
        menu();
    } else {
        tempFile = fopen("TempFile.bin", "wb+");
        printf("\nEnter name to Delete: ");
        scanf("%s", target);
        target[0] = toupper(target[0]);

        while (fread(&st, sizeof(med_info), 1, sourceFile) == 1) {
            if (strcmp(target, st.medication_name) != 0) {
                fwrite(&st, sizeof(med_info), 1, tempFile);
            } else {
                found = 1;
            }
        }

        fclose(sourceFile);
        fclose(tempFile);

        if (!found) {
            printf("\nRecord not Found\n");
        } else {
            remove("NextFile.bin");
            rename("TempFile.bin", "NextFile.bin");
            printf("\nRecord deleted\n");
        }

        printf("\nPress any key to go to Main Menu!");
        getch();
        menu();
    }
}



void read_item() {
    FILE *fp;
    med_info m;

    if ((fp = fopen("NextFile.bin", "r")) == NULL) {
        printf("NO RECORDS\n");
        printf("\nPress any key to go back to Menu.");
        getch();
        menu();
    } else {
        system("cls");
        printf("============================== STOCK DETAILS ==============================\n");
        printf("=============================================================================\n");
        printf("Product Name\t\tProduct Price\tProduct Company\tProduct CODE\tProduct Quantity\n");
        printf("=============================================================================\n");

        while (fscanf(fp, "%s %s %d %d %d %d/%d/%d %d/%d/%d %s\n", m.medication_name, m.medication_brand,
                      &m.available_quantity, &m.unit_price, &m.productid,
                      &m.manufacturing_date[0], &m.manufacturing_date[1], &m.manufacturing_date[2],
                      &m.expiry_date[0], &m.expiry_date[1], &m.expiry_date[2], m.medication_brand) != EOF) {
            printf("%-15s\t%-13d\t%-15s\t%-12d\t%-15d\n",
                   m.medication_name, m.unit_price, m.medication_brand, m.productid, m.available_quantity);
        }

        printf("=============================================================================\n");
        fclose(fp);
    }

    printf("\nPress any key to go to Main Menu!");
    getch();
    menu();
}


void edit_item() {
    int id;
    FILE *fp, *tempFile;
    med_info m;
    int found = 0;

    if ((fp = fopen("NextFile.bin", "rb")) == NULL) {
        printf("NO RECORD ADDED.\n");
        menu();
    } else {
        tempFile = fopen("TempFile.bin", "wb+");
        printf("Enter Product Code for edit: ");
        scanf("%i", &id);

        while (fread(&m, sizeof(med_info), 1, fp) == 1) {
            if (id == m.productid) {
                found = 1;
                printf("\n\t***** Record Found *****\n");
                printf("Product Name     : %s\n", m.medication_name);
                printf("Product Company  : %s\n", m.medication_brand);
                printf("Price            : %d\n", m.unit_price);
                printf("Product Code     : %d\n", m.productid);
                printf("Product Quantity : %d\n\n", m.available_quantity);

                // Input new data for the product
                printf("Enter New Product Name: ");
                scanf("%s", m.medication_name);
                printf("Enter New Product Company: ");
                scanf("%s", m.medication_brand);
                printf("Enter New Price [10-5000] Rupees: ");
                scanf("%d", &m.unit_price);
                printf("Enter New Product Quantity: ");
                scanf("%d", &m.available_quantity);

                printf("\nPress 'y' to save changes or any other key to cancel...");
                char edit = getch();
                if (edit == 'y' || edit == 'Y') {
                    fseek(tempFile, 0, SEEK_END);
                    fwrite(&m, sizeof(med_info), 1, tempFile);
                    printf("\n\n\t\tYOUR RECORD IS SUCCESSFULLY EDITED!!!\n");
                }
            } else {
                fwrite(&m, sizeof(med_info), 1, tempFile);
            }
        }

        fclose(fp);
        fclose(tempFile);

        if (!found) {
            printf("\n\nTHIS PRODUCT DOESN'T EXIST!!!!\n");
        }

        remove("NextFile.bin");
        rename("TempFile.bin", "NextFile.bin");

        printf("\nPress any key to go to Main Menu!");
        getch();
        menu();
    }
}
