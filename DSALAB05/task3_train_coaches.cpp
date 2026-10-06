#include <iostream>
#include <string>
using namespace std;
struct Coach {
    int number;
    string type;
    int capacity, passengers;
    Coach *next, *prev;
};
Coach *head = NULL, *current = NULL;
Coach* findCoach(int num) {
    if (head == NULL) return NULL;
    Coach* c = head;
    do {
        if (c->number == num) return c;
        c = c->next;
    } while (c != head);
    return NULL;
}
Coach* readCoach() {
    Coach* c = new Coach;
    cout << "Coach Number: "; cin >> c->number; cin.ignore();
    cout << "Coach Type: "; getline(cin, c->type);
    cout << "Passenger Capacity: "; cin >> c->capacity;
    cout << "Current Passengers: "; cin >> c->passengers;
    return c;
}
void showCoach(Coach* c) {
    cout << "Coach " << c->number << ", Type: " << c->type << ", Capacity: " << c->capacity
         << ", Passengers: " << c->passengers << ", Empty Seats: "
         << c->capacity - c->passengers << endl;
}
void addCoach() {
    Coach* c = readCoach();
    if (head == NULL) {
        c->next = c;
        c->prev = c;
        head = current = c;
    } else {
        Coach* last = head->prev;
        c->next = head;
        c->prev = last;
        last->next = c;
        head->prev = c;
    }
}
void insertCoach() {
    int after;
    cout << "Insert after coach number: "; cin >> after;
    Coach* pos = findCoach(after);
    if (pos == NULL) { cout << "Coach not found.\n"; return; }
    Coach* c = readCoach();
    c->next = pos->next;
    c->prev = pos;
    pos->next->prev = c;
    pos->next = c;
}
void removeCoach() {
    int num;
    cout << "Coach number to remove: "; cin >> num;
    Coach* c = findCoach(num);
    if (c == NULL) { cout << "Coach not found.\n"; return; }

    if (c->next == c) {
        head = current = NULL;
    } else {
        c->prev->next = c->next;
        c->next->prev = c->prev;
        if (head == c) head = c->next;
        if (current == c) current = c->next;
    }
    delete c;
}
void moveForward() {
    if (current == NULL) { cout << "Train is empty.\n"; return; }
    current = current->next;
    showCoach(current);
}
void moveBackward() {
    if (current == NULL) { cout << "Train is empty.\n"; return; }
    current = current->prev;
    showCoach(current);
}
void displayClockwise() {
    if (current == NULL) { cout << "Train is empty.\n"; return; }
    Coach* c = current;
    do {
        showCoach(c);
        c = c->next;
    } while (c != current);
}
void displayAnticlockwise() {
    if (current == NULL) { cout << "Train is empty.\n"; return; }
    Coach* c = current;
    do {
        showCoach(c);
        c = c->prev;
    } while (c != current);
}
void searchCoach() {
    int num;
    cout << "Coach number to search: "; cin >> num;
    Coach* c = findCoach(num);
    if (c == NULL) cout << "Coach not found.\n";
    else showCoach(c);
}
void maxCapacity() {
    if (head == NULL) { cout << "Train is empty.\n"; return; }
    Coach* best = head;
    Coach* c = head->next;
    while (c != head) {
        if (c->capacity - c->passengers > best->capacity - best->passengers) best = c;
        c = c->next;
    }
    showCoach(best);
}
void displayCurrent() {
    if (current == NULL) { cout << "Train is empty.\n"; return; }
    showCoach(current);
}
void reverseTrain() {
    if (head == NULL) { cout << "Train is empty.\n"; return; }
    Coach* newHead = head->prev;
    Coach* c = head;
    do {
        Coach* nextCoach = c->next;
        c->next = c->prev;
        c->prev = nextCoach;
        c = nextCoach;
    } while (c != head);
    head = newHead;
}
int main() {
    int n, choice;
    cout << "Number of coaches: "; cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "Coach " << i + 1 << ":\n";
        addCoach();
    }
    do {
        cout << "\n1. Add Coach\n2. Insert Coach\n3. Remove Coach\n4. Move Forward\n"
             << "5. Move Backward\n6. Display Train Clockwise\n7. Display Train Anti-clockwise\n"
             << "8. Search Coach\n9. Find Maximum Available Capacity\n10. Display Current Coach\n"
             << "11. Reverse Train Direction\n0. Exit\nChoice: ";
        cin >> choice;
        switch (choice) {
            case 1: addCoach(); break;
            case 2: insertCoach(); break;
            case 3: removeCoach(); break;
            case 4: moveForward(); break;
            case 5: moveBackward(); break;
            case 6: displayClockwise(); break;
            case 7: displayAnticlockwise(); break;
            case 8: searchCoach(); break;
            case 9: maxCapacity(); break;
            case 10: displayCurrent(); break;
            case 11: reverseTrain(); break;
        }
    } while (choice != 0);
    while (head != NULL) {
        Coach* c = head;
        if (c->next == c) head = NULL;
        else {
            c->prev->next = c->next;
            c->next->prev = c->prev;
            head = c->next;
        }
        delete c;
    }
    return 0;
}