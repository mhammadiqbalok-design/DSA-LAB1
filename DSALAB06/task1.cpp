// Task 1: Infix / Postfix / Prefix conversion and evaluation
// Uses our own array-based Stack (no STL stack).
#include <iostream>
#include <string>
#include <stdexcept>
#include <cmath>
#include <cctype>
#include <limits>
using namespace std;

// ---------- Generic array-based stack (grows automatically) ----------
template <typename T>
class Stack {
    T* data;
    int topIdx;      // index of the top element (-1 when empty)
    int capacity;

    void grow() {
        int newCap = capacity * 2;
        T* bigger = new T[newCap];
        for (int i = 0; i <= topIdx; i++) bigger[i] = data[i];
        delete[] data;
        data = bigger;
        capacity = newCap;
    }
public:
    Stack(int cap = 16) : topIdx(-1), capacity(cap) { data = new T[capacity]; }
    ~Stack() { delete[] data; }
    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;

    void push(const T& v) {
        if (topIdx + 1 == capacity) grow();
        data[++topIdx] = v;
    }
    T pop() {
        if (isEmpty()) throw runtime_error("Stack underflow (invalid expression)");
        return data[topIdx--];
    }
    T& top() {
        if (isEmpty()) throw runtime_error("Stack is empty");
        return data[topIdx];
    }
    bool isEmpty() const { return topIdx == -1; }
};

// ---------- Helpers ----------
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

int precedence(char op) {
    switch (op) {
        case '^': return 3;
        case '*':
        case '/': return 2;
        case '+':
        case '-': return 1;
    }
    return 0;
}

string reverseString(const string& s) {
    string r = s;
    int i = 0, j = (int)r.size() - 1;
    while (i < j) { char t = r[i]; r[i] = r[j]; r[j] = t; i++; j--; }
    return r;
}

// Shunting-yard algorithm. reversedMode = true when building a prefix
// expression (input was reversed), because the associativity rule flips.
string convertToPostfix(const string& expr, bool reversedMode) {
    Stack<char> st;
    string out;
    for (char c : expr) {
        if (c == ' ') continue;
        if (isalnum((unsigned char)c)) {
            out += c;                                  // operand -> output
        } else if (c == '(') {
            st.push(c);
        } else if (c == ')') {
            while (!st.isEmpty() && st.top() != '(') out += st.pop();
            if (st.isEmpty()) throw runtime_error("Mismatched parentheses");
            st.pop();                                  // discard '('
        } else if (isOperator(c)) {
            while (!st.isEmpty() && st.top() != '(') {
                int pt = precedence(st.top()), pc = precedence(c);
                bool popIt = (pt > pc) ||
                             (pt == pc && (reversedMode ? c == '^' : c != '^'));
                if (!popIt) break;
                out += st.pop();
            }
            st.push(c);
        } else {
            throw runtime_error(string("Invalid character: ") + c);
        }
    }
    while (!st.isEmpty()) {
        char t = st.pop();
        if (t == '(') throw runtime_error("Mismatched parentheses");
        out += t;
    }
    return out;
}

double applyOp(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) throw runtime_error("Division by zero");
            return a / b;
        case '^': return pow(a, b);
    }
    throw runtime_error("Unknown operator");
}

// ================= THE 5 REQUIRED FUNCTIONS =================

// 1) Infix -> Postfix
string infix_to_postfix(string expr) {
    return convertToPostfix(expr, false);
}

// 2) Infix -> Prefix
string infix_to_prefix(string expr) {
    // reverse, swap brackets, convert, reverse the result
    string rev = reverseString(expr);
    for (char& c : rev) {
        if (c == '(') c = ')';
        else if (c == ')') c = '(';
    }
    return reverseString(convertToPostfix(rev, true));
}

