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
    printf("\n============================================\n");
    printf("-------     Patient Registration     -------\n");
    printf("============================================\n");
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

int sIdx = specIDs[idx] - 1;
    double baseFee = BASE_FEES[sIdx];
    double surchargeRate = (urgencies[idx] == 1) ? 0.0 : (urgencies[idx] == 2) ? 0.20 : 0.50;
    double surcharge = baseFee * surchargeRate;

    double wardCost = (wardAdmitted[idx] == 1) ? (daysAdmitted[idx] * WARD_RATES[wardIDs[idx] - 1]) : 0.0;
    double gross = baseFee + surcharge + wardCost;

double discount = (ages[idx] < 5 || ages[idx] > 65) ? (gross * 0.15) : 0.0;
    finalPayables[idx] = gross - discount;
    queueCounts[sIdx]++;
    (*patientCount)++;

    FILE *fp = fopen("patient_records.txt", "a");
    if (fp) {
        fprintf(fp, "%s,%d,%d,%.2f\n", names[idx], ages[idx], urgencies[idx], finalPayables[idx]);
        fclose(fp);
    }
    printf("\nPatient registered successfully!\n");
}

void displayAllBills(char names[][50], int ages[], int urgencies[], int specIDs[],
                     int wardAdmitted[], int wardIDs[], int daysAdmitted[],
                     double finalPayables[], int queueCounts[NUM_SPECIALTIES], int patientCount) {
    if (patientCount == 0) {
        printf("No patients registered yet.\n");
        return;
    }
    int runningQueue[NUM_SPECIALTIES] = {0};

    for (int i = 0; i < patientCount; i++) {
        int sIdx = specIDs[i] - 1;
        double baseFee = BASE_FEES[sIdx];
        int surchargePct = (urgencies[i] == 1) ? 0 : (urgencies[i] == 2) ? 20 : 50;
        double surchargeRate = (urgencies[i] == 1) ? 0.0 : (urgencies[i] == 2) ? 0.20 : 0.50;
        double surcharge = baseFee * surchargeRate;
        double wardCost = (wardAdmitted[i] == 1) ? (daysAdmitted[i] * WARD_RATES[wardIDs[i] - 1]) : 0.0;
        double gross = baseFee + surcharge + wardCost;
        double discount = (ages[i] < 5 || ages[i] > 65) ? (gross * 0.15) : 0.0;
        double waitTime = runningQueue[sIdx] * CONSULT_TIMES[sIdx];
        runningQueue[sIdx]++;

        printf("\n===========================================================\n");
        printf("              SMART HOSPITAL ADMISSION & BILL              \n");
        printf("-----------------------------------------------------------\n");
        printf("Patient ID               : PAT-%d\n", 1001 + i);
        printf("Patient Name             : %s\n", names[i]);
        printf("Age                      : %d Years %s\n", ages[i], (ages[i] < 5 || ages[i] > 65) ? "(15% Subsidy Eligible)" : "");
        printf("Specialty                : %s\n", SPECIALTY_NAMES[sIdx]);
        if (wardAdmitted[i] == 1) {
            printf("Assigned Ward            : %s (Bed #%02d)\n", WARD_NAMES[wardIDs[i] - 1], i + 1);
        } else {
            printf("Assigned Ward            : Outpatient (OPD)\n");
        }
        if (urgencies[i] == 1)      printf("Urgency Level            : Level 1 (Normal)\n");
        else if (urgencies[i] == 2) printf("Urgency Level            : Level 2 (Urgent)\n");
        else if (urgencies[i] == 3) printf("Urgency Level            : Level 3 (Critical)\n");
        printf("-----------------------------------------------------------\n");
        printf("Base Consultation Fee    : LKR %.2f\n", baseFee);
        printf("Emergency Surcharge      : LKR %.2f (%d%%)\n", surcharge, surchargePct);
        printf("Ward Stay Cost (%2d Days) : LKR %.2f\n",daysAdmitted[i], wardCost);
        printf("-----------------------------------------------------------\n");
        printf("Gross Total Bill         : LKR %.2f\n", gross);
        printf("Age Subsidy Discount     : LKR -%.2f\n", discount);
        printf("-----------------------------------------------------------\n");
        printf("Final Payable Amount     : LKR %.2f\n", finalPayables[i]);
        if (urgencies[i] == 3) {
            printf("Estimated Waiting Time   : 0.00 mins (Immediate Attention)\n");
        } else {
            printf("Estimated Waiting Time   : %.2f mins\n", waitTime);
        }
        printf("===========================================================\n");
    }
}

