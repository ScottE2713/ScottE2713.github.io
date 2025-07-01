//============================================================================
// Name        : AdvisingProgram.cpp
// Author      : Scott Enos
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

// Structure to hold information about a course
struct Course {
    string courseNumber; // Unique identifier for the course
    string title; // Title of the course
    vector<string> prerequisites; // List of prerequisites for the course
};

// TreeNode structure for Binary Search Tree
struct TreeNode {
    Course course; // Course data stored in this node
    TreeNode* left; // Pointer to left subtree
    TreeNode* right; // Pointer to right subtree

    // Constructor to initialize a node with a course
    TreeNode(const Course& crs) : course(crs), left(nullptr), right(nullptr) {}
};


class BinarySearchTree {
public:
    TreeNode* root; // Root node of the tree

    // Constructor initializes the tree as empty
    BinarySearchTree() : root(nullptr) {}

    // Insert a course into the binary search tree
    void insert(const Course& course) {
        TreeNode** cur = &root;
        while (*cur) {
            const string& curCourseNumber = (*cur)->course.courseNumber;
            if (course.courseNumber < curCourseNumber) {
                cur = &((*cur)->left);
            } else {
                cur = &((*cur)->right);
            }
        }
        *cur = new TreeNode(course);
    }

    // Find a course by course number
    TreeNode* find(const string& courseNumber) const {
        TreeNode* cur = root;
        while (cur) {
            if (courseNumber == cur->course.courseNumber) {
                return cur;
            } else if (courseNumber < cur->course.courseNumber) {
                cur = cur->left;
            } else {
                cur = cur->right;
            }
        }
        return nullptr;
    }

    // Perform in-order traversal of the tree to collect course numbers
    void inOrderTraversal(TreeNode* node, vector<string>& courseNumbers) const {
        if (!node) return;
        inOrderTraversal(node->left, courseNumbers);
        courseNumbers.push_back(node->course.courseNumber);
        inOrderTraversal(node->right, courseNumbers);
    }
};

// AdvisingProgram class manages the user interface and interaction
class AdvisingProgram {
private:
    BinarySearchTree bst; // Binary search tree to store course information

public:
    void loadCourseData(); // Loads course data from a file into the BST
    void printCourseList() const; // Prints all courses in the BST in alphanumeric order
    void printCourse(const string& courseNumber) const; // Prints details for a specific course
    void displayMenu(); // Displays user interface menu and handles user input
};

// Loads course data from a file into the binary search tree
void AdvisingProgram::loadCourseData() {
    string filename = "src\\ABCU_Advising_Program_Input.txt"; // Relative path to the data file
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: File '" << filename << "' cannot be opened. Please check the file path." << endl;
        return;
    }

    string line, courseNumber, title, prerequisite;
    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        getline(ss, courseNumber, ',');
        getline(ss, title, ',');
        Course course{courseNumber, title};

        while (getline(ss, prerequisite, ',')) {
            course.prerequisites.push_back(prerequisite);
        }

        bst.insert(course); // Insert course into the binary search tree
    }
    file.close();
    cout << "Data loaded successfully." << endl;
}

// Prints all courses in alphanumeric order
void AdvisingProgram::printCourseList() const {
    if (!bst.root) {
        cout << "No course data available. Please load the data first." << endl;
        return;
    }

    vector<string> courseNumbers;
    bst.inOrderTraversal(bst.root, courseNumbers); // Collect all course numbers through in-order traversal
    sort(courseNumbers.begin(), courseNumbers.end());

    for (const string& num : courseNumbers) {
        TreeNode* node = bst.find(num);
        if (node) {
            cout << num << ": " << node->course.title << endl;
        }
    }
}

// Prints detailed information about a specific course
void AdvisingProgram::printCourse(const string& courseNumber) const {
    TreeNode* node = bst.find(courseNumber);
    if (!node) {
        cout << "Course '" << courseNumber << "' not found." << endl;
        return;
    }

    const Course& course = node->course;
    cout << "Course: " << course.title << " (" << course.courseNumber << ")" << endl;
    if (course.prerequisites.empty()) {
        cout << "Prerequisites: None" << endl;
    } else {
        cout << "Prerequisites: ";
        for (const string& prereq : course.prerequisites) {
            cout << prereq << " - ";
            TreeNode* prereqNode = bst.find(prereq);
            if (prereqNode) {
                cout << prereqNode->course.title << ", ";
            } else {
                cout << "Not found in current data, ";
            }
        }
        cout << "\b\b " << endl; // Remove the last comma
    }
}

// Displays the main menu and handles user interactions
void AdvisingProgram::displayMenu() {
    int choice;
    string courseNumber;
    do {
        cout << "\nMenu:\n1) Load Data Structure\n2) Print Course List\n3) Print Course\n4) Exit\nEnter your choice: ";
        while (!(cin >> choice)) {
            cin.clear(); // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard incorrect input
            cout << "Invalid input. Please enter a number: ";
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer

        switch (choice) {
            case 1:
                loadCourseData(); // Option to load data
                break;
            case 2:
                printCourseList(); // Option to print course list
                break;
            case 3:
                cout << "Enter the course number: ";
                getline(cin, courseNumber);
                printCourse(courseNumber); // Option to print specific course information
                break;
            case 4:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please enter a valid option." << endl;
                break;
        }
    } while (choice != 4); // Continue displaying the menu until the user selects 'Exit'
}


int main() {
    AdvisingProgram program; // Create an instance of AdvisingProgram
    program.displayMenu(); // Start the program by displaying the menu
    return 0;
}
