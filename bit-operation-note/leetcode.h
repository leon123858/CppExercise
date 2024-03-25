//
// Created by Leon Lin on 2024/3/25.
//

#ifndef TEST_LEETCODE_H
#define TEST_LEETCODE_H

void printWithArray(int *a, int size);
void printWithArray(int *a, int size, int b);

void findInLinkList(unsigned int DATA_A, unsigned int DATA_B);

std::vector<int> qsort(std::vector<int> arr);
std::vector<int> merge_sort(std::vector<int> arr);

// create a link list
struct Node{
    int data;
    Node *next;
    Node *prev;
};

class DoubleLinkList{
private:
    Node *head, *tail;
public:
    DoubleLinkList(){
        head = nullptr;
        tail = nullptr;
    }
    void addNode(int data){
        Node *newNode = new Node();
        newNode->data = data;
        newNode->next = nullptr;
        newNode->prev = nullptr;
        if (head == nullptr){
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    void printList(){
        Node *current = head;
        while (current != nullptr){
            printf("%d ", current->data);
            current = current->next;
        }
        printf("\n");
    }
    void reverseList(){
        Node *current = head;
        Node *temp = nullptr;
        while (current != nullptr){
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;
            current = current->prev;
        }
        if (temp != nullptr){
            head = temp->prev;
        }
    }
};

#endif //TEST_LEETCODE_H
