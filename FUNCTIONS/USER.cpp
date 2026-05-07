#include "UNIVERSAL.h"

void displayUserMenu(int loggedInUserID) {
     system("cls");
     ofstream outfile (USERS_FILE); 
    // report
    // incidents/suspects
    // reward
    // profile

    cout << "Logged in as User ID: " << loggedInUserID << "\n";
    cout << "\n";
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
    system("cls");
    string inputUser, inputPass;
    ofstream outfile (USERS_FILE); 

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
    return 0;
}

int registerUser() {
    system("cls");
    ofstream outfile (USERS_FILE); 

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
