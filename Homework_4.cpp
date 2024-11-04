#include <iostream>
#include <utility> 

template<typename T>
class UniqPtr
{
private:
    T* ptr; 

public:
    // Конструктор по умолчанию
    UniqPtr() : ptr(nullptr) {}

    // Конструктор с указателем
    explicit UniqPtr(T* p) : ptr(p) {}

    // Запрет копирования
    UniqPtr(const UniqPtr&) = delete;
    UniqPtr& operator=(const UniqPtr&) = delete;

    // Перемещение
    UniqPtr(UniqPtr&& other) noexcept : ptr(other.ptr)
    {
        other.ptr = nullptr; 
    }

    UniqPtr& operator=(UniqPtr&& other) noexcept
    {
        if (this != &other)
        {
            delete ptr; 
            ptr = other.ptr; 
            other.ptr = nullptr; 
        }
        return *this;
    }

    // Деструктор
    ~UniqPtr() 
    {
        delete ptr; 
    }

    // Метод swap
    void swap(UniqPtr& other)
    {
        std::swap(ptr, other.ptr);
    }

    // Метод free
    void free()
    {
        delete ptr; 
        ptr = nullptr;
    }

    // Метод release
    T* relise()
    {
        T* temp = ptr; 
        ptr = nullptr; 
        return temp; 
    }

    // Оператор разыменования
    T& operator*() const 
    {
        return *ptr;
    }

    // Оператор доступа к члену
    T* operator->() const 
    {
        return ptr;
    }

    // Проверка на наличие объекта
    explicit operator bool() const
    {
        return ptr != nullptr;
    }
};


int main()
{
    UniqPtr<int> ptr1(new int(42));
    std::cout << *ptr1; 

    UniqPtr<int> ptr2 = std::move(ptr1);
    std::cout << *ptr2;

    ptr2.free(); 

    return 0;
}
