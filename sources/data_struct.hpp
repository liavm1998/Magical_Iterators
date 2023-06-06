#ifndef MY_Linked_List_HPP
#define MY_Linked_List_HPP

#include <cmath>
#include <iostream>

struct Node
{
    int data;
    Node *next;
    Node *back;
    Node(int value) : data(value), next(nullptr), back(nullptr) {}

    bool operator==(const Node &other) const
    {
        return other.data == data && other.next == next && other.back == back;
    }
};

class LinkedList
{
private:
    Node *head;
    Node *tail;
    size_t size = 0;

public:
    LinkedList() : head(nullptr), tail(nullptr) {}

    ~LinkedList()
    {
        // Delete all nodes in the linked list
        Node *current = head;
        while (current != nullptr)
        {
            Node *next = current->next;
            delete current;
            current = next;
        }
    }

            // Copy constructor
        LinkedList(const LinkedList& other) = default;

        // Copy assignment operator
        LinkedList& operator=(const LinkedList& other)= default;

        // Move constructor
        LinkedList(LinkedList&& other)= default;

        // Move assignment operator
        LinkedList& operator=(LinkedList&& other)= default;

    void insert(int value)
    {
        Node *newNode = new Node(value);
        // case empty
        if (head == nullptr)
        {
            head = newNode;
            tail = newNode;
        }
        else if (value < head->data)
        { // case first
            head->back = newNode;
            newNode->next = head;
            head = newNode;
        }
        else if (value >= tail->data)
        { // gotta be last
            newNode->back = tail;
            tail->next = newNode;
            tail = newNode;
        }
        else
        { // middle
            Node *current = head;
            while (value >= current->next->data)
            { // find location
                current = current->next;
            }

            newNode->next = current->next;
            current->next->back = newNode;
            current->next = newNode;
            newNode->back = current;
        }
        this->size++;
    }

    void removeElement(int element)
    {
        if (head == nullptr)
        {
            return;
        }

        if (head->data == element)
        {

            Node *temp = head;
            head = head->next;

            if (head == nullptr)
            {
                tail = nullptr;
            }

            delete temp;
            size--;
            return;
        }

        Node *current = head;
        while (current->next != nullptr && current->next->data != element)
        {
            current = current->next;
        }

        if (current->next != nullptr)
        {
            Node *temp = current->next;
            current->next = current->next->next;

            if (current->next == nullptr)
            {
                tail = current;
            }
            size--;
            delete temp;
        }
        else {
            throw std::runtime_error("");
        }
    }

    size_t getSize() const
    {
        return this->size;
    }

    Node *getLast()
    {
        return this->tail;
    }

    Node *getHead()
    {
        return this->head;
    }

    Node *At(size_t index)
    {

        if (index > size)
        {
            std::cout << "Error: Index out of range" << std::endl;
            return nullptr;
        }

        Node *current = head;
        for (size_t i = 0; i < index; ++i)
        {
            current = current->next;
        }
        return current;
    }
    void display()
    {
        Node *current = head;
        while (current != nullptr)
        {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};

#endif // MY_Linked_List