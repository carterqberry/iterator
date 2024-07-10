#include <iostream>
#include <string>
#include "LinkedListInterface.h"
using namespace std;

template<typename T>
class Linked_list : public LinkedListInterface<T>
{
private:
    T* items;

    struct Node
    {
        T data;
        Node* next;
        Node(const T& d, Node* n) :data(d), next(n) {}

    };
    Node* head;

public:
    class Iterator
    {
    private:
        Node* iNode;
    public:
        Iterator(Node* head) : iNode(head) { }
        ~Iterator() {}

        bool operator!=(const Iterator& rhs) const
        {
            return iNode != rhs.iNode;
        }

        bool operator ==(const Iterator& rhs) const
        {
            return iNode == rhs.iNode;
        }

        Iterator& operator++()
        {
            if(iNode)
            {
                iNode = iNode->next;
            }
            return *this;
        }

        T& operator*() const
        {
            return iNode->data;
        }

        Node* getNode()
        {
            return iNode;
        }
    };



    Linked_list() : head(NULL){}
    Linked_list<T>(Linked_list &obj) {
        if (obj.head == NULL) {
            head = NULL;
        }
        else {
            head = new Node(obj.head->data, obj.head);
            Node *current = head;
            Node *objHead = obj.head;
            Node *currentObj = objHead;
            while (currentObj->next != NULL) {
                current->next = new Node(currentObj->next->data, current);
                currentObj = currentObj->next;
                current = current->next;
            }
            delete current;
            delete objHead;
            delete currentObj;
        }
    }

    ~Linked_list()
    {
        clear();
    }

    /** Insert Node(value) at beginning of linked list */
    virtual void push_front(const T& value)
    {
        head = new Node(value, head);
    }

    T& front()
    {
        return head->data;
    }



    /** Remove Node at beginning of linked list */
    virtual void pop_front(void)
    {
        Node* temp = head;
        head = head->next;
        head->data = temp->next->data;
        delete temp;
    }

    /** Return the number of nodes in the linked list */
    virtual int size(void) const
    {
        int size = 0;
        Node* node_ptr = head;           // point to the first node
        while (node_ptr != NULL)
        {
            size++;
            node_ptr = node_ptr->next;
        }
        return size;
    }


