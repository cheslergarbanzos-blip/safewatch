#include "UNIVERSAL.h"
#include <iomanip>

void admindRewardScreen() {
    system("cls");
        cout << "▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄\n";
        cout << "██                                               ██\n";
        cout << "██     ▄▄▄▄  ▄▄▄▄▄ ▄▄   ▄▄  ▄▄▄  ▄▄▄▄  ▄▄▄▄      ██\n";
        cout << "██     ██▄█▄ ██▄▄  ██ ▄ ██ ██▀██ ██▄█▄ ██▀██     ██\n";
        cout << "██     ██ ██ ██▄▄▄  ▀█▀█▀  ██▀██ ██ ██ ████▀     ██\n";
        cout << "██                                               ██\n";
        cout << "██▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀      ADMIN      ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀██\n";
        cout << "██                                               ██\n";
        cout << "██    [1] View Tips                              ██\n";
        cout << "██    [2] Approve Tips                           ██\n";
        cout << "██    [3] Back                                   ██\n";
        cout << "██                                               ██\n";
        cout << "██▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄██\n";
        cout << "\n";
        cout << "Choice: ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
            case 1:
                viewTipsScreen();
                break;
            case 2:
                approveReward();
                break;
            case 3:
                 displayAdminMenu();
                 break;
            default:
                cout << "Invalid choice. Please try again.\n";
                Sleep(1000);
                admindRewardScreen();
                break;
        }
}

void viewTipsScreen() {
    system("cls");
    cout << "▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄\n";
    cout << "██                                               ██\n";
    cout << "██     ▄▄▄▄  ▄▄▄▄▄ ▄▄   ▄▄  ▄▄▄  ▄▄▄▄  ▄▄▄▄      ██\n";
    cout << "██     ██▄█▄ ██▄▄  ██ ▄ ██ ██▀██ ██▄█▄ ██▀██     ██\n";
    cout << "██     ██ ██ ██▄▄▄  ▀█▀█▀  ██▀██ ██ ██ ████▀     ██\n";
    cout << "██                                               ██\n";
    cout << "▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀   TIPS    ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀\n";
    cout << "\n";

    if (transactionCount == 0) {
        cout << "No tips have been submitted yet." << endl;
    } else {
        for (int i = 0; i < transactionCount; i++) {
            cout << "\n";
            cout << "▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀\n";
            cout << "Tip #" << (i + 1) << ":" << endl;
            cout << "  Transaction ID: " << transactionID[i] << endl;
            cout << "  User ID:        " << transactionUserID[i] << endl;
            cout << "  Incident ID:    " << transactionIncidentID[i] << endl;
            cout << "  Submitted:      " << transactionTimestamp[i] << endl;
            cout << "  Tip Type:       " << transactionTipType[i] << endl;
            cout << "  Status:         " << transactionStatus[i] << endl;
            cout << "\n";
            cout << "▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀\n";
            cout << "\n";
        }
    }

    cout << "\nPress Enter to return to the Reward Menu..." << endl;
    cin.ignore(1000, '\n');
    cin.get();
}

void reportScreen() {
    system("cls");
    cout << "\n";
    cout << "\n";
    cout << "▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄\n";
    cout << "██                                          ██\n";
    cout << "██   ▄▄▄   ▄▄▄▄▄ ▄▄▄▄   ▄▄▄  ▄▄▄   ▄▄▄▄▄▄   ██\n";
    cout << "██   ██▄█▄ ██▄▄  ██▄█▀ ██▀██ ██▄█▄   ██     ██\n";
    cout << "██   ██ ██ ██▄▄▄ ██    ▀███▀ ██ ██   ██     ██\n";
    cout << "██                                          ██\n";
    cout << "██▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄██\n";
    cout << "██                                          ██\n";
    cout << "██     [1] Report Incident                  ██\n";
    cout << "██     [2] Report Suspect                   ██\n";
    cout << "██     [3] Back                             ██\n";
    cout << "██                                          ██\n";
    cout << "██▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄██\n";
    
    cout << "\n";
    cout << "Choice: ";
    cin >> choice;
    cin.ignore(); // Clear the newline character from the input buffer
    switch (choice) {
        case 1:
            addIncident();
            break;
        case 2:
            addSuspect();
            break;
        case 3:
            displayAdminMenu();
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            Sleep(1000);
            reportScreen();
            break;
    }
}

