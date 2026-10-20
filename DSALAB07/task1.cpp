#include <iostream>
#include <stack>
#include <string>
using namespace std;

// Node of a binary tree (char data for the string tree)
struct Node {
    char data;
    Node *left, *right;
    Node(char d) : data(d), left(NULL), right(NULL) {}
};

// ---------- 1. Build tree from string ----------
// Format: a(b(d,e),c(,f(g,)))  -> node(left,right), empty child allowed
Node* build(const string& s, int& i) {
    if (i >= s.length() || s[i] == ',' || s[i] == ')')
        return NULL;                      // empty child

    Node* root = new Node(s[i++]);        // read node letter

    if (i < s.length() && s[i] == '(') {
        i++;                              // skip '('
        root->left = build(s, i);         // left child
        i++;                              // skip ','
        root->right = build(s, i);        // right child
        i++;                              // skip ')'
    }
    return root;
}

// ---------- 2. Preorder (recursive) in string format ----------
void preorder(Node* root) {
    if (root == NULL) return;
    cout << root->data;
    if (root->left || root->right) {      // leaf has no brackets
        cout << "(";
        preorder(root->left);
        cout << ",";
        preorder(root->right);
        cout << ")";
    }
}

// ---------- 3. Inorder (iterative, using stack) ----------
void inorderIter(Node* root) {
    stack<Node*> st;
    Node* cur = root;
    while (cur != NULL || !st.empty()) {
        while (cur != NULL) {             // go as left as possible
            st.push(cur);
            cur = cur->left;
        }
        cur = st.top();
        st.pop();
        cout << cur->data << " ";         // visit
        cur = cur->right;                 // then go right
    }
}

// ---------- 4. Postorder (iterative, two stacks) ----------
void postorderIter(Node* root) {
    if (root == NULL) return;
    stack<Node*> s1, s2;
    s1.push(root);
    while (!s1.empty()) {
        Node* n = s1.top();
        s1.pop();
        s2.push(n);                       // s2 gets root-right-left order
        if (n->left)  s1.push(n->left);
        if (n->right) s1.push(n->right);
    }
    while (!s2.empty()) {                 // popping s2 gives left-right-root
        cout << s2.top()->data << " ";
        s2.pop();
    }
}

// ---------- 5. Validate string without building the tree ----------
bool validNode(const string& s, int& i, bool required) {
    // node can be empty (only for children)
    if (i >= s.length() || !isalpha(s[i]))
        return !required;
    i++;                                  // read node letter

    if (i < s.length() && s[i] == '(') {
        i++;
        if (!validNode(s, i, false)) return false;   // left
        if (i >= s.length() || s[i] != ',') return false;
        i++;
        if (!validNode(s, i, false)) return false;   // right
        if (i >= s.length() || s[i] != ')') return false;
        i++;
    }
    return true;
}

bool isValid(const string& s) {
    int i = 0;
    if (!validNode(s, i, true)) return false;
    return i == s.length();               // nothing should be left over
}

// ---------- 6. Height and depth ----------
int height(Node* root) {
    if (root == NULL) return -1;          // height counted in edges
    int l = height(root->left);
    int r = height(root->right);
    return 1 + (l > r ? l : r);
}

void printDepths(Node* root, int depth) {
    if (root == NULL) return;
    cout << "Depth of " << root->data << " = " << depth << endl;
    printDepths(root->left, depth + 1);
    printDepths(root->right, depth + 1);
}

// ---------- 7. BST from integers ----------
struct BNode {
    int data;
    BNode *left, *right;
    BNode(int d) : data(d), left(NULL), right(NULL) {}
};

BNode* insertBST(BNode* root, int val) {
    if (root == NULL) return new BNode(val);
    if (val < root->data) root->left = insertBST(root->left, val);
    else                  root->right = insertBST(root->right, val);
    return root;
}

void inorderBST(BNode* root) {
    if (root == NULL) return;
    inorderBST(root->left);
    cout << root->data << " ";
    inorderBST(root->right);
}

int main() {
    string s;
    Node* root = NULL;
    BNode* bst = NULL;
    int choice;

    do {
        cout << "\n===== Task 1 Menu =====\n"
             << "1. Enter tree string & validate\n"
             << "2. Build tree from string\n"
             << "3. Preorder (recursive)\n"
             << "4. Inorder (iterative)\n"
             << "5. Postorder (iterative)\n"
             << "6. Height and depth\n"
             << "7. Build BST from integers\n"
             << "0. Exit\nChoice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter tree string (no spaces): ";
            cin >> s;
            if (isValid(s)) cout << "Valid tree string." << endl;
            else            cout << "Invalid tree string." << endl;
            break;
        case 2:
            if (s == "" || !isValid(s)) {
                cout << "Enter a valid string first (option 1)." << endl;
                break;
            }
            {
                int i = 0;
                root = build(s, i);
                cout << "Tree built successfully." << endl;
            }
            break;
        case 3:
            if (root == NULL) { cout << "Build the tree first." << endl; break; }
            cout << "Preorder: ";
            preorder(root);
            cout << endl;
            break;
        case 4:
            if (root == NULL) { cout << "Build the tree first." << endl; break; }
            cout << "Inorder: ";
            inorderIter(root);
            cout << endl;
            break;
        case 5:
            if (root == NULL) { cout << "Build the tree first." << endl; break; }
            cout << "Postorder: ";
            postorderIter(root);
            cout << endl;
            break;
        case 6:
            if (root == NULL) { cout << "Build the tree first." << endl; break; }
            cout << "Height of tree = " << height(root) << endl;
            printDepths(root, 0);
            break;
        case 7: {
            int n, val;
            bst = NULL;
            cout << "How many integers? ";
            cin >> n;
            cout << "Enter " << n << " integers: ";
            for (int k = 0; k < n; k++) {
                cin >> val;
                bst = insertBST(bst, val);   // first value becomes root
            }
            cout << "BST inorder: ";
            inorderBST(bst);
            cout << endl;
            break;
        }
        }
    } while (choice != 0);

    return 0;
}
