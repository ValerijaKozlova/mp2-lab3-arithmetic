#pragma once
#include <stdio.h>
#include <iostream>


#ifndef __LIST_H__
#define __LIST_H__

#include <iostream>

using namespace std;

#ifndef __NODE__
#define __NODE__
template <class ValType>
struct node {
	node* next;
	ValType data;
};
#endif

template <class ValType>
class TList
{
protected:
	node<ValType>*head, *tail;				                //указатель на первый элемент, на последний
	int Size;
public:
	TList();					                            //конструктор по умолчанию
	~TList();					                            //деструктор
	bool IsStackEmpty() const;			                    //проверка на пустоту
	void InsertBegin(ValType str);
	void InsertEnd(ValType end);					    	//вставить в конец элемент end
	void Pop();										    //снять элемент с вершины
	ValType View();
	void Clear();

};

//конструктор по умолчанию
template <class ValType>
TList<ValType>::TList() { head = 0; tail = 0; }

//деструктор
template <class ValType>
TList<ValType>::~TList()
{
	if (head != 0)
	{
		node<ValType>* temp;
		while (head->next != 0)
		{
			temp = head;
			head = head->next;
			delete temp;
		}
		delete head;
	}
}

//проверка на пустоту
template <class ValType>
bool TList<ValType>::IsStackEmpty() const
{
	if (head == NULL)
		return true;
	else
		return false;
}

template <class ValType>
void TList<ValType>::InsertBegin(ValType str)
{

	node <ValType> *tmp = new node <ValType>;
	tmp->data = str;
	tmp->next = head;
	head = tmp;
}

//вставить в конец элемент end
template <class ValType>
void TList<ValType>::InsertEnd(ValType end)
{
	if (!IsStackEmpty())
	{
		tail->next = new node <ValType>;
		tail = tail->next;
		tail->data = end;
		tail->next = 0;
	}
	else
	{
		head = new node <ValType>;
		head->data = end;
		head->next = 0;
		tail = head;
	};
}

//снять элемент с вершины
template <class ValType>
void TList<ValType>::Pop()
{
	if (head)
	{
		node<ValType>* temp = head;
		head = head->next;
		delete temp;
	}
}

template <class ValType>
ValType TList<ValType>::View()
{
	return head->data;
}

template <class ValType>
void TList<ValType>::Clear()
{
	if (head != 0)
	{
		node<ValType>* temp;
		while (head->next != 0)
		{
			temp = head;
			head = head->next;
			delete temp;
		}
	}
	head = 0;
}

#endif

#ifndef __STACK_H__
#define __STACK_H__

using namespace std;

template <class ValType>
class MyStack : public TList <ValType>
{
private:
	TList<ValType> list;
public:
	MyStack();
	bool empty();
	void push(const ValType e1); 
	void pop();
	ValType top();

};

template <class ValType>
MyStack<ValType>::MyStack() {};

template <class ValType>
bool MyStack<ValType>::empty()
{
	return list.IsStackEmpty();
}

template <class ValType>
void MyStack<ValType>::push(const ValType e1)
{

	list.InsertBegin(e1);
}

template <class ValType>

void MyStack<ValType>::pop()
{
	list.Pop();
}

template <class ValType>
ValType MyStack<ValType>::top()
{
	ValType top = list.View();
	return top;
}

#endif






