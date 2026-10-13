// Task 3: Print Server Request Handling System
// Circular queue with dynamic resizing
#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

// Each print request has an ID, arrival time and processing time
struct Request {
    int id;
    int arrival;
    int proc;
};

// ---------- Circular queue (array based, resizes automatically) ----------
class CircularQueue {
    Request* arr;
    int cap;          // current capacity
    int frontIdx;     // index of the first element
    int count;        // number of elements stored
    static const int MIN_CAP = 4;

public:
    CircularQueue() {
        cap = MIN_CAP;
        frontIdx = 0;
        count = 0;
        arr = new Request[cap];
    }
    ~CircularQueue() { delete[] arr; }
    CircularQueue(const CircularQueue&) = delete;
    CircularQueue& operator=(const CircularQueue&) = delete;

    bool isEmpty() { return count == 0; }
    bool isFull() { return count == cap; }

    // Copies all requests (in order) into a new array. No data is lost.
    void resize(int newCap) {
        Request* newArr = new Request[newCap];
        for (int i = 0; i < count; i++)
            newArr[i] = arr[(frontIdx + i) % cap];   // front goes to index 0
        delete[] arr;
        arr = newArr;
        cout << "   [Resize] capacity changed from " << cap << " to " << newCap << "\n";
        cap = newCap;
        frontIdx = 0;
    }

    void enqueue(Request x) {
        if (isFull())
            resize(cap * 2);                         // full -> double the size
        arr[(frontIdx + count) % cap] = x;           // rear position
        count++;
    }

    Request dequeue() {
        Request x = arr[frontIdx];
        frontIdx = (frontIdx + 1) % cap;
        count--;
        if (cap > MIN_CAP && count <= cap / 4)       // too sparse -> halve the size
            resize(cap / 2 < MIN_CAP ? MIN_CAP : cap / 2);
        return x;
    }

    Request front() { return arr[frontIdx]; }

    // Shows the array exactly as stored, so the wrap-around is visible
    void display() {
        cout << "   Queue (size=" << count << ", capacity=" << cap << ")  |";
        for (int i = 0; i < cap; i++) {
            bool used = ((i - frontIdx + cap) % cap) < count;
            if (used) cout << " P" << arr[i].id << " |";
            else      cout << "  -  |";
        }
        cout << "\n";
    }
};

// ---------- Print server: statistics ----------
struct Stats {
    int clock = 0;        // time at which the printer becomes free
    int totalWait = 0;
    int served = 0;
};

void addRequest(CircularQueue& q, Request r) {
    cout << "Enqueue: P" << r.id << " (arrival=" << r.arrival << ", processing=" << r.proc << ")\n";
    q.enqueue(r);
    q.display();
}

void serveNext(CircularQueue& q, Stats& s) {
    if (q.isEmpty()) {
        cout << "No requests in the queue.\n";
        return;
    }
    Request r = q.front();
    int start = (s.clock > r.arrival) ? s.clock : r.arrival;   // printer may be idle
    int wait = start - r.arrival;

    cout << "Dequeue: P" << r.id << " starts at t=" << start
         << ", waiting time = " << wait << "\n";
    q.dequeue();
    q.display();

    s.clock = start + r.proc;
    s.totalWait += wait;
    s.served++;
}

void showAverage(Stats& s) {
    if (s.served == 0) {
        cout << "No requests have been processed yet.\n";
        return;
    }
    cout << fixed << setprecision(2);
    cout << "Requests processed : " << s.served << "\n"
         << "Total waiting time : " << s.totalWait << "\n"
         << "Average waiting time: " << (double)s.totalWait / s.served << "\n";
}

// Reads an integer safely (re-asks if the user types letters)
int readInt(string message) {
    int x;
    cout << message;
    while (!(cin >> x)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input, enter a number: ";
    }
    return x;
}

// Ready-made test: 5 requests arrive, then all are processed
void runDemo() {
    CircularQueue q;
    Stats s;
    Request demo[5] = { {1, 0, 5}, {2, 1, 3}, {3, 2, 4}, {4, 3, 2}, {5, 4, 6} };

    cout << "\n--- Demo: enqueue 5 requests ---\n";
    for (int i = 0; i < 5; i++) addRequest(q, demo[i]);

    cout << "\n--- Demo: dequeue all requests ---\n";
    while (!q.isEmpty()) serveNext(q, s);

    cout << "\n";
    showAverage(s);
}

int main() {
    CircularQueue q;
    Stats s;
    int choice;

    do {
        cout << "\n===== Print Server =====\n"
             << "1. Add print request (enqueue)\n"
             << "2. Process next request (dequeue)\n"
             << "3. Show front request\n"
             << "4. Show queue\n"
             << "5. Show average waiting time\n"
             << "6. Run demo\n"
             << "0. Exit\n";
        choice = readInt("Enter choice: ");

        if (choice == 1) {
            Request r;
            r.id = readInt("Request ID: ");
            r.arrival = readInt("Arrival time: ");
            r.proc = readInt("Processing time: ");
            if (r.arrival < 0 || r.proc <= 0)
                cout << "Invalid values! Arrival must be >= 0 and processing time > 0.\n";
            else
                addRequest(q, r);
        }
        else if (choice == 2) {
            serveNext(q, s);
        }
        else if (choice == 3) {
            if (q.isEmpty()) cout << "Queue is empty.\n";
            else {
                Request r = q.front();
                cout << "Front: P" << r.id << " (arrival=" << r.arrival
                     << ", processing=" << r.proc << ")\n";
            }
        }
        else if (choice == 4) {
            if (q.isEmpty()) cout << "Queue is empty.\n";
            q.display();
        }
        else if (choice == 5) {
            showAverage(s);
        }
        else if (choice == 6) {
            runDemo();
        }
        else if (choice != 0) {
            cout << "Invalid choice, try again.\n";
        }
    } while (choice != 0);
    cout << "\n--- Final Result ---\n";
    showAverage(s);
    return 0;
}