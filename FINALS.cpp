#include <iostream>
#include <string>
#include <fstream>
using namespace std;

//CONSTANTS----------------------------------

//Constant array sizes for storing data
const int MAX_INCIDENTS    = 100;
const int MAX_SUSPECTS     = 100;
const int MAX_USERS        = 50;
const int MAX_TRANSACTIONS = 200;

// INCIDENTS 
int    incidentID[MAX_INCIDENTS];
string incidentCrime[MAX_INCIDENTS];
string incidentLocation[MAX_INCIDENTS];
string incidentDate[MAX_INCIDENTS];
string incidentStatus[MAX_INCIDENTS];

// SUSPECTS 
int    suspectID[MAX_SUSPECTS];
int    suspectIncidentID[MAX_SUSPECTS]; 
string suspectName[MAX_SUSPECTS];
string suspectHeight[MAX_SUSPECTS];
string suspectBuild[MAX_SUSPECTS];
string suspectClothing[MAX_SUSPECTS];
string suspectLastLocation[MAX_SUSPECTS];

// USERS 
int    userID[MAX_USERS];
string userName[MAX_USERS];
string userPassword[MAX_USERS];
string userArea[MAX_USERS];
string userRole[MAX_USERS];         
int    userRewardPoints[MAX_USERS];

// TRANSACTIONS 
int    transactionID[MAX_TRANSACTIONS];
int    transactionUserID[MAX_TRANSACTIONS];
int    transactionIncidentID[MAX_TRANSACTIONS];
string transactionTimestamp[MAX_TRANSACTIONS];
string transactionTipType[MAX_TRANSACTIONS];
string transactionStatus[MAX_TRANSACTIONS];;

// counters
int incidentCount    = 0;
int suspectCount     = 0;
int userCount        = 0;
int transactionCount = 0;

//FUNCTIONS----------------------------------------

// Storage Module
void saveIncidentsToFile();
void saveSuspectsToFile();
void saveUsersToFile();
void saveTransactionsToFile();
void loadIncidentsFromFile();
void loadSuspectsFromFile();
void loadUsersFromFile();
void loadTransactionsFromFile();

// Input Module
void addIncident() {

    // Save data right away
    saveIncidentsToFile();
}
void addSuspect();
void addUser();

// Processing Module
bool isValidIncidentID(int id);   
bool isValidUserID(int id);       
bool isAdminUser(int userID);     

// Sorting & Searching
void sortIncidentsByID();
void sortIncidentsByLocation();
int  searchIncidentByID(int id);           
int  searchIncidentByLocation(string area);
int  searchUserByUsername(string username);
int  searchSuspectByIncidentID(int id);

// Notification Module
void displayAllAlerts();
void displayAlertsByLocation(string area);
void displaySuspectDetails(int incidentID);

// Reward Module
void submitTip(int userID, int incidentID);
void approveReward(int transactionID);
void displayUserRewards(int userID);

// UI Module
void displayMainMenu();
void displayAdminMenu();
void displayUserMenu();
int loginUser();  

//MAIN FUNCTION----------------------------------------
int main() {

    //LOAD DATA FROM FILES AT STARTUP
    loadIncidentsFromFile();
    loadSuspectsFromFile();
    loadUsersFromFile();
    loadTransactionsFromFile();



    //SAVE DATA TO FILES BEFORE EXITING
    saveIncidentsToFile();
    saveSuspectsToFile();
    saveUsersToFile();
    saveTransactionsToFile();
    return 0;
}