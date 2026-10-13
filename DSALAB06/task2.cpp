// Task 2: Expression Validators using Stack
//   Part A - Bracket validator
//   Part B - HTML/XML tag validator
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <limits>
using namespace std;

// ---------- Our own stack (array based, grows when full) ----------
template <typename T>
class Stack {
    T* data;
    int topIdx;
    int capacity;

    void grow() {
        T* bigger = new T[capacity * 2];
        for (int i = 0; i <= topIdx; i++) bigger[i] = data[i];
        delete[] data;
        data = bigger;
        capacity *= 2;
    }
public:
    Stack() { capacity = 10; topIdx = -1; data = new T[capacity]; }
    ~Stack() { delete[] data; }
    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;

    void push(T x) {
        if (topIdx + 1 == capacity) grow();
        data[++topIdx] = x;
    }
    T pop() { return data[topIdx--]; }      // always check isEmpty() before calling
    T peek() { return data[topIdx]; }
    bool isEmpty() { return topIdx == -1; }
};

// =================== Part A: Bracket Validator ===================
bool isValidBrackets(string s) {
    Stack<char> st;

    for (int i = 0; i < (int)s.length(); i++) {
        char c = s[i];

        if (c == '(' || c == '{' || c == '[') {
            st.push(c);                                  // opening bracket
        }
        else if (c == ')' || c == '}' || c == ']') {
            if (st.isEmpty()) return false;              // nothing to match with

            char open = st.pop();
            if ((open == '(' && c != ')') ||
                (open == '{' && c != '}') ||
                (open == '[' && c != ']'))
                return false;                            // wrong type of bracket
        }
    }
    return st.isEmpty();                                 // leftover = not closed
}

// =================== Part B: HTML/XML Tag Validator ===================
struct Tag {
    string name;
    int pos;        // position where the tag was opened
};

// HTML tags that never need a closing tag
bool isVoidTag(string name) {
    return name == "br" || name == "hr" || name == "img" ||
           name == "input" || name == "meta" || name == "link";
}

pair<bool, vector<string>> validate_markup(string s) {
    Stack<Tag> st;
    vector<string> errors;
    int i = 0;

    while (i < (int)s.length()) {
        if (s[i] != '<') { i++; continue; }              // skip normal text

        int start = i;
        int end = s.find('>', i);
        if (end == (int)string::npos) {
            errors.push_back("Tag starting at position " + to_string(start) + " is not closed with '>'");
            break;
        }

        string inner = s.substr(start + 1, end - start - 1);   // text between < and >
        i = end + 1;

        if (inner.empty()) {
            errors.push_back("Empty tag '<>' at position " + to_string(start));
            continue;
        }
        if (inner[0] == '!' || inner[0] == '?') continue;      // comments, <!DOCTYPE>

        bool isClosing = (inner[0] == '/');
        bool selfClosing = (!isClosing && inner[inner.length() - 1] == '/');

        // get only the tag name (ignore attributes like id="1")
        string body = inner;
        if (isClosing) body = body.substr(1);
        if (selfClosing) body = body.substr(0, body.length() - 1);

        string name = "";
        for (int k = 0; k < (int)body.length() && body[k] != ' '; k++)
            name += body[k];

        if (name.empty()) {
            errors.push_back("Tag without a name at position " + to_string(start));
            continue;
        }

        if (isClosing) {
            if (st.isEmpty()) {
                errors.push_back("Extra closing tag </" + name + "> at position " + to_string(start));
            }
            else if (st.peek().name == name) {
                st.pop();                                      // correct match
            }
            else {
                errors.push_back("Wrong nesting at position " + to_string(start) +
                                 ": expected </" + st.peek().name + "> but found </" + name + ">");
                st.pop();
            }
        }
        else if (selfClosing || isVoidTag(name)) {
            // nothing to do, no closing tag needed
        }
        else {
            Tag t;
            t.name = name;
            t.pos = start;
            st.push(t);                                        // opening tag
        }
    }

    // tags still on the stack were never closed
    while (!st.isEmpty()) {
        Tag t = st.pop();
        errors.push_back("Tag <" + t.name + "> opened at position " + to_string(t.pos) + " is never closed");
    }

    return make_pair(errors.empty(), errors);
}

// =================== Main: asks the user for input ===================
int main() {
    int choice;

    do {
        cout << "\n===== Expression Validators =====\n"
             << "1. Bracket Validator\n"
             << "2. HTML/XML Tag Validator\n"
             << "0. Exit\n"
             << "Enter choice: ";

        if (!(cin >> choice)) {                          // user typed a non-number
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a number.\n";
            choice = -1;
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');   // remove leftover newline

        string input;

        if (choice == 1) {
            cout << "Enter expression with brackets: ";
            getline(cin, input);
            if (isValidBrackets(input))
                cout << "Result: VALID (brackets are balanced)\n";
            else
                cout << "Result: INVALID (brackets are not balanced)\n";
        }
        else if (choice == 2) {
            cout << "Enter HTML/XML string: ";
            getline(cin, input);

            pair<bool, vector<string>> result = validate_markup(input);
            if (result.first) {
                cout << "Result: VALID (all tags are properly nested and closed)\n";
            } else {
                cout << "Result: INVALID\n";
                for (int i = 0; i < (int)result.second.size(); i++)
                    cout << "  Error " << i + 1 << ": " << result.second[i] << "\n";
            }
        }
        else if (choice != 0) {
            cout << "Invalid choice, try again.\n";
        }
    } while (choice != 0);
    cout << "Goodbye!\n";
    return 0;
}