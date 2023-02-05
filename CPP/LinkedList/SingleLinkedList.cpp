#include<iostream>

using namespace std;

struct node {
    int data;
    node* next;
};

void init(node *&head) {
    head = NULL;
}

node *createNode(int x) {
    node *p = new node;
    p->data = x;
    p->next = NULL;
    return p;  
}

void addFirst(node *&head, int x) {
    node *p = createNode(x);
    p->next = head;
    head = p; 
}

void addLast(node *&head, int x) {
    node *p = createNode(x);
    if (head == NULL) {
        head = p; 
    } else {
        node *last = head;
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = p;
    }
}

void addAfter(node *&head, int v, int x) {
    node *p = createNode(x);

    node *q = head;
    while (q != NULL && q->data != v) {             
        q = q->next;
    }

    if (q != NULL) {
        p->next = q->next;
        q->next = p;
    }
}

void addAt(node *&head, int index, int x) {
    node *p = createNode(x);
    if (index == 0) {
        p->next = head;
        head = p;
    } else {
        node *q = head;
        for (int i = 0; i < index - 1; i++){
        q = q ->next;
        }
        if (q != NULL) {
            p->next = q->next;
            q->next = p;
        }
    }
}

void deleteFirst(node *&head) {
    if (head != NULL) {
        node *p = head;
        head = p->next;
        p->next = NULL;
        delete(p);
    }
}

void deleteLast(node *&head) {
    if (head != NULL) {
        node *last = head;
        node *prev = NULL;
        while (last->next != NULL) {
            prev = last;
            last = last->next;
        }

        if (prev == NULL) {
           deleteFirst(head);     
        } else{
            prev->next = NULL;
            delete(last);
        }
    }
}

void deleteNode(node *&head, int v) {
    if (head != NULL){
        node *q = head;
        node *prev = NULL;
        while (q != NULL && q->data != v) { 
            prev = q;            
            q = q->next;
        }

        if(q != NULL) {
            if (prev == NULL) {
                deleteFirst(head);
            } else {
                prev->next = q->next;
                q->next = NULL;

                delete(q);
            }       
        } 
    }
}

void deleteAt(node *&head, int index) {
    if (head != NULL) {
        if (index == 0) {
            deleteFirst(head);
        } else {
        node *p = head;
        for (int i = 0; i < index - 1; i++){
            p = p ->next;
        }
        node *q = p->next;
        p->next = p->next->next;
        q->next = NULL;
        delete(q);
        }
    }
}

void clean(node *&head) {
    while (head != NULL) {
        deleteFirst(head);
    }
}

void printList(node *head) {
	node *p = head;
	while (p != NULL) {
		cout << p->data << "\t";
		p = p->next;
	}
}

int main() {
    node *head;

    init(head);

    addLast(head, 11);
    addFirst(head, 10);
    addFirst(head, 15);
    // addFirst(head, 20);
    // addLast(head, 21);
    // addLast(head, 31);

    cout << "--------------------List---------------------" << endl;
    printList(head);
    cout << endl;

    // addAfter(head, 20, 200);
    // addAt(head, 0, 32);
    // deleteNode(head, 11);
    clean(head);
    // deleteAt(head, 0);

    cout << "-------------List after changed--------------" << endl;
    printList(head);
    return 0;
}