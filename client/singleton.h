#ifndef SINGLETON_H
#define SINGLETON_H

// Для использования необходимо унаследоваться от этого класса с модификатором public,
// сделать конструкторы и деструкторы приватными и прописать
// friend class Singleton<ClassName>

template <class T> class Singleton
{
    protected:
        static inline T * p_instance = nullptr;
        Singleton();
        Singleton(const Singleton& );
        Singleton& operator = (Singleton &);
    public:
        static T* getInstance();
};

// Определение в заголовочном файле, так как этого требует шаблонная функция.

template<class T>
Singleton<T>::Singleton()
{

}

template<class T>
T* Singleton<T>::getInstance()
{
    if (!p_instance)
        p_instance = new T();
    return p_instance;
}

#endif // SINGLETON_H