void addIncident() {
     system("cls");
    if (incidentCount >= MAX_INCIDENTS) {
        cout << "Maximum incident limit reached. Cannot add more incidents.\n";
        return;
    }

    cout << "\n";
    cout << "▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄\n";
    cout << "██                                          ██\n";
    cout << "██   ▄▄▄   ▄▄▄▄▄ ▄▄▄▄   ▄▄▄  ▄▄▄   ▄▄▄▄▄▄   ██\n";
    cout << "██   ██▄█▄ ██▄▄  ██▄█▀ ██▀██ ██▄█▄   ██     ██\n";
    cout << "██   ██ ██ ██▄▄▄ ██    ▀███▀ ██ ██   ██     ██\n";
    cout << "██                                          ██\n";
    cout << "██▄▄▄▄▄▄▄▄▄▄▄▄▄   INCIDENTS   ▄▄▄▄▄▄▄▄▄▄▄▄▄▄██\n";
    cout << "\n";

    // Auto-generate Incident ID
    int nextID = 1;
    for (int i = 0; i < incidentCount; i++) {
        if (incidentID[i] >= nextID) nextID = incidentID[i] + 1;
    }
    incidentID[incidentCount] = nextID;
    cout << "[System] Generated Incident ID: " << nextID << "\n\n";

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
     system("cls");
    if (suspectCount >= MAX_SUSPECTS) {
        cout << "Maximum suspect limit reached. Cannot add more suspects.\n";
        return;
    }

    cout << "\n";
    cout << "▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄\n";
    cout << "██                                          ██\n";
    cout << "██   ▄▄▄   ▄▄▄▄▄ ▄▄▄▄   ▄▄▄  ▄▄▄   ▄▄▄▄▄▄   ██\n";
    cout << "██   ██▄█▄ ██▄▄  ██▄█▀ ██▀██ ██▄█▄   ██     ██\n";
    cout << "██   ██ ██ ██▄▄▄ ██    ▀███▀ ██ ██   ██     ██ \n";
    cout << "██                                          ██\n";
    cout << "██▄▄▄▄▄▄▄▄▄▄▄▄▄▄   SUSPECT   ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄██\n";
    cout << "\n";

    // Auto-generate Suspect ID
    int nextSID = 1;
    for (int i = 0; i < suspectCount; i++) {
        if (suspectID[i] >= nextSID) nextSID = suspectID[i] + 1;
    }
    suspectID[suspectCount] = nextSID;
    cout << "[System] Generated Suspect ID: " << nextSID << "\n\n";

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

void displayUserManagement() {
    system("cls");
    cout << "\n";
    cout << "▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄\n";
    cout << "██                                         ██\n";
    cout << "██      ▄▄ ▄▄  ▄▄▄▄ ▄▄▄▄▄ ▄▄▄▄   ▄▄▄▄      ██\n";
    cout << "██      ██ ██ ███▄▄ ██▄▄  ██▄█▄ ███▄▄      ██\n";
    cout << "██      ▀███▀ ▄▄██▀ ██▄▄▄ ██ ██ ▄▄██▀      ██\n";
    cout << "██                                         ██\n";
    cout << "██▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄██\n";
    cout << "██                                         ██\n";
    cout << "██     [1] Grant Admin                     ██\n";
    cout << "██     [2] Show Users List                 ██\n";
    cout << "██     [3] Back                            ██\n";
    cout << "██                                         ██\n";
    cout << "██▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄██\n";

    cout << "\n";  
    cout << "Choice: ";
    cin >> choice;
    cin.ignore();
    switch (choice) {
        case 1:
            addUser();
            break;
        case 2:
            displayUsers();
            break;
        case 3:
            displayAdminMenu();
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            Sleep(1000);
            displayUserManagement();
            break;
    }
}

void addUser(){
    system("cls");
    if (userCount >= MAX_USERS) {
        cout << "Maximum user limit reached. Cannot add more users.\n";
        Sleep(2000);
        return;
    }

    cout << "\n";
    cout << "▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄\n";
    cout << "██                                         ██\n";
    cout << "██      ▄▄ ▄▄  ▄▄▄▄ ▄▄▄▄▄ ▄▄▄▄   ▄▄▄▄      ██\n";
    cout << "██      ██ ██ ███▄▄ ██▄▄  ██▄█▄ ███▄▄      ██\n";
    cout << "██      ▀███▀ ▄▄██▀ ██▄▄▄ ██ ██ ▄▄██▀      ██\n";
    cout << "██                                         ██\n";
    cout << "██▄▄▄▄▄▄▄▄▄▄▄    GRANT ADMIN     ▄▄▄▄▄▄▄▄▄▄██\n";
    cout << "\n";   

    string role;
    while (true) {
        cout << "Role to assign (admin/user): ";
        getline(cin, role);
        if (role == "admin" || role == "user") break;
        cout << "[!] Invalid role. Please type exactly 'admin' or 'user'.\n";
    }
    userRole[userCount] = role;

    cout << "Username: ";
    getline(cin, userName[userCount]);

    if (isDuplicateUser(userName[userCount], role)) {
        cout << "Username already exists. Please choose a different username.\n";
        Sleep(2000);
        return;
    }

    cout << "Full Name: ";
    getline(cin, userFullName[userCount]);

    cout << "Password: ";
    getline(cin, userPassword[userCount]);

    cout << "Home Area/Address: ";
    getline(cin, userArea[userCount]);

    if (role == "admin") {
        cout << "\n[Authority Details Required]\n";
        cout << "Position/Badge Type: ";
        getline(cin, userAuthorityType[userCount]);
        
        cout << "Station Assignment: ";
        getline(cin, userStation[userCount]);
    } else {
        userAuthorityType[userCount] = "none";
        userStation[userCount] = "none";
    }

    userID[userCount] = userCount + 1;
    userRewardPoints[userCount] = 0;
    
    userCount++;

    cout << "\n[System] Account created successfully for " << userName[userCount-1] << ".\n";

    // Call appropriate save function based on role
    if (role == "admin") {
        saveAdminsToFile();
    } else {
        saveUsersToFile();
    }
    
    Sleep(2000);
}

void displayUsers() {
    system("cls");
    cout << "\n";
    cout << "▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄\n";
    cout << "██                                         ██\n";
    cout << "██      ▄▄ ▄▄  ▄▄▄▄ ▄▄▄▄▄ ▄▄▄▄   ▄▄▄▄      ██\n";
    cout << "██      ██ ██ ███▄▄ ██▄▄  ██▄█▄ ███▄▄      ██\n";
    cout << "██      ▀███▀ ▄▄██▀ ██▄▄▄ ██ ██ ▄▄██▀      ██\n";
    cout << "██                                         ██\n";
    cout << "██▄▄▄▄▄▄▄▄▄▄▄   USER ACCOUNTS    ▄▄▄▄▄▄▄▄▄▄██\n";
    cout << "\n";

    if (userCount == 0) {
        cout << "No users found.\n";
    } else {
        cout << left << setw(5) << "ID" 
             << setw(10) << "Role"
             << setw(18) << "Username"
             << setw(24) << "Full Name"
             << setw(18) << "Area"
             << setw(16) << "Authority"
             << setw(16) << "Station" << "\n";
        cout << string(107, '=') << "\n";

        for (int i = 0; i < userCount; i++) {
            cout << left << setw(5) << userID[i]
                 << setw(10) << userRole[i]
                 << setw(18) << userName[i]
                 << setw(24) << userFullName[i]
                 << setw(18) << userArea[i]
                 << setw(16) << userAuthorityType[i]
                 << setw(16) << userStation[i] << "\n";
        }
    }

    cout << "\nPress Enter to return to User Management...";
    string pause;
    getline(cin, pause);
}


void displayAdminMenu() {
    bool stay = true;
    while (stay) {
        system("cls");
        cout << "\n";
        cout << "▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄\n";
        cout << "██                                                                        ██\n";
        cout << "██     ▄█████  ▄▄▄  ▄▄▄▄▄ ▄▄▄▄▄ ██     ██ ▄████▄ ██████ ▄█████ ██  ██     ██\n";
        cout << "██     ▀▀▀▄▄▄ ██▀██ ██▄▄  ██▄▄  ██ ▄█▄ ██ ██▄▄██   ██   ██     ██████     ██\n";
        cout << "██     █████▀ ██▀██ ██    ██▄▄▄  ▀██▀██▀  ██  ██   ██   ▀█████ ██  ██     ██\n";
        cout << "██                                                                        ██\n";
        cout << "██▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀   A D M I N   ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀██\n";

        // Display logged in admin info
        for (int i = 0; i < userCount; i++) {
            if (userID[i] == loggedInUserID) {
                cout << "██  Logged In: " << left << setw(20) << userFullName[i] 
                     << " | Badge: " << setw(15) << userAuthorityType[i] 
                     << " | Station: " << setw(13) << userStation[i] << " ██\n";
                break;
            }
        }
        cout << "██▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄██\n";
        cout << "██                                                                        ██\n";
        cout << "██    [1] User Management    - Manage User and Authority accounts         ██\n";
        cout << "██    [2] Crime Database     - Register New Incidents and Suspects    1    ██\n";
        cout << "██    [3] Reward Management  - Verify Tips and Approve Rewards            ██\n";
        cout << "██    [4] Admin Profile      - View Personnel Details                     ██\n";
        cout << "██    [5] Logout             - Return to Role Selection                   ██\n";
        cout << "██                                                                        ██\n";
        cout << "▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀\n";
        cout << "\nChoice: ";
        if (!(cin >> choice)) { cin.clear(); cin.ignore(1000, '\n'); continue; }
        cin.ignore();

        switch (choice) {
            case 1:
                displayUserManagement();
                break;
            case 2:
                reportScreen();
                break;
            case 3:
                admindRewardScreen();
                break;
            case 4:
                profileScreen();
                break;
            case 5:
                cout << "\nLogging out...\n";
                Sleep(1000);
                stay = false;
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                Sleep(1000);
        }
    }
}