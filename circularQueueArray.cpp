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

// here i use modules (%) to move from 0 to size - 1 every time

#define size 5
class Queue
{
  public:
    int queue[size];
    int front = 0;
    int rear = 0;
    int count = 0;

  public:
    Queue() {}

    bool isEmpty()
    {
        return count == 0;
    }

    bool isFull()
    {
        return count == size;
    }

    // Add a new element to the end
    void enqueue(int value)
    {
        if (isFull())
            throw QueueOverflowError();
        queue[rear] = value;
        rear = (rear + 1) % size;
        count++;
    }

    // Remove an element from the front
    void dequeue()
    {
        if (isEmpty())
            throw QueueUnderflowError();
        front = (front + 1) % 5;
        count--;
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
        cout << "{";
        for (int i = 0; i < count; i++)
        {
            cout << queue[(front + i) % size];
            if (i < count - 1)
                cout << ", ";
        }
        cout << "}\n";
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
        nums.display();

        cout << "peek = " << nums.peek() << endl;
        cout << "front = " << nums.front << endl;
        cout << "rear = " << nums.rear << endl;
        cout <<  "count = " << nums.count << endl;
    }
    catch (runtime_error &e)
    {
        cerr << e.what() << endl;
    }

    return 0;
}