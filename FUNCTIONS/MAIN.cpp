#include "UNIVERSAL.h"
#include <filesystem>

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
string userStation[MAX_USERS];        // Station assignment for authorities

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
        Sleep(2000);
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
        Sleep(2000);
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
        outfile.close();
    } else {
        cout << "CRITICAL ERROR: Could not save to " << USERS_FILE << ". Ensure 'DATA' folder exists.\n";
        Sleep(2000);
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
        Sleep(2000);
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
            if (!getline(ss, temp, ',')) continue;
            incidentID[incidentCount] = stoi(temp);
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
            if (line.empty()) continue;
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
            if (line.empty()) continue;
            stringstream ss(line);
            string temp;
            getline(ss, temp, ','); userID[userCount] = stoi(temp);
            getline(ss, userName[userCount], ',');
            getline(ss, userFullName[userCount], ',');
            getline(ss, userPassword[userCount], ',');
            getline(ss, userArea[userCount], ',');
            getline(ss, userRole[userCount], ',');
            getline(ss, temp, ','); userRewardPoints[userCount] = stoi(temp);
            getline(ss, userAuthorityType[userCount], ',');
            getline(ss, userStation[userCount], ',');
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
            if (line.empty()) continue;
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

// Reward Module------------------------------------------------------

void submitTip(int tipUserID, int tipIncidentID) {

    // check if the incident actually exists first
    if (!isValidIncidentID(tipIncidentID)) {
        cout << "Error: Incident ID " << tipIncidentID << " does not exist." << endl;
        return;
    }

    // check if the user actually exists
    if (!isValidUserID(tipUserID)) {
        cout << "Error: User ID " << tipUserID << " does not exist." << endl;
        return;
    }

    // check if transaction storage is full
    if (transactionCount >= MAX_TRANSACTIONS) {
        cout << "Error: Transaction storage is full." << endl;
        return;
    }

    // ask for tip details
    string tipType, reportedLocation;

    //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    cout << "\n--- Submit a Tip ---" << endl;
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

    //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    cout << "\nTip submitted successfully! Status: PENDING" << endl;
    cout << "Transaction ID: " << transactionCount << endl;
}

void approveReward(int tid) {

    // find the transaction
    int index = -1;
    for (int i = 0; i < transactionCount; i++) {
        if (transactionID[i] == tid) {
            index = i;
            break;
        }
    }

    // transaction not found
    if (index == -1) {
        cout << "Error: Transaction ID " << tid << " not found." << endl;
        return;
    }

    // check if already approved
    if (transactionStatus[index] == "reward-approved") {
        cout << "Error: Transaction " << tid << " is already approved." << endl;
        return;
    }

    // approve the transaction
    transactionStatus[index] = "reward-approved";

    // find the user and add reward points
    //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    int pointsAwarded = 100; 
    for (int i = 0; i < userCount; i++) {
        if (userID[i] == transactionUserID[index]) {
            userRewardPoints[i] += pointsAwarded;
            cout << "\nReward approved for User ID: " << userID[i] << endl;
            cout << "Points awarded: "  << pointsAwarded           << endl;
            cout << "Total points now: " << userRewardPoints[i]    << endl;
            break;
        }
    }

    // save both since both arrays changed
    saveTransactionsToFile();
    saveUsersToFile();
}

void displayUserRewards(int uid) {

    // check if user exists
    if (!isValidUserID(uid)) {
        cout << "Error: User ID " << uid << " does not exist." << endl;
        return;
    }

    //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    cout << "\n--- Reward Summary for User ID: " << uid << " ---" << endl;

    // find and display all tips by this user
    int totalPoints  = 0;
    int tipCount     = 0;
    bool found       = false;

    //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    for (int i = 0; i < transactionCount; i++) {
        if (transactionUserID[i] == uid) {
            found = true;
            tipCount++;

            cout << "\nTip #"         << tipCount                      << endl;
            cout << "Transaction ID: " << transactionID[i]             << endl;
            cout << "Incident ID:    " << transactionIncidentID[i]     << endl;
            cout << "Tip Type:       " << transactionTipType[i]        << endl;
            cout << "Submitted:      " << transactionTimestamp[i]      << endl;
            cout << "Status:         " << transactionStatus[i]         << endl;

            if (transactionStatus[i] == "reward-approved") {
                cout << "Points Earned:  100"                          << endl;
            } else {
                cout << "Points Earned:  0 (still pending)"           << endl;
            }
        }
    }

    if (!found) {
        cout << "No tips submitted yet." << endl;
    }

    // show total points from user array
    for (int i = 0; i < userCount; i++) {
        if (userID[i] == uid) {
            cout << "\n--- Total Reward Points: " << userRewardPoints[i] << " ---" << endl;
            break;
        }
    }
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
        cout << "██                                               ██\n";
        cout << "██    [1] Submit Tip                             ██\n";
        cout << "██    [2] View Rewards                           ██\n";
        cout << "██    [3] Back                                   ██\n";
        cout << "██                                               ██\n";
        cout << "██                                               ██\n";
        cout << "▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀\n";
        cout << "\nChoice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                submitTip(loggedInUserID, targetID);
                Sleep(2000);
                break;
            case 2:
                displayUserRewards(loggedInUserID);
                Sleep(2000);
                break;
            case 3:
                displayUserMenu(loggedInUserID);
                return;
            default:
                cout << "Invalid choice. Try Again!" << endl;
                Sleep(2000);
        }
    }
}

