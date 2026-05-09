#include "UNIVERSAL.h"

void addIncident() {
     system("cls");
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
     system("cls");
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
    getline(cin, userName[userCount]);

    if (isDuplicateUser(userName[userCount])) {
        cout << "Username already exists. Please choose a different username.\n";
        Sleep(1000);
        return;
    }

    //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    cout << "===== ADD USER =====\n";
    cout << "Full Name: ";
    getline(cin, userFullName[userCount]);

    cout << "Password: ";
    getline(cin, userPassword[userCount]);

    cout << "Address: ";
    getline(cin, userArea[userCount]);

    cout << "Role (admin/user): ";
    getline(cin, userRole[userCount]);

    // If adding an admin user, require authority type and station
    //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    if (userRole[userCount] == "admin") {
        cout << "\n--- AUTHORITY INFORMATION ---\n";
        cout << "Authority Type (police_officer/detective/captain/commissioner/none): ";
        getline(cin, userAuthorityType[userCount]);
        
        cout << "Station Assignment (e.g., Baluarte, Villa, etc.): ";
        getline(cin, userStation[userCount]);
    } else {
        userAuthorityType[userCount] = "none";
        userStation[userCount] = "none";
    }

    userRewardPoints[userCount] = 0;

    userCount++;

    cout << "\nUser registered successfully!\n";

     // Save data right away
     saveUsersToFile();
}

void displayAdminMenu() {
    bool stay = true;
    while (stay) {
        system("cls");
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
    cout << "██▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀   A D M I N   ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀██\n";
    
    // Display logged in admin info
    for (int i = 0; i < userCount; i++) {
        if (userID[i] == loggedInUserID) {
            cout << "██  Logged In: " << userFullName[i] << " | Badge: " << userAuthorityType[i] << " | Station: " << userStation[i] << "\n";
            break;
        }
    }
    
    cout << "██                                                                        ██\n";
    cout << "██    [1] Users                                                           ██\n";
    cout << "██    [2] Incidents                                                       ██\n";
    cout << "██    [3] Reward                                                          ██\n";
    cout << "██    [4] Profile                                                         ██\n";
    cout << "██    [5] Logout                                                          ██\n";
    cout << "██                                                                        ██\n";
    cout << "██                                                                        ██\n";
    cout << "▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀\n";
    cout << "\n";
    cout << "Choice: ";
    cin >> choice;
    cin.ignore();

    switch (choice) {
        case 1:
             addUser();
            break;
        case 2:
            addIncident();
            addSuspect();
            break;
        case 3:
            cout << "Reward management coming soon...\n";
            Sleep(1000);
            break;
        case 4:
            cout << "Profile management coming soon...\n";
            Sleep(1000);
            break;
        case 5:
            cout << "Logging out...\n";
            Sleep(1000);
            stay = false;
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            Sleep(1000);
    }
    }
}