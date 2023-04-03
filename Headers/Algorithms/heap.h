#ifndef GRAFY_HEAP_H
#define GRAFY_HEAP_H


#include <stdexcept>
#include <vector>

typedef struct priorityQueueItem {
    int priority;
    int data;
} PRIORITY_QUEUE_ITEM;

class Heap {
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

inline void Heap::push(int priority, int data) {
    this->list_.push_back({priority, data});

    int index = this->list_.size() - 1;
    while (getParentIndex(index) >= 0 && priority < this->list_[getParentIndex(index)].priority) {
        this->swap(index, getParentIndex(index));
        index = getParentIndex(index);
    }
}

inline int Heap::pop() {
    if (this->list_.empty()) {
        throw std::logic_error("Heap empty!");
    }

    this->swap(indexOfPeek(), this->list_.size() - 1);

    int data = this->list_[this->list_.size() - 1].data;

    this->list_.erase(std::next(this->list_.begin(), this->list_.size() - 1),
                      std::next(this->list_.begin(), this->list_.size()));

    int index = 0;
    while (getGreaterSonIndex(index) >= 0
           && this->list_[index].priority > this->list_[getGreaterSonIndex(index)].priority) {
        this->swap(index, getGreaterSonIndex(index));
        index = getGreaterSonIndex(index);
    }

    return data;
}

inline int Heap::getParentIndex(int index) {
    int parentIndex = ((index + 1) / 2) - 1;
    if (parentIndex >= 0) {
        return parentIndex;
    }
    return -1;
}

inline int Heap::getGreaterSonIndex(int index) {
    int leftSonIndex = (index + 1) * 2 - 1;
    int rightSonIndex = (index + 1) * 2;

    if (rightSonIndex < this->list_.size()
        && this->list_[leftSonIndex].priority >= this->list_[rightSonIndex].priority) {
        return rightSonIndex;
    } else if (leftSonIndex < this->list_.size()) {
        return leftSonIndex;
    }
    return -1;
}

inline int Heap::indexOfPeek() {
    if (this->list_.empty()) {
        throw std::logic_error("Heap empty!");
    }

    return 0;
}

inline void Heap::swap(int index1, int index2) {
    int tmpPrio = this->list_[index1].priority;
    int tmpData = this->list_[index1].data;

    this->list_[index1].priority = this->list_[index2].priority;
    this->list_[index1].data = this->list_[index2].data;

    this->list_[index2].priority = tmpPrio;
    this->list_[index2].data = tmpData;
}

inline bool Heap::empty() {
    return this->list_.empty();
}


#endif //GRAFY_HEAP_H
