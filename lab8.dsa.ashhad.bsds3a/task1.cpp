#include <iostream>
#include <string>
#include <stack>
using namespace std;

// Node of the binary tree
struct Node
{
char data;
Node* left;
Node* right;

// Constructor initializes a new node
Node(char value)
{
data = value;
left = NULL;
right = NULL;
}
};

// TASK 1: Build the binary tree from the given string
// Time Complexity: O(n)
// Space Complexity: O(n) for the tree and recursion stack
Node* buildTree(string s, int& i)
{
// If there is no character to read, return NULL
if (i >= s.length() || s[i] == ',' || s[i] == ')')
return NULL;

// Create a node using the current character
Node* root = new Node(s[i]);
i++;

// children check krne k liye :D
if (i < s.length() && s[i] == '(')
{
i++; // Skip opening bracket

// Build the left child agar exist krta ha
if (i < s.length() && s[i] != ',')
root->left = buildTree(s, i);

// Skip the comma between children like we skip ungraded activities
if (i < s.length() && s[i] == ',')
i++;

// Build the right child if it exists
if (i < s.length() && s[i] != ')')
root->right = buildTree(s, i);

// Skip closing bracket
if (i < s.length() && s[i] == ')')
i++;
}

return root;
}

// TASK 2: Recursive preorder traversal
// Order: Root, Left, Right
// Time Complexity: O(n)
// Space Complexity: O(h), where h is tree height
void preorder(Node* root)
{
if (root == NULL)
return;
cout << root->data << " ";
preorder(root->left);
preorder(root->right);
}
// TASK 3: Iterative inorder traversal using a stack
// Order: Left, Root, Right
// Time Complexity: O(n)
// Space Complexity: O(h)
void inorder(Node* root)
{
stack<Node*> st;
Node* current = root;

// Continue until sab nodes visit hoty
while (current != NULL || !st.empty())
{
// Move to the leftmost node
while (current != NULL)
{
st.push(current);
current = current->left;
}
// Visit the node at the top of the stack
current = st.top();
st.pop();
cout << current->data << " ";
// Now visit its right subtree
current = current->right;
}
}

// TASK 4: Iterative postorder traversal using a stack
// Order: Left, Right, Root
// Time Complexity: O(n)
// Space Complexity: O(h)
void postorder(Node* root)
{
if (root == NULL)
return;
stack<Node*> st;
Node* current = root;
Node* lastVisited = NULL;
while (current != NULL || !st.empty())
{
if (current != NULL)
{
// left pe moving
st.push(current);
current = current->left;
}
else
{
Node* topNode = st.top();

// Visit the right subtree agar it is not visited
if (topNode->right != NULL &&
lastVisited != topNode->right)
{
current = topNode->right;
}
else
{
// Both subtrees are visited, so print the node
cout << topNode->data << " ";
lastVisited = topNode;
st.pop();
}
}
}
}

// TASK 5: Validate the string without building a tree
// Time Complexity: O(n)
// Space Complexity: O(n) in the worst case due to recursion
bool validate(string s, int& i)
{
// A node must have a character
if (i >= s.length() || s[i] == ',' || s[i] == ')'
|| s[i] == '(')
return false;
// Read the node character
i++;
// A leaf node is also valid
if (i >= s.length() || s[i] != '(')
return true;
i++; // Skip opening bracket buahahahhahaa
// Check the left child kiun k it may be empty
if (i < s.length() && s[i] != ',')
{
if (!validate(s, i))
return false;
}
// A comma must separate the left and right children
if (i >= s.length() || s[i] != ',')
return false;
i++; // Skip comma
// Check the right child cuz again it may be empty
if (i < s.length() && s[i] != ')')
{
if (!validate(s, i))
return false;
}
// Every opening bracket must have a closing bracket
if (i >= s.length() || s[i] != ')')
return false;
i++; // Skip closing bracket
return true;
}
// TASK 6: Calculate the height of the tree
// Time Complexity: O(n)
// Space Complexity: O(h)
int height(Node* root)
{
if (root == NULL)
return 0;
int leftHeight = height(root->left);
int rightHeight = height(root->right);
// Add one for the current node
if (leftHeight > rightHeight)
return leftHeight + 1;
else
return rightHeight + 1;
}
// TASK 6: Display the depth of every node
// Time Complexity: O(n)
// Space Complexity: O(h)
void showDepth(Node* root, int depth)
{
if (root == NULL)
return;
cout << "Node " << root->data
<< " has depth " << depth << endl;
// Each child has depth one more than its parent like obv
showDepth(root->left, depth + 1);
showDepth(root->right, depth + 1);
}
// Insert a value into a Binary Search Tree
// Time Complexity: O(h) per insertion
// Space Complexity: O(h) due to recursion
Node* insertBST(Node* root, int value)
{
if (root == NULL)
return new Node(char(value));

if (value < root->data)
root->left = insertBST(root->left, value);
else if (value > root->data)
root->right = insertBST(root->right, value);
return root;
}
// TASK 7: Display the inorder traversal of the BST
// Time Complexity: O(n)
// Space Complexity: O(h)
void displayBST(Node* root)
{
if (root == NULL)
return;
displayBST(root->left);
cout << int(root->data) << " ";
displayBST(root->right);
}
int main()
{
// Given binary tree string
string treeString = "a(b(d,e),c(,f(g,)))";
// Build the binary tree
int index = 0;
Node* root = buildTree(treeString, index);
cout << "Original String: " << treeString << endl;
// Preorder traversal
cout << "\nPreorder: ";
preorder(root);
// Inorder traversal using a stack
cout << "\nInorder: ";
inorder(root);
// Postorder traversal using a stack
cout << "\nPostorder: ";
postorder(root);
// Validate the string without building another tree
int checkIndex = 0;
bool isValid = validate(treeString, checkIndex)
&& checkIndex == treeString.length();
cout << "\n\nTree String Valid: ";
if (isValid)
cout << "Yes";
else
cout << "No";
// Height of the tree
cout << "\nHeight of Tree: " << height(root);
// Depth of each node
cout << "\n\nDepth of Each Node:\n";
showDepth(root, 0);
// Generate a BST from the given integer sequence
int values[] = {50, 30, 70, 20, 40, 60, 80};
int size = sizeof(values) / sizeof(values[0]);
Node* bstRoot = NULL;
for (int i = 0; i < size; i++)
{
bstRoot = insertBST(bstRoot, values[i]);
}
cout << "\nBST Inorder Traversal: ";
displayBST(bstRoot);
cout << endl;
return 0; }
