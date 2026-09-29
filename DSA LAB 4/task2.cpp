#include <iostream>
using namespace std;
struct Node
{
    int id;
    Node *next;
};
int main()
{
    int n, k;
    cout << "Enter people: ";
    cin >> n;
    cout << "Enter step: ";
    cin >> k;
    Node *head = new Node{1, NULL};
    Node *last = head;
    for (int i = 2; i <= n; i++)
    {
        Node *newNode = new Node{i, NULL};
        last->next = newNode;
        last = newNode;
    }
    last->next = head;
    Node *current = head;
    Node *previous = last;
    cout << "Eliminated: ";
    while (current->next != current)
    {
        for (int i = 1; i < k; i++)
        {
            previous = current;
            current = current->next;
        }
        cout << current->id << " ";
        previous->next = current->next;
        delete current;
        current = previous->next;
    }
    cout << "\nSurvivor: " << current->id << endl;
    delete current;
    return 0;
}