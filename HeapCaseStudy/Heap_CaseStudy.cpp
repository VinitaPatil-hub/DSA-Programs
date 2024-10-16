#include <iostream>
using namespace std;

// Job class to store job details
class Job 
{
public:
    int id;       // Job ID
    int priority; // Job priority

    Job(int id, int priority)
    {
        this->id = id;
        this->priority = priority;
    }
};

// MinHeap class to manage the jobs
class MinHeap 
{
private:
    Job* heap[10]; // Array to store pointers to Job objects
    int size; // Current number of jobs

    void heapifyUp(int index) 
    {
        while (index > 0) 
        {
            int parentIndex = (index - 1) / 2;
            if (heap[index]->priority < heap[parentIndex]->priority) 
            {
                swap(heap[index], heap[parentIndex]);
                index = parentIndex;
            } 
            else 
            {
                break;
            }
        }
    }

    void heapifyDown(int index) 
    {
        int smallest = index;
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;

        if (leftChild < size && heap[leftChild]->priority < heap[smallest]->priority) 
        {
            smallest = leftChild;
        }
        if (rightChild < size && heap[rightChild]->priority < heap[smallest]->priority) 
        {
            smallest = rightChild;
        }
        if (smallest != index) 
        {
            swap(heap[index], heap[smallest]);
            heapifyDown(smallest);
        }
    }

public:
    MinHeap() 
    {
        size = 0;
    }

    void insert(int id, int priority) 
    {
        if (size < 10) 
        {
            heap[size] = new Job(id, priority);
            heapifyUp(size);
            size++;
        } 
        else 
        {
            cout << "Heap is full. Cannot insert job." << endl;
        }
    }

    Job* extractMin() 
    {
        if (size == 0) 
        {
            cout << "Heap is empty. No jobs to execute." << endl;
            return NULL;
        }
        Job* minJob = heap[0];
        heap[0] = heap[size - 1];
        size--;
        heapifyDown(0);
        return minJob;
    }

    bool isEmpty() 
    {
        return size == 0;
    }
};

int main() 
{
    MinHeap jobQueue; // Create a min heap

    while (true) 
    {
        int choice;
        cout << "1. Submit Job\n2. Execute Job\n3. Exit\nEnter choice: ";
        cin >> choice;

        switch (choice) 
        {
            case 1: 
            {
                int id, priority;
                cout << "Enter job ID and priority: ";
                cin >> id >> priority;
                jobQueue.insert(id, priority);
                cout << "Job " << id << " submitted with priority " << priority << endl;
                break;
            }
            case 2: 
            {
                // Execute only one job
                Job* job = jobQueue.extractMin();
                if (job) 
                {
                    cout << "Executing job " << job->id << " with priority " << job->priority << endl;
                    delete job; // Free the memory of the executed job
                }
                break;
            }
            case 3: 
            {
                cout << "Exiting..." << endl;
                return 0;
            }
            default:
                cout << "Invalid choice. Try again." << endl;
        } 
    }
    return 0;
}

