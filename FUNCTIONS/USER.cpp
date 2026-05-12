#include "UNIVERSAL.h"

int loginAdmin() {
    system("cls");
    string inputUser, inputPass;

    cout << "\n";
    cout << "▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄\n";
    cout << "██                                                                        ██\n";
    cout << "██                    ADMIN AUTHORITY LOGIN PORTAL                        ██\n";
    cout << "██                     (FOR LAW ENFORCEMENT ONLY)                         ██\n";
    cout << "██                                                                        ██\n";
    cout << "▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀\n";
    cout << "\n";

    cout << "Employee Username: ";
    getline(cin, inputUser);
    cout << "\n";

    cout << "Password: ";
    getline(cin, inputPass);
    cout << "\n";

    for (int i = 0; i < userCount; i++) {
        if (userName[i] == inputUser && userPassword[i] == inputPass) {
            // Check if user role is admin
            if (userRole[i] != "admin") {
                system("cls");
                cout << "\n";
                cout << "██▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀██\n";
                cout << "██                           ! ACCESS DENIED !                               ██\n";
                cout << "██                                                                           ██\n";
                cout << "██  You do not have the required authorization to access the admin portal.   ██\n";
                cout << "██  Only admin personnel are permitted access.                               ██\n";
                cout << "██                                                                           ██\n";
                cout << "██  Your account credentials have been logged for security purposes.         ██\n";
                cout << "██▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄██\n";
                cout << "\n";
                Sleep(1500);
                roleSelectionScreen();
                return 0;
            }

            loggedInUserID = userID[i];
            system("cls");
            cout << "\n";
            cout << "▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄\n";
            cout << "██                                                                        ██\n";
            cout << "██                           LOGIN SUCCESSFUL                             ██\n";
            cout << "██                                                                        ██\n";
            cout << "██▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀██\n";
            cout << "██                                                                        ██\n";
            cout << "██  Welcome, " << userFullName[i] << "                                                         ██\n";     
            cout << "██  Badge/Position: " << userAuthorityType[i] << "                                                       ██\n";     
            cout << "██  Station: " << userStation[i] << "                                                         ██\n";                                 
            cout << "██                                                                        ██\n";
            cout << "▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀\n";
            cout << "\n";
            Sleep(2000);
            displayAdminMenu();
            return userID[i];
        }
    }
    system("cls");
    cout << "\n";
    cout << "▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄\n";
    cout << "██                                                                        ██\n";
    cout << "██                              LOGIN FAILED                              ██\n";
    cout << "██                                                                        ██\n";
    cout << "██▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀██\n";
    cout << "██  ✗ INVALID CREDENTIALS ✗                                              ██\n";
    cout << "██  Username or password is incorrect.                                    ██\n";
    cout << "██                                                                        ██\n";
    cout << "▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀\n";
    cout << "\n";
    Sleep(5000);
    return 0;
}

void displayUserMenu(int currentUID) {
    string currentUserArea = "";
    for (int i = 0; i < userCount; i++) {
        if (userID[i] == currentUID) {
            currentUserArea = userArea[i];
            break;
        }
    }

    while (true) {
        system("cls");
        cout << "▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄\n";
        cout << "██                                                                        ██\n";
        cout << "██     ▄█████  ▄▄▄  ▄▄▄▄▄ ▄▄▄▄▄ ██     ██ ▄████▄ ██████ ▄█████ ██  ██     ██\n";
        cout << "██     ▀▀▀▄▄▄ ██▀██ ██▄▄  ██▄▄  ██ ▄█▄ ██ ██▄▄██   ██   ██     ██████     ██\n";
        cout << "██     █████▀ ██▀██ ██    ██▄▄▄  ▀██▀██▀  ██  ██   ██   ▀█████ ██  ██     ██\n";
        cout << "██                                                                        ██\n";
        cout << "██▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀     USER       ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀██\n";
        cout << "██                                                                        ██\n";
        cout << "██    USER ID: " << left << setw(53) << loggedInUserID << "      ██\n";
        cout << "██                                                                        ██\n";
        cout << "██▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄██\n";
        cout << "██                                                                        ██\n";
        cout << "██    [1] Notification Center                                             ██\n";
        cout << "██    [2] List of Incidents                                               ██\n";
        cout << "██    [3] Reward                                                          ██\n";
        cout << "██    [4] Profile                                                         ██\n";
        cout << "██    [5] Logout                                                          ██\n";
        cout << "██                                                                        ██\n";
        cout << "▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀\n";
        cout << "\nChoice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        cin.ignore();

        switch (choice) {
            case 1:
                displayNotificationCenter(currentUserArea);
                break;
            case 2:
                displayAllAlerts();
                break;
            case 3:
                rewardMenu();
                break;
            case 4:
                profileScreen();
                break;
            case 5:
                cout << "Logging out...\n";
                Sleep(1000);
                roleSelectionScreen();
                ::loggedInUserID = 0; 
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                Sleep(1000);
                break;
        }
    }
}

