#pragma once
#include <stdexcept>
#include <initializer_list>

using std::initializer_list;

#define MFOREACHLIST(_LIST_, _V_) for(ListIndex _V_ = 0; _V_ < _LIST_.Length(); _V_++)

typedef size_t ListIndex;
typedef size_t ListSize;

//OList类：
//模板类，实现了各类型通用的列表及其所需的部分功能
//主要实现为动态数组

template <class T>
class OList
{
private:
    T* p_list;
    ListSize size;

public:
    static constexpr ListIndex NPOS = SIZE_MAX;

    OList() {
        size = 0;
        p_list = new T[size];
    }

    OList(initializer_list<T> ilist) {
        size = ilist.size();
        if (size >= NPOS) {
            throw std::out_of_range("List too large");
        }
        p_list = new T[size];
        const T* iter = ilist.begin();
        for (int i = 0; i < size; i++) {
            p_list[i] = *iter;
            iter++;
        }
    }

    ~OList() {
        delete[] p_list;
    }

    //在尾部添加新元素
    void push(const T& element) {
        if (!this->isEmpty()) {
            size++;
            if (size >= NPOS) {
                throw std::out_of_range("List too large");
            }
            T* p_newList = new T[size];
            T* p_oldList = p_list;
            for (int i = 0; i <= size - 2; i++) {
                p_newList[i] = p_oldList[i];
            }
            p_newList[size - 1] = element;
            p_list = p_newList;
            delete[] p_oldList;
        }
        else {
            size++;
            delete[] p_list;
            p_list = new T[size];
            p_list[size - 1] = element;
        }
    }

    //下标运算符及其const变体的重载
    const T& operator[](const ListIndex index) const{
        if (index > size - 1) {
            throw std::out_of_range("Index out of range");
        }
        return p_list[index];
    }

    T& operator[](const ListIndex index){
        if (index > size - 1) {
            throw std::out_of_range("Index out of range");
        }
        return p_list[index];
    }

    ListSize Length() const {
        return size;
    }

    bool isEmpty() const {
        return size == 0;
    }

    //查找OList中是否含有某元素，若存在则返回其位置，否则返回NPOS
    //startpos为查找起点（包含），默认为0，即查找全表
    ListSize contains(const T& TargetElement, const ListIndex startpos = 0) const{
        for (ListIndex i = startpos; i < size; i++) {
            if (p_list[i] == TargetElement) {
                return i;
            }
        }
        return NPOS;
    }

    //移除指定下标的元素
    void remove(ListIndex Tindex) {
        if (Tindex < 0 || Tindex >= size) {
            throw std::out_of_range("Failed in removing element: index out of range");
        }

        T* p_newlist = new T[size - 1];
        int newindex = 0;
        int oldindex = 0;
        while (oldindex < size) {
            if (oldindex != Tindex) {
                p_newlist[newindex] = p_list[oldindex];
                newindex++;
            }
            oldindex++;
        }
        delete[] p_list;
        p_list = p_newlist;
        size--;
    }

    void clear() {
        size = 0;
        delete[] p_list;
        p_list = new T[size];
    }

    void swap(ListIndex iL, ListIndex iR) {
        T tmp;
        tmp = p_list[iL];
        p_list[iL] = p_list[iR];
        p_list[iR] = tmp;
    }

    const T* begin() {
        return p_list[0];
    }

    const T* end() {
        return p_list[size - 1];
    }
};