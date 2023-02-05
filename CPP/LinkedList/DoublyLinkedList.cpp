#include<iostream>

using namespace std;

struct node {
    int data;
    node *next;
    node *prev;
};

struct douList {
    node *head;
    node *tail;
};

void init(douList &l) {
    l.head = NULL;
    l.tail = NULL;
}

node *createNode(int x) {
    node *p = new node;
    p->data = x;
    p->next = NULL;
    p->prev = NULL;
    return p;
}

void addFirst(douList &l, int x) {
    node *p = createNode(x);
    if (l.head == NULL) {
        l.head = l.tail = p;
    } else {
        l.head->prev = p;
        p->next = l.head;
        l.head = p;
    }
}

void addLast(douList &l, int x) {
    node *p = createNode(x);
    if (l.head == NULL) {
        l.head = l.tail = p;
    } else {
        l.tail->next = p;
        p->prev = l.tail;
        l.tail = p;
    }
}

void addAfter(douList &l, int v, int x) {
    node *q = l.head;
    while (q != NULL && q->data != v) {             
        q = q->next;
    }

    if (q != NULL) {
        if (q == l.tail) {
            addLast(l, x);           
        } else {
            node *p = createNode(x);
            q->next->prev = p;
            p->next = q->next;
            q->next = p;
            p->prev =q;
        }
    }
}

void addAt(douList &l, int index, int x)
{
    node *q = l.head;
    for (int i = 0; i < index - 1; i++){
    q = q ->next;
    }
    if (q != NULL) {
        if (q == l.head) {
            addFirst(l, x);
        } else {
            if (q ==l.tail) {
                addLast(l, x);
            } else {
                node *p = createNode(x);
                q->next->prev = p;
                p->next = q->next;
                q->next = p;
                p->prev =q;
            }
        }       
    }
}

void deleteFirst(douList &l) {
    if (l.head != NULL) {
        node *p = l.head;

        if (p->next == NULL) {
            l.head = NULL;
            l.tail = NULL;
        } else {
            l.head = p->next;
            p->next->prev = NULL;
            p->next = NULL;
        }

        delete(p);
    }
}

void deleteLast(douList &l) {
    if (l.head != NULL) {
        node *p = l.tail;

        if (p->prev == NULL) {
            l.head = NULL;
            l.tail = NULL;
        } else {
            l.tail = p->prev;
            p->prev->next = NULL;
            p->prev = NULL;
        }

        delete(p);
    }
}

void deleteNode(douList &l, int v) {
    node *p = l.head;
    while (p != NULL && p->data != v) {             
        p = p->next;
    }

    if (p != NULL) {
        if (p == l.tail) {
            deleteLast(l);                     
        } else {
            if (p == l.head) {
                deleteFirst(l);
            } else {
                p->prev->next = p->next;
                p->next->prev = p->prev;
                p->next = NULL;
                p->prev = NULL;

                delete(p);
            }
        }
    }
}

void deleteAt(douList &l, int index) {
    node *p = l.head;
    for (int i = 0; i < index ; i++){
    p = p ->next;
    }
    if (p != NULL) {
        if (p == l.head) {
            deleteFirst(l); 
        } else {
            if (p ==l.tail) {
            deleteLast(l);                     
            } else {
                p->prev->next = p->next;
                p->next->prev = p->prev;
                p->next = NULL;
                p->prev = NULL;

                delete(p);                        
            }
        }       
    }
}

void clean(douList &l) {
    while (l.head != NULL) {
        deleteFirst(l);
    }
}

void printList(douList l) {
    node *p = l.head;
    while (p != NULL) {
        cout << p->data << "\t";
        p = p->next;
    }
    cout << endl;
}

int main() {
    douList l;

    init(l);
    // addLast(l, 50);
    // addFirst(l, 10);
    // addFirst(l, 20);
    // addFirst(l, 30);
    // addLast(l, 40);

    cout << "--------------------List---------------------" << endl;

    printList(l);
    // addAt(l, 0, 31);
    // addAfter(l, 30, 99);
    // deleteFirst(l);
    // deleteLast(l);
    // deleteNode(l, 30);
    // deleteAt(l, 4);
    clean(l);

    cout << "--------------List After Change--------------" << endl;

    printList(l);

    return 0;
}