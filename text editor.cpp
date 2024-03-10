//create a text editor in c++ with the following functionalities
//1. insert data
//2. update data
//3. append data
//4. delete data
//5. undo operation
//6. redo operation
//7. display data
//8. Search data
#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include<conio.h>
using namespace std;

struct Node
{
    string data;
    Node *next;
    Node *pre;
};

class LinkedList
{
    stack<Node*> undoStack;
    stack<Node*> redoStack;
    Node *head;
    Node *tail;
    int num;
public:
    LinkedList() : head(nullptr), tail(nullptr), num(0) {}

    // Inserting data
    void insertData(const string& data) {
        Node* node = new Node();
        node->data = data;
        node->next = nullptr;
        if (head == nullptr) {
            node->pre = nullptr;
            head = node;
            tail = node;
        } else {
            node->pre = tail;
            tail->next = node;
            tail = node;
        }
        undoStack.push(node);
        num++;
    }

    // Updating data
    void updateData(const string& oldData, const string& newData) {
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->data == oldData) {
                undoStack.push(temp);
                temp->data = newData;
                return;
            }
            temp = temp->next;
        }
        cout << "Data not found." << endl;
    }

    // Appending data
    void appendData(const string& afterData, const string& newData) {
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->data == afterData) {
                Node* node = new Node();
                node->data = newData;
                node->next = temp->next;
                node->pre = temp;
                if (temp->next != nullptr)
                    temp->next->pre = node;
                else
                    tail = node;
                temp->next = node;
                undoStack.push(node);
                num++;
                return;
            }
            temp = temp->next;
        }
        cout << "Data not found to append after." << endl;
    }

    // Deleting data
    void deleteData(const string& data) {
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->data == data) {
                undoStack.push(temp);
                if (temp == head) {
                    head = temp->next;
                    if (head != nullptr)
                        head->pre = nullptr;
                } else if (temp == tail) {
                    tail = temp->pre;
                    tail->next = nullptr;
                } else {
                    temp->pre->next = temp->next;
                    temp->next->pre = temp->pre;
                }
                delete temp;
                num--;
                return;
            }
            temp = temp->next;
        }
        cout << "Data not found to delete." << endl;
    }

    // Searching data
    void searchData(const string& data) {
        Node* temp = head;
        int count = 0;
        while (temp != nullptr) {
            if (temp->data == data) {
                cout << "Data found at position " << count + 1 << endl;
                return;
            }
            temp = temp->next;
            count++;
        }
        cout << "Data not found." << endl;
    }

    // Printing data
    void printData() {
        if (head == nullptr) {
            cout << "No data found." << endl;
        } else {
            Node* temp = head;
            cout << "Data: ";
            while (temp != nullptr) {
                cout << temp->data << " ";
                temp = temp->next;
            }
            cout << endl;
        }
    }

    // Undo operation
    void undoOperation() {
        if (!undoStack.empty()) {
            Node* node = undoStack.top();
            undoStack.pop();
            redoStack.push(node);
            if (node == head) {
                head = node->next;
                if (head != nullptr)
                    head->pre = nullptr;
            } else if (node == tail) {
                tail = node->pre;
                tail->next = nullptr;
            } else {
                node->pre->next = node->next;
                node->next->pre = node->pre;
            }
            delete node;
            num--;
        } else {
            cout << "Undo stack is empty." << endl;
        }
    }

    // Redo operation
    void redoOperation() {
        if (!redoStack.empty()) {
            Node* node = redoStack.top();
            redoStack.pop();
            undoStack.push(node);
            if (node == head) {
                head = node;
                if (tail == nullptr)
                    tail = head;
            } else if (node == tail) {
                tail = node;
                if (head == nullptr)
                    head = tail;
            } else {
                node->pre->next = node;
                node->next->pre = node;
            }
        } else {
            cout << "Redo stack is empty." << endl;
        }
    }

    // Destructor to deallocate memory
    ~LinkedList() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    LinkedList obj;
    int choice;
    string data, oldData, newData, afterData;
    while (true) {
        system("cls");

        cout << "Enter the choice:" << endl;
        cout << "1. Insert data" << endl;
        cout << "2. Update data" << endl;
        cout << "3. Append data" << endl;
        cout << "4. Delete data" << endl;
        cout << "5. Undo operation" << endl;
        cout << "6. Redo operation" << endl;
        cout << "7. Display data" << endl;
        cout << "8. Search data" << endl;
        cout << "9. Exit" << endl;
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter data to insert: ";
                cin >> data;
                obj.insertData(data);
                cout<<"Data is inserted"<<endl;
                break;
            case 2:
                cout << "Enter data to update: ";
                cin >> oldData;
                cout << "Enter new data: ";
                cin >> newData;
                obj.updateData(oldData, newData);
                cout<<"Data is updated"<<endl;
                break;
            case 3:
                cout << "Enter data to append after: ";
                cin >> afterData;
                cout << "Enter new data: ";
                cin >> newData;
                obj.appendData(afterData, newData);
                cout<<"Data is appended"<<endl;
                break;
            case 4:
                cout << "Enter data to delete: ";
                cin >> data;
                obj.deleteData(data);
                cout<<"Data is deleted"<<endl;
                break;
            case 5:
                obj.undoOperation();
                cout<<"undo operation done"<<endl;
                break;
            case 6:
                obj.redoOperation();
                cout<<"Redu operation done"<<endl;
                break;
            case 7:
                obj.printData();
                break;
            case 8:
                cout << "Enter data to search: ";
                cin >> data;
                obj.searchData(data);
                break;
            case 9:
                exit(0);
            default:
                cout << "Invalid choice." << endl;
        }
        system("pause");
    }
    return 0;
}

