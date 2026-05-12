#include "UNIVERSAL.h"

namespace fs = std::filesystem;

static string resolveDataFile(const string& filename) {
    fs::path cwd = fs::current_path();
    fs::path candidate1 = cwd / "DATA" / filename;
    if (fs::exists(candidate1.parent_path()) || fs::exists(candidate1)) {
        return candidate1.string();
    }

    fs::path candidate2 = cwd / ".." / "DATA" / filename;
    if (fs::exists(candidate2.parent_path()) || fs::exists(candidate2)) {
        return candidate2.string();
    }

    // Fallback to local DATA path if the folder exists in the current directory.
    fs::path fallback1 = fs::path("DATA") / filename;
    if (fs::exists(fallback1.parent_path())) {
        return fallback1.string();
    }

    // Fallback to parent directory DATA path.
    fs::path fallback2 = fs::path("..") / "DATA" / filename;
    if (fs::exists(fallback2.parent_path())) {
        return fallback2.string();
    }

    return fallback1.string();
}

//CONSTANTS========================================================================================
int choice;

const string INCIDENTS_FILE    = resolveDataFile("incidents.csv");
const string SUSPECTS_FILE     = resolveDataFile("suspects.csv");
const string USERS_FILE        = resolveDataFile("users.csv");
const string ADMINS_FILE       = resolveDataFile("admin.csv");
const string TRANSACTIONS_FILE = resolveDataFile("transactions.csv");

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

// ADMIN SECURITY
string userAuthorityType[MAX_USERS];  // Type of authority: police_officer, detective, captain, etc.
string userStation[MAX_USERS];        

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
        outfile.close();
    } else {
        cout << "CRITICAL ERROR: Could not save to " << INCIDENTS_FILE << ". Ensure 'DATA' folder exists.\n";
        Sleep(1500);
    }
}

void saveSuspectsToFile() {
    fs::path suspectsPath = SUSPECTS_FILE;
    if (!suspectsPath.parent_path().empty() && !fs::exists(suspectsPath.parent_path())) {
        fs::create_directories(suspectsPath.parent_path());
    }

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
    } else {
        cout << "CRITICAL ERROR: Could not save to " << SUSPECTS_FILE << ". Ensure 'DATA' folder exists.\n";
        Sleep(1500);
    }
}

void saveUsersToFile() {
    fs::path usersPath = USERS_FILE;
    if (!usersPath.parent_path().empty() && !fs::exists(usersPath.parent_path())) {
        fs::create_directories(usersPath.parent_path());
    }

    ofstream outfile (USERS_FILE);
    if (outfile.is_open()) {
        for (int i = 0; i < userCount; i++) {
            if (userRole[i] == "user") {
                outfile << userID[i] << "," 
                        << userName[i] << "," 
                        << userFullName[i] << ","
                        << userPassword[i] << "," 
                        << userArea[i] << "," 
                        << userRole[i] << "," 
                        << userRewardPoints[i] << ","
                        << userAuthorityType[i] << ","
                        << userStation[i] << endl;
            }
        } 
        outfile.close();
    } else {
        cout << "CRITICAL ERROR: Could not save to " << USERS_FILE << ". Ensure 'DATA' folder exists.\n";
        Sleep(1500);
    }
}

void saveAdminsToFile() {
    fs::path adminsPath = ADMINS_FILE;
    if (!adminsPath.parent_path().empty() && !fs::exists(adminsPath.parent_path())) {
        fs::create_directories(adminsPath.parent_path());
    }

    ofstream outfile (ADMINS_FILE);
    if (outfile.is_open()) {
        for (int i = 0; i < userCount; i++) {
            if (userRole[i] == "admin") {
                outfile << userID[i] << "," 
                        << userName[i] << "," 
                        << userFullName[i] << ","
                        << userPassword[i] << "," 
                        << userArea[i] << "," 
                        << userRole[i] << "," 
                        << userRewardPoints[i] << ","
                        << userAuthorityType[i] << ","
                        << userStation[i] << endl;
            }
        } 
        outfile.close();
    } else {
        cout << "CRITICAL ERROR: Could not save to " << USERS_FILE << ". Ensure 'DATA' folder exists.\n";
        Sleep(1500);
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
        outfile.close();
    } else {
        cout << "CRITICAL ERROR: Could not save to " << TRANSACTIONS_FILE << ". Ensure 'DATA' folder exists.\n";
        Sleep(1500);
    }
}

