#include <iostream>
#include <string>
using namespace std;

struct Song {
    int id;
    string name;
    string duration;
    Song* prev;
    Song* next;
    Song(int i, string n, string d) : id(i), name(n), duration(d), prev(nullptr), next(nullptr) {}
};

class Playlist {
    Song* head;
    Song* tail;
    Song* current;
public:
    Playlist() : head(nullptr), tail(nullptr), current(nullptr) {}

    void addSong(int id, string name, string duration) {
        Song* newSong = new Song(id, name, duration);
        if (!head) {
            head = tail = current = newSong;
        } else {
            tail->next = newSong;
            newSong->prev = tail;
            tail = newSong;
        }
        cout << "Song added successfully.\n";
    }

    void deleteSong(int id) {
        Song* temp = head;
        while (temp && temp->id != id) temp = temp->next;
        if (!temp) {
            cout << "Song with ID " << id << " not found.\n";
            return;
        }

        if (temp == head) head = temp->next;
        if (temp == tail) tail = temp->prev;
        if (temp->prev) temp->prev->next = temp->next;
        if (temp->next) temp->next->prev = temp->prev;
        if (current == temp) current = head;
        delete temp;
        cout << "Song deleted successfully.\n";
    }

    void displayForward() {
        if (!head) { cout << "Playlist is empty.\n"; return; }
        Song* temp = head;
        while (temp) {
            cout << "[" << temp->id << "] " << temp->name << " (" << temp->duration << ") -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }

    void displayBackward() {
        if (!tail) { cout << "Playlist is empty.\n"; return; }
        Song* temp = tail;
        while (temp) {
            cout << "[" << temp->id << "] " << temp->name << " (" << temp->duration << ") -> ";
            temp = temp->prev;
        }
        cout << "NULL\n";
    }

    void searchSong(int id) {
        Song* temp = head;
        while (temp) {
            if (temp->id == id) {
                cout << "Found: [" << temp->id << "] " << temp->name << " (" << temp->duration << ")\n";
                return;
            }
            temp = temp->next;
        }
        cout << "Song not found.\n";
    }

    void playNext() {
        if (current && current->next) { 
            current = current->next; 
            cout << "Now Playing: " << current->name << "\n"; 
        } else if (current) {
            cout << "Now Playing: " << current->name << " (End of playlist)\n";
        } else {
            cout << "Playlist is empty.\n";
        }
    }

    void playPrev() {
        if (current && current->prev) { 
            current = current->prev; 
            cout << "Now Playing: " << current->name << "\n"; 
        } else if (current) {
            cout << "Now Playing: " << current->name << " (Start of playlist)\n";
        } else {
            cout << "Playlist is empty.\n";
        }
    }

    void reversePlaylist() {
        Song* temp = nullptr;
        Song* curr = head;
        tail = head;
        while (curr) {
            temp = curr->prev;
            curr->prev = curr->next;
            curr->next = temp;
            curr = curr->prev;
        }
        if (temp) head = temp->prev;
        cout << "Playlist reversed successfully.\n";
    }
};

int main() {
    Playlist myPlaylist;

    // Preset initial songs as requested
    myPlaylist.addSong(1, "Dil (Bohemia)", "3:45");
    myPlaylist.addSong(2, "Kal Chaudvin Ki Raat Thi", "5:10");
    myPlaylist.addSong(3, "California Love", "4:00");

    int choice;
    do {
        cout << "\n=== PLAYLIST MENU ===\n"
             << "1. Add Song\n"
             << "2. Delete Song\n"
             << "3. Display Forward\n"
             << "4. Display Backward\n"
             << "5. Search Song\n"
             << "6. Play Next\n"
             << "7. Play Previous\n"
             << "8. Reverse Playlist\n"
             << "0. Exit\n"
             << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int id; string name, dur;
            cout << "Enter Song ID: "; cin >> id;
            cin.ignore();
            cout << "Enter Song Name: "; getline(cin, name);
            cout << "Enter Duration (m:s): "; cin >> dur;
            myPlaylist.addSong(id, name, dur);
        } else if (choice == 2) {
            int id; cout << "Enter Song ID to delete: "; cin >> id;
            myPlaylist.deleteSong(id);
        } else if (choice == 3) {
            myPlaylist.displayForward();
        } else if (choice == 4) {
            myPlaylist.displayBackward();
        } else if (choice == 5) {
            int id; cout << "Enter Song ID to search: "; cin >> id;
            myPlaylist.searchSong(id);
        } else if (choice == 6) {
            myPlaylist.playNext();
        } else if (choice == 7) {
            myPlaylist.playPrev();
        } else if (choice == 8) {
            myPlaylist.reversePlaylist();
        }
    } while (choice != 0);

    return 0;
}