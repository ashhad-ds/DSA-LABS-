#include <iostream>
using namespace std;
struct Node
{
    int bit;
    Node *next, *prev;
};
void add(Node *&head, Node *&tail, int bit)
{
    Node *n = new Node{bit, NULL, NULL};

    if (head == NULL)
        head = tail = n;
    else
    {
        tail->next = n;
        n->prev = tail;
        tail = n;
    }
}
void display(Node *head)
{
    while (head != NULL)
    {
        cout << head->bit;
        head = head->next;
    }
    cout << endl;
}
void ones(Node *head)
{
    while (head != NULL)
    {
        head->bit = 1 - head->bit;
        head = head->next;
    }
}
int decimal(Node *head)
{
    int x = 0;

    while (head != NULL)
    {
        x = x * 2 + head->bit;
        head = head->next;
    }
    return x;
}
int main()
{
    Node *head = NULL;
    Node *tail = NULL;
    string b;
    cout << "Enter binary: ";
    cin >> b;
    for (char c : b)
        add(head, tail, c - '0');
    cout << "Binary: ";
    display(head);
    cout << "Decimal: " << decimal(head) << endl;
    ones(head);
    cout << "1's Complement: ";
    display(head);
    return 0;
}