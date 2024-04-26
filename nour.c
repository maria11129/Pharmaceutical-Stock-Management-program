#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h> // Include for sleep function

#define DATE_LENGTH 11
#define MAX_MEDS 1000
#define MAX_NAME_LENGTH 60
#define MAX_BRAND_LENGTH 60
#define MIN_YEAR 2000

typedef int date[3]; // dd/mm/yy

typedef struct {
    char medication_name[MAX_NAME_LENGTH];
    int available_quantity;
    int unit_price;
    date manufacturing_date;
    date expiry_date;
    char medication_brand[MAX_BRAND_LENGTH];
} med_info;

void load_medication_data(med_info m[], int max_meds, const char *filename);
void save_medication_data(med_info m[], int num_meds, const char *filename);
void display_stock(med_info m[]);
void initialize_medication(med_info *m, char *name, int quantity, int unit_price, int year, int month, int day, char *brand);
void add_medication(med_info *m, const char *filename);
void format_date(int date[], char formatted_date[]);
void find_and_select_medication(med_info m[], int max_meds);

int main() {
    med_info m[MAX_MEDS];
    int num_meds = 0;

    save_medication_data(m, num_meds, "medications.bin");
    load_medication_data(m, MAX_MEDS, "medications.bin");

    char medication_name[MAX_NAME_LENGTH], brand[MAX_BRAND_LENGTH];
    int quantity, unit_price, year, month, day;
    while (num_meds < MAX_MEDS) {
        printf("Fill the medication stock :\n");
        sleep(1); // Pause for 1 second
        printf("Name of medication: ");
        scanf("%59s", medication_name);
        printf("Brand: ");
        scanf("%59s", brand);
        printf("Quantity of medication: ");
        scanf("%d", &quantity);
        printf("Price of medication (in Algerian dinar): ");
        scanf("%d", &unit_price);
        printf("Manufacturing date (year month day): ");
        printf("\nYear: ");
        do {
            scanf("%d", &year);
            if (year < MIN_YEAR || year > 2024) {
                printf("Invalid year. Please try again: ");
            }
        } while (year < MIN_YEAR || year > 2024);

        printf("Month: ");
        do {
            scanf("%d", &month);
            if (month < 1 || month > 12) {
                printf("Invalid month. Please try again: ");
            }
        } while (month < 1 || month > 12);

        printf("Day: ");
        do {
            scanf("%d", &day);
            if (day < 1 || day > 31) {
                printf("Invalid day. Please try again: ");
            }
        } while (day < 1 || day > 31);

        initialize_medication(&m[num_meds], medication_name, quantity, unit_price, year, month, day, brand);
        num_meds++;

        printf("Add another medication? (enter 'y'/'n'): ");
        char c;
        scanf(" %c", &c);
        if (c != 'y') {
            break;
        }
    }

    find_and_select_medication(m, num_meds);
    display_stock(m);

    return 0;
}

void load_medication_data(med_info m[], int max_meds, const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file: %s\n", filename);
        return;
    }

    int i = 0;
    while (i < max_meds && fscanf(fp, "%59s %d %d %d/%d/%d %d/%d/%d %59s\n",
                                  m[i].medication_name, &m[i].available_quantity, &m[i].unit_price,
                                  &m[i].manufacturing_date[0], &m[i].manufacturing_date[1], &m[i].manufacturing_date[2],
                                  &m[i].expiry_date[0], &m[i].expiry_date[1], &m[i].expiry_date[2],
                                  m[i].medication_brand) == 10) {
        i++;
        printf("Loaded medication: %s\n", m[i - 1].medication_name);
    }

    fclose(fp);
}

void save_medication_data(med_info m[], int num_meds, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < num_meds; i++) {
        fprintf(fp, "%s %d %d %d/%d/%d %d/%d/%d %s\n",
                m[i].medication_name, m[i].available_quantity, m[i].unit_price,
                m[i].manufacturing_date[0], m[i].manufacturing_date[1], m[i].manufacturing_date[2],
                m[i].expiry_date[0], m[i].expiry_date[1], m[i].expiry_date[2],
                m[i].medication_brand);
    }

    fclose(fp);
}

