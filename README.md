# **Smart Hospital \& Resource Allocation System**



A modular, menu-driven C application designed for automated patient intake, bed allocation, emergency triage sorting, persistent file logging, and medical billing estimations.



### **📋 System Overview**



The **Smart Hospital \& Resource Allocation System** optimizes daily hospital operations using modular custom functions, lookup tables, and parallel array data structures\[cite: 1]. The system manages multi-specialty OPD queues, ward admissions, triage sorting, automated billing with subsidies/surcharges, dynamic bed occupancy tracking, persistent file logging, and analytics.



### ✨ **Key Features \& Functions**

###### 

1. ###### **Patient Registration \& Intelligent Billing ('registerPatient')**
* **Parallel Array Storage** : Stores patient names, ages, urgency levels, specialty IDs, ward stay details, and calculated payable amounts.
* **Emergency Surcharges**   : Calculates surcharges based on triage level.

&#x09;**Level 1 (Normal)**   : '0%' surcharge

&#x09;**Level 2 (Urgent)**   : '20%' surcharge

&#x09;**Level 3 (Critical)** : '50%' surcharge

* **Ward Allocation:** Assigns available beds across General, Paediatric, Surgical, and ICU wards.
* **Age Subsidy:** Applies a **15% discount** on the gross bill for patients aged **< 5 years** or **> 65 years**.
* **Automatic File Logging**: Appends patient registration entries directly to 'patient\_records.txt'.



###### **2. Formatted Billing Invoices ('displayAllBills')**

* Displays itemized billing invoices matching exact specifications.
* Outputs assigned ward details with bed numbers (e.g.: 'ICU (Bed #01)').
* Displays inline descriptive triage levels ('Level 1 (Normal)' , 'Level 2 (Urgent)' , 'Level 3 (Critical)').
* Displays estimated consultation waiting times (set to '0.00 mins (Immediate Attention)' for critical cases).



###### **3. Emergency Triage Priority Sorting ('displayTriageList')**

* Implements a **Bubble Sorting Algorithm** to sort and display patients by urgency level in descending priority order (Level 3 Critical → Level 2 Urgent → Level 1 Normal).



###### **4. Performance Reports \& Analytics ('displayAnalytics')**

* Summarizes total patient registrations categorized by urgency level.
* Displays total revenue earned across all consultations and ward stays.
* Identifies and displays the highest-paying patient record.
* Calculates real-time **bed occupancy percentages** for all hospital wards.

###### 

###### **5. Persistent File Storage ('saveBedStatusToFile' \& 'loadBedStatusFromFile')**

* 'beds\_status.txt'     : Automatically loads bed occupancy matrix states on launch ('"r"') and updates them on file ('"w"') after new admissions.
* 'patient\_records.txt' : Appends permanent logs ('"a"') containing patient name, age, urgency level, and final bill amount upon intake.

###### 

###### **6. User Interface \& Screen Control ('clearScreen' \& 'pauseScreen')**

* Cross-platform screen clearing utility ('cls' on Windows / 'clear' on Linux/macOS) executed upon entering each menu option while preserving all in-memory patient data.

# 

### **🛠️ Data Structures \& Lookup Tables**

# 

* ###### **Doctor Specialties Data**

|**Speciality ID**|**Specialty Name**|**Base Consultation Fee**|**Consult Time / Patient**|
|-|-|-|-|
|1|General  Practice (OPD)|LKR 1,500.00|15 mins|
|2|Paediatrics|LKR 2,500.00|20 mins|
|3|Cardiology|LKR 4,500.00|30 mins|
|4|Neurology|LKR 5,000.00|30 mins|

# 

* ###### **Hospital Wards Data**

|**Ward ID**|**Ward Name**|**Daily Bed Rate**|**Total Capacity**|
|-|-|-|-|
|1|General Ward|LKR 3000.00|20 Beds|
|2|Paediatric Ward|LKR 6000.00|10 Beds|
|3|Surgical Ward|LKR 12000.00|10 Beds|
|4|ICU ( Intensive Care )|LKR 25000.00|05 Beds|

# 

### **📁 Repository Structure**

###### 

###### **text**

###### **Smart-Hospital-Resource-Allocation-System**

###### &#x09;├── **main.c**              # Application entry point and interactive menu loop

###### &#x09;├── **hospital.h**          # Header file containing macros and function signatures

###### &#x09;├── **hospital.c**          # Core implementations of hospital operations \& calculations

###### &#x09;├── **beds\_status.txt**     # Persistent bed occupancy matrix record file

###### &#x09;├── **patient\_records.txt** # Persistent patient registration and billing log file

###### &#x09;├── **.gitignore**          # Configured git ignore file for build artifacts

###### &#x09;└── **README.md**           # Project documentation

