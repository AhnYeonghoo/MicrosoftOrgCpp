#include <iostream>

struct Node
{
    Node *next;
    Node *last;
    int data;
};

Node *Init(Node *tmp)
{
    tmp = new Node();
    tmp->next = NULL;
    tmp->last = NULL;
    tmp->data = 0;
    return tmp;
}

Node *Insert(Node *head, int data)
{
    if (head == NULL)
    {
        head = Init(head);
        head->data = data;
        head->last = head;
        return head;
    }
}