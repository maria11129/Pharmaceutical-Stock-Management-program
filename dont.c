#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include <stdbool.h>

#define ENTER 13
#define BKSP 8
#define SPACE 32
#define TAB 9
#define MIN_YEAR 2000

typedef int date[3]; // dd/mm/yy

typedef struct
{
	char productname[40],productcomp[40],c;
	int productid;
	int price;
	int Qnt;
	date manufacturing_date;
    date expiry_date;
}st;

void wel_come(void);
void title(void);
void login();
void menu(void);
void title(void);
void deleteproduct(void);
void gotoxy(short x, short y)
{
	COORD pos ={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}

void add_item();
void read_item();
void search_item();
void edit_item();
void main(void)

{
wel_come();
login();
}
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
	printf("|\t\t\t\t|\tPHARMACEUTICAL STOCK MANAGEMENT SYSTEM\t |\t\t\t\t\t\t|\n");
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
	printf("  \n\n\n       WELCOME TO PRODUCT MANAGEMENT SYSTEM !!!! LOGIN IS SUCCESSFUL");
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
	printf("\n======================== Pharmaceutical Stock Management System ========================");
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
bool isExpired(int expiry_date[3]) {
    int current_date[3] = {2024, 4, 27};

    if (expiry_date[2] < current_date[2] ||
        (expiry_date[2] == current_date[2] && expiry_date[1] < current_date[1]) ||
        (expiry_date[2] == current_date[2] && expiry_date[1] == current_date[1] && expiry_date[0] < current_date[0])) {
        return true;
    }
    return false;
}

#include <stdbool.h>

void add_item() {
    FILE *fp;
    st st;
    int index, valid;
    char c;
    bool expired;
    fp = fopen("NextFile.bin", "a");
    do {
        system("cls");
        printf("============ Enter Product Detail ============\n");
        do
		{
			fflush(stdin);
			printf("\nm=Medecine Name\t :");
			gets(st.productname); // get input string
			st.productname[0]=toupper(st.productname[0]);
			//iterate for every character in string
			for (index=0; index<strlen(st.productname); ++index)
			{	//check if character is valid or not
				if(isalpha(st.productname[index]))
					valid = 1;
				else
				{
					valid = 0;
					break;
				}
			}
			if (!valid)
			{
				printf("\n Name contain invalid character. Please 'Enter' again");
				getch();


			}
		}while(!valid);	//while end here


        // Input validation for Medicine Brand
        do
		{
			char productcomp[40];
			fflush(stdin);
			printf("\nMedecine brand\t :");
			gets(st.productcomp); // get input string
			st.productcomp[0]=toupper(st.productcomp[0]);
			for (index=0; index<strlen(st.productcomp); ++index)
			{
				if(isalpha(st.productcomp[index]))
					valid = 1;
				else
				{
					valid = 0;
					break;
				}
			}
			if (!valid)
			{
				printf("\n Name contain invalid character. Please 'Enter' again");
				getch();
			}
		}while(!valid);

        // Input validation for Price
        do {
            printf("\nPrice [Algerian Dinar]: ");
            scanf("%i", &st.price);
            if (st.price < 0 || st.price > 10000) {
                printf("Invalid price. Please enter a price between 0 and 10000.\n");
            }
        } while (st.price < 0 || st.price > 10000);

        // Input validation for Quantity
        do {
            printf("\nQuantity [1-500]: ");
            scanf("%i", &st.Qnt);
            if (st.Qnt < 1 || st.Qnt > 500) {
                printf("Invalid quantity. Please enter a quantity between 1 and 500.\n");
            }
        } while (st.Qnt < 1 || st.Qnt > 500);

        // Input validation for Manufacturing Date
        printf("\nManufacturing Date (DD/MM/YYYY): ");
        printf("\nYear: ");
        do {
            scanf("%d", &st.manufacturing_date[2]);
            if (st.manufacturing_date[2] < MIN_YEAR || st.manufacturing_date[2] > 2024) {
                printf("Invalid year. Please try again: ");
            }
        } while (st.manufacturing_date[2] < MIN_YEAR || st.manufacturing_date[2] > 2024);

        printf("Month: ");
        do {
            scanf("%d", &st.manufacturing_date[1]);
            if (st.manufacturing_date[1] < 1 || st.manufacturing_date[1] > 12) {
                printf("Invalid month. Please try again: ");
            }
        } while (st.manufacturing_date[1] < 1 || st.manufacturing_date[1] > 12);

        printf("Day: ");
        do {
            scanf("%d", &st.manufacturing_date[0]);
            if (st.manufacturing_date[0] < 1 || st.manufacturing_date[0] > 31) {
                printf("Invalid day. Please try again: ");
            }
        } while (st.manufacturing_date[0] < 1 || st.manufacturing_date[0] > 31);

        // Input validation for Expiry Date
        printf("\nExpiry Date (DD/MM/YYYY): ");
        printf("\nYear: ");
        do {
            scanf("%d", &st.expiry_date[2]);
            if (st.expiry_date[2] < MIN_YEAR || st.expiry_date[2] > 2024) {
                printf("Invalid year. Please try again: ");
            }
        } while (st.expiry_date[2] < MIN_YEAR || st.expiry_date[2] > 2024);

        printf("Month: ");
        do {
            scanf("%d", &st.expiry_date[1]);
            if (st.expiry_date[1] < 1 || st.expiry_date[1] > 12) {
                printf("Invalid month. Please try again: ");
            }
        } while (st.expiry_date[1] < 1 || st.expiry_date[1] > 12);

        printf("Day: ");
        do {
            scanf("%d", &st.expiry_date[0]);
            if (st.expiry_date[0] < 1 || st.expiry_date[0] > 31) {
                printf("Invalid day. Please try again: ");
            }
        } while (st.expiry_date[0] < 1 || st.expiry_date[0] > 31);

        expired = isExpired(st.expiry_date);

        if (expired) {
            printf("Medication is expired. Not added to the list.\n");
        } else {
            printf("Medication added to the list.\n");
            fprintf(fp, "\n%s %s %i %i %i %d/%d/%d %d/%d/%d", st.productname, st.productcomp, st.price, st.productid, st.Qnt,
                st.manufacturing_date[0], st.manufacturing_date[1], st.manufacturing_date[2],
                st.expiry_date[0], st.expiry_date[1], st.expiry_date[2]);
        }

        fclose(fp);

        printf("\nPress 'Enter' to add more items or any other key to go to the main menu.\n");

    }while ((c = getch()) == '\r');

    menu();
}


void search_item() {
    FILE *fp;
    st st;
    char search_key[50];
    int found = 0;

    printf("\nEnter the first characters of the medication name to search: ");
    fflush(stdin);
    fgets(search_key, sizeof(search_key), stdin);
    search_key[strcspn(search_key, "\n")] = '\0'; // Remove newline character
    search_key[0] = toupper(search_key[0]);  // Ensure the first character is uppercase

    fp = fopen("NextFile.dat", "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("Search results:\n");
    while (fscanf(fp, "%s %s %i %i %i\n", st.productname, st.productcomp, &st.price, &st.productid, &st.Qnt) != EOF) {
        if (strstr(st.productname, search_key) != NULL) {
            printf("Name: %s, Quantity: %d, Price: %d\n", st.productname, st.Qnt, st.price);
            found = 1;
        }
    }

    if (!found) {
        printf("No medication found with the provided search key.\n");
    }

    fclose(fp);

    printf("\nPress any key to go to the Main Menu!\n");
    while (getchar() != '\n');  // Clear input buffer
    getchar();  // Wait for user input
    menu();  // Assuming you have a function named menu() to go back to the main menu
}


void deleteproduct(void)
{
	char target[40];
	int found = 0;
	st st;
	FILE *sfile, *tfile;

	printf("\n Enter name to Delete: ");
	fflush(stdin);
	fgets(target, sizeof(target), stdin);
	target[strcspn(target, "\n")] = '\0'; // Remove newline character

	sfile = fopen("NextFile.dat", "r");
	if (sfile == NULL) {
		printf("File not found or cannot be opened.\n");
		getch();
		menu();
		return;
	}

	tfile = fopen("TempFile.dat", "w");
	if (tfile == NULL) {
		printf("Temporary file cannot be created.\n");
		fclose(sfile);
		getch();
		menu();
		return;
	}

	while (fscanf(sfile, "%s %s %i %i %i\n", st.productname, st.productcomp, &st.price, &st.productid, &st.Qnt) != EOF)
	{
		if (strcmp(target, st.productname) == 0)
		{
			found = 1;
		}
		else
		{
			fprintf(tfile, "%s %s %i %i %i\n", st.productname, st.productcomp, st.price, st.productid, st.Qnt);
		}
	}

	fclose(sfile);
	fclose(tfile);

	if (!found)
	{
		printf("\n Record not Found");
		remove("TempFile.dat"); // Remove the temporary file
		getch();
		menu();
	}
	else
	{
		printf("\n Record deleted");
		remove("NextFile.dat");
		rename("TempFile.dat", "NextFile.dat");
	}

	printf("\nPress any key to go to Main Menu!");
	while ((st.c = getch()) == '\r');
	menu();
}

void read_item()
{
	FILE *f;
	st st;
	int i, q;
	if ((f = fopen("NextFile.dat", "r")) == NULL)
	{
		gotoxy(10, 3);
		printf("NO RECORDS");
		printf("\n\t\tPress any key to go back to Menu.");
		getch();
		menu();
	}
	else
	{
		gotoxy(0, 5);
		for (i = 0; i < 120; i++)
		{
			printf("-");
		}
		gotoxy(5, 6);
		printf("Medecine Name");
		gotoxy(25, 6);
		printf("Medecine Price");
		gotoxy(40, 6);
		printf("Meddecine company");
		gotoxy(60, 6);
		printf("Medecine quantity");
		gotoxy(80, 6);
		printf("Manufacturing date");
		gotoxy(100, 6);
		printf("Expiry date\n");

		for (i = 0; i < 120; i++)
		{
			printf("-");
		}
		q = 8;
		while (fscanf(f, "%s %s %i %i %i %d/%d/%d %d/%d/%d", st.productname, st.productcomp, &st.price, &st.productid, &st.Qnt,
					  &st.manufacturing_date[0], &st.manufacturing_date[1], &st.manufacturing_date[2],
					  &st.expiry_date[0], &st.expiry_date[1], &st.expiry_date[2]) != EOF)
		{
			gotoxy(5, q);
			printf("%s", st.productname);
			gotoxy(25, q);
			printf("%i", st.price);
			gotoxy(40, q);
			printf("%s", st.productcomp);
			gotoxy(60, q);
			printf("%i", st.Qnt);
			gotoxy(80, q);
			printf("%02d/%02d/%04d", st.manufacturing_date[0], st.manufacturing_date[1], st.manufacturing_date[2]);
			gotoxy(100, q);
			printf("%02d/%02d/%04d", st.expiry_date[0], st.expiry_date[1], st.expiry_date[2]);
			q++;
		}
		printf("\n");
		for (i = 0; i < 120; i++)
			printf("-");
	}
	fclose(f);

	printf("\nPress any key to go to Main Menu!");
	getch();
	menu();
}

void edit_item()
{
	int index, valid;
	st st;
	char target[40];
	FILE *fp, *rp;
	int a=0;
	int id;
	char edit;
	long int size=sizeof(st);
	if((fp=fopen("NextFile.dat","r+"))==NULL)
	{
		printf("NO RECORD ADDED.");
		menu();
	}
	else
	{
		rp = fopen("TempFile.dat","a");
		system("cls");
		printf("Enter Product Code for edit:");
		scanf("%i",&id);
		fflush(stdin);
		while(fscanf(fp,"%s %s %i %i %i\n", st.productname,st.productcomp, &st.price, &st.productid,&st.Qnt)!=EOF)
		{
			if(id==st.productid)
			{

				a=1;
				printf("\n\t*****  Record Found  *****");
				printf("\nProduct Name\t\t: %s",st.productname);
				printf("\nProduct Company\t\t: %s",st.productcomp);
				printf("\nPrice\t\t\t: %i",st.price);
				printf("\nProduct Code\t\t: %i",st.productid);
				printf("\nProduct Quantity\t:%i",st.Qnt);

				printf("\n\n\t*** New Record ***");
			do
				{

					fflush(stdin);
					printf("\nNew Product Name\t\t: ");
					gets(st.productname); // get input string
					st.productname[0]=toupper(st.productname[0]);
					//iterate for every character in string
					for (index=0; index<strlen(st.productname); ++index)
					{	//check if character is valid or not
						if(isalpha(st.productname[index]))
							valid = 1;
						else
						{
							valid = 0;
							break;
						}
					}
					if (!valid)
					{
						printf("\n Name contain invalid character. Please 'Enter' again");
						getch();


					}
				}while(!valid);	//while end here


				//Product Company
				do
				{
					char productcomp[40];
					fflush(stdin);
					printf("\nNew Product Company\t\t:");
					gets(st.productcomp); // get input string
					st.productcomp[0]=toupper(st.productcomp[0]);
					//iterate for every character in string
					for (index=0; index<strlen(st.productcomp); ++index)
					{	//check if character is valid or not
						if(isalpha(st.productcomp[index]))
							valid = 1;
						else
						{
							valid = 0;
							break;
						}
					}
					if (!valid)
					{
						printf("\n Name contain invalid character. Please 'Enter' again");
						getch();


					}
				}while(!valid);

					do
			{
				printf("\nNew Price [10-5000]Rupees:");
				scanf("%i",&st.price);
				if(st.price<10 || st.price>5000)
				{
					printf("\n\tYou Cannot Enter the price limit [10-5000].Re-Enter.");
				}
			}while(st.price<10 || st.price>5000);

				printf("\nEnter New Product Code\t\t:");
				scanf("%i",&st.productid);

				do
			{
				printf("\nNew Quantity [1-500]\t:");
				scanf("%i",&st.Qnt);
				if(st.Qnt<1 || st.Qnt>500)
				{
					printf("\n\tEnter New Quantity[1-500] only.Re-Enter.");
				}
			}while(st.Qnt<1 || st.Qnt>500);


				printf("Press 'y' to edit the existing record or any key to cancel...");
				edit=getche();
				if(edit=='y' || edit=='Y')
				{
					fprintf(rp,"%s %s %i %i %i\n", st.productname, st.productcomp, st.price, st.productid,st.Qnt);
					fflush(stdin);
					printf("\n\n\t\tYOUR RECORD IS SUCCESSFULLY EDITED!!!");
				}
			}
			else
			{
				fprintf(rp,"%s %s %i %i %i\n", st.productname, st.productcomp, st.price, st.productid,st.Qnt);
				fflush(stdin);
			}

		}
		if(!a)
		{
			printf("\n\nTHIS PRODUCT DOESN'T EXIST!!!!");
		}
		fclose(rp);
		fclose(fp);
		remove("NextFile.dat");
		rename("TempFile.dat","NextFile.dat");
		getch();
	}
	menu();
}
