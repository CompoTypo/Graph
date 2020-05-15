#ifndef ADJACENCYLIST_HPP
#define ADJACENCYLIST_HPP

#include "./structs/flightData.hpp"
#include "./structs/vert.hpp"

class AdjacencyList {
    private:
        vert *head;
    public:
        AdjacencyList() {
            head = new vert();
        }

        void insert(flightData in) {
            if (head->name == "" || head == NULL) {
                head->name = in.origin;
                head->edges.insert(in);
            } else {
                vert *temp = head;
                while(temp->next != NULL) { // traverse adj list
                    if (temp->name < in.origin && temp->next->name > in.origin) {
                        vert *injVert = new vert(in.origin);
                        injVert->edges.insert(in);
                        injVert->next = temp->next;
                        temp->next = injVert;
                        return;
                    }
                    if (temp->name == in.origin) {
                        temp->edges.insert(in);
                        return;
                    }
                    temp = temp->next;
                }
                if (temp->name == in.origin) {
                    temp->edges.insert(in);
                } else if (temp->name > in.origin) {     
                    vert *injVert = new vert(in.origin);
                    injVert->edges.insert(in);
                    injVert->next = temp;
                    head = injVert;
                } else {
                    temp->next = new vert(in.origin);                
                    temp->next->edges.insert(in);    
                }
            }
        }

        vert* find(std::string toFind) {
            vert *temp = head;
            while(temp != NULL && temp->name != toFind){
                temp = temp->next;
            }
            if (temp == NULL) 
                return NULL;
            else if (temp->name == toFind) 
                return temp;
            else
                return NULL;
            
        }

        std::vector<std::string> getAllVerts() {
            std::vector<std::string> verts;

            vert *temp = head;
            while(temp != NULL){
                verts.push_back(temp->name);
                temp = temp->next;
            }
            return verts;   
        }

        void display() {
            std::cout << "displaying adj list" << std::endl;
            vert *temp = head;
            while (temp != NULL) {
                std::cout << temp->name;
                temp->edges.display();
                if (temp->next != NULL) {
                    std::cout << std::endl << " | " << std::endl;
                } else {
                    std::cout << std::endl;
                }
                  
                temp = temp->next;
            }
        }
};
#endif

