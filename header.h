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

#endif
