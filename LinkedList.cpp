#include <iostream>

struct Node
{
	Node* next;
	Node* last;
	int data;
};

Node* init(Node* temp)
{
	temp = new Node();
	temp->next = NULL;
	temp->last = NULL;
	temp->data = 0;
	return temp;
}

Node* insert(Node* head, int data)
{
	if (head == NULL)
	{
		head = init(head);
		head->data = data;
		head->last = head;
		return head;
	}

	Node* cur_node = head->last;
	Node* new_node = NULL;
	new_node = init(new_node);
	cur_node->next = new_node;
	new_node->data = data;
	head->last = new_node;
	return head;
}

int getData(Node* head, int index)
{
	Node* cur_node = head;
	for (int i = 0; i < index && cur_node != NULL; i++)
	{
		cur_node = cur_node->next;
	}
	if (cur_node == NULL)
		return -1;
	return cur_node->data;
}

int count(Node* head, int data)
{
	int _cnt = 0;
	Node* cur_node = head;
	while (cur_node->next != NULL)
	{
		if (cur_node->data == data)
		{
			_cnt += 1;
		}
		cur_node = cur_node->next;
	}
	return _cnt;
}

Node* remove(Node* head, int index)
{
	Node* cur_node = head;
	Node* pre_node = NULL;
	for (int i = 0; i < index && cur_node != NULL; i++)
	{
		pre_node = cur_node;
		cur_node = cur_node->next;
	}
	if (cur_node == NULL)
	{
		return head;
	}
	if (pre_node == NULL)
	{
		head->next->last = head->last;
		head = head->next;
		return head;
	}
	if (cur_node->next == NULL)
	{
		head->last = pre_node;
	}
	pre_node->next = cur_node->next;
	return head;
}