#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include <sstream>
using namespace std;

//CONSTANTS========================================================================================
int choice;

const string INCIDENTS_FILE    = "DATA/incidents.csv";
const string SUSPECTS_FILE     = "DATA/suspects.csv";
const string USERS_FILE        = "DATA/users.txt";
const string TRANSACTIONS_FILE = "DATA/transactions.txt";


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
string transactionStatus[MAX_TRANSACTIONS];

// SEARCHING AND SORTING TARGETS
int targetID;
string keyCrime;
string keyLocation;
string keyUsername;

// counters
int incidentCount    = 0;
int suspectCount     = 0;
int userCount        = 0;
int transactionCount = 0;

// Function prototypes
bool isDuplicateUser(string username);
bool isValidIncidentID(int id);
void displayAdminMenu();
void displayUserMenu(int loggedInUserID);

//FUNCTIONS=========================================================================================

// Storage Module-----------------------------------------
void saveIncidentsToFile() {
    ofstream outfile (INCIDENTS_FILE);
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
    ofstream outfile (SUSPECTS_FILE);
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
        outfile.close();
    }
}

void saveUsersToFile() {
    ofstream outfile (USERS_FILE);
    if (outfile.is_open()) {
        for (int i = 0; i < userCount; i++) {
            outfile << userID[i] << "," 
                    << userName[i] << "," 
                    << userFullName[i] << ","
                    << userPassword[i] << "," 
                    << userArea[i] << "," 
                    << userRole[i] << "," 
                    << userRewardPoints[i] << endl;
        } 
        outfile.close();
    }

}

void saveTransactionsToFile(){
    ofstream outfile (TRANSACTIONS_FILE);
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
    ifstream infile (INCIDENTS_FILE);
    if (infile.is_open()) {
        string line;
        while (getline(infile, line) && incidentCount < MAX_INCIDENTS) {
            stringstream ss(line);
            string temp;
            getline(ss, temp, ','); incidentID[incidentCount] = stoi(temp);
            getline(ss, incidentCrime[incidentCount], ',');
            getline(ss, incidentLocation[incidentCount], ',');
            getline(ss, incidentDate[incidentCount], ',');
            getline(ss, incidentStatus[incidentCount], ',');
            incidentCount++;
        }
        infile.close();
    }
}

void loadSuspectsFromFile(){
    ifstream infile (SUSPECTS_FILE);
    if (infile.is_open()) {
        string line;
        while (getline(infile, line) && suspectCount < MAX_SUSPECTS) {
            stringstream ss(line);
            string temp;
            getline(ss, temp, ','); suspectID[suspectCount] = stoi(temp);
            getline(ss, temp, ','); suspectIncidentID[suspectCount] = stoi(temp);
            getline(ss, suspectName[suspectCount], ',');
            getline(ss, suspectHeight[suspectCount], ',');
            getline(ss, suspectBuild[suspectCount], ',');
            getline(ss, suspectClothing[suspectCount], ',');
            getline(ss, suspectLastLocation[suspectCount], ',');
            suspectCount++;
        }
        infile.close();
    }
}

void loadUsersFromFile(){
    ifstream infile (USERS_FILE);
    if (infile.is_open()) {
        string line;
        while (getline(infile, line) && userCount < MAX_USERS) {
            stringstream ss(line);
            string temp;
            getline(ss, temp, ','); userID[userCount] = stoi(temp);
            getline(ss, userName[userCount], ',');
            getline(ss, userFullName[userCount], ',');
            getline(ss, userPassword[userCount], ',');
            getline(ss, userArea[userCount], ',');
            getline(ss, userRole[userCount], ',');
            getline(ss, temp, ','); userRewardPoints[userCount] = stoi(temp);
            userCount++;
        }
        infile.close();
    }
}

