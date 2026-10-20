#include <iostream>
#include <string>
using namespace std;

struct Student {
    int studentID;
    string name;
    float GPA;
    Student* left;
    Student* right;
};

// create a new student node
Student* createNode(int id, string name, float gpa) {
    Student* s = new Student;
    s->studentID = id;
    s->name = name;
    s->GPA = gpa;
    s->left = s->right = NULL;
    return s;
}

void display(Student* s) {
    cout << "ID: " << s->studentID << " | Name: " << s->name
         << " | GPA: " << s->GPA << endl;
}

// Insert (BST ordered by studentID)
Student* Insert(Student* root, int id, string name, float gpa) {
    if (root == NULL) return createNode(id, name, gpa);
    if (id < root->studentID)
        root->left = Insert(root->left, id, name, gpa);
    else if (id > root->studentID)
        root->right = Insert(root->right, id, name, gpa);
    else
        cout << "ID " << id << " already exists!" << endl;   // no duplicates
    return root;
}

// Search by ID
Student* Search(Student* root, int id) {
    if (root == NULL || root->studentID == id) return root;
    if (id < root->studentID) return Search(root->left, id);
    return Search(root->right, id);
}

// smallest ID node in a subtree (used by delete)
Student* findMin(Student* root) {
    while (root->left != NULL) root = root->left;
    return root;
}

// Delete by ID
Student* Delete(Student* root, int id) {
    if (root == NULL) return NULL;           // not found

    if (id < root->studentID)
        root->left = Delete(root->left, id);
    else if (id > root->studentID)
        root->right = Delete(root->right, id);
    else {
        // case 1 & 2: zero or one child
        if (root->left == NULL) {
            Student* temp = root->right;
            delete root;
            return temp;
        }
        if (root->right == NULL) {
            Student* temp = root->left;
            delete root;
            return temp;
        }
        // case 3: two children -> copy inorder successor, then delete it
        Student* succ = findMin(root->right);
        root->studentID = succ->studentID;
        root->name = succ->name;
        root->GPA = succ->GPA;
        root->right = Delete(root->right, succ->studentID);
    }
    return root;
}

// Inorder traversal (sorted by ID)
void inorder(Student* root) {
    if (root == NULL) return;
    inorder(root->left);
    display(root);
    inorder(root->right);
}

// Count total students
int countStudents(Student* root) {
    if (root == NULL) return 0;
    return 1 + countStudents(root->left) + countStudents(root->right);
}

// Highest GPA (tree is ordered by ID, so whole tree must be checked)
Student* highestGPA(Student* root) {
    if (root == NULL) return NULL;
    Student* best = root;
    Student* l = highestGPA(root->left);
    Student* r = highestGPA(root->right);
    if (l != NULL && l->GPA > best->GPA) best = l;
    if (r != NULL && r->GPA > best->GPA) best = r;
    return best;
}

// Lowest GPA
Student* lowestGPA(Student* root) {
    if (root == NULL) return NULL;
    Student* low = root;
    Student* l = lowestGPA(root->left);
    Student* r = lowestGPA(root->right);
    if (l != NULL && l->GPA < low->GPA) low = l;
    if (r != NULL && r->GPA < low->GPA) low = r;
    return low;
}

// Students with GPA above threshold
void aboveThreshold(Student* root, float t) {
    if (root == NULL) return;
    aboveThreshold(root->left, t);
    if (root->GPA > t) display(root);
    aboveThreshold(root->right, t);
}

int main() {
    Student* root = NULL;
    int choice, id;
    string name;
    float gpa;

    do {
        cout << "\n--- Student Record System ---\n"
             << "1. Insert student\n2. Search student\n3. Delete student\n"
             << "4. Display all (sorted by ID)\n5. Count students\n"
             << "6. Highest & lowest GPA\n7. GPA above threshold\n0. Exit\n"
             << "Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter ID, name, GPA: ";
            cin >> id >> name >> gpa;
            root = Insert(root, id, name, gpa);
            break;
        case 2: {
            cout << "Enter ID to search: ";
            cin >> id;
            Student* f = Search(root, id);
            if (f) display(f);
            else cout << "Student not found." << endl;
            break;
        }
        case 3:
            cout << "Enter ID to delete: ";
            cin >> id;
            if (Search(root, id)) {
                root = Delete(root, id);
                cout << "Deleted." << endl;
            } else cout << "Student not found." << endl;
            break;
        case 4:
            if (root == NULL) cout << "No records." << endl;
            else inorder(root);
            break;
        case 5:
            cout << "Total students: " << countStudents(root) << endl;
            break;
        case 6:
            if (root == NULL) cout << "No records." << endl;
            else {
                cout << "Highest GPA: "; display(highestGPA(root));
                cout << "Lowest GPA:  "; display(lowestGPA(root));
            }
            break;
        case 7:
            cout << "Enter GPA threshold: ";
            cin >> gpa;
            aboveThreshold(root, gpa);
            break;
        }
    } while (choice != 0);

    return 0;
}
