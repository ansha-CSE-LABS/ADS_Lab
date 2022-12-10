#include <iostream>
using namespace std;

class Node{
    public:
        int key;
        Node *l;
        Node *r;
        int height;
};

int height(Node *t){
    return t == NULL ? 0:t->height;
}

Node *newnode(int key)
{
    Node* node = new Node();
    node->key =key;
    node->l=NULL;
    node->r=NULL;
    node->height=1;
    return node;
}
Node *rRotate(Node *y){
    Node *x=y->l;
    Node *t2= x->r;

    x->r = y;
    y->l = t2;
    y->height =max(height(y->l),height(y->r))+1;
    x->height = max(height(x->l),height(x->r))+1;
    return x;
}
Node *lRotate(Node *y){
    Node *x=y->r;
    Node *t2= x->l;

    x->l = y;
    y->r = t2;
    y->height =max(height(y->l),height(y->r))+1;
    x->height = max(height(x->l),height(x->r))+1;
    return x;
}
int getBal(Node *N){
    if (N==NULL) return 0;
    return height(N->l)-height(N->r);
}
Node* insert(Node *node, int key){
    if(node==NULL) return (newnode(key));
    if (key<node->key)
        node->l = insert(node->l,key);
    else if(key>node->key)
        node->r =insert(node->r,key);
    else return node;

    int bal = getBal(node);

    if (bal > 1 && key < node->l->key)
        return rRotate(node);

    if (bal < -1 && key > node->r->key)
        return lRotate(node);

    if (bal > 1 && key > node->l->key) {
        node->l = lRotate(node->l);
        return rRotate(node);
    }
    if (bal < -1 && key < node->r->key) {
        node->r = rRotate(node->r);
        return lRotate(node);
    }
    return node;
}
void preOrder(Node *root)
{
    if(root != NULL)
    {
        cout << root->key << " ";
        preOrder(root->l);
        preOrder(root->r);
    }
}
Node* minValueNode(Node* node)
{
    Node* current = node;
      while (current->l != NULL)
        current = current->l;

    return current;
}
Node* deleteNode(Node* root, int key)
{
    if (root == NULL)
        return root;

    if ( key < root->key )
        root->l = deleteNode(root->l, key);

    else if( key > root->key )
        root->r = deleteNode(root->r, key);

    else
    {
        if( (root->l == NULL) || (root->r == NULL) ) {
            Node *temp = root->l ? root->l : root->r;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            }
            else  *root = *temp;
        }
        else{
            Node* temp = minValueNode(root->r);
            root->key = temp->key;
            root->r = deleteNode(root->r, temp->key);
        }
    }

    if (root == NULL)
    return root;

    root->height = 1 + max(height(root->l),
                           height(root->r));

    int bal = getBal(root);

    if (bal > 1 && getBal(root->l) >= 0)
        return rRotate(root);

    if (bal < -1 && getBal(root->r) <= 0)
        return lRotate(root);

    if (bal > 1 && getBal(root->l) < 0) {
        root->l = lRotate(root->l);
        return rRotate(root);
    }
    if (bal < -1 && getBal(root->r) > 0) {
        root->r = rRotate(root->r);
        return lRotate(root);
    }
    return root;
}

int main()
{
    Node* root = NULL;
    int choice, val;
    while (choice!=4)
    {
        cout << "\nChoose an operation:\n"
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
            root = insert(root, val);
            break;
        case 2:
            preOrder(root);
            break;
        case 3:
            cout << "Enter value to delete:";
            cin >> val;
            root = deleteNode(root, val);
            break;
        case 4:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Choose correct operation!\n";
            break;
        }
    }
    return 0;
}
