#include<iostream>

using namespace std;

struct node {
    int data;
    node *next;
};

struct cirList{
    node *head;
    node *tail;
};

void init(cirList &l) {
    l.head = l.tail = NULL;
}

node *createNode(int x) {
    node *p = new node;
    p->data = x;
    p->next = NULL;
    return p;
}

void addFirst(cirList &l, int x) {
    node *p = createNode(x);
    if (l.head == NULL) {
        l.head = l.tail = p;
        l.tail->next = l.head;  
    } else {
        p->next = l.head;
        l.head = p;
        l.tail->next = l.head;
    }
}

void addLast(cirList &l, int x) {
    node *p = createNode(x);
    if (l.head == NULL) {
        l.head = l.tail = p;
        l.tail->next = l.head;  
    } else {
        l.tail->next = p;
        l.tail = p;
        l.tail->next = l.head;
    }  
}

void addAfter(cirList &l, int v, int x) {
    node *q = l.head;
    while (q != NULL && q->data != v) {
        q = q->next;
    }

    if (q != NULL) {
        if (q == l.tail) {
            addLast(l, x);
        } else {
            node *p = createNode(x);
            p->next = q->next;
            q->next = p;
        }      
    }
}

void addAt(cirList &l, int index, int x) {
    if (l.head != NULL) {
        if (index == 0) {
            addFirst(l, x);
        } else {
            node *q = l.head;
            int i = 0;
            do {
                q = q->next;
                i++;
            } while (q != l.head && i < index - 1);
            if (q != l.head) {
                if (q == l.tail) {
                    addLast(l, x);
                } else {
                    node *p = createNode(x);
                    p->next = q->next;
                    q->next = p;
                }
            }
        }
    }    
}

void deleteFirst(cirList &l) {
    if (l.head != NULL) {
        node *p = l.head;
        l.head = p->next;
        l.tail->next = l.head;
        p->next = NULL;

        delete(p);
    }
}

void deleteLast(cirList &l) {
    
}

void printList(cirList l) {
    if (l.head != NULL) {
        node *p = l.head;
        do {
            cout << p->data << "\t";
            p = p->next;
        } while ( p != l.head);

        cout << endl;
    }
}

int main() {
    cirList l;
    init(l);

    addLast(l, 5);
    addFirst(l, 30);
    addFirst(l, 20);
    addFirst(l, 10);
    // addLast(l,25);

    cout << "---------------------List---------------------" << endl;
    printList(l);

    // addAfter(l, 30, 11);
    // addAt(l, 1, 3);
    deleteFirst(l);

    cout << "--------------List After Changed--------------" << endl;
    printList(l);

    return 0;
}