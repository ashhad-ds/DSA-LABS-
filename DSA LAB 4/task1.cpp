#include <iostream>
using namespace std;
struct Node
{
    int id;
    string name, duration;
    Node *next, *prev;
};
Node *head = NULL;
void add(int id, string name, string duration)
{
    Node *n = new Node{id, name, duration, NULL, NULL};

    if (head == NULL)
        head = n;
    else
    {
        Node *p = head;
        while (p->next != NULL)
            p = p->next;

        p->next = n;
        n->prev = p;
    }
}
void display()
{
    Node *p = head;
    while (p != NULL)
    {
        cout << p->id << " " << p->name
             << " " << p->duration << endl;
        p = p->next;
    }
}
void search(int id)
{
    Node *p = head;
    while (p != NULL)
    {
        if (p->id == id)
        {
            cout << "Found: " << p->name << endl;
            return;
        }
        p = p->next;
    }
    cout << "Not found\n";
}
void remove(int id)
{
    Node *p = head;
    while (p != NULL && p->id != id)
        p = p->next;
    if (p == NULL)
    {
        cout << "Not found\n";
        return;
    }
    if (p->prev != NULL)
        p->prev->next = p->next;
    else
        head = p->next;
    if (p->next != NULL)
        p->next->prev = p->prev;
    delete p;
}
void reverse()
{
    Node *p = head, *temp = NULL;
    while (p != NULL)
    {
        temp = p->prev;
        p->prev = p->next;
        p->next = temp;
        p = p->prev;
    }
    if (temp != NULL)
        head = temp->prev;
}
int main()
{
    add(1, "Song A", "3:20");
    add(2, "Song B", "4:10");
    add(3, "Song C", "2:50");
    cout << "Playlist:\n";
    display();
    cout << "\nSearch:\n";
    search(2);
    cout << "\nAfter deleting Song 2:\n";
    remove(2);
    display();
    cout << "\nAfter reversing:\n";
    reverse();
    display();
    return 0;
}