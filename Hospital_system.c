#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <time.h>
// function to add a new patient


void addPatient ()
{     char name[50];
      int age;
      char gender;
      char address[100];
      long phone;
      char disease[200];
      char treatment[200];
      char additionalDetails[200];

      printf("Enter patient name: ");
      fgets(name, sizeof(name), stdin);
      name[strcspn(name, "\n")] = 0; // remove newline character
      printf("Enter patient age: ");
      scanf("%d", &age);
      printf("Enter patient gender (M/F): ");
      scanf(" %c", &gender);
      printf("Enter patient address: ");
      getchar(); // consume newline character
      fgets(address, sizeof(address), stdin);
      address[strcspn(address, "\n")] = 0; // remove newline character
      printf("Enter patient phone number: ");
      scanf("%ld", &phone);
      printf("Enter patient disease/issue(s): ");
      getchar(); // consume newline character
      fgets(disease, sizeof(disease), stdin);
      disease[strcspn(disease, "\n")] = 0; // remove newline character
      printf("Enter treatment: ");
      fgets(treatment, sizeof(treatment), stdin);
      treatment[strcspn(treatment, "\n")] = 0; // remove newline character
      printf("Enter additional details: ");
      fgets(additionalDetails, sizeof(additionalDetails), stdin);
      additionalDetails[strcspn(additionalDetails, "\n")] = 0; // remove newline character
      printf("Patient added successfully!\n");
      
      
      FILE *file = fopen("patients.txt", "a");
      if (file == NULL) {
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
      fprintf(file, "Date of admission: %s", __DATE__);
      fprintf(file, "Time of admission: %s", __TIME__);
      fprintf(file, "Additonal details: %s\n", additionalDetails);
      fprintf(file, "----------------------------------------\n");
      fclose(file);
      printf("Patient information saved to file.\n");  
}

void searchPatient(){
  char name[50];
  printf("Enter patient name to search: ");
  fgets(name, sizeof(name), stdin);
  name[strcspn(name, "\n")] = 0; // remove newline character

  FILE *file = fopen("patients.txt", "r");
  if (file == NULL) {
      perror("Error opening file");
      return;
  }
  char line[256];
  while (fgets(line, sizeof(line), file)) {
      if(strstr(line, name) != NULL) {
          printf("Patient found:\n");
          printf("%s", line);
          while (fgets(line, sizeof(line), file) && strcmp(line, "----------------------------------------\n") != 0) {
              printf("%s", line);
          }
          break;
      }
  }
}

int main(){   
  addPatient();
  searchPatient();
  printf("Press any key to continue...\n");
  getchar(); // wait for user input
  return 0;
}
