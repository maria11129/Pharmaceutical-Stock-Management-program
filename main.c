#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

/*1. Add a new medication to the stock:
- The program should prompt the user to enter the following information for each
medication:
- Medication name
- Available quantity
- Unit price
- Manufacturing date (format DD/MM/YYYY)
- Expiry date (format DD/MM/YYYY)
- Medication brand
- Before adding the medication to the stock, the program should verify that the expiry date
is valid and display a warning if it is near or exceeded.*/

 typedef int date[3];  // dd/mm/yy
 
  typedef struct  // a function that hold medication infos
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




  int main()

{
     
    med_info m;
   
    









    return 0;
}