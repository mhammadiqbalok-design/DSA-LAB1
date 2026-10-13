// Task 4: Waiting Room Management System (Emergency Ward)
// Array-based queue
#include <iostream>
#include <limits>
using namespace std;
const int MAX_PATIENTS = 10;      // size of the waiting room (change if you want)
class WaitingRoom {
    int queueArr[MAX_PATIENTS];   // stores patient IDs
    int frontIdx;                 // index of the patient who is served next
    int count;                    // number of patients waiting
    int nextId;                   // auto-generated ID (starts at 1)
public:
    WaitingRoom() {
        frontIdx = 0;
        count = 0;
        nextId = 1;
    }
    // Gives the patient a new ID and adds him/her at the end of the queue
    void RegisterPatient() {
        if (count == MAX_PATIENTS) {
            cout << "Waiting room is full! Cannot register more patients.\n";
            return;
        }
        int rear = (frontIdx + count) % MAX_PATIENTS;
        queueArr[rear] = nextId;
        count++;
        cout << "Patient registered. Assigned ID = " << nextId << "\n";
        nextId++;
    }
    // Calls the patient who has been waiting the longest (front of the queue)
    void ServePatient() {
        if (count == 0) {
            cout << "No patients are waiting.\n";
            return;
        }
        int id = queueArr[frontIdx];
        frontIdx = (frontIdx + 1) % MAX_PATIENTS;
        count--;
        cout << "Now serving patient ID = " << id << "\n";
    }
    // Removes all waiting patients (IDs keep increasing, so they stay unique)
    void CancelAll() {
        if (count == 0) {
            cout << "No appointments to cancel.\n";
            return;
        }
        cout << count << " appointment(s) cancelled. Doctor can go to lunch.\n";
        frontIdx = 0;
        count = 0;
    }
    // true if nobody is waiting, otherwise false
    bool CanDoctorGoHome() {
        return count == 0;
    }
    // Shows the IDs of all waiting patients in sorted order
    void ShowAllPatient() {
        if (count == 0) {
            cout << "No patients are waiting.\n";
            return;
        }
        // copy the IDs into a temporary array (the queue itself is not changed)
        int temp[MAX_PATIENTS];
        for (int i = 0; i < count; i++)
            temp[i] = queueArr[(frontIdx + i) % MAX_PATIENTS];

        // sort the copy (bubble sort)
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - i - 1; j++) {
                if (temp[j] > temp[j + 1]) {
                    int t = temp[j];
                    temp[j] = temp[j + 1];
                    temp[j + 1] = t;
                }
            }
        }
        cout << "Waiting patients (" << count << "): ";
        for (int i = 0; i < count; i++)
            cout << temp[i] << " ";
        cout << "\n";
    }
};
int main() {
    WaitingRoom room;
    int choice;
    do {
        cout << "\n===== Emergency Ward Waiting Room =====\n"
             << "1. Register patient\n"
             << "2. Serve patient\n"
             << "3. Cancel all appointments\n"
             << "4. Can doctor go home?\n"
             << "5. Show all waiting patients\n"
             << "0. Exit\n"
             << "Enter choice: ";
        if (!(cin >> choice)) {                       // user typed letters
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a number.\n";
            choice = -1;
            continue;
        }
        if (choice == 1)      room.RegisterPatient();
        else if (choice == 2) room.ServePatient();
        else if (choice == 3) room.CancelAll();
        else if (choice == 4) {
            if (room.CanDoctorGoHome())
                cout << "Yes, no one is waiting. Doctor can go home.\n";
            else
                cout << "No, patients are still waiting.\n";
        }
        else if (choice == 5) room.ShowAllPatient();
        else if (choice != 0) cout << "Invalid choice, try again.\n";

    } while (choice != 0);
    cout << "Goodbye!\n";
    return 0;
}