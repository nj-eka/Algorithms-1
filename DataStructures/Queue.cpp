#include <cstdint>
#include <iostream>
#include <stdexcept>

template<typename Type>
class Queue
{
public:
    explicit Queue() noexcept = default;
    explicit Queue(const Queue& another) noexcept 
        : : mHead(copyNode(another.mHead)), mSize(another.mSize) {}
    explicit Queue(Queue&& another) noexcept;
    Queue& operator = (const Queue& another) noexcept;
    Queue& operator = (Queue&& another) noexcept;
    void push(const Type& value) noexcept;
    void pop();
    void clear();
    Type front() const;
    std::size_t getSize() const noexcept;
    bool isEmpty() const noexcept;
    ~Queue();
private:
    struct Node
    {
        Type value = Type();
        Node* next = nullptr;
    };
    Node* copyNode(Node* other) noexcept;
private:
    Node* mHead = nullptr;
    std::size_t mSize = 0;
};

template<typename Type>
Queue<Type>::Queue(Queue&& another) noexcept
    : mHead(another.mHead), mSize(another.mSize)
{
    another.mSize = 0;
    another.mHead = nullptr;
}

template<typename Type>
Queue<Type>& Queue<Type>::operator = (const Queue& another) noexcept
{
    if (this != &another) 
    {
        if (!isEmpty())
            clear();
        mHead = copyNode(another.mHead);
        mSize = another.mSize;
    }
    return *this;
}

template<typename Type>
Queue<Type>& Queue<Type>::operator = (Queue&& another) noexcept
{
    if (this != &another)
    {
        if (!isEmpty())
            clear();
        mHead = another.mHead;
        another.mHead = nullptr;
        mSize = another.mSize;
        another.mSize = 0;
    }
    return *this;
}

template<typename Type>
auto Queue<Type>::copyNode(Node* another) noexcept -> Node*
{
    if (!another)
        return nullptr;

    Node* newNode = new Node();
    newNode->value = another->value;
    newNode->next = copyNode(another->next);
    return newNode;
}

template<typename Type>
void Queue<Type>::push(const Type& value) noexcept
{
    if (isEmpty())
    {
        mHead = new Node;
        mHead->value = value;
    }
    else
    {
        Node* newHead = new Node;
        newHead->value = value;
        newHead->next = mHead;
        mHead = newHead;
    }
    mSize++;
}

template<typename Type>
void Queue<Type>::pop()
{
    if (!isEmpty())
    {
        Node* tmpPtr = mHead;
        mHead = mHead->next;
        delete tmpPtr;
        mSize--;
    }
    else
    {
        throw std::runtime_error("Queue is empty. Could not delete the first element.");
    }
}

template<typename Type>
void Queue<Type>::clear()
{
    while (!isEmpty())
        pop();
}

template<typename Type>
Type Queue<Type>::front() const
{
    if (!isEmpty())
        return mHead->value;
    else
        throw std::runtime_error("Queue is empty. Could not give the first element.");
}

template<typename Type>
std::size_t Queue<Type>::getSize() const noexcept
{
    return mSize;
}

template<typename Type>
bool Queue<Type>::isEmpty() const noexcept
{
    return mSize == 0;
}

template<typename Type>
Queue<Type>::~Queue()
{
    clear();
}

int main()
{
    try 
    {
        Queue<int> queue;
        for (auto &val : { 4, 6, 7, 2, 8, 8 })
            queue.push(val);

        while (!queue.isEmpty())
        {
            std::cout << "Value: " << queue.front() << std::endl;
            queue.pop();
        }

        return EXIT_SUCCESS;
    }
    catch (const std::exception& e) 
    {
        std::cerr << "Error! Cause: " << e.what() << std::endl;
        return EXIT_SUCCESS;
    }
}
