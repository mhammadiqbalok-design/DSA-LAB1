#include <iostream>
#include <string>
#include <cmath>
using namespace std;

struct BitNode {
    int bit;
    BitNode* prev;
    BitNode* next;
    BitNode(int b) : bit(b), prev(nullptr), next(nullptr) {}
};

class BinaryNumber {
public:
    BitNode* head;
    BitNode* tail;

    BinaryNumber() : head(nullptr), tail(nullptr) {}

    void clear() {
        BitNode* curr = head;
        while (curr) {
            BitNode* nextNode = curr->next;
            delete curr;
            curr = nextNode;
        }
        head = tail = nullptr;
    }

    void store(string binString) {
        clear();
        for (char c : binString) {
            if (c == '0' || c == '1') {
                BitNode* newNode = new BitNode(c - '0');
                if (!head) {
                    head = tail = newNode;
                } else {
                    tail->next = newNode;
                    newNode->prev = tail;
                    tail = newNode;
                }
            }
        }
    }

    void display() const {
        BitNode* temp = head;
        while (temp) { cout << temp->bit; temp = temp->next; }
        cout << "\n";
    }

    void onesComplement() {
        BitNode* temp = head;
        while (temp) {
            temp->bit = (temp->bit == 0) ? 1 : 0;
            temp = temp->next;
        }
    }

    void addOne() {
        BitNode* temp = tail;
        int carry = 1;
        while (temp && carry) {
            int sum = temp->bit + carry;
            temp->bit = sum % 2;
            carry = sum / 2;
            temp = temp->prev;
        }
        if (carry) {
            BitNode* newNode = new BitNode(1);
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void twosComplement() {
        onesComplement();
        addOne();
    }

    int toDecimal() const {
        int dec = 0, power = 0;
        BitNode* temp = tail;
        while (temp) {
            dec += temp->bit * pow(2, power++);
            temp = temp->prev;
        }
        return dec;
    }

    static BinaryNumber add(const BinaryNumber& b1, const BinaryNumber& b2) {
        BinaryNumber result;
        BitNode* t1 = b1.tail;
        BitNode* t2 = b2.tail;
        int carry = 0;
        string resStr = "";

        while (t1 || t2 || carry) {
            int sum = carry;
            if (t1) { sum += t1->bit; t1 = t1->prev; }
            if (t2) { sum += t2->bit; t2 = t2->prev; }
            resStr = to_string(sum % 2) + resStr;
            carry = sum / 2;
        }
        result.store(resStr);
        return result;
    }

    static BinaryNumber multiply(const BinaryNumber& b1, const BinaryNumber& b2) {
        BinaryNumber result;
        result.store("0");
        int multiplier = b2.toDecimal();
        
        for (int i = 0; i < multiplier; i++) {
            result = add(result, b1);
        }
        return result;
    }
};

int main() {
    string bin1, bin2;
    cout << "Enter first binary string (e.g., 101): ";
    cin >> bin1;
    cout << "Enter second binary string (e.g., 011): ";
    cin >> bin2;

    BinaryNumber b1, b2;
    b1.store(bin1);
    b2.store(bin2);

    cout << "\n--- Decimal Conversion ---\n";
    cout << "Binary 1 to Decimal: " << b1.toDecimal() << "\n";
    cout << "Binary 2 to Decimal: " << b2.toDecimal() << "\n";

    cout << "\n--- Binary 1 Complements ---\n";
    b1.onesComplement();
    cout << "1's Complement: "; b1.display();
    b1.onesComplement(); // Revert back
    b1.twosComplement();
    cout << "2's Complement: "; b1.display();

    // Re-store original string for arithmetic operations
    b1.store(bin1);

    cout << "\n--- Arithmetic Operations ---\n";
    BinaryNumber sum = BinaryNumber::add(b1, b2);
    cout << "Addition Result: "; sum.display();
    cout << "Addition (Decimal): " << sum.toDecimal() << "\n";

    BinaryNumber product = BinaryNumber::multiply(b1, b2);
    cout << "Multiplication Result: "; product.display();
    cout << "Multiplication (Decimal): " << product.toDecimal() << "\n";

    return 0;
}