#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

/*2. Display the list of medications in stock:
- The program should display all information about each stored medication, including the
name, available quantity, unit price, manufacturing date, expiry date, and brand.
*/

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
 
 printf("the available quantity is : %d\n",m.available_quantity);


  }


void display_stock(med_info m[])
{
    printf("Name\tAvailable Quantity\tUnit Price\tManufacturing Date\tExpiry Date\tBrand\n");
    for (int i = 0; i < 5; i++)
    {
        printf("%s\t%d\t\t%d\t\t%d/%d/%d\t\t%d/%d/%d\t\t%s\n",m[i].medication_name,m[i].available_quantity,m[i].unit_price, m[i].manufacturing_date[0],m[i].manufacturing_date[1], m[i].manufacturing_date[2], m[i].expiry_date[0],m[i].expiry_date[1],m[i].expiry_date[2],m[i].medication_brand);
               
    }
}

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

    display_stock(m);

    free(m);
    return 0;
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

