#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 100

extern int bedOccupancy[4][20];
extern int patientIDs[MAX_PATIENTS];
extern char patientNames[MAX_PATIENTS][50];
extern int patientAges[MAX_PATIENTS];
extern int urgencyLevels[MAX_PATIENTS];
extern int specialtyIDs[MAX_PATIENTS];
extern int isAdmitted[MAX_PATIENTS];
extern int wardIDs[MAX_PATIENTS];
extern int daysAdmitted[MAX_PATIENTS];
extern int assignedBeds[MAX_PATIENTS];
extern double finalPayables[MAX_PATIENTS];

extern int totalPatients;
extern int specialtyQueueCounts[4];

extern const char *SPECIALTY_NAMES[4];
extern const double BASE_FEES[4];
extern const int AVG_TIMES[4];
extern const int DAILY_CAPS[4];

extern const char *WARD_NAMES[4];
extern const double WARD_RATES[4];
extern const int WARD_CAPACITIES[4];

int calculateWaitingTime(int specialtyIndex);

#endif
