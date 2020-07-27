#ifndef _NODE_H
#define _NODE_H
template <typename T> class Node
{
public:
	T key;
	Node<T>* next, *prev;
public:
	Node()
	{
		next = 0;
		prev = 0;
	}
	Node(T key, Node* next, Node* prev)
	{
		this->key = key;
		this->next = next;
		this->prev = prev;
	}
	~Node()
	{
	}
};
#endif