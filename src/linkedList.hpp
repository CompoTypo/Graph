#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

#include "./structs/flightData.hpp"
#include "./structs/edge.hpp"

class LinkedList
{
private:
    edge *head;

public:
    LinkedList()
    {
        head = new edge();
    }

    int size()
    {
        int counter = 0;
        edge *temp = head;
        while (temp != NULL)
        {
            counter++;
            temp = temp->next;
        }
        return counter;
    }

    void insert(flightData in)
    {
        edge *newEdge = new edge(in.dest, in.c, in.t);
        if (head->name == "")
        {
            head = newEdge;
        }
        else if (head == NULL || head->name >= in.dest)
        {
            newEdge->next = head;
            head = newEdge;
        }
        else
        {
            edge *temp = head;
            while (temp->next != NULL && temp->next->name < in.dest)
            { // traverse adj list
                temp = temp->next;
            }
            newEdge->next = temp->next;
            temp->next = newEdge;
        }
    }

    edge *firstEdge()
    {
        return head;
    }

    bool hasEdge(std::string toFind)
    {
        edge *temp = head;
        while (temp != NULL && temp->name != toFind)
        {
            temp = temp->next;
        }
        if (temp == NULL)
        {
            return false;
        }
        else if (temp->name == toFind)
        {
            return true;
        }
    }

    edge *findIndex(int x)
    {
        int counter = 0;
        edge *temp = head;
        while (temp != NULL && counter != x)
        {
            counter++;
            temp = temp->next;
        }
        if (temp == NULL)
            return NULL;
        else if (counter == x)
            return temp;
        else
            return NULL;
    }

    void display()
    {
        edge *temp = head;
        while (temp != NULL)
        {
            std::cout << " -> " << temp->name;
            temp = temp->next;
        }
    }
};
#endif
