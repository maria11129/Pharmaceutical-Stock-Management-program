#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MEDS 100

typedef int date[3]; // dd/mm/yyyy format

typedef struct {
  char* medication_name;
  int available_quantity;
  int unit_price;
  date manufacturing_date;
  date expiry_date;
  char medication_brand[60];
} med_info;

void clear_input_buffer() {
  scanf("%*[^\n]"); // Clear any remaining characters in the input buffer
}

// Function to validate and get user input for a date
void get_date(date d) {
  int valid_input = 0;
  while (!valid_input) {
    printf("Enter the date (DD/MM/YYYY): ");
    if (scanf("%d/%d/%d", &d[0], &d[1], &d[2]) != 3) {
      printf("Invalid input. Please enter a valid date format.\n");
      clear_input_buffer();
    } else {
      if (d[0] <= 0 || d[0] > 31 || d[1] <= 0 || d[1] > 12 || d[2] < 2000) {
        printf("Invalid date. Please enter a valid day, month, and year.\n");
      } else {
        valid_input = 1;
      }
    }
  }
}

int isExpired(med_info d) {
  time_t now = time(NULL);
  struct tm *local_time = localtime(&now);

  if (local_time == NULL) {
    printf("Failed to get the current time.\n");
    return 0;
  }

  int current_day = local_time->tm_mday;
  int current_month = local_time->tm_mon + 1; // Month is 0-indexed
  int current_year = local_time->tm_year + 1900; // Years since 1900

  if (current_year > d.expiry_date[2] ||
      (current_year == d.expiry_date[2] && current_month > d.expiry_date[1]) ||
      (current_year == d.expiry_date[2] && current_month == d.expiry_date[1] && current_day > d.expiry_date[0])) {
    return 1; // Item is expired
  }

  return 0; // Item is not expired
}

void add_medication(med_info* medications, int* num_meds, med_info new_med) {
  if (*num_meds >= MAX_MEDS) {
    printf("Maximum medication capacity reached.\n");
    return;
  }

  // Check if medication is expired before adding (optional)
  if (isExpired(new_med)) {
    printf("Cannot add expired medication.\n");
    return;
  }

  medications[*num_meds] = new_med; // Copy new medication data to the array
  (*num_meds)++; // Increment the number of medications
  printf("Medication added successfully!\n");
}

void format_date(int date[], char formatted_date[]) {
  sprintf(formatted_date, "%02d/%02d/%04d", date[0], date[1], date[2]);
}

void display_stock(med_info medications[], int num_meds) {
  printf("Name\t\tAvailable Quantity\tUnit Price\tMfg Date\t\tExp Date\t\t\tBrand\n");
  printf("\n");
  for (int i = 0; i < num_meds; i++) {
    char manufacturing_date_str[11], expiry_date_str[11];
    format_date(medications[i].manufacturing_date, manufacturing_date_str);
    format_date(medications[i].expiry_date, expiry_date_str);
     printf("%-20s\t%-3d\t\t%-7d\t%-20s\t%-20s\t\t%s\n",
        medications[i].medication_name,
        medications[i].available_quantity,
        medications[i].unit_price,
        manufacturing_date_str,
        expiry_date_str,
        medications[i].medication_brand);
  }
}

int main()
{




return 0;

}