void loadTransactionsFromFile(){
    ifstream infile (TRANSACTIONS_FILE);
    if (infile.is_open()) {
        string line;
        while (getline(infile, line) && transactionCount < MAX_TRANSACTIONS) {
            stringstream ss(line);
            string temp;
            getline(ss, temp, ','); transactionID[transactionCount] = stoi(temp);
            getline(ss, temp, ','); transactionUserID[transactionCount] = stoi(temp);
            getline(ss, temp, ','); transactionIncidentID[transactionCount] = stoi(temp);
            getline(ss, transactionTimestamp[transactionCount], ',');
            getline(ss, transactionTipType[transactionCount], ',');
            getline(ss, transactionStatus[transactionCount], ',');
            transactionCount++;
        }
        infile.close();
    }
}

// Input Module-------------------------------------------------
void addIncident() {
    if (incidentCount >= MAX_INCIDENTS) {
        cout << "Maximum incident limit reached. Cannot add more incidents.\n";
        return;
    }

    cout << "\n";
    cout << "▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄\n";
    cout << "██   ▄▄▄   ▄▄▄▄▄ ▄▄▄▄   ▄▄▄  ▄▄▄   ▄▄▄▄▄▄   ██    \n";
    cout << "██   ██▄█▄ ██▄▄  ██▄█▀ ██▀██ ██▄█▄   ██     ██\n";
    cout << "██   ██ ██ ██▄▄▄ ██    ▀███▀ ██ ██   ██     ██ \n";
    cout << "██▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄██\n";
    cout << "\n";

    cout << "Incident ID: ";
    cin >> incidentID[incidentCount];
    cin.ignore(); 
    cout << "\n";

    cout << "Crime Type: ";
    getline(cin, incidentCrime[incidentCount]);
    cout << "\n";

    cout << "Location: ";
    getline(cin, incidentLocation[incidentCount]);
    cout << "\n";

    cout << "Date (YYYY-MM-DD): ";
    getline(cin, incidentDate[incidentCount]);
    cout << "\n";
    cout << "\n";

    cout << "Status: ";
    getline(cin, incidentStatus[incidentCount]);
    cout << "\n";

    incidentCount++;

    cout << "\nIncident added successfully!\n";


    // Save data right away
    saveIncidentsToFile();
}
void addSuspect(){
    if (suspectCount >= MAX_SUSPECTS) {
        cout << "Maximum suspect limit reached. Cannot add more suspects.\n";
        return;
    }

    cout << "\n";
    cout << "▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄\n";
    cout << "██   ▄▄▄   ▄▄▄▄▄ ▄▄▄▄   ▄▄▄  ▄▄▄   ▄▄▄▄▄▄   ██    \n";
    cout << "██   ██▄█▄ ██▄▄  ██▄█▀ ██▀██ ██▄█▄   ██     ██\n";
    cout << "██   ██ ██ ██▄▄▄ ██    ▀███▀ ██ ██   ██     ██ \n";
    cout << "██▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄██\n";
    cout << "\n";

    cout << "Suspect ID: ";
    cin >> suspectID[suspectCount];
    cin.ignore();
    cout << "\n";

    cout << "Related Incident ID: ";
    cin >> suspectIncidentID[suspectCount];
    cin.ignore(); 
    cout << "\n";

    cout << "Name: (type N/A if not identified) ";
    getline(cin, suspectName[suspectCount]);
    cout << "\n";

    cout << "Height: ";
    getline(cin, suspectHeight[suspectCount]);
    cout << "\n";

    cout << "Build: ";
    getline(cin, suspectBuild[suspectCount]);
    cout << "\n";

    cout << "Clothing: ";
    getline(cin, suspectClothing[suspectCount]);
    cout << "\n";

    cout << "Last Known Location: ";
    getline(cin, suspectLastLocation[suspectCount]);
    cout << "\n";

    suspectCount++;

    cout << "\nSuspect added successfully!\n";

     // Save data right away
     saveSuspectsToFile();
}
void addUser(){
    if (userCount >= MAX_USERS) {
        cout << "Maximum user limit reached. Cannot add more users.\n";
        return;
    }

      userID[userCount] = userCount + 1;

    cout << "Username: ";
    cin >> userName[userCount];

    if (isDuplicateUser(userName[userCount])) {
        cout << "Username already exists. Please choose a different username.\n";
        return;
    }

    cout << "===== ADD USER =====\n";

    cin.ignore();

    cout << "Full Name: ";
    getline(cin, userFullName[userCount]);

    cout << "Password: ";
    getline(cin, userPassword[userCount]);

    cout << "Address: ";
    getline(cin, userArea[userCount]);

    cout << "Role (admin/user): ";
    getline(cin, userRole[userCount]);

    userRewardPoints[userCount] = 0;

    userCount++;

    cout << "\nUser registered successfully!\n";

     // Save data right away
     saveUsersToFile();


}

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
void sortIncidentsByID() {
      
    for (int i = 1; i < incidentCount; i++) {
        int key = incidentID[i];
        int j = i - 1;

        while (j >= 0 && incidentID[j] > key) {
            incidentID[j + 1] = incidentID[j];
            j--;
        }
    }     
}

