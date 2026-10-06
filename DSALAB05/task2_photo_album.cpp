#include <iostream>
#include <string>
using namespace std;
struct Photo {
    int id;
    string name, date, location;
    Photo *next, *prev;
};
Photo *head = NULL, *current = NULL;
int count = 0;
Photo* readPhoto() {
    Photo* p = new Photo;
    cout << "Photo ID: "; cin >> p->id; cin.ignore();
    cout << "Name: "; getline(cin, p->name);
    cout << "Date Taken: "; getline(cin, p->date);
    cout << "Location: "; getline(cin, p->location);
    return p;
}
void showPhoto(Photo* p) {
    cout << "ID: " << p->id << ", Name: " << p->name << ", Date: " << p->date
         << ", Location: " << p->location << endl;
}
void addPhoto() {
    Photo* p = readPhoto();
    if (head == NULL) {
        p->next = p;
        p->prev = p;
        head = current = p;
    } else {
        Photo* last = head->prev;
        p->next = head;
        p->prev = last;
        last->next = p;
        head->prev = p;
    }
    count++;
}
void insertAfterCurrent() {
    if (current == NULL) { addPhoto(); return; }
    Photo* p = readPhoto();
    p->next = current->next;
    p->prev = current;
    current->next->prev = p;
    current->next = p;
    count++;
}
void deletePhoto(Photo* p) {
    if (p->next == p) {
        head = current = NULL;
    } else {
        p->prev->next = p->next;
        p->next->prev = p->prev;
        if (head == p) head = p->next;
        if (current == p) current = p->next;
    }
    delete p;
    count--;
}
void removeById() {
    if (head == NULL) { cout << "Album is empty.\n"; return; }
    int id;
    cout << "Photo ID to remove: "; cin >> id;
    Photo* p = head;
    do {
        if (p->id == id) { deletePhoto(p); return; }
        p = p->next;
    } while (p != head);
    cout << "Photo not found.\n";
}
void removeCurrent() {
    if (current == NULL) { cout << "Album is empty.\n"; return; }
    deletePhoto(current);
}
void moveNext() {
    if (current == NULL) { cout << "Album is empty.\n"; return; }
    current = current->next;
    showPhoto(current);
}
void movePrev() {
    if (current == NULL) { cout << "Album is empty.\n"; return; }
    current = current->prev;
    showPhoto(current);
}
void displayForward() {
    if (current == NULL) { cout << "Album is empty.\n"; return; }
    Photo* p = current;
    do {
        showPhoto(p);
        p = p->next;
    } while (p != current);
}
void displayBackward() {
    if (current == NULL) { cout << "Album is empty.\n"; return; }
    Photo* p = current;
    do {
        showPhoto(p);
        p = p->prev;
    } while (p != current);
}
void searchPhoto() {
    if (head == NULL) { cout << "Album is empty.\n"; return; }
    int id;
    cout << "Photo ID to search: "; cin >> id;
    Photo* p = head;
    do {
        if (p->id == id) { showPhoto(p); return; }
        p = p->next;
    } while (p != head);
    cout << "Photo not found.\n";
}
int main() {
    int n, choice;
    cout << "Number of photos: "; cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "Photo " << i + 1 << ":\n";
        addPhoto();
    }
    do {
        cout << "\n1. Add Photo\n2. Insert Photo After Current\n3. Remove Photo\n"
             << "4. Remove Current Photo\n5. Move Next\n6. Move Previous\n"
             << "7. Display Album Forward\n8. Display Album Backward\n9. Search Photo\n"
             << "10. Count Photos\n0. Exit\nChoice: ";
        cin >> choice;
        switch (choice) {
            case 1: addPhoto(); break;
            case 2: insertAfterCurrent(); break;
            case 3: removeById(); break;
            case 4: removeCurrent(); break;
            case 5: moveNext(); break;
            case 6: movePrev(); break;
            case 7: displayForward(); break;
            case 8: displayBackward(); break;
            case 9: searchPhoto(); break;
            case 10: cout << "Total photos: " << count << endl; break;
        }
    } while (choice != 0);

    while (head != NULL) deletePhoto(head);
    return 0;
}