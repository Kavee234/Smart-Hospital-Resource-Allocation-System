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

const char *SPECIALTY_NAMES[4] = {"General Practice (OPD)", "Paediatrics", "Cardiology", "Neurology"};
const double BASE_FEES[4]      = {1500.00, 2500.00, 4500.00, 5000.00};
const int AVG_TIMES[4]         = {15, 20, 30, 30};
const int DAILY_CAPS[4]        = {30, 20, 12, 10};

const char *WARD_NAMES[4]      = {"General Ward", "Paediatric Ward", "Surgical Ward", "ICU"};
const double WARD_RATES[4]     = {3000.00, 6000.00, 12000.00, 25000.00};
const int WARD_CAPACITIES[4]   = {20, 10, 10, 5};

int calculateWaitingTime(int specialtyIndex) {
    return specialtyQueueCounts[specialtyIndex] * AVG_TIMES[specialtyIndex];
}

double calculateSurcharge(double baseFee, int urgency) {
    if (urgency == 2) return baseFee * 0.20;
    if (urgency == 3) return baseFee * 0.50;
    return 0.0;
}