// 3) Postfix -> Infix
string postfix_to_infix(string expr) {
    Stack<string> st;
    for (char c : expr) {
        if (c == ' ') continue;
        if (isalnum((unsigned char)c)) {
            st.push(string(1, c));
        } else if (isOperator(c)) {
            string b = st.pop();
            string a = st.pop();
            st.push("(" + a + c + b + ")");
        } else {
            throw runtime_error(string("Invalid character: ") + c);
        }
    }
    string result = st.pop();
    if (!st.isEmpty()) throw runtime_error("Invalid postfix expression");
    return result;
}

// 4) Evaluate postfix (numbers separated by spaces, e.g. "2 3 * 5 4 * +")
double evaluate_postfix(string expr) {
    Stack<double> st;
    int i = 0, n = (int)expr.size();
    while (i < n) {
        while (i < n && expr[i] == ' ') i++;
        if (i >= n) break;
        int start = i;
        while (i < n && expr[i] != ' ') i++;
        string tok = expr.substr(start, i - start);

        if (tok.size() == 1 && isOperator(tok[0])) {
            double b = st.pop();
            double a = st.pop();
            st.push(applyOp(a, b, tok[0]));
        } else {
            st.push(stod(tok));
        }
    }
    double result = st.pop();
    if (!st.isEmpty()) throw runtime_error("Invalid postfix expression");
    return result;
}

// 5) Evaluate prefix (numbers separated by spaces, e.g. "+ * 2 3 * 5 4")
//    Scans from RIGHT to LEFT.
double evaluate_prefix(string expr) {
    Stack<double> st;
    int i = (int)expr.size() - 1;
    while (i >= 0) {
        while (i >= 0 && expr[i] == ' ') i--;
        if (i < 0) break;
        int end = i;
        while (i >= 0 && expr[i] != ' ') i--;
        string tok = expr.substr(i + 1, end - i);

        if (tok.size() == 1 && isOperator(tok[0])) {
            double a = st.pop();      // first popped = LEFT operand
            double b = st.pop();
            st.push(applyOp(a, b, tok[0]));
        } else {
            st.push(stod(tok));
        }
    }
    double result = st.pop();
    if (!st.isEmpty()) throw runtime_error("Invalid prefix expression");
    return result;
}

// ---------- Menu: asks the user for input ----------
int main() {
    int choice;
    do {
        cout << "\n===== Expression Conversion & Evaluation =====\n"
             << "1. Infix   -> Postfix\n"
             << "2. Infix   -> Prefix\n"
             << "3. Postfix -> Infix\n"
             << "4. Evaluate Postfix\n"
             << "5. Evaluate Prefix\n"
             << "0. Exit\n"
             << "Choice: ";
        if (!(cin >> choice)) break;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');   // clear leftover newline

        if (choice == 0) break;
        if (choice < 1 || choice > 5) {
            cout << "Invalid choice.\n";
            continue;
        }

        string expr;
        switch (choice) {
            case 1:
            case 2: cout << "Enter infix expression (e.g. (A+B)*C): "; break;
            case 3: cout << "Enter postfix expression (e.g. AB+C*): "; break;
            case 4: cout << "Enter postfix expression with spaces (e.g. 2 3 * 5 4 * +): "; break;
            case 5: cout << "Enter prefix expression with spaces (e.g. + * 2 3 * 5 4): "; break;
        }
        getline(cin, expr);

        try {
            switch (choice) {
                case 1: { string r = infix_to_postfix(expr); cout << "Postfix: " << r << "\n"; break; }
                case 2: { string r = infix_to_prefix(expr);  cout << "Prefix : " << r << "\n"; break; }
                case 3: { string r = postfix_to_infix(expr); cout << "Infix  : " << r << "\n"; break; }
                case 4: { double r = evaluate_postfix(expr); cout << "Result : " << r << "\n"; break; }
                case 5: { double r = evaluate_prefix(expr);  cout << "Result : " << r << "\n"; break; }
            }
            
        } catch (const exception& ex) {
            cout << "Error: " << ex.what() << "\n";
        }
    } while (true);

    cout << "Goodbye!\n";
    return 0;
}