    /** Return true if linked list size == 0 */
    virtual bool empty(void) const
    {
        if(size() == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    /** Remove all Nodes with value from linked list */
    virtual void remove(const T& value)
    {
        while(find(value))
        {
            if(head == NULL)
            {
                return;
            }
            if(head->data == value)
            {
                head = head->next;
                return;
            }
            else
            {
                Node* node_ptr = head;
                while(node_ptr->next != NULL && node_ptr->next->data != value)
                {
                    node_ptr = node_ptr->next;
                }
                if(node_ptr->next != NULL)
                {
                    Node* holder = node_ptr->next;
                    node_ptr->next = holder->next;
                    delete holder;
                }
            }
        }
    }

    /** Remove all Nodes from linked list */
    virtual void clear(void)
    {
//        /* deref head_ref to get the real head */
//        Node* current = head;
//        Node* next = NULL;
//
//        while (current != NULL)
//        {
//            next = current->next;
//            free(current);
//            current = next;
//        }
//
//        head = NULL;
        while(head!= NULL)
        {
            remove(head->data);
        }
        delete head;

    }

    /** Reverse Nodes in linked list */
    virtual void reverse()
    {
        // Initialize current, previous and
        // next pointers
        Node* current = head;
        Node *prev = NULL, *next = NULL;

        while (current != NULL) {
            // Store next
            next = current->next;

            // Reverse current node's pointer
            current->next = prev;

            // Move pointers one position ahead.
            prev = current;
            current = next;
        }
        head = prev;
    }








    /** Return contents of Linked List as a string */
    virtual std::string toString(void) const
    {
        string list;
        Node* temp = head;
        while (temp != NULL) {
            list += temp->data + " ";
            temp = temp->next;
        }
        return list;
    }

    /** BONUS ** Insert Node(value) at end of linked list */
    //virtual void push_back(const T& value) = 0;

    /** BONUS ** Remove Node at end of linked list */
    //virtual void pop_back(void) = 0;

    /** BONUS ** Return reference to value of Node at end of linked list */
    //virtual T& back(void) = 0;

    // add item to front of list
    virtual void addItem(const T& item)
    {
        head = new Node(item, head);

    }

    // find item in list
    Node* find(const T& item)
    {
        Node* node_ptr = head;           // point to the first node
        while (node_ptr != NULL)
        {
            if (node_ptr->data == item) break;
            node_ptr = node_ptr->next;
        }
        return node_ptr;
    }

    // insert item1 after item2
    virtual bool insertAfter(const T& item1, const T& item2)
    {
        Node* after = find(item1);
        if (after == NULL) return false;
        after->next = new Node(item2, after->next);
        return true;
    }

    friend ostream& operator<<(ostream& os, Linked_list& ll)
    {
        Node* node_ptr = ll.head;
        while (node_ptr != NULL)
        {
            os << node_ptr->data << ((node_ptr->next != NULL) ? " ==> " : "");
            node_ptr = node_ptr->next;    // move to the next node
        }
        return os;
    }

    /** Return iterator pointing to the first value in linked list */
    Iterator begin(void)
    {
        return Linked_list<T>::Iterator(head);
    }

    /** Return iterator pointing to something not in linked list */
    Iterator end(void)
    {
        return Linked_list<T>::Iterator(NULL);
    }

    /** Return iterator pointing to value found in linked list */
    bool find(Iterator first, Iterator last, const T& value)
    {
        Iterator myIndex = first;
        while(myIndex != last)
        {
            if (*myIndex == value)
            {
                 return true;
            }
            else
            {
                ++myIndex;
            }

        }
       return false;
    }

    Iterator findPosition(Iterator first, Iterator last, const T& value)
    {
        Iterator myIndex = first;
        while(myIndex != last)
        {
            if(*myIndex != value)
            {
                ++myIndex;
            }
            else
            {
                break;
            }
        }
        return myIndex;
    }

    Iterator findPositionBefore(Iterator first, Iterator last, const T& value)
    {
        Iterator myIndex = first;
        Iterator temp = myIndex;
        while(myIndex != last)
        {
            if(*myIndex != value)
            {
                temp = myIndex;
                ++myIndex;
                if(*myIndex == value)
                {
                    return temp;
                }
            }
            else
            {
                break;
            }
        }
        return myIndex;
    }

    void insertAfter(Iterator position, const T& value)
    {
            Node* after = new Node(value, position.getNode()->next);
            position.getNode()->next = after;
    }

    void insertBefore(Iterator position, const T& value)
    {
        if(position.getNode() == head)
        {
            push_front(value);
        }
        else
        {
            Node* before = new Node(value, position.getNode()->next);
            position.getNode()->next = before;
        }

    }

    Iterator erase(Iterator position, Iterator positionBefore)
    {
        positionBefore.getNode()->next = position.getNode()->next;

        delete position.getNode();
        return positionBefore.getNode()->next;
    }

    void replace(Iterator first, Iterator last, const T& old_value, const T& new_value)
    {
            Iterator position = findPosition(first, last, old_value);
            Iterator positionBefore = findPositionBefore(first, last, old_value);
            Node* newNode = new Node(new_value, position.getNode()->next);
            positionBefore.getNode()->next = newNode;
            delete position.getNode();
    }

    void replaceHead(Iterator first, Iterator last, const T& old_value, const T& new_value)
    {
        Iterator position = findPosition(first, last, old_value);

        head = new Node(new_value, position.getNode()->next);

        delete position.getNode();
    }




    string iterate()
    {
        string listOut;
        Iterator iter = begin();
        while (iter != end())
        {
            listOut += "\n [" + *iter + "]";
            ++iter;
        }
        return listOut;
    }


};


