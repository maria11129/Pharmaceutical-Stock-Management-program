#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MEDS 100

typedef int date[3]; // dd/mm/yy

typedef struct {
  char* medication_name;
  int available_quantity;
  int unit_price;
  date manufacturing_date;
  date expiry_date;
  char medication_brand[60];
} med_info;

void ctr_date(date d); // Function declaration for date input validation

int isExpired(med_info d);

void add_medication(med_info* medications, int* num_meds, med_info new_med);

void format_date(int date[], char formatted_date[]);

void display_stock(med_info medications[], int num_meds);

void update_medication_quantity(med_info* medication, int new_quantity);

int main() {

  int num_meds = 0; // Keeps track of the number of medications added
  med_info* medications = (med_info*)malloc(MAX_MEDS * sizeof(med_info));

  if (medications == NULL) {
    printf("Memory allocation failed\n");
    return 1;
  }

  // Sample data (can be replaced with functions to add medications)
  med_info med1 = {"paracetamol", 100, 10, {1, 1, 2024}, {31, 12, 2026}, "panadol"};
  add_medication(medications, &num_meds, med1);

  // Add more medications using the add_medication function

  display_stock(medications, num_meds);

  // Search and update medication functionality (commented out for brevity)

  free(medications);
  return 0;
}

void ctr_date(date d) {
  int valid_input = 0;
  while (!valid_input) {
    printf("Enter the date (DD/MM/YYYY): ");
    if (scanf("%d/%d/%d", &d[0], &d[1], &d[2]) != 3) {
      printf("Invalid input. Please enter a valid date format.\n");
      scanf("%*[^\n]"); // Clear the input buffer
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

void add_medication(med_info* medications, int* num_meds, med_info new_med)
 {
  if (*num_meds >= MAX_MEDS) {
    printf("Maximum medication capacity reached.\n");
    return;
  }
}
  // Check if medication is expired before adding (optional)
  // if (isExpired(new_med)) {
  //   printf("Cannot add expired medication.\n");
  //   return;
  // }


