#include "UNIVERSAL.h"

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
int loggedInUserID   = 0;

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
        int mid = low + (high - low) / 2;
        if (incidentID[mid] == id) {
            return mid; //found
        } else if (incidentID[mid] < id) {
            low = mid + 1;
        } else {
            high = mid - 1;
        } 
    }

    return -1;
}           
int  searchIncidentByLocation(string area) {
    // Implementation for searching incident by location

    int low = 0;
    int high = incidentCount - 1;

    while (low <= high) {

        int mid = low + (high - low) / 2;
        if (incidentLocation[mid] == area) {
            return mid;
        } else if (incidentLocation[mid] < area) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }        
    }
    
   return -1;
}

int  searchUserByUsername(string username) {
    // Implementation for searching user by username

    int low = 0;
    int high = userCount - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (userName[mid] == username) {
            return mid;
        } else if (userName[mid] < username) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

int  searchSuspectByIncidentID(int id) {
    // Implementation for searching suspect by incident ID

    int low = 0;
    int high = suspectCount - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (suspectIncidentID[mid] == id) {
            return mid;
        } else if (suspectIncidentID[mid] < id) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

// Notification Module-------------------------------------------------
void displayAllAlerts();
void displayAlertsByLocation(string area);
void displaySuspectDetails(int incidentID);

// Reward Module------------------------------------------------------
void submitTip(int userID, int incidentID) {
    
}
void approveReward(int transactionID) {

}
void displayUserRewards(int userID){

}

// UI Module---------------------------------------------------------

void startMenu() {
    system("cls");
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
    cout << "Choice: ";
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
            Sleep(5000);
            startMenu();
    }



}


//MAIN FUNCTION===================================================================================
int main() {

    // TEXT FORMATTING
    SetConsoleOutputCP(CP_UTF8);

    //LOAD DATA FROM FILES AT STARTUP
    loadIncidentsFromFile();
    loadSuspectsFromFile();
    loadUsersFromFile();
    loadTransactionsFromFile();
    loadNotifications();

    while (true) {
        startMenu();
    }

    return 0;
}