void displayTriageList(char names[][50], int urgencies[], int patientCount) {
    if (patientCount == 0) {
        printf("No registered patients available.\n");
        return;
    }
    int indices[MAX_PATIENTS];
    for (int i = 0; i < patientCount; i++) indices[i] = i;

    for (int i = 0; i < patientCount - 1; i++) {
        for (int j = 0; j < patientCount - i - 1; j++) {
            if (urgencies[indices[j]] < urgencies[indices[j + 1]]) {
                int temp = indices[j];
                indices[j] = indices[j + 1];
                indices[j + 1] = temp;
            }
        }
    }

    printf("\n=====================================================================\n");
    printf("------------        Emergency Triage Sorting List        ------------\n");
    printf("=====================================================================\n");
    for (int i = 0; i < patientCount; i++) {
        int idx = indices[i];
        printf("Priority %d | Name: %-30s | Urgency Level: %d\n", i + 1, names[idx], urgencies[idx]);
    }
}

void displayAnalytics(int urgencies[], double finalPayables[], int bedOccupancy[NUM_WARDS][20], int patientCount) {
    printf("\n====================================================================\n");
    printf("--------       System Performance Reports & Analytics       --------\n");
    printf("====================================================================\n");
    int l1 = 0, l2 = 0, l3 = 0;
    double totalRevenue = 0.0;
    int highestIdx = 0;

    for (int i = 0; i < patientCount; i++) {
        if (urgencies[i] == 1) l1++;
        else if (urgencies[i] == 2) l2++;
        else if (urgencies[i] == 3) l3++;

        totalRevenue += finalPayables[i];
        if (finalPayables[i] > finalPayables[highestIdx]) highestIdx = i;
    }

    printf("Total Patients             : %d (Level 1: %d, Level 2: %d, Level 3: %d)\n", patientCount, l1, l2, l3);
    printf("Total Revenue Earned       : LKR %.2f\n", totalRevenue);

    if (patientCount > 0) {
        printf("Highest Paying Patient     : PAT-%d (LKR %.2f)\n", 1001 + highestIdx, finalPayables[highestIdx]);
    }

    printf("\nBed Occupancy Rates        :\n");
    for (int w = 0; w < NUM_WARDS; w++) {
        int occupied = 0;
        for (int b = 0; b < WARD_CAPACITIES[w]; b++) {
            if (bedOccupancy[w][b] == 1) occupied++;
        }
        double rate = ((double)occupied / WARD_CAPACITIES[w]) * 100.0;
        printf("- %s: %.2f%% (%d/%d beds)\n", WARD_NAMES[w], rate, occupied, WARD_CAPACITIES[w]);
    }
}

void saveBedStatusToFile(int bedOccupancy[NUM_WARDS][20]) {
    FILE *fp = fopen("beds_status.txt", "w");
    for (int i = 0; i < NUM_WARDS; i++) {
        for (int j = 0; j < WARD_CAPACITIES[i]; j++) {
            fprintf(fp, "%d ", bedOccupancy[i][j]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}

void loadBedStatusFromFile(int bedOccupancy[NUM_WARDS][20]) {
    FILE *fp = fopen("beds_status.txt", "r");
    if (!fp) return;
    for (int i = 0; i < NUM_WARDS; i++) {
        for (int j = 0; j < WARD_CAPACITIES[i]; j++) {
            if (fscanf(fp, "%d", &bedOccupancy[i][j]) != 1) break;
        }
    }
    fclose(fp);
}

void savePatientRecordsToFile(char names[][50], int ages[], int urgencies[], int specIDs[],
                              int wardAdmitted[], int wardIDs[], int daysAdmitted[],
                              double finalPayables[], int patientCount) {
    FILE *fp = fopen("patient_records.txt", "w");
    if (!fp) return;

    fprintf(fp, "%d\n", patientCount);
    for (int i = 0; i < patientCount; i++) {
        fprintf(fp, "%s|%d|%d|%d|%d|%d|%d|%.2f\n",
                names[i], ages[i], urgencies[i], specIDs[i],
                wardAdmitted[i], wardIDs[i], daysAdmitted[i], finalPayables[i]);
    }
    fclose(fp);
}

void loadPatientRecordsFromFile(char names[][50], int ages[], int urgencies[], int specIDs[],
                              int wardAdmitted[], int wardIDs[], int daysAdmitted[],
                              double finalPayables[], int queueCounts[NUM_SPECIALTIES], int *patientCount) {
    FILE *fp = fopen("patient_records.txt", "r");
    if (!fp) return;

    if (fscanf(fp, "%d\n", patientCount) != 1) {
        fclose(fp);
        return;
    }

    for (int i = 0; i < *patientCount; i++) {
        fscanf(fp, " %49[^|]|%d|%d|%d|%d|%d|%d|%lf\n",
               names[i], &ages[i], &urgencies[i], &specIDs[i],
               &wardAdmitted[i], &wardIDs[i], &daysAdmitted[i], &finalPayables[i]);

        int sIdx = specIDs[i] - 1;
        if (sIdx >= 0 && sIdx < NUM_SPECIALTIES) {
            queueCounts[sIdx]++;
        }
    }
    fclose(fp);
}
