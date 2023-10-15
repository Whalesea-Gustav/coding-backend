#pragma once

#include <cstdio>
#include <utility>
#include <concepts>
#include <atomic>

template<typename T>
struct DefaultDeleter {
    void operator()(T *p) const {
        delete p;
    }
};

//针对数组的偏特化
template<typename T>
struct DefaultDeleter<T[]> {
    void operator()(T *p) const {
        delete[] p;
    }
};

//针对单独类型的全特化
template<>
struct DefaultDeleter<FILE> {
    void operator()(FILE *p) const {
        fclose(p);
    }
};


template<typename T, typename U>
T exchange(T &dst, U &&val) {
    T tmp = std::move(dst);
    dst = val;
    return tmp;
}

template<typename T>
class SharedControlBlock {

    template<typename U, typename UDeleter>
    friend class SharedPtr1st;
    template<typename Y>
    friend class SharedControlBlock;

    std::atomic<size_t> m_count;

    explicit SharedControlBlock(int count = 0) {
        m_count = count;
    }

    template<class U> requires (std::convertible_to<U*, T*>) // 有 C++20 的写法
    SharedControlBlock(SharedControlBlock<U> &&that) : m_count(that.m_count) {
    }
};


template<typename T, typename Deleter = DefaultDeleter<T>>
class SharedPtr1st {

    friend class SharedControlBlock<T>;

    template<class U, class UDeleter>
    friend class SharedPtr1st;

private:
    T *m_p;
    SharedControlBlock<T> *m_controller;

    void IncControllerCount() {
        if (m_controller) {
            if (m_controller->m_count > 0) {
                ++m_controller->m_count;
            }
        }
    }

    void DecControllerCount() {
        if (m_controller) {
            if (m_controller->m_count > 0) {
                --m_controller->m_count;
                if (m_controller->m_count == 0) {
                    Deleter{}(m_p);
                    delete m_controller;
                }
            }
        }
    }

public:

    SharedPtr1st(std::nullptr_t dummy = nullptr) {
        m_p = nullptr;
        m_controller = nullptr;
    }

    explicit SharedPtr1st(T *p) {
        m_p = p;
        m_controller = new SharedControlBlock<T>(1);
    }

    template<class U, class UDeleter> requires (std::convertible_to<U *, T *>) // 有 C++20 的写法
    SharedPtr1st(SharedPtr1st<U, UDeleter> &&that) {  // 从子类型U的智能指针转换到T类型的智能指针
        m_p = exchange(that.m_p, nullptr);
        m_controller = exchange(that.m_controller, nullptr);
    }

    ~SharedPtr1st() {
        release();
    }

    //拷贝
    SharedPtr1st(SharedPtr1st const &that) : m_p(that.m_p), m_controller(that.m_controller) {
        IncControllerCount();
    }

    // 1.需要注意自己赋值自己
    // 2.需要对之前指向的内容进行Dec操作
    // 3.需要对之后指向的内容进行Inc操作
    SharedPtr1st &operator=(SharedPtr1st const &that) {
        //handle self-assignment
        if (m_controller != that.m_controller) {
            release();
            m_p = that.m_p;
            m_controller = that.m_controller;
            IncControllerCount();
        }

        return *this;
    }

    //移动构造
    SharedPtr1st(SharedPtr1st const &&that) {
        m_p = exchange(that.m_p, nullptr);
        m_controller = exchange(that.m_controller, nullptr);
        IncControllerCount();
    }

    //移动赋值
    SharedPtr1st &operator=(SharedPtr1st &&that) {
        if (m_controller != that.m_controller) {
            release();
            m_p = exchange(that.m_p, nullptr);
            m_controller = exchange(that.m_controller, nullptr);
            IncControllerCount();
        }

        return *this;
    }

    T *get() const {
        return m_p;
    }

    T &operator*() const {
        return *m_p;
    }

    // 1. ->是一个递归调用
    T *operator->() const {
        return m_p;
    }

    size_t use_count() const {
        return m_controller ? m_controller->m_count : 0;
    }

    bool unique() const {
        return m_controller && m_controller->m_count == 1;
    }

    //类型转换函数
    //有时能和使用构造函数作为替代，但是对于这个函数来说，只能定义bool类型的转换函数
    explicit operator bool() const noexcept {
        return m_p != nullptr;
    }

    void release() {
        if (m_p) {
            DecControllerCount();
        }
    }

    void reset(T *p) {
        release();
        m_p = p;
        m_controller = new SharedControlBlock<T>(1);
    }

    void swap(SharedPtr1st &that) {
        m_p = exchange(that.m_p, m_p);
        m_controller = exchange(that.m_controller, m_controller);
    }
};

template<typename T, typename ...Args>
SharedPtr1st<T> makeShared(Args &&...args) {
    return SharedPtr1st(new T(std::forward<Args>(args)...));
}
