#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    int key;
    Node **forward;
    Node(int, int);
};

Node::Node(int key, int level)
{
    this->key = key;
    forward = new Node *[level + 1];
    memset(forward, 0, sizeof(Node *) * (level + 1));
}

class SkipList
{
public:
    int MAXLVL;
    float p;
    int level;
    Node *header;
    SkipList(int maxlvl, float p);
    int randomlevel();
    Node *createNode(int, int);
    void insertElement(int);
    void searchElement(int);
    void deleteElement(int);
    void displayList();
};

SkipList::SkipList(int maxlvl, float pp)
{
    this->MAXLVL = maxlvl;
    this->p = pp;
    level = 0;
    header = new Node(-1, MAXLVL);
};

Node *SkipList::createNode(int key, int level)
{
    Node *n = new Node(key, level);
    return n;
};

int SkipList::randomlevel()
{
    float r = (float)rand() / RAND_MAX;
    int lvl = 0;
    while (r < p && lvl < MAXLVL)
    {
        lvl++;
        r = (float)rand() / RAND_MAX;
    }
    return lvl;
};

void SkipList::insertElement(int key)
{
    Node *current = header;
    Node *update[MAXLVL + 1];
    memset(update, 0, sizeof(Node *) * (MAXLVL + 1));

    for (int i = level; i >= 0; i--)
    {
        while (current->forward[i] != NULL && current->forward[i]->key < key)
            current = current->forward[i];
        update[i] = current;
    }
    current = current->forward[0];
    if (current == NULL || current->key != key)
    {
        int rlevel = randomlevel();
        if (rlevel > level)
        {
            for (int i = level + 1; i < rlevel + 1; i++)
                update[i] = header;
            level = rlevel;
        }

        Node *n = createNode(key, rlevel);

        for (int i = 0; i <= rlevel; i++)
        {
            n->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = n;
        }
        cout << "Successfully Inserted key: " << key << "\n";
    }
};

void SkipList::searchElement(int key)
{
    Node *current = header;
    
    for (int i = level; i >= 0; i--)
    {
        while (current->forward[i]->key < key && current->forward[i])
            current = current->forward[i];
    }
    current = current->forward[0];
    if (current and current->key == key)
    {
        cout << ("Element found") << endl;
        return;
    }
    cout << "Element not found" << endl;
}

void SkipList::deleteElement(int key)
{
    Node *current = header;
    Node *update[MAXLVL + 1];
    memset(update, 0, sizeof(Node *) * (MAXLVL + 1));
    for (int i = level; i >= 0; i--)
    {
        while (current->forward[i] != NULL && current->forward[i]->key < key)
        {
            current = current->forward[i];
        }
        update[i] = current;
    }
    current = current->forward[0];
        if (current!= NULL || current->key == key){
            for (int i = 0; i <= level; i++)
            {
                if (update[i]->forward[i] != current)
                    break;
                update[i]->forward[i] = current->forward[i];
            }
            while (level > 0 && header->forward[level] == 0)
                level--;
            cout << "Successfully deleted key: " << key << "\n";
        }
};
        

void SkipList::displayList()
{
    cout << "\n***Skip List***\n";
    for (int i = 0; i <= level; i++)
    {
        Node *node = header->forward[i];
        cout << "Level" << i << ": ";
        while (node != NULL)
        {
            cout << node->key << " ";
            node = node->forward[i];
        }
        cout << "\n";
    }
};

int main()
{
    srand((unsigned)time(0));

    SkipList lst(3, 0.5);

    int choice, val;
    while (choice != 5)
    {
        cout << "\nChoose an operaton:\n"
                "1.Insert\n"
                "2.Display list\n"
                "3.Delete\n"
                "4.Search\n"
                "5.Exit\n";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Enter value to enter:";
            cin >> val;
            lst.insertElement(val);
            break;
        case 2:
            lst.displayList();
            break;
        case 3:
            cout << "Enter value to delete:";
            cin >> val;
            lst.deleteElement(val);
            break;
        case 4:
            cout << "Enter value to search:";
            cin >> val;
            lst.searchElement(val);
            break;
        case 5:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Choose correct operation!\n";
            break;
        }
    }
    return 0;
}