int loginUser() {
    system("cls");
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
            loggedInUserID = userID[i];
            cout << "\nLogin successful! Welcome, " << userFullName[i] << "!\n";
            if (userRole[i] == "admin") {
                displayAdminMenu();
            } else {
                loadNotifications();
                displayNotificationCenter(userArea[i]);
                displayUserMenu(userID[i]);
            }
            return userID[i];
        }
    }
    cout << "\nInvalid username or password. Please try again.\n";
    Sleep(5000);
    roleSelectionScreen();
    return 0;
}

int registerUser() {
    system("cls");

    if (userCount >= MAX_USERS) {
        cout << "Error: Maximum user limit reached. Please contact an administrator.\n";
        Sleep(2000);
        return -1;
    }

    cout << "\n";
    cout << "▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄\n";
    cout << "██                                                             ██\n";
    cout << "██    █████▄  ██████  ▄████  ██ ▄█████ ██████ ██████ █████▄    ██\n";
    cout << "██    ██▄▄██▄ ██▄▄   ██  ▄▄▄ ██ ▀▀▀▄▄▄   ██   ██▄▄   ██▄▄██    ██\n";
    cout << "██    ██   ██ ██▄▄▄▄  ▀███▀  ██ █████▀   ██   ██▄▄▄▄ ██   ██   ██\n";
    cout << "██                                                             ██\n";
    cout << "▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀\n";
    cout << "\n";

    cout << "Username: ";
    getline(cin, userName[userCount]);

    if (isDuplicateUser(userName[userCount], userRole[userCount])) {
        cout << "Username already exists. Please choose a different username.\n";
        Sleep(2000);
        return -1;
    }

    cout << "Full Name: ";
    getline(cin, userFullName[userCount]);

    cout << "Password: ";
    getline(cin, userPassword[userCount]);

     string addresses[] = {
        "Jaro",
        "La Paz",
        "Molo",
        "Mandurriao",
        "Villa",
        "City Proper"
    };
    cout << "Select your area of residence:\n";
    for (int i = 0; i < 6; i++) {
        cout << "[" << (i + 1) << "] " << addresses[i] << "\n";
    }

    int areaChoice;
    cout << "Enter your choice: ";
    cin >> areaChoice;
    cin.ignore();

    if (areaChoice >= 1 && areaChoice <= 6) {
        userArea[userCount] = addresses[areaChoice - 1] + ", Iloilo City";
    } else {
        cout << "Invalid address. Please try again.\n";
        Sleep(2000);
        return -1;
    }

    userRole[userCount] = "user";
    userRewardPoints[userCount] = 0;
    userID[userCount] = userCount + 1;
    userAuthorityType[userCount] = "none";
    userStation[userCount] = "none";

    userCount++;

    cout << "\nUser registered successfully!\n";

     // Save data right away
     saveUsersToFile();

      Sleep(2000);

    // Return to main menu
    roleSelectionScreen();

    return userID[userCount - 1];
}