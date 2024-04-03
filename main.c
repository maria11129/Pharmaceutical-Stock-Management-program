#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define MAX_MEDS 100


 typedef int date[3];  // dd/mm/yy

  typedef struct  // a function that holds medication infos
  {
    char medication_name[60];
    int available_quantity;
    int unit_price;
    date manufacturing_date;
    date expiry_date;
    char medication_brand[60];

  }med_info;


   void ctr_date(date d);
  int isExpired(med_info d);
  void add_medication(med_info m);
  void format_date(int date[], char formatted_date[]);
  void display_stock(med_info m[]);  // theres a display bug here some lines is messy and some are not



  int main()

{

    med_info *m = (med_info *)malloc(sizeof(med_info));



    strcpy(m[0].medication_name, "paracetamol");
    m[0].available_quantity = 100;
    m[0].unit_price = 10;
    m[0].manufacturing_date[0] = 1;
    m[0].manufacturing_date[1] = 1;
    m[0].manufacturing_date[2] = 2024;
    m[0].expiry_date[0] = 31;
    m[0].expiry_date[1] = 12;
    m[0].expiry_date[2] = 2026;
    strcpy(m[0].medication_brand, "panadol");

    strcpy(m[1].medication_name, "ibuprofen");
    m[1].available_quantity = 100;
    m[1].unit_price = 15;
    m[1].manufacturing_date[0] = 15;
    m[1].manufacturing_date[1] = 2;
    m[1].manufacturing_date[2] = 2024;
    m[1].expiry_date[0] = 31;
    m[1].expiry_date[1] = 1;
    m[1].expiry_date[2] = 2027;
    strcpy(m[1].medication_brand, "advil");

    strcpy(m[2].medication_name, "Cetirizine");
    m[2].available_quantity = 30;
    m[2].unit_price = 20;
    m[2].manufacturing_date[0] = 10;
    m[2].manufacturing_date[1] = 3;
    m[2].manufacturing_date[2] = 2024;
    m[2].expiry_date[0] = 28;
    m[2].expiry_date[1] = 2;
    m[2].expiry_date[2] = 2027;
    strcpy(m[2].medication_brand, "zyrtec");

    strcpy(m[3].medication_name, "Aspirin");
    m[3].available_quantity = 80;
    m[3].unit_price = 8;
    m[3].manufacturing_date[0] = 5;
    m[3].manufacturing_date[1] = 4;
    m[3].manufacturing_date[2] = 2024;
    m[3].expiry_date[0] = 3;
    m[3].expiry_date[1] = 3;
    m[3].expiry_date[2] = 2027;
    strcpy(m[3].medication_brand, "bayer");

    strcpy(m[4].medication_name, "Diphenhydramine");
    m[4].available_quantity = 60;
    m[4].unit_price = 12;
    m[4].manufacturing_date[0] = 30;
    m[4].manufacturing_date[1] = 4;
    m[4].manufacturing_date[2] = 2024;
    m[4].expiry_date[0] = 30;
    m[4].expiry_date[1] = 4;
    m[4].expiry_date[2] = 2027;
    strcpy(m[4].medication_brand, "benadryl");

    strcpy(m[5].medication_name, "imane");
     m[5].available_quantity = 00;
    m[5].unit_price = 12;
    m[5].manufacturing_date[0] = 30;
    m[5].manufacturing_date[1] = 4;
    m[5].manufacturing_date[2] = 2024;
    m[5].expiry_date[0] = 30;
    m[5].expiry_date[1] = 4;
    m[5].expiry_date[2] = 2027;
    strcpy(m[5].medication_brand, "benadryl");
    display_stock(m);


/*
3. Search for a medication by the first characters of its name:
- The user should be able to enter the first characters of the medication name they are

If multiple medications match these characters, the program should provide a list of
suggestions to the user to choose the desired medication.

*/
     

printf("\n\n");

  int found_count=0;
  med_info found_meds[MAX_MEDS]; // Array to store found medications
  
    printf("Hello, enter please the first letter of the medication you want to find: ");

    char first_letter;
    scanf(" %c", &first_letter); // Use space before %c to consume newline from previous input

    for (int i = 0; i < MAX_MEDS; i++)
     {
        if (m[i].medication_name[0] == first_letter){ 
                                                      
            // Copy entire medication name, not just the first letter
            strcpy(found_meds[found_count].medication_name, m[i].medication_name);
            found_count++;
        }
    }

    if (found_count > 0) {
        printf("Found medications:\n");

        for (int i = 0; i < found_count; i++) 
        {
            printf("%s\n", found_meds[i].medication_name);
        }
    } 
    
    else {
        printf("\nNo medication found starting with '%c'.\n", first_letter);
    }




 
  printf("Enter the number corresponding to your desired medication (or 0 to cancel): ");
  int user_choice;
  scanf("%d", &user_choice);



if (user_choice > 0 && user_choice <= found_count)

 {
  // User chose a valid suggestion
  int selected_index = user_choice - 1; // Convert choice to index (0-based)
  // Access the selected medication using found_meds[selected_index]
  printf("You selected: %s\n", found_meds[selected_index].medication_name);
  // Perform actions based on the selected medication (optional)
} else if (user_choice == 0) {
  printf("Selection cancelled.\n");
} else {
  printf("Invalid choice. Please enter a number between 1 and %d (or 0 to cancel).\n", found_count);
}









free(m);
return 0;}




    void ctr_date(date d)  // a function that controls the date given by the user
  {
    int bool=0;
    while(bool==0)
    {
        printf("give the date:");
        scanf("%d",d[0]);

    if((d[0]<=0)|| (d[0]>31))
{
      printf("the day should be between 1 - 31 \n");
      bool =0;
}
else
  bool =1;

  }

  bool=0;

  while(bool==0)
  {
    printf("enter the month :");
    scanf("%d",&d[1]);
    if((d[1]<=0)|| (d[1]>12))
    {
       printf("the month should be a value in between 1 -12 \n");
    }

 else bool=1;

  }


     bool =0;

     while(bool==0)
     {
        printf("enter the year :");
        scanf("%d",&d[2]);

        if((d[2]<2000))
        {
            printf("the year should be superior than 2000.\n");
        }
        else bool=1;
     }
     }


