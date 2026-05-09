#ifndef UNIVERSAL_H
#define UNIVERSAL_H

#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include <sstream>
#include <vector>
using namespace std;

extern int choice;

extern const string INCIDENTS_FILE;
extern const string SUSPECTS_FILE;
extern const string USERS_FILE;
extern const string TRANSACTIONS_FILE;

extern const int MAX_INCIDENTS;
extern const int MAX_SUSPECTS;
extern const int MAX_USERS;
extern const int MAX_TRANSACTIONS;

extern int incidentID[];
extern string incidentCrime[];
extern string incidentLocation[];
extern string incidentDate[];
extern string incidentStatus[];

extern int suspectID[];
extern int suspectIncidentID[];
extern string suspectName[];
extern string suspectHeight[];
extern string suspectBuild[];
extern string suspectClothing[];
extern string suspectLastLocation[];

extern int userID[];
extern string userName[];
extern string userFullName[];
extern string userPassword[];
extern string userArea[];
extern string userRole[];
extern int userRewardPoints[];

extern string userAuthorityType[];
extern string userStation[];

extern int transactionID[];
extern int transactionUserID[];
extern int transactionIncidentID[];
extern string transactionTimestamp[];
extern string transactionTipType[];
extern string transactionStatus[];

extern int targetID;
extern string keyCrime;
extern string keyLocation;
extern string keyUsername;

extern int incidentCount;
extern int suspectCount;
extern int userCount;
extern int transactionCount;
extern int loggedInUserID;

bool isDuplicateUser(string username);
bool isValidIncidentID(int id);
bool isValidUserID(int id);
bool isAdminUser(int id);
bool isAuthorized(int userID);
int loginAdmin();
void displayAdminMenu();
void displayUserMenu(int loggedInUserID);
int loginUser();
int registerUser();

void loadNotifications();
void displayNotificationCenter(string userLocation);


void saveIncidentsToFile();
void saveSuspectsToFile();
void saveUsersToFile();
void saveTransactionsToFile();
void loadIncidentsFromFile();
void loadSuspectsFromFile();
void loadUsersFromFile();
void loadTransactionsFromFile();

void addIncident();
void addSuspect();
void addUser();

void displayAllAlerts();
void displayAlertsByLocation(string area);
void displaySuspectDetails(int incidentID);

void rewardMenu();
void submitTip(int userID, int incidentID);
void approveReward(int transactionID);
void displayUserRewards(int userID);

void roleSelectionScreen();
void startMenu();

void profileScreen();

#endif 