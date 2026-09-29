#include <iostream>
using namespace std;

struct Person {
    int id;
    Person* next;
    Person(int i) : id(i), next(nullptr) {}
};

void josephusSimulation(int N, int k) {
    if (N <= 0 || k <= 0) {
        cout << "Invalid input parameters.\n";
        return;
    }

    Person* head = new Person(1);
    Person* prev = head;
    for (int i = 2; i <= N; i++) {
        Person* newPerson = new Person(i);
        prev->next = newPerson;
        prev = newPerson;
    }
    prev->next = head; // Circle formation

    Person* curr = head;
    Person* prevNode = prev;

    cout << "\nEliminated Order: ";
    while (curr->next != curr) {
        for (int i = 1; i < k; i++) {
            prevNode = curr;
            curr = curr->next;
        }
        
        cout << curr->id << " ";
        prevNode->next = curr->next;
        Person* temp = curr;
        curr = curr->next;
        delete temp;
    }

    cout << "\nSurvivor: " << curr->id << "\n";
    delete curr;
}

int main() {
    int N, k;
    cout << "Enter total number of people (N): ";
    cin >> N;
    cout << "Enter step count (k): ";
    cin >> k;

    josephusSimulation(N, k);

    return 0;
}