void loadIncidentsFromFile(){
    ifstream infile (INCIDENTS_FILE);
    if (infile.is_open()) {
        string line;
        while (getline(infile, line) && incidentCount < MAX_INCIDENTS) {
            if (line.empty()) continue;
            stringstream ss(line);
            string temp;
            try {
                if (!getline(ss, temp, ',')) continue;
                incidentID[incidentCount] = stoi(temp);
                getline(ss, incidentCrime[incidentCount], ',');
                getline(ss, incidentLocation[incidentCount], ',');
                getline(ss, incidentDate[incidentCount], ',');
                getline(ss, incidentStatus[incidentCount], ',');
                incidentCount++;
            } catch (const std::exception&) {
                continue;
            }
        }
        infile.close();
    }
}

void loadSuspectsFromFile(){
    ifstream infile (SUSPECTS_FILE);
    if (infile.is_open()) {
        string line;
        while (getline(infile, line) && suspectCount < MAX_SUSPECTS) {
            if (line.empty()) continue;
            stringstream ss(line);
            string temp;
            try {
                if (!getline(ss, temp, ',')) continue; suspectID[suspectCount] = stoi(temp);
                if (!getline(ss, temp, ',')) continue; suspectIncidentID[suspectCount] = stoi(temp);
                getline(ss, suspectName[suspectCount], ',');
                getline(ss, suspectHeight[suspectCount], ',');
                getline(ss, suspectBuild[suspectCount], ',');
                getline(ss, suspectClothing[suspectCount], ',');
                getline(ss, suspectLastLocation[suspectCount], ',');
                suspectCount++;
            } catch (const std::exception&) {
                continue;
            }
        }
        infile.close();
    }
}

void loadUsersFromFile(){
    ifstream infile (USERS_FILE);
    if (infile.is_open()) {
        string line;
        while (getline(infile, line) && userCount < MAX_USERS) {
            if (line.empty()) continue;
            stringstream ss(line);
            string temp;
            try {
                if (!getline(ss, temp, ',')) continue; userID[userCount] = stoi(temp);
                getline(ss, userName[userCount], ',');
                getline(ss, userFullName[userCount], ',');
                getline(ss, userPassword[userCount], ',');
                getline(ss, userArea[userCount], ',');
                getline(ss, userRole[userCount], ',');
                if (!getline(ss, temp, ',')) continue; userRewardPoints[userCount] = stoi(temp);
                getline(ss, userAuthorityType[userCount], ',');
                getline(ss, userStation[userCount], ',');
                userCount++;
            } catch (const std::exception&) {
                continue;
            }
        }
        infile.close();
    }
}

void loadAdminsFromFile(){
    ifstream infile (ADMINS_FILE);
    if (infile.is_open()) {
        string line;
        while (getline(infile, line) && userCount < MAX_USERS) {
            if (line.empty()) continue;
            stringstream ss(line);
            string temp;
            try {
                if (!getline(ss, temp, ',')) continue; userID[userCount] = stoi(temp);
                getline(ss, userName[userCount], ',');
                getline(ss, userFullName[userCount], ',');
                getline(ss, userPassword[userCount], ',');
                getline(ss, userArea[userCount], ',');
                getline(ss, userRole[userCount], ',');
                userRole[userCount] = "admin";
                if (!getline(ss, temp, ',')) continue; userRewardPoints[userCount] = stoi(temp);
                getline(ss, userAuthorityType[userCount], ',');
                getline(ss, userStation[userCount], ',');
                userCount++;
            } catch (const std::exception&) {
                continue;
            }
        }
        infile.close();
    }
}

