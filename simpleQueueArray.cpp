#include <iostream>
#include <stdexcept>

using namespace std;

class QueueOverflowError : public runtime_error
{
  public:
    QueueOverflowError() : runtime_error("QueueOverflowError: The queue is full") {}
};

class QueueUnderflowError : public runtime_error
{
  public:
    QueueUnderflowError() : runtime_error("QueueUnderflowError: The queue is empty") {}
};

#define size 5
class Queue
{
  public:
    int queue[size];
    int front = -1;
    int rear = -1;

  public:
    Queue() {}

    bool isEmpty()
    {
        if (rear == -1 || front > rear)
            return true;
        else
            return false;
    }

    // Add a new element to the end
    void enqueue(int value)
    {
        if (rear == size - 1)
            throw QueueOverflowError();
        else if (front == -1)
        {
            front++;
            queue[++rear] = value;
        }
        else
            queue[++rear] = value;
    }

    // Remove an element from the front
    void dequeue()
    {
        if (isEmpty())
            throw QueueUnderflowError();
        else
            front++;
    }

    int peek()
    {
        if (isEmpty())
            throw QueueUnderflowError();
        else
            return queue[front];
    }

    void display()
    {
        if (isEmpty())
            throw QueueUnderflowError();
        else
        {
            cout << "{";

            for (int i = front; i <= rear; i++)
            {
                cout << queue[i];

                if (i < rear)
                    cout << ", ";
            }

            cout << "}\n";
        }
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
        nums.display();
        nums.dequeue();
        nums.dequeue();
        nums.dequeue();
        nums.display();

        cout << "peek = " << nums.peek() << endl;
        cout << "front = " << nums.front << endl;
        cout << "rear = " << nums.rear << endl;
    }
    catch (runtime_error &e)
    {
        cerr << e.what() << endl;
    }

    return 0;
}