void sortIncidentsByLocation() {

    for (int i = 1; i < incidentCount; i++) {
        string key = incidentLocation[i];
        int j = i - 1;

        while (j >= 0 && incidentLocation[j] > key) {
            incidentLocation[j + 1] = incidentLocation[j];
            j--;
        }
    }

     
}
int  searchIncidentByID(int id) {

    int low = 0;
    int high = incidentCount - 1;

    while (low <= high) {
        int mid = low + high / 2;
        if (incidentID[mid] == targetID) {
            return mid; //found
        } else if (incidentID[mid] < targetID) {
            low = mid + 1;
        } else {
            high = mid - 1;
        } 
    }

    return -1; //not found
}           
int  searchIncidentByLocation(string area) {
    // Implementation for searching incident by location

    int low = 0;
    int high = incidentCount - 1;

    while (low <= high) {

        int mid = low + high / 2;
        if (incidentLocation[mid] == keyLocation) {
            return mid;
        } else if (incidentLocation[mid] < keyLocation) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }        
    }
    
   return -1; //not found 
}
int  searchUserByUsername(string username) {
    // Implementation for searching user by username

    int low = 0;
    int high = userCount - 1;

    for (int i = 0; i < userCount; i++) {
        
        int mid = low + high / 2;
        if (userName[mid] == keyUsername) {
            return mid;
        } else if (userName[mid] < keyUsername) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
        }
        return -1; // not found
}

int  searchSuspectByIncidentID(int id) {
    // Implementation for searching suspect by incident ID

    int low = 0;
    int high = suspectCount - 1;

    for (int i = 0; i < suspectCount; i++) {

        int mid = low + high / 2;
        if (suspectIncidentID[mid] == targetID) {
            return mid;
        } else if (suspectIncidentID[mid] < targetID) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1; // not found
}

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
    cout << "\n";
    cout << "▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄\n";
    cout << "██                                                                        ██\n";
    cout << "██     ▄█████  ▄▄▄  ▄▄▄▄▄ ▄▄▄▄▄ ██     ██ ▄████▄ ██████ ▄█████ ██  ██     ██\n";
    cout << "██     ▀▀▀▄▄▄ ██▀██ ██▄▄  ██▄▄  ██ ▄█▄ ██ ██▄▄██   ██   ██     ██████     ██\n";
    cout << "██     █████▀ ██▀██ ██    ██▄▄▄  ▀██▀██▀  ██  ██   ██   ▀█████ ██  ██     ██\n";
    cout << "██                                                                        ██\n";
    cout << "██▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀██\n";
    cout << "██                                                                        ██\n";
    cout << "██    [1] Report                                                          ██\n";
    cout << "██    [2] List of Incidents                                               ██\n";
    cout << "██    [3] Reward                                                          ██\n";
    cout << "██    [4] Profile                                                         ██\n";
    cout << "██    [5] Logout                                                          ██\n";
    cout << "██                                                                        ██\n";
    cout << "██                                                                        ██\n";
    cout << "▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀\n";
    cout << "\n";
    cout << "Choice: ";
    cin >> choice;
}


