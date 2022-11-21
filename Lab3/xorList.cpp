#include <iostream>
#include <cstdint>
#include <vector>
using namespace std;

struct Node
{
    int data;
    Node* npx;
};

Node* XOR(Node* x, Node* y) {
    return (Node*)((uintptr_t)(x) ^ (uintptr_t)(y));
}

void traverse(Node* head)
{
    Node* curr = head;
    Node* prev = nullptr;
    Node* next;

    while (curr != nullptr)
    {
        cout << curr->data << " —> ";
 
        next = XOR(prev, curr->npx);
        prev = curr;
        curr = next;
    }
    cout << "NULL";
}

void insert(Node* &headRef, int data)
{
    Node* newNode = new Node();
    newNode->data = data;
    newNode->npx = XOR(headRef, nullptr);
 
    if (headRef)
    {
        headRef->npx = XOR(newNode, XOR(headRef->npx, nullptr));
    }
    headRef = newNode;
}
//deletion from end
void deletion(Node* &headRef)
{
    if (headRef==nullptr)
        cout << "List is empty";
    else
    {
        struct Node* curr = headRef;
        struct Node* prev = NULL;
        struct Node* next;
       
        while (XOR(curr->npx, prev) != NULL)
        {
            next = XOR(prev, curr->npx);
            prev = curr;
            curr = next;
        }
        if (prev != NULL) {
            prev->npx = XOR(XOR(prev->npx, curr), NULL);
        }
        else 
            headRef=nullptr;
        delete(curr);
    }
}
int main()
{
    Node* head = nullptr;
    int choice, val;
    while (choice!=4)
    {
        cout << "\nChoose an operaton:\n"
            "1.Insert\n"
            "2.Display list\n"
            "3.Delete\n"
            "4.Exit\n";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Enter value to enter:";
            cin >> val;
            insert(head, val);
            break;
        case 2:
            traverse(head);
            break;
        case 3:
            deletion(head);
            break;
        default:
            cout << "Choose correct operation!\n";
            break;
        }
    }
    return 0;
}