void displayAllAlerts() {
    system("cls");

    //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    cout << "\n--- Current Alerts ---" << endl;

    if (incidentCount == 0) {
        cout << "No incidents available at this time." << endl;
        Sleep(3000);
        return;
    }

    for (int i = 0; i < incidentCount; i++) {
        cout << "\nIncident ID: " << incidentID[i] << endl;
        cout << "Crime:       " << incidentCrime[i] << endl;
        cout << "Location:    " << incidentLocation[i] << endl;
        cout << "Date:        " << incidentDate[i] << endl;
        cout << "Status:      " << incidentStatus[i] << endl;
    }

    cout << "\nPress any key to continue..." << endl;
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
    cout << "██    [3] Back to Main Menu                                               ██\n";
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
            cout << "██    [2] Back to Role Selection                                          ██\n";
            cout << "██                                                                        ██\n";
            cout << "██                                                                        ██\n";
            cout << "▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀\n";
            cout << "\n";
            cout << "Choice: ";
            cin >> choice;
            cin.ignore();
            
            if (choice == 1) {
                loginAdmin();
            } else {
                roleSelectionScreen();
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
            cout << "██    [3] Back                                                            ██\n";
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
                    roleSelectionScreen();
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
                    Sleep(5000);
                    roleSelectionScreen();
            }
            break;
            
        case 3:
            cout << "Exiting...\n";
            exit(0);
            break;
            
        default:
            cout << "Invalid choice. Please try again.\n";
            Sleep(5000);
            roleSelectionScreen();
    }
}

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
    cout << "██    [1] Select User Type                                                ██\n";
    cout << "██    [2] Exit                                                            ██\n";
    cout << "██                                                                        ██\n";
    cout << "██                                                                        ██\n";
    cout << "▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀\n";
    cout << "\n";
    cout << "Choice: ";
    cin >> choice;
    cin.ignore(); // Essential to clear buffer for next getline
    
    switch (choice) {
        case 1:
            roleSelectionScreen();
            break;
        case 2:
            cout << "Exiting...\n";
            exit(0);
        default:
            cout << "Invalid choice. Please try again.\n";
            Sleep(5000);
            startMenu();
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
        Sleep(2000);
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
        cout << "██   Username     : " << left << setw(52) << userName[idx]         << "   ██\n";
        cout << "██   Full Name    : " << left << setw(52) << userFullName[idx]     << "   ██\n";
        cout << "██   Area / Address: " << left << setw(51) << userArea[idx]        << "   ██\n";
        cout << "██   Role         : " << left << setw(52) << userRole[idx]         << "   ██\n";

        // Only show authority fields if they are set
        if (!userAuthorityType[idx].empty() && userAuthorityType[idx] != "none") {
        cout << "██   Authority    : " << left << setw(52) << userAuthorityType[idx] << "  ██\n";
        cout << "██   Station      : " << left << setw(52) << userStation[idx]       << "  ██\n";
        }

        cout << "██   Reward Points: " << left << setw(52) << userRewardPoints[idx] << "   ██\n";
        cout << "██                                                                        ██\n";
        cout << "██▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀██\n";
        cout << "██                                                                        ██\n";
        cout << "██    [1] Change Address                                                  ██\n";
        cout << "██    [2] Back                                                            ██\n";
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
                displayUserMenu(loggedInUserID);
                break;
            }

            case 2:
                displayUserMenu(loggedInUserID);
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
                Sleep(2000);
                break;
        }
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
        roleSelectionScreen();
    }

    return 0;
}
