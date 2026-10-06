#include <iostream>
#include <string>
using namespace std;
struct Tab {
    int id;
    string title, url;
    Tab *next, *prev;
};
Tab* current = NULL;
void openTab() {
    Tab* n = new Tab;
    cout << "Tab ID: "; cin >> n->id; cin.ignore();
    cout << "Title: "; getline(cin, n->title);
    cout << "URL: "; getline(cin, n->url);

    if (current == NULL) {
        n->next = n;
        n->prev = n;
    } else {
        n->next = current->next;
        n->prev = current;
        current->next->prev = n;
        current->next = n;
    }
    current = n;
}
void closeTab() {
    if (current == NULL) { cout << "No tabs open.\n"; return; }
    Tab* temp = current;
    if (temp->next == temp) {
        current = NULL;
    } else {
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        current = temp->next;
    }
    delete temp;
}
void showTab(Tab* t) {
    cout << "ID: " << t->id << ", Title: " << t->title << ", URL: " << t->url << endl;
}
void moveNext() {
    if (current == NULL) { cout << "No tabs open.\n"; return; }
    current = current->next;
}
void movePrev() {
    if (current == NULL) { cout << "No tabs open.\n"; return; }
    current = current->prev;
}
void displayCurrent() {
    if (current == NULL) { cout << "No tabs open.\n"; return; }
    showTab(current);
}
void displayForward() {
    if (current == NULL) { cout << "No tabs open.\n"; return; }
    Tab* t = current;
    do {
        showTab(t);
        t = t->next;
    } while (t != current);
}
void displayBackward() {
    if (current == NULL) { cout << "No tabs open.\n"; return; }
    Tab* t = current;
    do {
        showTab(t);
        t = t->prev;
    } while (t != current);
}
void searchTab() {
    if (current == NULL) { cout << "No tabs open.\n"; return; }
    int id;
    cout << "Tab ID to search: "; cin >> id;
    Tab* t = current;
    do {
        if (t->id == id) { showTab(t); return; }
        t = t->next;
    } while (t != current);
    cout << "Tab not found.\n";
}
int main() {
    int choice;
    do {
        cout << "\n1. Open New Tab\n2. Close Current Tab\n3. Move Next\n4. Move Previous\n"
             << "5. Display Current Tab\n6. Display All Tabs Forward\n"
             << "7. Display All Tabs Backward\n8. Search Tab\n0. Exit\nChoice: ";
        cin >> choice;
        switch (choice) {
            case 1: openTab(); break;
            case 2: closeTab(); break;
            case 3: moveNext(); break;
            case 4: movePrev(); break;
            case 5: displayCurrent(); break;
            case 6: displayForward(); break;
            case 7: displayBackward(); break;
            case 8: searchTab(); break;
        }
    } while (choice != 0);

    while (current != NULL) closeTab();
    return 0;
}