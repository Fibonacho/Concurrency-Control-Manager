#include <iostream>

#ifndef DLIST_H
#define DLIST_H

template <typename T>
class DList
{
    struct Node
    {
        T mData;
        Node* mPrev;
        Node* mNext;
        Node(T pType, Node* pPrev, Node* pNext): mData(pType), mPrev(pPrev), mNext(pNext) {}
    };
    
    Node* mHead;
    Node* mTail;
    
public:
    DList() : mHead(nullptr), mTail(nullptr)
    {
    }
    
    template<int N>
    DList(T (&arr) [N]): mHead(nullptr), mTail(nullptr)
    {
        for(int i(0); i != N; ++i) //foreach
           pushBack(arr[i]);
    }
    
    //check if function is empty
    bool empty() const
    {
        return ( !mHead || !mTail );
    }
    
    int count() const
    {
        int c = 0;
        Node* mNode = mHead;
        while (mNode != nullptr)
        {
            c++;
            mNode = mNode->mNext;
        }
        return c;
    }
    
    operator bool() const {
        return !empty();
    }
    

    void pushBack(T);
    void pushFront(T);
    void remove(T);
    T returnElement(int pIndex);
    void remove(int pIndex);
    
    T popBack();
    T popFront();
    ~DList()
    {
        while(mHead)
        {
            Node* temp(mHead);
            mHead=mHead->mNext;
            delete temp;
        }
    }
};

template <typename T>
T DList<T>::returnElement(int pIndex)
{
    Node* node = mHead;
    for (int i = 0; i < pIndex; i++)
    {
        node = node->mNext;
    }
    return node->mData;
}

template <typename T>
void DList<T>::remove(int pIndex)
{
    //remove object at index pIndex
}

template <typename T>
void DList<T>::remove(T)
{
    //remove the object T from the list
}

template <typename T>
void DList<T>::pushBack(T data)
{
    mTail = new Node(data, mTail, nullptr);
    if(mTail->mPrev)
        mTail->mPrev->mNext = mTail;
    if( empty() )
        mHead = mTail;
}

template <typename T>
void DList<T>::pushFront(T pData)
{
    mHead = new Node(pData, nullptr, mHead);
    if(mHead->mNext)
        mHead->mNext->mPrev = mHead;
    if(empty() )
        mTail = mHead;
}

template<typename T>
T DList<T>::popBack()
{
    if( empty() )
        throw("DList : list empty");
    Node* temp(mTail);
    T mData(mTail->mData);
    mTail = mTail->mPrev;
    if(mTail)
        mTail->mNext = nullptr;
    else
        mHead = nullptr;
    delete temp;
    return mData;
}

template<typename T>
T DList<T>::popFront()
{
    if( empty() )
        throw("DList : list empty");
    Node* temp(mHead);
    T data(mHead->mData);
    mHead = mHead->mNext;
    if(mHead)
        mHead->prev = nullptr;
    else
        mTail = nullptr;
    delete temp;
    return data;
}

#endif

