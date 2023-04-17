#ifndef GRAFY_HEAP_H
#define GRAFY_HEAP_H


#include <stdexcept>
#include <vector>

namespace Grafy
{
    typedef struct priorityQueueItem
    {
        int priority_;
        int data_;
    } PRIORITY_QUEUE_ITEM;

    class Heap
    {
    public:
        void push(int priority, int data);

        int pop();

        bool empty();

    private:
        int indexOfPeek();

        int getParentIndex(int index);

        int getGreaterSonIndex(int index);

        void swap(int index1, int index2);

    private:
        std::vector<PRIORITY_QUEUE_ITEM> list_;
    };

    inline void Heap::push(int priority, int data)
    {
        list_.push_back({priority, data});

        int index = list_.size() - 1;
        while (getParentIndex(index) >= 0 && priority < list_[getParentIndex(index)].priority_)
        {
            swap(index, getParentIndex(index));
            index = getParentIndex(index);
        }
    }

    inline int Heap::pop()
    {
        if (list_.empty())
        {
            throw std::logic_error("Heap empty!");
        }

        swap(indexOfPeek(), list_.size() - 1);

        int data = list_[list_.size() - 1].data_;

        list_.erase(std::next(list_.begin(), list_.size() - 1),
                    std::next(list_.begin(), list_.size()));

        int index = 0;
        while (getGreaterSonIndex(index) >= 0
               && list_[index].priority_ > list_[getGreaterSonIndex(index)].priority_)
        {
            swap(index, getGreaterSonIndex(index));
            index = getGreaterSonIndex(index);
        }

        return data;
    }

    inline int Heap::getParentIndex(int index)
    {
        int parentIndex = ((index + 1) / 2) - 1;
        if (parentIndex >= 0)
        {
            return parentIndex;
        }
        return -1;
    }

    inline int Heap::getGreaterSonIndex(int index)
    {
        int leftSonIndex = (index + 1) * 2 - 1;
        int rightSonIndex = (index + 1) * 2;

        if (rightSonIndex < list_.size()
            && list_[leftSonIndex].priority_ >= list_[rightSonIndex].priority_)
        {
            return rightSonIndex;
        } else if (leftSonIndex < list_.size())
        {
            return leftSonIndex;
        }
        return -1;
    }

    inline int Heap::indexOfPeek()
    {
        if (list_.empty())
        {
            throw std::logic_error("Heap empty!");
        }

        return 0;
    }

    inline void Heap::swap(int index1, int index2)
    {
        int tmpPrio = list_[index1].priority_;
        int tmpData = list_[index1].data_;

        list_[index1].priority_ = list_[index2].priority_;
        list_[index1].data_ = list_[index2].data_;

        list_[index2].priority_ = tmpPrio;
        list_[index2].data_ = tmpData;
    }

    inline bool Heap::empty()
    {
        return list_.empty();
    }
}


#endif //GRAFY_HEAP_H
