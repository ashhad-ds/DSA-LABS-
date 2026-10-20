#include <iostream>
#include <string>
using namespace std;
// Structure for storing nalaik student k records. Not Me <^_^>
struct Student
{
    int studentID;
    string name;
    float GPA;
    Student* left;
    Student* right;
    // Constructor to initialize student information
    Student(int id, string n, float g)
    {
        studentID = id;
        name = n;
        GPA = g;
        left = NULL;
        right = NULL;
    }
};
// TASK 2: Insert a student into the BST
// Time Complexity: O(h)
// Space Complexity: O(h) due to recursion
Student* insert(Student* root, int id, string name, float gpa)
{
    // If the position is empty toh this creates a new student node
    if (root == NULL)
    {
        return new Student(id, name, gpa);
    }
    // this compares IDs to maintain BST order
    if (id < root->studentID)
    {
        root->left = insert(root->left, id, name, gpa);
    }
    else if (id > root->studentID)
    {
        root->right = insert(root->right, id, name, gpa);
    }
    else
    {
        // this makes sure k student IDs must be unique wrna yk kya masla hoga :<
        cout << "Student ID already exists: " << id << endl;
    }
    return root;
}
// this searchs for a student using Student ID
// Time Complexity: O(h)
// Space Complexity: O(h) due to recursion
Student* search(Student* root, int id)
{
    // Student was not found toh NULL return hoga
    if (root == NULL)
        return NULL;
    // Student found toh return that node
    if (root->studentID == id)
        return root;
    // This searchs the left subtree
    if (id < root->studentID)
        return search(root->left, id);
    // this searchs the right subtree
    return search(root->right, id);
}
// ts is to display the details of one student
void displayStudent(Student* student)
{
    if (student == NULL)
    {
        cout << "Student not found." << endl;
        return;
    }
    cout << "Student ID: " << student->studentID << endl;
    cout << "Name: " << student->name << endl;
    cout << "GPA: " << student->GPA << endl;
}
// ts finds the student with the smallest ID in a subtree
// ts is used when deleting a node with two children
Student* findMin(Student* root)
{
    while (root != NULL && root->left != NULL)
    {
        root = root->left;
    }
    return root;
}
// Deletes a student using Student ID
// Time Complexity: O(h)
// Space Complexity: O(h) due to recursion
Student* deleteStudent(Student* root, int id)
{
    if (root == NULL)
        return NULL;
    // Find the student to delete
    if (id < root->studentID)
    {
        root->left = deleteStudent(root->left, id);
    }
    else if (id > root->studentID)
    {
        root->right = deleteStudent(root->right, id);
    }
    else
    {
        // Case 1: Node has no children
        if (root->left == NULL && root->right == NULL)
        {
            delete root;
            return NULL;
        }
        // Case 2: Node has only a right child
        else if (root->left == NULL)
        {
            Student* temp = root->right;
            delete root;
            return temp;
        }
        // Case 2: Node has only a left child
        else if (root->right == NULL)
        {
            Student* temp = root->left;
            delete root;
            return temp;
        }
        // Case 3: Node has two children
        // Replace it with the smallest node in the right subtree
        Student* temp = findMin(root->right);
        root->studentID = temp->studentID;
        root->name = temp->name;
        root->GPA = temp->GPA;
        // Delete the copied successor node
        root->right = deleteStudent(root->right, temp->studentID);
    }

    return root;
}
// ts displays all students sorted by Student ID
// Time Complexity: O(n)
// Space Complexity: O(h) due to recursion
void inorder(Student* root)
{
    if (root == NULL)
        return;
    inorder(root->left);
    cout << "ID: " << root->studentID
         << " | Name: " << root->name
         << " | GPA: " << root->GPA << endl;

    inorder(root->right);
}

// ts counts the total number of students
// Time Complexity: O(n)
// Space Complexity: O(h)
int countStudents(Student* root)
{
    if (root == NULL)
        return 0;
    return 1 + countStudents(root->left)
             + countStudents(root->right);
}
// Find and display the student with the highest GPA
// Time Complexity: O(n)
// Space Complexity: O(h)
void highestGPA(Student* root, Student*& highest)
{
    if (root == NULL)
        return;
    // Update the highest GPA when a better one is found
    if (highest == NULL || root->GPA > highest->GPA)
        highest = root;
    highestGPA(root->left, highest);
    highestGPA(root->right, highest);
}
// ts finds and displays the student with the lowest GPA
// Time Complexity: O(n)
// Space Complexity: O(h)
void lowestGPA(Student* root, Student*& lowest)
{
    if (root == NULL)
        return;

    // Update the lowest GPA when a smaller one is found
    if (lowest == NULL || root->GPA < lowest->GPA)
        lowest = root;

    lowestGPA(root->left, lowest);
    lowestGPA(root->right, lowest);
}
// ts displays students jinka GPA threshold se above ha
// Space Complexity: O(h)
void displayAboveGPA(Student* root, float threshold)
{
    if (root == NULL)
        return;
    // Check the left subtree
    displayAboveGPA(root->left, threshold);
    // ts display only students above the threshold. Nalaik log bahar <^_^>
    if (root->GPA > threshold)
    {
        cout << "ID: " << root->studentID
             << " | Name: " << root->name
             << " | GPA: " << root->GPA << endl;
    }
    // ts checks the right subtree
    displayAboveGPA(root->right, threshold);
}
int main()
{
    Student* root = NULL;
    // inserting data khudse and yeah sabka gpa mere se zyada ha :()
    root = insert(root, 103, "Ali", 3.50);
    root = insert(root, 101, "Ahmed", 3.20);
    root = insert(root, 105, "Sara", 3.90);
    root = insert(root, 102, "Usman", 2.80);
    root = insert(root, 104, "Ayesha", 3.70);
    // Display all students in ascending order of ID
    cout << "===== All Students =====" << endl;
    inorder(root);
    // Search for a student
    cout << "\n===== Search Student =====" << endl;
    int searchID = 103;
    Student* found = search(root, searchID);
    displayStudent(found);
    // Delete a student record
    cout << "\n===== Delete Student =====" << endl;
    int deleteID = 102;

    root = deleteStudent(root, deleteID);
    cout << "Student with ID " << deleteID
         << " deleted (if it existed)." << endl;

    // Display students after deletion
    cout << "\n===== Students After Deletion =====" << endl;
    inorder(root);

    // Count all students
    cout << "\nTotal Students: "
         << countStudents(root) << endl;

    // Find the student with the highest GPA
    Student* highest = NULL;
    highestGPA(root, highest);
    cout << "\n===== Highest GPA =====" << endl;
    displayStudent(highest);
    // Find the student with the lowest GPA
    Student* lowest = NULL;
    lowestGPA(root, lowest);
    cout << "\n===== Lowest GPA =====" << endl;
    displayStudent(lowest);
    // Display students above a user defined GPA threshold
    float threshold;
    cout << "\nEnter GPA threshold: ";
    cin >> threshold;
    cout << "\n===== Students Above GPA "
         << threshold << " =====" << endl;
    displayAboveGPA(root, threshold);
    return 0;
}