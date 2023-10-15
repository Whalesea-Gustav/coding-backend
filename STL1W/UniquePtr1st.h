#pragma once

#include <cstdio>
#include <utility>
#include <concepts>

template<typename T>
class DefaultDeletor {
    void operator()(T *p) const {
        delete p;
    }
};

//针对数组的偏特化
template<typename T>
class DefaultDeletor<T[]> {
    void operator()(T *p) const {
        delete[] p;
    }
};

//针对单独类型的全特化
template<>
class DefaultDeletor<FILE> {
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


template<typename T, typename Deletor = DefaultDeletor<T>>
class UniquePtr1st {
    private:
        T* m_p;

    template<typename U, typename UDeletor>
    friend class UniquePtr1st;

    public:

        //默认构造处理nullptr
        UniquePtr1st(std::nullptr_t dummy = nullptr)
        {
            m_p = nullptr;
        }

        //显式的指针构造
        explicit UniquePtr1st(T* p = nullptr)
        {
            m_p = p;
        }

        ~UniquePtr1st() { // 析构函数
            if (m_p)
                Deletor{}(m_p);
        }

        //删除拷贝构造，赋值
        UniquePtr1st(UniquePtr1st const &  that) = delete;
        UniquePtr1st& operator=(UniquePtr1st const & that) = delete;

        UniquePtr1st(UniquePtr1st && that)
        {
            m_p = exchange(that, nullptr);
        }

        UniquePtr1st& operator=(UniquePtr1st && that)
        {
            if(m_p)
            {
                Deletor{}(m_p);
            }
            m_p = exchange(that, nullptr);

            return *this;
        }

        T* get() const
        {
            return m_p;
        }

        T* release() const
        {
            return exchange(m_p, nullptr);
        }

        void reset(T* p = nullptr)
        {
            if(m_p)
                Deletor{}(m_p);
            m_p = p;
        }

        T& operator*() const
        {
            return *m_p;
        }

        T* operator->() const
        {
            return m_p;
        }
};

//只有在定义模板变参时，...放在变参名前面，表示"定义"
template<typename T, typename ...Args>
UniquePtr1st<T> makeUnique(Args ...args)
{
    return UniquePtr1st<T>(new T(std::forward<Args>(args)...));
}