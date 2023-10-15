#include <cstdio>
#include <utility>
#include <concepts>

template <class T>
struct DefaultDeleter { // 默认使用 delete 释放内存
    void operator()(T *p) const {
        delete p;
    }
};

template <class T>
struct DefaultDeleter<T[]> { // 偏特化
    void operator()(T *p) const {
        delete[] p;
    }
};

template <>
struct DefaultDeleter<FILE> { // 全特化
    void operator()(FILE *p) const {
        fclose(p);
    }
};

template <class T, class U>
T exchange(T &dst, U &&val) { // 同标准库的 std::exchange
    T tmp = std::move(dst);
    dst = std::forward<U>(val);
    return tmp;
}

template <class T, class Deleter = DefaultDeleter<T>>
struct UniquePtr {
private:
    T *m_p;

    template <class U, class UDeleter>
    friend struct UniquePtr;

public:
    UniquePtr(std::nullptr_t dummy = nullptr) { // 默认构造函数
        m_p = nullptr;
    }

    explicit UniquePtr(T *p) { // 自定义构造函数
        m_p = p;
    }

    template <class U, class UDeleter, class = std::enable_if_t<std::is_convertible_v<U *, T *>>> // 没有 C++20 的写法
    //template <class U, class UDeleter> requires (std::convertible_to<U *, T *>) // 有 C++20 的写法
    UniquePtr(UniquePtr<U, UDeleter> &&that) {  // 从子类型U的智能指针转换到T类型的智能指针
        m_p = exchange(that.m_p, nullptr);
    }

    ~UniquePtr() { // 析构函数
        if (m_p)
            Deleter{}(m_p);
    }

    // 删除两个拷贝
    UniquePtr(UniquePtr const &that) = delete; // 拷贝构造函数
    UniquePtr &operator=(UniquePtr const &that) = delete; // 拷贝赋值函数


    // 移动构造中对资源所有权进行转移
    UniquePtr(UniquePtr &&that) { // 移动构造函数
        m_p = exchange(that.m_p, nullptr);
    }

    UniquePtr &operator=(UniquePtr &&that) { // 移动赋值函数
        if (this != &that) [[likely]] {
            if (m_p)
                Deleter{}(m_p);
            m_p = exchange(that.m_p, nullptr);
        }
        return *this;
    }
    // }}}

    T *get() const {
        return m_p;
    }

    //归还所有权
    T *release() {
        return exchange(m_p, nullptr);
    }

    void reset(T *p = nullptr) {
        if (m_p)
            Deleter{}(m_p);
        m_p = p;
    }

    T &operator*() const {
        return *m_p;
    }

    //-> 操作符是递归调用
    T *operator->() const {
        return m_p;
    }
};

template <class T, class Deleter>
struct UniquePtr<T[], Deleter> : UniquePtr<T, Deleter> {};

template <class T, class ...Args>
UniquePtr<T> makeUnique(Args &&...args) {
    return UniquePtr<T>(new T(std::forward<Args>(args)...));
}

template <class T>
UniquePtr<T> makeUniqueForOverwrite() {
    return UniquePtr<T>(new T);
}