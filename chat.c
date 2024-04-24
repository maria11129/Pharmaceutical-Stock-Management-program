#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define DATE_LENGTH 11


#define MAX_MEDS 100
#define MAX_NAME_LENGTH 60
#define MAX_BRAND_LENGTH 60
#define MAX_DAY 31
#define MAX_MONTH 12
#define MIN_YEAR 2000

typedef int date[3]; // dd/mm/yy

typedef struct // a function that holds medication infos
{
    char medication_name[MAX_NAME_LENGTH];
    int available_quantity;
    int unit_price;
    date manufacturing_date;
    date expiry_date;
    char medication_brand[MAX_BRAND_LENGTH];

} med_info;

void ctr_date(date d);
int isExpired(med_info d);
void add_medication(med_info *m);
void format_date(int date[], char formatted_date[]);
void display_stock(med_info m[]);
void update_medication_quantity(med_info *medication, int new_quantity);
void initialize_medication(med_info *m, const char *name, int quantity, int unit_price, int year, int month, int day, const char *brand);
void find_and_select_medication(med_info m[], int max_meds);


int main()
{
    med_info m[MAX_MEDS]; // Use the predefined array instead of allocating memory

    initialize_medication(&m[0], "paracetamol", 100, 10, 2024, 1, 1, "panadol");
    initialize_medication(&m[1], "ibuprofen", 100, 15, 2024, 2, 15, "advil");
    initialize_medication(&m[2], "Cetirizine", 30, 20, 2024, 3, 10, "zyrtec");
    initialize_medication(&m[3], "Aspirin", 80, 8, 2024, 4, 5, "bayer");
    initialize_medication(&m[4], "Diphenhydramine", 60, 12, 2024, 4, 30, "benadryl");
    initialize_medication(&m[5], "imane", 19, 12, 2024, 4, 30, "benadryl");

    // Display the initial stock
    display_stock(m);

/*
    // Example of updating medication quantity
    update_medication_quantity(&m[0], 150); // Increase quantity of "paracetamol" to 150

    // Display the updated stock
    display_stock(m);

*/


find_and_select_medication(m,MAX_MEDS);












    return 0;
}

void ctr_date(date d)
{
    int bool = 0;
    while (bool == 0)
    {
        printf("give the date:");
        scanf("%d", &d[0]);

        if ((d[0] <= 0) || (d[0] > 31))
        {
            printf("the day should be between 1 - 31 \n");
            bool = 0;
        }
        else
            bool = 1;
    }

    bool = 0;

    while (bool == 0)
    {
        printf("enter the month :");
        scanf("%d", &d[1]);
        if ((d[1] <= 0) || (d[1] > 12))
        {
            printf("the month should be a value in between 1 -12 \n");
        }

        else
            bool = 1;
    }

    bool = 0;

    while (bool == 0)
    {
        printf("enter the year :");
        scanf("%d", &d[2]);

        if ((d[2] < 2000))
        {
            printf("the year should be superior than 2000.\n");
        }
        else
            bool = 1;
    }
}

int isExpired(med_info d)
{
    time_t now = time(NULL);
    struct tm *local_time = localtime(&now);

    if (local_time == NULL)
    {
        printf("Failed to get the current time.\n");
        return 0;
    }

    int current_day = local_time->tm_mday;
    int current_month = local_time->tm_mon + 1; // Month is 0-indexed
    int current_year = local_time->tm_year + 1900; // Years since 1900

    if (current_year > d.expiry_date[2] ||
        (current_year == d.expiry_date[2] && current_month > d.expiry_date[1]) ||
        (current_year == d.expiry_date[2] && current_month == d.expiry_date[1] && current_day > d.expiry_date[0]))
    {
        return 1; // Item is expired
    }

    return 0; // Item is not expired
}

void add_medication(med_info *m)
{
    if (isExpired(*m) == 0)
    {
        m->available_quantity++;
    }

    printf("the available quantity is : %d\n", m->available_quantity);
}

void format_date(int date[], char formatted_date[])
{
    sprintf(formatted_date, "%02d/%02d/%04d", date[0], date[1], date[2]);
}

void display_stock(med_info m[])
{
    printf("Name\t\tAvailable Quantity\tUnit Price\tMnf Date\t\tExp Date\t\t\tBrand\n");
    printf("\n");
    for (int i = 0; i < 6; i++)
    {
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

void update_medication_quantity(med_info *medication, int new_quantity)
{
    if (medication == NULL)
    {
        printf("Error: Medication pointer is NULL\n");
        return;
    }

    
    medication->available_quantity = new_quantity;
    printf("Quantity updated successfully!\n");
}

void initialize_medication(med_info *m, const char *name, int quantity, int unit_price, int year, int month, int day, const char *brand)
{
    strcpy(m->medication_name, name);
    m->available_quantity = quantity;
    m->unit_price = unit_price;
    m->manufacturing_date[0] = day;
    m->manufacturing_date[1] = month;
    m->manufacturing_date[2] = year;
    m->expiry_date[0] = day;
    m->expiry_date[1] = month;
    m->expiry_date[2] = year + 2; // Expiry date is two years after manufacturing date
    strcpy(m->medication_brand, brand);
}





void find_and_select_medication(med_info m[], int max_meds) {
    printf("\n\n");

    int found_count = 0;
    med_info found_meds[MAX_MEDS]; // Array to store found medications

    printf("Hello, please enter the first letter of the medication you want to find: ");

    char first_letter;
    scanf(" %c", &first_letter); // Use space before %c to consume newline from previous input

    for (int i = 0; i < max_meds; i++) { // Iterate up to max_meds instead of MAX_MEDS
        if (m[i].medication_name[0] == first_letter) {
            // Copy entire medication details, not just the name
            strcpy(found_meds[found_count].medication_name, m[i].medication_name);
            found_meds[found_count].available_quantity = m[i].available_quantity;
            found_meds[found_count].unit_price = m[i].unit_price;
            memcpy(found_meds[found_count].manufacturing_date, m[i].manufacturing_date, sizeof(char) * DATE_LENGTH);
            memcpy(found_meds[found_count].expiry_date, m[i].expiry_date, sizeof(char) * DATE_LENGTH);
            strcpy(found_meds[found_count].medication_brand, m[i].medication_brand);

            found_count++; // Increment found_count for each found medication
        }
    }

    if (found_count > 0) {
        printf("Found medications:\n");

        for (int i = 0; i < found_count; i++) {
            printf("%d. %s\n", i + 1, found_meds[i].medication_name);
        }

        printf("Enter the number corresponding to your desired medication (or 0 to cancel): ");
        int user_choice;
        // Validate input for user choice
        while (scanf("%d", &user_choice) != 1) {
            printf("Invalid input. Please enter a number: ");
            while (getchar() != '\n'); // Clear input buffer
        }

        int selected_index = user_choice - 1;
        if (user_choice > 0 && user_choice <= found_count) {
            // User chose a valid suggestion
            // Access the selected medication using found_meds[selected_index]
            printf("You selected: %s\n", found_meds[selected_index].medication_name);
            // Perform actions based on the selected medication (optional)
        } else if (user_choice == 0) {
            printf("Selection cancelled.\n");
        } else {
            printf("Invalid choice. Please enter a number between 1 and %d (or 0 to cancel).\n", found_count);
        }
    } else {
        printf("\nNo medication found starting with '%c'.\n", first_letter);
    }
}