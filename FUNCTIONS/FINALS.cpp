#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
using namespace std;

//CONSTANTS========================================================================================

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
string userFullName[MAX_USERS];
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

//FUNCTIONS=========================================================================================

// Storage Module-----------------------------------------
void saveIncidentsToFile() {
    ofstream outfile ("incidents.txt");
    if (outfile.is_open()) {
        for (int i = 0; i < incidentCount; i++) {
            outfile << incidentID[i] << "," 
                    << incidentCrime[i] << "," 
                    << incidentLocation[i] << "," 
                    << incidentDate[i] << "," 
                    << incidentStatus[i] << endl;
        } 
    }
    outfile.close();
}

void saveSuspectsToFile() {
    ofstream outfile ("suspects.txt");
    if (outfile.is_open()) {
        for (int i = 0; i < suspectCount; i++) {
            outfile << suspectID[i] << "," 
                    << suspectIncidentID[i] << "," 
                    << suspectName[i] << "," 
                    << suspectHeight[i] << "," 
                    << suspectBuild[i] << "," 
                    << suspectClothing[i] << "," 
                    << suspectLastLocation[i] << endl;
        } 
    }
}

void saveUsersToFile() {
    ofstream outfile ("users.txt");
    if (outfile.is_open()) {
        for (int i = 0; i < userCount; i++) {
            outfile << userID[i] << "," 
                    << userName[i] << "," 
                    << userPassword[i] << "," 
                    << userArea[i] << "," 
                    << userRole[i] << "," 
                    << userRewardPoints[i] << endl;
        } 
    }

}

void saveTransactionsToFile(){
    ofstream outfile ("transactions.txt");
    if (outfile.is_open()) {
        for (int i = 0; i < transactionCount; i++) {
            outfile << transactionID[i] << ","
                    << transactionUserID[i] << ","
                    << transactionIncidentID[i] << ","
                    << transactionTimestamp[i] << ","
                    << transactionTipType[i] << ","
                    << transactionStatus[i] << endl;
        }
    }
    outfile.close();
}

void loadIncidentsFromFile(){
    ifstream infile ("incidents.txt");
    if (infile.is_open()) {
        string line;
        while (getline(infile, line)) {
            incidentCount++;
        }
        
    }
}

void loadSuspectsFromFile(){
    ifstream infile ("suspects.txt");
    if (infile.is_open()) {
        string line;
        while (getline(infile, line)) {
            suspectCount++;
        }
        
    }
}

void loadUsersFromFile(){
    ifstream infile ("users.txt");
    if (infile.is_open()) {
        string line;
        while (getline(infile, line)) {
            userCount++;
        }
    }
}

void loadTransactionsFromFile(){
    ifstream infile ("transactions.txt");
    if (infile.is_open()) {
        string line;
        while (getline(infile, line)) {
            transactionCount++;
        }
    }
}

// Input Module-------------------------------------------------
void addIncident() {

    // Save data right away
    saveIncidentsToFile();
}
void addSuspect();
void addUser();
int loginUser();
int registerUser();

// Processing Module---------------------------------------------
bool isValidIncidentID(int id) {
    for (int i = 0; i < incidentCount; i++) {
        if (incidentID[i] == id) {
            return true;
        }
    }
    return false;
}

bool isValidUserID(int id) {
    for (int i = 0; i < userCount; i++) {
        if (userID[i] == id) {
            return true;
        }
    }
    return false;
}

bool isDuplicateUser(string username) {
    for (int i = 0; i < userCount; i++) {
        if (userName[i] == username) {
            return true;
        }
    }
    return false;
}

bool isAdminUser(int id) {
    for (int i = 0; i < userCount; i++) {
        if (userID[i] == id && userRole[i] == "admin") {
            return true;
        }
    }
    return false;
}


