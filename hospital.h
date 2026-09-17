#ifndef HOSPITAL_H
#define HOSPITAL_H

#define MAX_PATIENTS 100
#define NUM_SPECIALTIES 4
#define NUM_WARDS 4

extern const char SPECIALTY_NAMES[NUM_SPECIALTIES][30];
extern const double BASE_FEES[NUM_SPECIALTIES];
extern const int CONSULT_TIMES[NUM_SPECIALTIES];
extern const int DAILY_CAPS[NUM_SPECIALTIES];

extern const char WARD_NAMES[NUM_WARDS][30];
extern const double WARD_RATES[NUM_WARDS];
extern const int WARD_CAPACITIES[NUM_WARDS];

void clearScreen(void);
void pauseScreen(void);

void initializeSystem(int bedOccupancy[NUM_WARDS][20], int queueCounts[NUM_SPECIALTIES]);
void registerPatient(char names[][50], int ages[], int urgencies[], int specIDs[],
                     int wardAdmitted[], int wardIDs[], int daysAdmitted[],
                     double finalPayables[], int bedOccupancy[NUM_WARDS][20],
                     int queueCounts[NUM_SPECIALTIES], int *patientCount);
void displayAllBills(char names[][50], int ages[], int urgencies[], int specIDs[],
                     int wardAdmitted[], int wardIDs[], int daysAdmitted[],
                     double finalPayables[], int queueCounts[NUM_SPECIALTIES], int patientCount);
void displayTriageList(char names[][50], int urgencies[], int patientCount);
void displayAnalytics(int urgencies[], double finalPayables[], int bedOccupancy[NUM_WARDS][20], int patientCount);
void saveBedStatusToFile(int bedOccupancy[NUM_WARDS][20]);
void loadBedStatusFromFile(int bedOccupancy[NUM_WARDS][20]);

#endif
