#include <iostream>
#include <stdexcept>

using namespace std;

class QueueUnderflowError : public runtime_error
{
  public:
    QueueUnderflowError() : runtime_error("QueueUnderflowError: The queue is empty") {}
};

struct Node
{
    int data;
    Node *next = nullptr;
};

class Queue
{
  public:
    Node *front = nullptr;
    Node *rear = nullptr;

  public:
    Queue() {}

    ~Queue()
    {
        while (!isEmpty())
            dequeue();
    }

    bool isEmpty()
    {
        return !front && !rear;
    }

    // Add new node
    void enqueue(int value)
    {
        Node *newNode = new Node;
        newNode->data = value;

        if (isEmpty())
            front = rear = newNode;
        else
        {
            rear->next = newNode;
            rear = newNode;
        }
    }

    void display()
    {
        if (isEmpty())
            throw QueueUnderflowError();
        else
        {
            Node *temp = front;

            cout << "{";
            while (temp)
            {
                cout << temp->data;
                if (temp->next)
                    cout << ", ";
                temp = temp->next;
            }
            cout << "}\n";
        }
    }

    // Delete the first node
    void dequeue()
    {
        if (isEmpty())
            throw QueueUnderflowError();
        else if (front == rear)
        {
            delete front;
            front = rear = nullptr;
        }
        else
        {
            Node *firstNode = front;
            front = front->next;
            delete firstNode;
        }
    }

    int peak()
    {
        if (isEmpty())
            throw QueueUnderflowError();
        else
            return front->data;
    }
};

int main(int argc, char *argv[])
{
    try
    {
        Queue nums;

        nums.enqueue(5);
        nums.enqueue(10);
        nums.enqueue(15);
        nums.enqueue(20);
        nums.enqueue(25);
        nums.display();

        cout << "Peak = " << nums.peak() << endl;

        nums.dequeue();
        nums.dequeue();
        nums.enqueue(30);
        nums.display();

        cout << "Peak = " << nums.peak() << endl;
    }
    catch (QueueUnderflowError &e)
    {
        cerr << e.what() << endl;
    }

    return 0;
}