void displayUserMenu(int loggedInUserID) {
    // report
    // incidents/suspects
    // reward
    // profile

    // recent incidents   
    cout << "▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄\n";
    cout << "██                                                                        ██\n";
    cout << "██     ▄█████  ▄▄▄  ▄▄▄▄▄ ▄▄▄▄▄ ██     ██ ▄████▄ ██████ ▄█████ ██  ██     ██\n";
    cout << "██     ▀▀▀▄▄▄ ██▀██ ██▄▄  ██▄▄  ██ ▄█▄ ██ ██▄▄██   ██   ██     ██████     ██\n";
    cout << "██     █████▀ ██▀██ ██    ██▄▄▄  ▀██▀██▀  ██  ██   ██   ▀█████ ██  ██     ██\n";
    cout << "██                                                                        ██\n";
    cout << "██▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀██\n";
    cout << "██                                                                        ██\n";
    cout << "██    [1] Report                                                          ██\n";
    cout << "██    [2] List of Incidents                                               ██\n";
    cout << "██    [3] Reward                                                          ██\n";
    cout << "██    [4] Profile                                                         ██\n";
    cout << "██    [5] Logout                                                          ██\n";
    cout << "██                                                                        ██\n";
    cout << "██                                                                        ██\n";
    cout << "▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀\n";
    cout << "\n";
    cout << "Choice: ";
    cin >> choice;
    cout << "\n";
    cout << "\n";
}

int loginUser() {
    string inputUser, inputPass;
    cout << "\n";
    cout << "▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄\n";
    cout << "██                               ██\n";
    cout << "██  ▄▄     ▄▄▄   ▄▄▄▄ ▄▄ ▄▄  ▄▄  ██\n";
    cout << "██  ██    ██▀██ ██ ▄▄ ██ ███▄██  ██\n";
    cout << "██  ██▄▄▄ ▀███▀ ▀███▀ ██ ██ ▀██  ██\n";
    cout << "██                               ██\n";
    cout << "▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀\n";
    cout << "\n";

    cout << "Username: ";
    getline (cin, inputUser);
    cout << "\n";

    cout << "Password: ";
    getline (cin, inputPass);
    cout << "\n";
  
    
    for (int i = 0; i < userCount; i++) {
        if (userName[i] == inputUser && userPassword[i] == inputPass) {
            cout << "\nLogin successful! Welcome, " << userFullName[i] << "!\n";
            if (userRole[i] == "admin") {
                displayAdminMenu();
            } else {
                displayUserMenu(userID[i]);
            }
            return userID[i];
        }
    }
    cout << "\nInvalid username or password. Please try again.\n";
    return 0;
    }

int registerUser() {

    cout << "\n";
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
    if (isDuplicateUser(userName[userCount])) {
        cin.ignore();
        cout << "Username already exists. Please choose a different username.\n";
        return -1;
    }
    cin.ignore();

    cout << "Full Name: ";
    getline(cin, userFullName[userCount]);

    cout << "Password: ";
    getline(cin, userPassword[userCount]);

    cout << "Address: ";
    getline(cin, userArea[userCount]);

    userRole[userCount] = "user";
    userRewardPoints[userCount] = 0;
    userID[userCount] = userCount + 1;

    userCount++;

    cout << "\nUser registered successfully!\n";

     // Save data right away
     saveUsersToFile();

    return userID[userCount - 1];
}

void startMenu() {

    cout << "\n";
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
    cin.ignore(); // Essential to clear buffer for next getline
    
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

//MAIN FUNCTION===================================================================================
int main() {

    //LOAD DATA FROM FILES AT STARTUP
    loadIncidentsFromFile();
    loadSuspectsFromFile();
    loadUsersFromFile();
    loadTransactionsFromFile();

    while (true) {
        startMenu();
    }

    return 0;
}