void display_stock(med_info m[]) {
    printf("Name\t\tAvailable Quantity\tUnit Price\tMnf Date\t\tExp Date\t\tBrand\n");
    printf("\n");
    for (int i = 0; i < MAX_MEDS; i++) {
        if (m[i].available_quantity > 0) {
            char manufacturing_date_str[DATE_LENGTH], expiry_date_str[DATE_LENGTH];
            format_date(m[i].manufacturing_date, manufacturing_date_str);
            format_date(m[i].expiry_date, expiry_date_str);
            printf("%-20s\t%-3d\t\t%-7d\t%-10s\t%-10s\t\t%s\n",
                   m[i].medication_name,
                   m[i].available_quantity,
                   m[i].unit_price,
                   manufacturing_date_str,
                   expiry_date_str,
                   m[i].medication_brand);
        }
    }
}

void initialize_medication(med_info *m, char *name, int quantity, int unit_price, int year, int month, int day, char *brand) {
    strcpy(m->medication_name, name);
    m->available_quantity = quantity;
    m->unit_price = unit_price;
    m->manufacturing_date[0] = day;
    m->manufacturing_date[1] = month;
    m->manufacturing_date[2] = year;
    m->expiry_date[0] = day;
    m->expiry_date[1] = month;
    m->expiry_date[2] = year + 2;
    strcpy(m->medication_brand, brand);
}

void add_medication(med_info *m, const char *filename) {
    FILE *fp = fopen(filename, "a"); // Append mode
    if (fp == NULL) {
        printf("Error opening file for appending.\n");
        return;
    }

    fprintf(fp, "%s %d %d %d/%d/%d %d/%d/%d %s\n",
            m->medication_name, m->available_quantity, m->unit_price,
            m->manufacturing_date[0], m->manufacturing_date[1], m->manufacturing_date[2],
            m->expiry_date[0], m->expiry_date[1], m->expiry_date[2],
            m->medication_brand);

    fclose(fp);
}

void format_date(int date[], char formatted_date[]) {
    sprintf(formatted_date, "%02d/%02d/%04d", date[0], date[1], date[2]);
}

void find_and_select_medication(med_info m[], int num_meds) {
    printf("\n");

    int found_count = 0;
    med_info found_meds[MAX_MEDS];

    printf("Enter the first letter of the medication you want to find: ");
    char first_letter;
    scanf(" %c", &first_letter);

    for (int i = 0; i < num_meds; i++) {
        if (m[i].medication_name[0] == first_letter) {
            strcpy(found_meds[found_count].medication_name, m[i].medication_name);
            found_meds[found_count].available_quantity = m[i].available_quantity;
            found_meds[found_count].unit_price = m[i].unit_price;
            memcpy(found_meds[found_count].manufacturing_date, m[i].manufacturing_date, sizeof(int) * 3);
            memcpy(found_meds[found_count].expiry_date, m[i].expiry_date, sizeof(int) * 3);
            strcpy(found_meds[found_count].medication_brand, m[i].medication_brand);
            found_count++;
        }
    }

    if (found_count > 0) {
        printf("Found medications:\n");
        for (int i = 0; i < found_count; i++) {
            char manufacturing_date_str[DATE_LENGTH], expiry_date_str[DATE_LENGTH];
            format_date(found_meds[i].manufacturing_date, manufacturing_date_str);
            format_date(found_meds[i].expiry_date, expiry_date_str);
            printf("%-20s\t%-3d\t\t%-7d\t%-20s\t%-20s\t\t%s\n",
                   found_meds[i].medication_name,
                   found_meds[i].available_quantity,
                   found_meds[i].unit_price,
                   manufacturing_date_str,
                   expiry_date_str,
                   found_meds[i].medication_brand);
        }
    } else {
        printf("No medication found starting with '%c'.\n", first_letter);
    }
}