// Sorting & Searching-------------------------------------------------
void sortIncidentsByID();
void sortIncidentsByLocation();
int  searchIncidentByID(int id);           
int  searchIncidentByLocation(string area);
int  searchUserByUsername(string username);
int  searchSuspectByIncidentID(int id);

// Notification Module-------------------------------------------------
void displayAllAlerts();
void displayAlertsByLocation(string area);
void displaySuspectDetails(int incidentID);

// Reward Module------------------------------------------------------
void submitTip(int userID, int incidentID);
void approveReward(int transactionID);
void displayUserRewards(int userID);

// UI Module---------------------------------------------------------
void displayAdminMenu() {
    // manage reports
    
    // rewards
    // profile

    // list of incidents
}


void displayUserMenu() {
    // report
    // incidents/suspects
    // reward
    // profile

    // list of incidents   
}

void startMenu() {
       int choice;

    cout << "▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄\n";
    cout << "██                                                                        ██\n";
    cout << "██     ▄█████  ▄▄▄  ▄▄▄▄▄ ▄▄▄▄▄ ██     ██ ▄████▄ ██████ ▄█████ ██  ██     ██\n";
    cout << "██     ▀▀▀▄▄▄ ██▀██ ██▄▄  ██▄▄  ██ ▄█▄ ██ ██▄▄██   ██   ██     ██████     ██\n";
    cout << "██     █████▀ ██▀██ ██    ██▄▄▄  ▀██▀██▀  ██  ██   ██   ▀█████ ██  ██     ██\n";
    cout << "██                                                                        ██\n";
    cout << "██▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀██\n";
    cout << "██                                                                        ██\n";
    cout << "██    [1] Login                                                           ██\n";
    cout << "██    [2] Register                                                        ██\n";
    cout << "██    [3] Exit                                                            ██\n";
    cout << "██                                                                        ██\n";
    cout << "██                                                                        ██\n";
    cout << "▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀\n";
    cout << "\n";
    cout << "Choice:";
    cin >> choice;
    
    switch (choice) {
        case 1:
            loginUser();
            break;
        case 2:
            registerUser();
            break;
        case 3:
            cout << "Exiting...\n";
            exit(0);
        default:
            cout << "Invalid choice. Please try again.\n";
            startMenu();
    }



}

 



int loginUser() {
    string inputUser, inputPass;
    cout << "▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄\n";
    cout << "██                               ██\n";
    cout << "██  ▄▄     ▄▄▄   ▄▄▄▄ ▄▄ ▄▄  ▄▄  ██\n";
    cout << "██  ██    ██▀██ ██ ▄▄ ██ ███▄██  ██\n";
    cout << "██  ██▄▄▄ ▀███▀ ▀███▀ ██ ██ ▀██  ██\n";
    cout << "██                               ██\n";
    cout << "▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀\n";
    cout << "\n";

    cout << "Username: " << endl;
    getline (cin, inputUser);

    cout << "Password: " << endl;
    getline (cin, inputPass);
    
    return 0;
    }

int registerUser() {

    cout << "▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄\n";
    cout << "██                                                             ██\n";
    cout << "██    █████▄  ██████  ▄████  ██ ▄█████ ██████ ██████ █████▄    ██\n";
    cout << "██    ██▄▄██▄ ██▄▄   ██  ▄▄▄ ██ ▀▀▀▄▄▄   ██   ██▄▄   ██▄▄██    ██\n";
    cout << "██    ██   ██ ██▄▄▄▄  ▀███▀  ██ █████▀   ██   ██▄▄▄▄ ██   ██   ██\n";
    cout << "██                                                             ██\n";
    cout << "▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀\n";
    cout << "\n";

    cout << "Username: ";
    cin >> userName[userCount];

    cout << "Full Name:";
    cin >> userFullName[userCount];

    cout << "Password: ";
    cin >> userPassword[userCount];

    cout << "Address: ";
    cin >> userArea[userCount];
    
    return 0;
}

//MAIN FUNCTION===================================================================================
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

    startMenu();
    return 0;
}