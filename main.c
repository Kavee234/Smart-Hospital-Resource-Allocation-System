#include <stdio.h>
#include <stdlib.h>
#include "hospital.h"

int main(void) {
    char patientNames[MAX_PATIENTS][50];
    int patientAges[MAX_PATIENTS];
    int patientUrgencies[MAX_PATIENTS];
    int specialtyIDs[MAX_PATIENTS];
    int wardAdmitted[MAX_PATIENTS];
    int wardIDs[MAX_PATIENTS];
    int daysAdmitted[MAX_PATIENTS];
    double finalPayables[MAX_PATIENTS];

    int bedOccupancy[NUM_WARDS][20];
    int queueCounts[NUM_SPECIALTIES];
    int patientCount = 0;

    initializeSystem(bedOccupancy, queueCounts);
    loadBedStatusFromFile(bedOccupancy);

    int choice;
    do {
        clearScreen();
        printf("\n=======================================================\n");
        printf("---   SMART HOSPITAL & RESOURCE ALLOCATION SYSTEM   ---\n");
        printf("=======================================================\n");
        printf("1. Register Patient & Calculate Bill\n");
        printf("2. Display All Patient Billing Logs\n");
        printf("3. View Emergency Triage Priority List\n");
        printf("4. Generate Performance Reports & Analytics\n");
        printf("5. Exit System\n");
        printf("=======================================================\n");
        printf("Enter Choice (1-5): ");
        if (scanf("%d", &choice) != 1) break;

        clearScreen();
        switch (choice) {
            case 1:
                registerPatient(patientNames, patientAges, patientUrgencies, specialtyIDs,
                                wardAdmitted, wardIDs, daysAdmitted, finalPayables,
                                bedOccupancy, queueCounts, &patientCount);
                saveBedStatusToFile(bedOccupancy);
                pauseScreen();
                break;
            case 2:
                displayAllBills(patientNames, patientAges, patientUrgencies, specialtyIDs,
                                wardAdmitted, wardIDs, daysAdmitted, finalPayables,
                                queueCounts, patientCount);
                pauseScreen();
                break;
            case 3:
                displayTriageList(patientNames, patientUrgencies, patientCount);
                pauseScreen();
                break;
            case 4:
                displayAnalytics(patientUrgencies, finalPayables, bedOccupancy, patientCount);
                pauseScreen();
                break;
            case 5:
                printf("Exiting system. Data saved successfully.\n");
                break;
            default:
                printf("Invalid choice! Please select 1-5.\n");
                pauseScreen();
                break;
        }
    } while (choice != 5);

    return 0;
}
