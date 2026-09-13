#include "header.h"

int bedOccupancy[4][20] = {0};
int patientIDs[MAX_PATIENTS];
char patientNames[MAX_PATIENTS][50];
int patientAges[MAX_PATIENTS];
int urgencyLevels[MAX_PATIENTS];
int specialtyIDs[MAX_PATIENTS];
int isAdmitted[MAX_PATIENTS];
int wardIDs[MAX_PATIENTS];
int daysAdmitted[MAX_PATIENTS];
int assignedBeds[MAX_PATIENTS];
double finalPayables[MAX_PATIENTS];

int totalPatients = 0;
int specialtyQueueCounts[4] = {0};
