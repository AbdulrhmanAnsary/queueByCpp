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

// here i use if statement to control the flow

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
        return (front == -1 && rear == -1);
    }

    bool isFull()
    {
        if (front == 0 && rear == size - 1)
            return true;
        else if (rear == front - 1)
            return true;
        else
            return false;
    }

    // Add a new element to the end
    void enqueue(int value)
    {
        if (isFull())
            throw QueueOverflowError();
        else if (isEmpty())
        {
            front = rear = 0;
            queue[rear] = value;
        }
        else if (rear == size - 1)
        {
            rear = 0;
            queue[rear] = value;
        }
        else
            queue[++rear] = value;
    }

    // Remove an element from the front
    void dequeue()
    {
        if (isEmpty())
            throw QueueUnderflowError();
        else if (front == rear)
            front = rear = -1;
        else if (front == size - 1)
            front = 0;
        else
            front++;
    }

    // Return the first element
    int peek()
    {
        if (isEmpty())
            throw QueueUnderflowError();
        return queue[front];
    }

    void display()
    {
        if (isEmpty())
            throw QueueUnderflowError();
        else
        {
            cout << "{";
            if (front <= rear)
            {
                for (int i = front; i <= rear; i++)
                {
                    cout << queue[i];
                    if (i < rear)
                        cout << ", ";
                }
            }
            else
            {
                for (int i = front; i < size; i++)
                {
                    cout << queue[i];
                    if (i < size)
                        cout << ", ";
                }
                for (int i = 0; i <= rear; i++)
                {
                    cout << queue[i];
                    if (i < rear)
                        cout << ", ";
                }
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
        nums.enqueue(20);
        nums.enqueue(25);
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