void loadTransactionsFromFile(){
    ifstream infile (TRANSACTIONS_FILE);
    if (infile.is_open()) {
        string line;
        while (getline(infile, line) && transactionCount < MAX_TRANSACTIONS) {
            if (line.empty()) continue;
            stringstream ss(line);
            string temp;
            try {
                if (!getline(ss, temp, ',')) continue; transactionID[transactionCount] = stoi(temp);
                if (!getline(ss, temp, ',')) continue; transactionUserID[transactionCount] = stoi(temp);
                if (!getline(ss, temp, ',')) continue; transactionIncidentID[transactionCount] = stoi(temp);
                getline(ss, transactionTimestamp[transactionCount], ',');
                getline(ss, transactionTipType[transactionCount], ',');
                getline(ss, transactionStatus[transactionCount], ',');
                transactionCount++;
            } catch (const std::exception&) {
                continue;
            }
        }
        infile.close();
    }
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

bool isDuplicateUser(string username, string role) {
    for (int i = 0; i < userCount; i++) {
        if (userName[i] == username && userRole[i] == role) {
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

bool isAuthorized(int id) {
    for (int i = 0; i < userCount; i++) {
        if (id == userID[i] && !userAuthorityType[i].empty() && userAuthorityType[i] != "none") {
            return true;
        }
    }
    return false;
}


// Sorting & Searching-------------------------------------------------
void sortIncidentsByID() {
    for (int i = 1; i < incidentCount; i++) {
        // Store the current element's data
        int keyID = incidentID[i];
        string keyCrime = incidentCrime[i];
        string keyLocation = incidentLocation[i];
        string keyDate = incidentDate[i];
        string keyStatus = incidentStatus[i];
        
        int j = i - 1;
        
        // Shift elements that are greater than key
        while (j >= 0 && incidentID[j] > keyID) {
            incidentID[j + 1] = incidentID[j];
            incidentCrime[j + 1] = incidentCrime[j];
            incidentLocation[j + 1] = incidentLocation[j];
            incidentDate[j + 1] = incidentDate[j];
            incidentStatus[j + 1] = incidentStatus[j];
            j--;
        }
        
        // Place the key in its correct position
        incidentID[j + 1] = keyID;
        incidentCrime[j + 1] = keyCrime;
        incidentLocation[j + 1] = keyLocation;
        incidentDate[j + 1] = keyDate;
        incidentStatus[j + 1] = keyStatus;
    }
}

void sortIncidentsByLocation() {
    for (int i = 1; i < incidentCount; i++) {
        // Store the current element's data
        string keyLocation = incidentLocation[i];
        int keyID = incidentID[i];
        string keyCrime = incidentCrime[i];
        string keyDate = incidentDate[i];
        string keyStatus = incidentStatus[i];
        
        int j = i - 1;
        
        // Shift elements that are greater than key
        while (j >= 0 && incidentLocation[j] > keyLocation) {
            incidentLocation[j + 1] = incidentLocation[j];
            incidentID[j + 1] = incidentID[j];
            incidentCrime[j + 1] = incidentCrime[j];
            incidentDate[j + 1] = incidentDate[j];
            incidentStatus[j + 1] = incidentStatus[j];
            j--;
        }
        
        // Place the key in its correct position
        incidentLocation[j + 1] = keyLocation;
        incidentID[j + 1] = keyID;
        incidentCrime[j + 1] = keyCrime;
        incidentDate[j + 1] = keyDate;
        incidentStatus[j + 1] = keyStatus;
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

// Reward Module------------------------------------------------------

void submitTip(int tipUserID, int tipIncidentID) {
        system("cls");
        cout << "▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄\n";
        cout << "██                                               ██\n";
        cout << "██     ▄▄▄▄  ▄▄▄▄▄ ▄▄   ▄▄  ▄▄▄  ▄▄▄▄  ▄▄▄▄      ██\n";
        cout << "██     ██▄█▄ ██▄▄  ██ ▄ ██ ██▀██ ██▄█▄ ██▀██     ██\n";
        cout << "██     ██ ██ ██▄▄▄  ▀█▀█▀  ██▀██ ██ ██ ████▀     ██\n";
        cout << "██                                               ██\n";
        cout << "▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀  SUBMIT TIP  ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀\n";
        cout << "\n";

    // If no incident ID was provided (passed as 0 from the menu), ask for it
    if (tipIncidentID <= 0) {
        cout << " ACTIVE INCIDENTS FOR TIP SUBMISSION:\n";
        cout << " ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄\n";

        if (incidentCount == 0) {
            cout << "\n  [!] No incidents reported yet.\n";
        } else {
            for (int i = 0; i < incidentCount; i++) {
                cout << "\n";
                cout << "  ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀\n";
                cout << "    Incident ID: " << incidentID[i] << endl;
                cout << "    Crime:       " << incidentCrime[i] << endl;
                cout << "    Location:    " << incidentLocation[i] << endl;
                cout << "    Date:        " << incidentDate[i] << endl;
                cout << "    Status:      " << incidentStatus[i] << endl;
                cout << "  ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀\n";
            }
        }
        cout << "\n ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄\n\n";

        cout << "Enter Incident ID to submit tip for (or 0 to go back): ";
        cin >> tipIncidentID;
        cin.ignore(); // Clear newline from buffer
    }

    if (tipIncidentID == 0) return;

    system("cls");

    cout << "▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄\n";
    cout << "██                                               ██\n";
    cout << "██     ▄▄▄▄  ▄▄▄▄▄ ▄▄   ▄▄  ▄▄▄  ▄▄▄▄  ▄▄▄▄      ██\n";
    cout << "██     ██▄█▄ ██▄▄  ██ ▄ ██ ██▀██ ██▄█▄ ██▀██     ██\n";
    cout << "██     ██ ██ ██▄▄▄  ▀█▀█▀  ██▀██ ██ ██ ████▀     ██\n";
    cout << "██                                               ██\n";
    cout << "▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀  SUBMIT TIP  ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀\n";
    cout << "\n";

    if (!isValidIncidentID(tipIncidentID)) {
        cout << "Error: Incident ID " << tipIncidentID << " does not exist." << endl;
        cout << "\nPress Enter to return..." << endl;
        cin.get();
        return;
    }

    // check if the user actually exists
    if (!isValidUserID(tipUserID)) {
        cout << "Error: User ID " << tipUserID << " does not exist." << endl;
        cout << "\nPress Enter to return..." << endl;
        cin.get();
        return;
    }

    // check if transaction storage is full
    if (transactionCount >= MAX_TRANSACTIONS) {
        cout << "Error: Transaction storage is full." << endl;
        cout << "\nPress Enter to return..." << endl;
        cin.get();
        return;
    }

    // ask for tip details
    string tipType, reportedLocation;

    cout << "Tip Type (sighting / photo / information): ";
    getline(cin, tipType);

    cout << "Reported Location: ";
    getline(cin, reportedLocation);

    // get current timestamp (simple version)
    string timestamp;
    cout << "Enter date and time (e.g. 2025-04-21 14:30): ";
    getline(cin, timestamp);

    // store into transaction arrays
    transactionID[transactionCount]         = transactionCount + 1;
    transactionUserID[transactionCount]     = tipUserID;
    transactionIncidentID[transactionCount] = tipIncidentID;
    transactionTimestamp[transactionCount]  = timestamp;
    transactionTipType[transactionCount]    = tipType;
    transactionStatus[transactionCount]     = "pending";

    transactionCount++;

    // save immediately so data isnt lost
    saveTransactionsToFile();

    cout << "\n";
    cout << "\nTip submitted successfully! Status: PENDING" << endl;
    cout << "Transaction ID: " << transactionCount << endl;
    cout << "\nPress Enter to return to the Rewards Menu..." << endl;
    cin.ignore(1000, '\n');
    cin.get();
}

void approveReward() {
    int transactionId = 0;

        system("cls");
        cout << "▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄\n";
        cout << "██                                               ██\n";
        cout << "██     ▄▄▄▄  ▄▄▄▄▄ ▄▄   ▄▄  ▄▄▄  ▄▄▄▄  ▄▄▄▄      ██\n";
        cout << "██     ██▄█▄ ██▄▄  ██ ▄ ██ ██▀██ ██▄█▄ ██▀██     ██\n";
        cout << "██     ██ ██ ██▄▄▄  ▀█▀█▀  ██▀██ ██ ██ ████▀     ██\n";
        cout << "██                                               ██\n";
        cout << "▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀  APPROVE REWARD  ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀\n";
        cout << "\n";

    if (transactionCount == 0) {
        cout << "  [!] No tips have been submitted yet.\n";
        cout << "\n  Press Enter to return...";
        cin.get();
        return;
    }

    cout << "\n▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀ PENDING TIPS ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀\n";

    bool foundPending = false;
    for (int i = 0; i < transactionCount; i++) {
        if (transactionStatus[i] == "pending") {
            foundPending = true;
            cout << "\n";
            cout << "  ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀\n";
            cout << "  Tip #" << (i + 1) << ":" << endl;
            cout << "    Transaction ID: " << transactionID[i] << endl;
            cout << "    User ID:        " << transactionUserID[i] << endl;
            cout << "    Incident ID:    " << transactionIncidentID[i] << endl;
            cout << "    Submitted:      " << transactionTimestamp[i] << endl;
            cout << "    Tip Type:       " << transactionTipType[i] << endl;
            cout << "    Status:         " << transactionStatus[i] << endl;
            cout << "  ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀\n";
        }
    }
    if (!foundPending) {
        cout << "\n  [!] No pending tips available for approval.\n";
    }
   
    cout << "\n▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀ APPROVED TIPS ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀\n";
    bool foundApproved = false;
    for (int i = 0; i < transactionCount; i++) {
        if (transactionStatus[i] == "reward-approved") {
            foundApproved = true;
            cout << "\n";
            cout << "  ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀\n";
            cout << "  Tip #" << (i + 1) << ":" << endl;
            cout << "    Transaction ID: " << transactionID[i] << endl;
            cout << "    User ID:        " << transactionUserID[i] << endl;
            cout << "    Incident ID:    " << transactionIncidentID[i] << endl;
            cout << "    Submitted:      " << transactionTimestamp[i] << endl;
            cout << "    Tip Type:       " << transactionTipType[i] << endl;
            cout << "    Status:         " << transactionStatus[i] << endl;
            cout << "  ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀\n";
        }
    }
    if (!foundApproved) {
        cout << "\n  [!] No approved tips found.\n";
    }
    cout << "\n ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄\n\n";

        cout << "Transaction ID to approve (or 0 to go back): ";
        cin >> transactionId;
        cin.ignore(); // clear newline from input buffer

        if (transactionId == 0) return;

        system("cls");

    // find the transaction
    int index = -1;
    for (int i = 0; i < transactionCount; i++) {
        if (transactionID[i] == transactionId) {
            index = i;
            break;
        }
    }

    // transaction not found
    if (index == -1) {
        cout << "Error: Transaction ID " << transactionId << " not found." << endl;
        cout << "\nPress Enter to return...";
        cin.get();
        return;
    }

    // check if already approved
    if (transactionStatus[index] == "reward-approved") {
        cout << "Error: Transaction " << transactionId << " is already approved." << endl;
        cout << "\nPress Enter to return...";
        cin.get();
        return;
    }

    // approve the transaction
    transactionStatus[index] = "reward-approved";

    // find the user and add reward points
    
    int pointsAwarded = 100; 
    for (int i = 0; i < userCount; i++) {
        if (userID[i] == transactionUserID[index]) {
            userRewardPoints[i] += pointsAwarded;
            cout << "▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀\n";
            cout << "\n";
            cout << "\nReward approved for User ID: " << userID[i] << endl;
            cout << "Points awarded: "  << pointsAwarded           << endl;
            cout << "Total points now: " << userRewardPoints[i]    << endl;
            cout << "\n";
            cout << "▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀\n";
            cout << "\n";
            break;
        }
    }

    // save both since both arrays changed
    saveTransactionsToFile();
    saveUsersToFile();

    cout << "Press Enter to return to Reward Management...";
    cin.get();
}

void displayUserRewards(int uid) {
        system("cls");
        cout << "▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄\n";
        cout << "██                                               ██\n";
        cout << "██     ▄▄▄▄  ▄▄▄▄▄ ▄▄   ▄▄  ▄▄▄  ▄▄▄▄  ▄▄▄▄      ██\n";
        cout << "██     ██▄█▄ ██▄▄  ██ ▄ ██ ██▀██ ██▄█▄ ██▀██     ██\n";
        cout << "██     ██ ██ ██▄▄▄  ▀█▀█▀  ██▀██ ██ ██ ████▀     ██\n";
        cout << "██                                               ██\n";
        cout << "▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀  USER  REWARDS   ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀\n";

    // check if user exists
    if (!isValidUserID(uid)) {
        cout << "Error: User ID " << uid << " does not exist." << endl;
        return;
    }

    cout << "\n";
    cout << "\nReward Summary for User ID: " << uid << "";
    cout << "\n";
    cout << "▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀";
    cout << "\n";


    // find and display all tips by this user
    int totalPoints  = 0;
    int tipCount     = 0;
    bool found       = false;

    for (int i = 0; i < transactionCount; i++) {
        if (transactionUserID[i] == uid) {
            found = true;
            tipCount++;
            cout << "▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀\n";
            cout << "\n";

            cout << "  Tip #"         << tipCount                      << endl;
            cout << "  Transaction ID: " << transactionID[i]             << endl;
            cout << "  Incident ID:    " << transactionIncidentID[i]     << endl;
            cout << "  Tip Type:       " << transactionTipType[i]        << endl;
            cout << "  Submitted:      " << transactionTimestamp[i]      << endl;
            cout << "  Status:         " << transactionStatus[i]         << endl;

            cout << "\n";
            cout << "▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄\n";
            cout << "\n";
            if (transactionStatus[i] == "reward-approved") {
                cout << "Points Earned:  100"                          << endl;
            } else {
                cout << "Points Earned:  0 (still pending)"           << endl;
            }
        }
    }

    if (!found) {
        cout << "\n";
        cout << "No tips submitted yet." << endl;
        cout << "\n";
    }

    // show total points from user array
    for (int i = 0; i < userCount; i++) {
        if (userID[i] == uid) {
            cout << "\n";
            cout << "▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀\n";
            cout << "\n";
            cout << "\n  Total Reward Points: " << userRewardPoints[i] << "" << endl;
            cout << "\n";
            cout << "▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄\n";
            break;
        }
    }
    cout << "\nPress Enter to return to the Rewards Menu..." << endl;
    cin.ignore(1000, '\n'); 
    cin.get();
}

void rewardMenu() {
    while (true) {
        system("cls");
        cout << "▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄\n";
        cout << "██                                               ██\n";
        cout << "██     ▄▄▄▄  ▄▄▄▄▄ ▄▄   ▄▄  ▄▄▄  ▄▄▄▄  ▄▄▄▄      ██\n";
        cout << "██     ██▄█▄ ██▄▄  ██ ▄ ██ ██▀██ ██▄█▄ ██▀██     ██\n";
        cout << "██     ██ ██ ██▄▄▄  ▀█▀█▀  ██▀██ ██ ██ ████▀     ██\n";
        cout << "██                                               ██\n";
        cout << "██▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀██\n";
        cout << "██   Current Points Balance: " << left << setw(18) << userRewardPoints[loggedInUserID - 1] << "  ██\n";
        cout << "██▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄██\n";
        cout << "██                                               ██\n";
        cout << "██    [1] View Detailed Reward History           ██\n";
        cout << "██    [2] Submit Tip                             ██\n";
        cout << "██    [3] Back to Main Menu                      ██\n";
        cout << "██                                               ██\n";
        cout << "▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀\n";
        cout << "\nChoice: ";
        cin >> choice;
        cin.ignore(); 

        switch (choice) {
            case 1:
                displayUserRewards(loggedInUserID);
                break;
            case 2:
                submitTip(loggedInUserID, 0); 
                break;
            case 3:
                return; // Return to the caller (displayUserMenu) instead of calling it again
            default:
                cout << "Invalid choice. Try Again!" << endl;
                Sleep(1500);
        }
    }
}

void displayAllAlerts() {
    system("cls");

    cout << "▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄\n";
    cout << "██                                        ██\n";
    cout << "██      ▄▄▄  ▄▄    ▄▄▄▄▄ ▄▄▄▄  ▄▄▄▄▄▄     ██\n";
    cout << "██     ██▀██ ██    ██▄▄  ██▄█▄   ██       ██\n";
    cout << "██     ██▀██ ██▄▄▄ ██▄▄▄ ██ ██   ██       ██\n";
    cout << "██                                        ██\n";
    cout << "▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀\n";
    cout << "\n";

    if (incidentCount == 0) {
        cout << "No incidents available at this time." << endl;
        Sleep(1500);
        return;
    }

    for (int i = 0; i < incidentCount; i++) {
        cout << "\nIncident ID: " << incidentID[i] << endl;
        cout << "Crime:       " << incidentCrime[i] << endl;
        cout << "Location:    " << incidentLocation[i] << endl;
        cout << "Date:        " << incidentDate[i] << endl;
        cout << "Status:      " << incidentStatus[i] << endl;
        cout << "\n";
        cout << "▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀\n";
        cout << "\n";
    }

    cout << "\nPress Enter to return to the Menu...";
    cin.ignore(1000, '\n');
    cin.get();
}

// UI Module---------------------------------------------------------

void roleSelectionScreen() {
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
    cout << "██         SELECT YOUR ROLE:                                              ██\n";
    cout << "██                                                                        ██\n";
    cout << "██    [1] Admin                                                           ██\n";
    cout << "██    [2] User                                                            ██\n";
    cout << "██    [3] Return to Role Selection                                        ██\n";
    cout << "██                                                                        ██\n";
    cout << "██                                                                        ██\n";
    cout << "▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀\n";
    cout << "\n";
    cout << "Choice: ";
    cin >> choice;
    cin.ignore(); // Essential to clear buffer for next getline
    
    switch (choice) {
        case 1:
            // Admin login/register path
            system("cls");
            cout << "\n";
            cout << "▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄\n";
            cout << "██                                                                        ██\n";
            cout << "██     ▄█████  ▄▄▄  ▄▄▄▄▄ ▄▄▄▄▄ ██     ██ ▄████▄ ██████ ▄█████ ██  ██     ██\n";
            cout << "██     ▀▀▀▄▄▄ ██▀██ ██▄▄  ██▄▄  ██ ▄█▄ ██ ██▄▄██   ██   ██     ██████     ██\n";
            cout << "██     █████▀ ██▀██ ██    ██▄▄▄  ▀██▀██▀  ██  ██   ██   ▀█████ ██  ██     ██\n";
            cout << "██                                                                        ██\n";
            cout << "██▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀   ADMIN PORTAL    ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀██\n";
            cout << "██                                                                        ██\n";
            cout << "██    [1] Login as Admin                                                  ██\n";
            cout << "██    [2] Return to Role Selection                                        ██\n";
            cout << "██                                                                        ██\n";
            cout << "██                                                                        ██\n";
            cout << "▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀\n";
            cout << "\n";
            cout << "Choice: ";
            cin >> choice;
            cin.ignore();
            
            if (choice == 1) {
                loginAdmin();
            }
            break;
            
        case 2:
            // User login/register path
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
            cout << "██    [3] Return to Role Selection                                        ██\n";
            cout << "██                                                                        ██\n";
            cout << "██                                                                        ██\n";
            cout << "▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀\n";
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
                    cin.ignore(1000);
                    break;
                case 3:
                    roleSelectionScreen();
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
                    Sleep(1500);
                    roleSelectionScreen();
            }
            break;
            
        case 3:
            cout << "Exiting...\n";
            exit(0);
            break;
            
        default:
            cout << "Invalid choice. Please try again.\n";
            Sleep(1500);
            roleSelectionScreen();
    }
}

// PROFILE MODULE

void profileScreen() {
    system("cls");
    cout << "\n";
     int idx = -1;
    for (int i = 0; i < userCount; i++) {
        if (userID[i] == loggedInUserID) {
            idx = i;
            break;
        }
    }

    if (idx == -1) {
        cout << "Error: Could not load profile. Please log in again.\n";
        Sleep(1500);
        return;
    }

    while (true) {
        system("cls");
        cout << "\n";
        cout << "▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄\n";
        cout << "██                                                                        ██\n";
        cout << "██               ▄▄▄▄  ▄▄▄▄   ▄▄▄  ▄▄▄▄▄ ▄▄ ▄▄    ▄▄▄▄▄                   ██\n";
        cout << "██               ██▄█▀ ██▄█▄ ██▀██ ██▄▄  ██ ██    ██▄▄                    ██\n";
        cout << "██               ██    ██ ██ ▀███▀ ██    ██ ██▄▄▄ ██▄▄▄                   ██\n";
        cout << "██                                                                        ██\n";
        cout << "██▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀██\n";
        cout << "██                                                                        ██\n";
        cout << "██   User ID      : " << left << setw(52) << userID[idx]           << "   ██\n";
        cout << "██   Username     : " << left << setw(52) << userName[idx]         << "  ██\n";
        cout << "██   Full Name    : " << left << setw(52) << userFullName[idx]     << "  ██\n";
        cout << "██   Area / Address: " << left << setw(51) << userArea[idx]        << "  ██\n";
        cout << "██   Role         : " << left << setw(52) << userRole[idx]         << "  ██\n";
        cout << "██   Reward Points: " << left << setw(52) << userRewardPoints[idx] << "   ██\n";
        cout << "██                                                                        ██\n";
        cout << "██▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀██\n";
        cout << "██                                                                        ██\n";
        cout << "██    [1] Change Address                                                  ██\n";
        cout << "██    [2] Return to Main Menu                                             ██\n";
        cout << "██                                                                        ██\n";
        cout << "▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀\n";
        cout << "\nChoice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {

            case 1: { 
                system("cls");
                cout << "▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄\n";
                cout << "██                                                                        ██\n";
                cout << "██                ▄▄▄▄  ▄▄▄▄   ▄▄▄  ▄▄▄▄▄ ▄▄ ▄▄    ▄▄▄▄▄                  ██\n";
                cout << "██                ██▄█▀ ██▄█▄ ██▀██ ██▄▄  ██ ██    ██▄▄                   ██\n";
                cout << "██                ██    ██ ██ ▀███▀ ██    ██ ██▄▄▄ ██▄▄▄                  ██\n";
                cout << "██                                                                        ██\n";
                cout << "▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀  CHANGE ADDRESS   ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀\n";
                cout << "\n";
                cout << "           Current Address: " << userArea[idx] << "\n";
                cout << "           Enter new address: ";
                string newAddress;
                getline(cin, newAddress);

                if (newAddress.empty()) {
                    cout << "Address cannot be empty. No changes made.\n";
                    Sleep(2000);
                    break;
                }

                userArea[idx] = newAddress;
                saveUsersToFile();

                cout << "\nAddress updated successfully!\n";
                cout << "New Address: " << userArea[idx] << "\n";
                Sleep(2000);
                system("cls");
                break;
            }

            case 2:
                return;

            default:
                cout << "Invalid choice. Please try again.\n";
                Sleep(2000);
                break;
        }
    }
}


//MAIN FUNCTION===================================================================================
void startMenu() {
    roleSelectionScreen();
}

int main() {

    // TEXT FORMATTING
    SetConsoleOutputCP(CP_UTF8);

    //LOAD DATA FROM FILES AT STARTUP
    loadIncidentsFromFile();
    loadSuspectsFromFile();
    loadUsersFromFile();
    loadAdminsFromFile();
    loadTransactionsFromFile();
    loadNotifications();

    while (true) {
        roleSelectionScreen();
    }

    return 0;
}
