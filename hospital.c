#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hospital.h"

const char SPECIALTY_NAMES[NUM_SPECIALTIES][30] = {"General Practice (OPD)", "Paediatrics", "Cardiology", "Neurology"};
const double BASE_FEES[NUM_SPECIALTIES] = {1500.00, 2500.00, 4500.00, 5000.00};
const int CONSULT_TIMES[NUM_SPECIALTIES] = {15, 20, 30, 30};
const int DAILY_CAPS[NUM_SPECIALTIES] = {30, 20, 12, 10};

const char WARD_NAMES[NUM_WARDS][30] = {"General Ward", "Paediatric Ward", "Surgical Ward", "ICU"};
const double WARD_RATES[NUM_WARDS] = {3000.00, 6000.00, 12000.00, 25000.00};
const int WARD_CAPACITIES[NUM_WARDS] = {20, 10, 10, 5};

void clearScreen(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pauseScreen(void) {
    printf("\nPress Enter to continue...");
    getchar();
    getchar();
}

void initializeSystem(int bedOccupancy[NUM_WARDS][20], int queueCounts[NUM_SPECIALTIES]) {
    for (int i = 0; i < NUM_WARDS; i++) {
        for (int j = 0; j < 20; j++) {
            bedOccupancy[i][j] = 0;
        }
    }
    for (int i = 0; i < NUM_SPECIALTIES; i++) {
        queueCounts[i] = 0;
    }
}

void registerPatient(char names[][50], int ages[], int urgencies[], int specIDs[],
                     int wardAdmitted[], int wardIDs[], int daysAdmitted[],
                     double finalPayables[], int bedOccupancy[NUM_WARDS][20],
                     int queueCounts[NUM_SPECIALTIES], int *patientCount) {
    if (*patientCount >= MAX_PATIENTS) {
        printf("Error: Patient database full!\n");
        return;
    }

    int idx = *patientCount;
    printf("\n====================================\n");
    printf("-----   Patient Registration   -----\n");
    printf("====================================\n");
    printf("Enter Patient Name: ");
    scanf(" %[^\n]", names[idx]);
    printf("Enter Age: ");
    scanf("%d", &ages[idx]);
    printf("\n---  Urgency Levels  ---\n");
    printf(" Normal   = 1\n");
    printf(" Urgent   = 2\n");
    printf(" Critical = 3\n");
    printf("Enter Urgency Level: ");
    scanf("%d", &urgencies[idx]);
    printf("\n-----   Specialties   -----\n");
    printf(" General Practice(OPD) = 1\n");
    printf(" Paediatrics           = 2\n");
    printf(" Cardiology            = 3\n");
    printf(" Neurology             = 4\n");
    printf("Select Specialty: ");
    scanf("%d", &specIDs[idx]);

    printf("\n---  Admitted to Ward  ---\n");
    printf(" Yes = 1\n");
    printf(" No  = 0\n");
    printf("Enter Option: ");
    scanf("%d", &wardAdmitted[idx]);

    if (wardAdmitted[idx] == 1) {
        printf("\n---   Wards List   ---\n");
        printf(" General    = 1\n");
        printf(" Paediatric = 2\n");
        printf(" Surgical   = 3\n");
        printf(" ICU        = 4\n");
        printf("Enter Ward: ");
        scanf("%d", &wardIDs[idx]);
        printf("Enter Days Admitted: ");
        scanf("%d", &daysAdmitted[idx]);

        int wIdx = wardIDs[idx] - 1;
        for (int b = 0; b < WARD_CAPACITIES[wIdx]; b++) {
            if (bedOccupancy[wIdx][b] == 0) {
                bedOccupancy[wIdx][b] = 1;
                break;
            }
        }
    } else {
        wardIDs[idx] = 0;
        daysAdmitted[idx] = 0;
    }