int isExpired(med_info d)

{
    time_t now = time(NULL);
    struct tm *local_time = localtime(&now);

    if (local_time == NULL) {
        printf("Failed to get the current time.\n");
        return 0;
    }

    int current_day = local_time->tm_mday;
    int current_month = local_time->tm_mon + 1;  // Month is 0-indexed
    int current_year = local_time->tm_year + 1900;  // Years since 1900

    if (current_year > d.expiry_date[2] ||
        (current_year == d.expiry_date[2] && current_month > d.expiry_date[1]) ||
        (current_year == d.expiry_date[2] && current_month == d.expiry_date[1] && current_day > d.expiry_date[0])) {
        return 1;  // Item is expired
    }

    return 0;  // Item is not expired
}



void add_medication(med_info m)

  {

   if (isExpired(m)==0)
   {
    m.available_quantity++;
   }

 printf("the available quantity is : %d\n",m.available_quantity);}




void format_date(int date[], char formatted_date[]) {
  sprintf(formatted_date, "%02d/%02d/%04d", date[0], date[1], date[2]);
}



void display_stock(med_info m[]) {
  printf("Name\t\tAvailable Quantity\tUp\tMnf Date\t\tExp Date\t\t\tBrand\n");
  printf("\n");
  for (int i = 0; i < 6; i++) {
    char manufacturing_date_str[11], expiry_date_str[11];
    format_date(m[i].manufacturing_date, manufacturing_date_str);
    format_date(m[i].expiry_date, expiry_date_str);
    printf("%-20s\t%-3d\t\t%-7d\t%-20s\t%-20s\t\t%s\n",
        m[i].medication_name,
        m[i].available_quantity,
        m[i].unit_price,
        manufacturing_date_str,
        expiry_date_str,
        m[i].medication_brand);
  }
}





















































/*
    printf("enter the medication name : \n");
    scanf("%s",m[i].medication_name);

    printf("enter the medication brand : \n");
    scanf("%s",m[i].medication_brand);

    printf("enter the quantity of this medication : \n");
    scanf("%d",&m[i].available_quantity);

    printf("enter the unit prince : \n");
    scanf("%d",m[i].unit_price);

    printf("enter the manufacturing date : \n");
    scanf("%d",&m[i].manufacturing_date);

    printf("enter the expiry date : \n");
    scanf("%d",&m[i].expiry_date);
*/

