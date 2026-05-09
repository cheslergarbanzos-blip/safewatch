#include "UNIVERSAL.h"
#include <thread>
#include <chrono>
#include <ctime>
#include <cctype>

// Notification data structure
struct Notification {
    int id;
    string name;
    string appearance;
    string lastLocation;
    string crimeType;
    bool read;
    string timestamp;
};

// Global notification list
vector<Notification> notifications;

// Function to create notification from incident and suspect data
Notification createNotification(int incidentIndex, int suspectIndex) {
    Notification n;
    n.id = incidentIndex;
    n.crimeType = incidentCrime[incidentIndex];
    n.lastLocation = incidentLocation[incidentIndex];
    if (suspectIndex != -1) {
        n.name = suspectName[suspectIndex];
        n.appearance = suspectHeight[suspectIndex] + ", " + suspectBuild[suspectIndex] + ", " + suspectClothing[suspectIndex];
    } else {
        n.name = "Unknown";
        n.appearance = "Not available";
    }
    n.read = false;
    n.timestamp = incidentDate[incidentIndex];
    return n;
}

// Load notifications from current data
void loadNotifications() {
    notifications.clear();
    for (int i = 0; i < incidentCount; i++) {
        int suspectIndex = -1;
        for (int j = 0; j < suspectCount; j++) {
            if (suspectIncidentID[j] == i) {
                suspectIndex = j;
                break;
            }
        }
        Notification n = createNotification(i, suspectIndex);
        notifications.push_back(n);
    }
}

// Filter notifications by user's location
vector<Notification> getFilteredNotifications(string userLocation) {
    vector<Notification> filtered;
    if (userLocation.empty()) return filtered;

    // Convert user location to lowercase for case-insensitive matching
    string lowerUserLoc = userLocation;
    for (char &c : lowerUserLoc) c = (char)tolower((unsigned char)c);

    for (auto& n : notifications) {
        // Convert incident location to lowercase
        string lowerIncLoc = n.lastLocation;
        for (char &c : lowerIncLoc) c = (char)tolower((unsigned char)c);

        // Check if the user's area keyword exists within the reported incident location
        if (lowerIncLoc.find(lowerUserLoc) != string::npos) {
            filtered.push_back(n);
        }
    }
    return filtered;
}

// Display notification center
void displayNotificationCenter(string userLocation) {
    loadNotifications();
    while (true) {
        system("cls");
    vector<Notification> filtered = getFilteredNotifications(userLocation);
        cout << "▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄\n";
        cout << "██                                           ██\n";
        cout << "██     ▄▄  ▄▄  ▄▄▄ ▄▄▄▄▄▄ ▄▄  ▄▄▄▄ ▄▄▄▄▄     ██\n";
        cout << "██     ███▄██ ██▀██  ██   ██ ██▀▀▀ ██▄▄      ██\n";
        cout << "██     ██ ▀██ ▀███▀  ██   ██ ▀████ ██▄▄▄     ██\n";
        cout << "██                                           ██\n";
        cout << "▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀\n";
        cout << "\n";
    if (filtered.empty()) {
        cout << "No notifications in your area.\n";
        Sleep(1500);
        return;
    }
    
    int filteredCount = static_cast<int>(filtered.size());
    for (int i = filteredCount - 1; i >= 0; i--) { // Most recent first
        Notification n = filtered[i];
        cout << (n.read ? "[READ] " : "[UNREAD] ") << n.crimeType << " | " << n.lastLocation << " | " << n.name << " |\n";
        cout << "Preview: " << n.appearance.substr(0, 50) << "...\n";
        cout << "Timestamp: " << n.timestamp << "\n";
        cout << "▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄\n";
        cout << "\n";
    }

    // Allow viewing details
    cout << "Enter notification number to view details (1-" << filteredCount << "), or 0 to go back to main menu: ";
    cout << "\n";
    int localChoice;
    if (!(cin >> localChoice)) { cin.clear(); cin.ignore(1000, '\n'); continue; }
    
    if (localChoice == 0) return; // Exit the notification center

    if (localChoice > 0 && localChoice <= filteredCount) {
        Notification n = filtered[filteredCount - localChoice];
        system("cls");
        cout << "▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄\n";
        cout << "██                                           ██\n";
        cout << "██     ▄▄  ▄▄  ▄▄▄ ▄▄▄▄▄▄ ▄▄  ▄▄▄▄ ▄▄▄▄▄     ██\n";
        cout << "██     ███▄██ ██▀██  ██   ██ ██▀▀▀ ██▄▄      ██\n";
        cout << "██     ██ ▀██ ▀███▀  ██   ██ ▀████ ██▄▄▄     ██\n";
        cout << "██                                           ██\n";
        cout << "▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀    DETAILS    ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀\n";
        cout << "\n";
        cout << "Crime Type: " << n.crimeType << "\n";
        cout << "Location: " << n.lastLocation << "\n";
        cout << "Name: " << n.name << "\n";
        cout << "Appearance: " << n.appearance << "\n";
        cout << "Timestamp: " << n.timestamp << "\n";
        cout << "▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄\n";
        // Update in global list
        for (auto& globalN : notifications) {
            if (globalN.id == n.id) {
                globalN.read = true;
                break;
            }
        }

        cout << "\nPress Enter to return to the notification list...";
        cin.ignore(1000, '\n'); // Clear buffer from localChoice input
        cin.get();
    }
    }
}

// Show pop-up notification
void showPopupNotification(Notification n) {
    string message = "New Alert: " + n.crimeType + " in " + n.lastLocation + "\nName: " + n.name + "\nAppearance: " + n.appearance;
    MessageBoxA(NULL, message.c_str(), "SafeWatch Alert", MB_OK | MB_ICONINFORMATION);
}

// Simulate real-time alerts (run in background thread)
void realTimeAlerts(string userLocation) {
    while (true) {
        // Simulate checking for new data (in real app, poll database or file)
        // For demo, assume new notifications are added externally
        // Here, just check if there are unread notifications
        vector<Notification> filtered = getFilteredNotifications(userLocation);
        for (auto& n : filtered) {
            if (!n.read) {
                showPopupNotification(n);
                n.read = true; // Mark as shown
                // Update global
                for (auto& globalN : notifications) {
                    if (globalN.id == n.id) {
                        globalN.read = true;
                        break;
                    }
                }
            }
        }
        this_thread::sleep_for(chrono::seconds(10)); // Check every 10 seconds
    }
}

// Start real-time monitoring (call this when user logs in)
thread* alertThread = nullptr;
void startRealTimeAlerts(string userLocation) {
    if (alertThread == nullptr) {
        alertThread = new thread(realTimeAlerts, userLocation);
    }
}

// Stop real-time monitoring (call this on logout)
void stopRealTimeAlerts() {
    if (alertThread != nullptr) {
        alertThread->detach();
        delete alertThread;
        alertThread = nullptr;
    }
}