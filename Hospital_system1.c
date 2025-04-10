#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <time.h>

void flushInput()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void addPatient()
{
    char name[50];
    int age;
    char gender;
    char address[100];
    long phone;
    char disease[200];
    char treatment[200];
    char additionalDetails[200];

    printf("Enter patient name: ");
    flushInput();
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    printf("Enter patient age: ");
    scanf("%d", &age);

    printf("Enter patient gender (M/F): ");
    scanf(" %c", &gender);

    printf("Enter patient address: ");
    flushInput();
    fgets(address, sizeof(address), stdin);
    address[strcspn(address, "\n")] = 0;

    printf("Enter patient phone number: ");
    scanf("%ld", &phone);

    printf("Enter patient disease/issue(s): ");
    flushInput();
    fgets(disease, sizeof(disease), stdin);
    disease[strcspn(disease, "\n")] = 0;

    printf("Enter treatment: ");
    fgets(treatment, sizeof(treatment), stdin);
    treatment[strcspn(treatment, "\n")] = 0;

    printf("Enter additional details: ");
    fgets(additionalDetails, sizeof(additionalDetails), stdin);
    additionalDetails[strcspn(additionalDetails, "\n")] = 0;

    printf("Patient added successfully!\n");

    FILE *file = fopen("patients.txt", "a");
    if (file == NULL)
    {
        perror("Error opening file");
        return;
    }

    fprintf(file, "Name: %s\n", name);
    fprintf(file, "Age: %d\n", age);
    fprintf(file, "Gender: %c\n", gender);
    fprintf(file, "Address: %s\n", address);
    fprintf(file, "Phone: +254 %ld\n", phone);
    fprintf(file, "Disease/issue(s): %s\n", disease);
    fprintf(file, "Treatment: %s\n", treatment);
    fprintf(file, "Date of admission: %s\n", __DATE__);
    fprintf(file, "Time of admission: %s\n", __TIME__);
    fprintf(file, "Additonal details: %s\n", additionalDetails);
    fprintf(file, "----------------------------------------\n");
    fclose(file);
    printf("Patient information saved to file.\n");
}

void searchPatient()
{
    char name[50];
    printf("Enter patient name to search: ");
    flushInput();
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    FILE *file = fopen("patients.txt", "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return;
    }

    char line[256];
    int found = 0;

    while (fgets(line, sizeof(line), file))
    {
        if (strstr(line, name) != NULL)
        {
            found = 1;
            printf("Patient found:\n");
            printf("%s", line);
            while (fgets(line, sizeof(line), file) && strcmp(line, "----------------------------------------\n") != 0)
            {
                printf("%s", line);
            }
            break;
        }
    }

    if (!found)
    {
        printf("Patient not found\n");
    }

    fclose(file);
}

void addDoctor()
{
    char name[50];
    char specialization[50];
    char gender;
    long phone;

    printf("Enter the doctor's name: ");
    flushInput();
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    printf("Enter the doctor's specialization: ");
    fgets(specialization, sizeof(specialization), stdin);
    specialization[strcspn(specialization, "\n")] = '\0';

    printf("Enter the doctor's gender (M/F): ");
    scanf(" %c", &gender);

    printf("Enter the doctor's phone number: ");
    scanf("%ld", &phone);

    FILE *file = fopen("doctors.txt", "a");
    if (file == NULL)
    {
        perror("Error opening file");
        return;
    }

    fprintf(file, "%s,%s,%c,%ld\n", name, specialization, gender, phone);
    printf("Doctor added successfully\n");
    fclose(file);
}

void searchDoctor()
{
    char name[50];
    printf("Enter doctor's name to search: ");
    flushInput();
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    FILE *file = fopen("doctors.txt", "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return;
    }

    char line[256];
    int found = 0;

    while (fgets(line, sizeof(line), file))
    {
        if (strstr(line, name) != NULL)
        {
            printf("Doctor found:\n%s", line);
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Doctor not found\n");
    }

    fclose(file);
}

int main()
{
    while (1)
    {
        int choice;
        printf("\n1. Sign Up\n");
        printf("2. Log in\n");
        printf("3. Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            int option;
            printf("1. Add Patient\n");
            printf("2. Add doctor\n");
            printf("3. Exit\n");
            printf("\nEnter your option: ");
            scanf("%d", &option);
            switch (option)
            {
            case 1:
                addPatient();
                break;
            case 2:
                addDoctor();
                break;
            case 3:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid input. Please try again.\n");
            }
            break;
        }
        case 2:
        {
            int loginOption;
            printf("1. Search patient\n");
            printf("2. Search doctor\n");
            printf("3. Exit\n");
            printf("\nEnter your choice: ");
            scanf("%d", &loginOption);
            switch (loginOption)
            {
            case 1:
                searchPatient();
                break;
            case 2:
                searchDoctor();
                break;
            case 3:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid input. Please try again.\n");
            }
            break;
        }
        case 3:
            printf("Exiting...\n");
            exit(0);
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
