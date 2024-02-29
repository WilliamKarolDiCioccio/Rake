#pragma once

#include <mutex>
#include <shared_mutex>
#include <functional>
#include <algorithm>
#include <execution>
#include <iterator>

namespace Rake::libraries
{

    template <typename T>
    concept DefaultConstructible = std::is_default_constructible_v<T>;

    /**
     * @brief A memory pool template class for managing memory allocation and deallocation.
     *
     * This container provides iterators pointing to the first and last elements of the MemoryPool,
     * making it compatible with standard library algorithms that operate on iterators.
     *
     * @tparam T The type of elements to be stored in the memory pool.
     *
     * @multithreading Inheritly thread-safe.
     */
    template <DefaultConstructible T>
    class MemoryPool final : public NonCopyable
    {
    private:
        T *m_pool;
        bool *m_inUse;
        size_t m_size, m_capacity;
        std::shared_mutex m_mutex;

    public:
        /**
         * @brief Constructs a MemoryPool with the specified capacity.
         *
         * @param _capacity The initial capacity of the memory pool.
         */
        MemoryPool(size_t _capacity);

        /**
         * @brief Destructor for cleaning up memory pool resources.
         */
        ~MemoryPool();

        /**
         * @brief Move assigment for transferring memory pool resources.
         */
        MemoryPool &operator=(MemoryPool &&_other) noexcept;

        /**
         * @brief Move constructor for transferring memory pool resources.
         */
        MemoryPool(MemoryPool<T> &&_other) noexcept;

        /**
         * @brief Copy assignment for copying memory pool resources.
         */
        MemoryPool &operator=(const MemoryPool &_other) noexcept;

        /**
         * @brief Copy constructor for copying memory pool resources.
         */
        MemoryPool(const MemoryPool<T> &_other) noexcept;

    public:
        /**
         * @brief Copies an object of type T to the memory pool to the first available free offset.
         *
         * @param _data The data to be stored in the allocated memory.
         * @return T* A pointer to the copied object.
         * @throws std::runtime_error if no free offsets are available.
         */
        T *Allocate(const T &_data);

        /**
         * @brief Copies an object of type T to the memory pool to the specified offset.
         *
         * @param _data The data to be stored in the allocated memory.
         * @param _offset The offset at which the object should be copied.
         * @return T* A pointer to the copied object.
         * @throws std::runtime_error if no free offset are available.
         */
        T *AllocateAt(const T &_data, size_t _offset);

        /**
         * @brief Constructs an object of type T using the provided arguments at the first available free offset.
         *
         * @tparam Args The types of the arguments to be forwarded to the constructor.
         * @param _args The arguments to be forwarded to the constructor of type T.
         * @return A pointer to the newly constructed object in the memory pool.
         * @throws std::runtime_error if no free offset are available.
         */
        template <typename... Args>
        T *Construct(Args &&..._args);

        /**
         * @brief Constructs an object of type T using the provided arguments at the specified offset.
         *
         * @tparam Args The types of the arguments to be forwarded to the constructor.
         * @param _offset The offset at which the object should be constructed.
         * @param _args The arguments to be forwarded to the constructor of type T.
         * @return T* A pointer to the newly constructed object at the specified offset.
         * @throws std::runtime_error if no free offset are available.
         */
        template <typename... Args>
        T *ConstructAt(size_t _offset, Args &&..._args);

        /**
         * @brief Deallocates memory for an element in the memory pool.
         *
         * @param _ptr A pointer to the memory to deallocate.
         */
        void Deallocate(T *_ptr) noexcept;

        /**
         * @brief Reallocates data from one offset to another within the memory pool.
         *
         * @param _srcOffset The source offset from which to move data.
         * @param _dstOffset The destination offset to which to move data.
         * @return T* A pointer to the reallocated memory.
         */
        T *Reallocate(size_t _srcOffset, size_t _dstOffset) noexcept;

        /**
         * @brief Shrinks or enlarges the memory pool buffer by hot swapping it with a new one.
         * @param _capacity The new capacity of the buffer.
         *
         * @throw std::bad_alloc if the capacity exceeds size_t numeric limits.
         */
        void Reserve(size_t _capacity);

        /**
         * @brief Compacts the memory pool by moving allocated data to contiguous positions.
         */
        void Compact() noexcept;

        /**
         * @brief Clears the memory pool by zeroing the entre memory block but keeps capacity the same.
         */
        void Clear() noexcept;

        /**
         * @brief Apply a given function to each element in the MemoryPool using the specified execution policy.
         *
         * This function applies a given function to each element in the MemoryPool using the provided execution policy.
         * The function must take a reference to an element of type T as its argument.
         *
         * @note The function should not modify the size or capacity of the MemoryPool or change the elements offsets.
         * @note This function is the only thread-safe way to iterate over and modify the values in the MemoryPool container.
         *
         * @tparam ExPo The execution policy to control how the function is parallelized.
         * @param _policy An execution policy object that specifies the parallelism strategy.
         * @param _function A callable object that represents the function to be applied to each element.
         */
        template <class ExPo>
        void Map(ExPo &&_policy, std::function<void(T &)> &&_function);

    public:
        /**
         * @brief Accesses an element in the memory pool by its offset.
         *
         * @param _offset The offset of the element to access.
         * @return T& A reference to the accessed element.
         * @throw std::out_of_range if the index is out of range.
         */
        NODISCARD inline T &operator[](size_t _offset)
        {
            std::shared_lock<std::shared_mutex> readLock(m_mutex);

            if (_offset < m_capacity)
                return m_pool[_offset];
            else
                throw std::out_of_range("Index out of range!");
        };

        /**
         * @brief Gets the total size of the memory pool in bytes.
         *
         * @return size_t The total size of the memory pool.
         */
        NODISCARD inline size_t GetPoolSize() const noexcept { return m_capacity * sizeof(T); };

        /**
         * @brief Gets the amount of free memory in the memory pool in bytes.
         *
         * @return size_t The amount of free memory.
         */
        NODISCARD inline size_t GetFreeMemory() const noexcept { return GetPoolSize() - (m_size * sizeof(T)); };

        /**
         * @brief Gets the current number of allocated offsets in the memory pool.
         *
         * @return size_t The number of allocated offsets.
         */
        NODISCARD inline size_t size() const noexcept { return m_size; };

        /**
         * @brief Gets the number of available offsets in the memory pool.
         *
         * @return size_t The number of available offsets.
         */
        NODISCARD inline size_t capacity() const noexcept { return m_capacity; };
    };

    template <DefaultConstructible T>
    MemoryPool<T>::MemoryPool(size_t _capacity) : m_capacity(_capacity), m_size(0)
    {
        m_pool = new T[m_capacity];
        std::memset(m_pool, NULL, sizeof(T) * m_capacity);
        m_inUse = new bool[m_capacity];
        std::memset(m_inUse, false, sizeof(bool) * m_capacity);
    };

    template <DefaultConstructible T>
    MemoryPool<T>::~MemoryPool()
    {
        delete[] (m_pool);
        delete[] (m_inUse);
    }

    template <DefaultConstructible T>
    MemoryPool<T> &MemoryPool<T>::operator=(MemoryPool &&_other) noexcept
    {
        if (this == &_other)
            return *this;

        m_capacity = _other.m_capacity;
        m_size = _other.m_size;
        _other.m_capacity = 0;
        _other.m_size = 0;

        delete[] m_inUse;
        delete[] m_pool;

        std::swap(m_inUse, _other.m_inUse);
        std::swap(m_pool, _other.m_pool);

        return *this;
    }

    template <DefaultConstructible T>
    MemoryPool<T>::MemoryPool(MemoryPool<T> &&_other) noexcept : m_capacity(_other.m_capacity), m_size(_other.m_size)
    {
        _other.m_capacity = 0;
        _other.m_size = 0;

        delete[] m_inUse;
        delete[] m_pool;

        std::swap(m_inUse, _other.m_inUse);
        std::swap(m_pool, _other.m_pool);
    }

    template <DefaultConstructible T>
    MemoryPool<T> &MemoryPool<T>::operator=(const MemoryPool<T> &_other) noexcept
    {
        if (this == &_other)
            return *this;

        delete[] m_inUse;
        delete[] m_pool;

        m_capacity = _other.m_capacity;
        m_size = _other.m_size;
        m_inUse = new bool[m_capacity];
        m_pool = new T[m_capacity];

        std::memcpy(m_inUse, _other.m_inUse, m_capacity * sizeof(bool));
        std::memcpy(m_pool, _other.m_pool, m_capacity * sizeof(T));

        return *this;
    }

    template <DefaultConstructible T>
    MemoryPool<T>::MemoryPool(const MemoryPool<T> &_other) noexcept
        : m_capacity(_other.m_capacity),
          m_size(_other.m_size),
          m_pool(new T[_other.m_capacity]),
          m_inUse(new bool[_other.m_capacity])
    {
        std::memcpy(m_inUse, _other.m_inUse, m_capacity * sizeof(bool));
        std::memcpy(m_pool, _other.m_pool, m_capacity * sizeof(T));
    }

    template <DefaultConstructible T>
    T *MemoryPool<T>::Allocate(const T &_data)
    {
        std::unique_lock<std::shared_mutex> writeLock(m_mutex);

        if (m_size >= m_capacity)
            throw std::runtime_error("No free offsets available in the memory pool.");

        for (size_t i = 0; i < m_capacity; ++i)
        {
            if (m_inUse[i])
                continue;

            m_inUse[i] = true;
            m_pool[i] = _data;
            m_size++;

            return &m_pool[i];
        }
    }

    template <DefaultConstructible T>
    T *MemoryPool<T>::AllocateAt(const T &_data, size_t _offset)
    {
        std::unique_lock<std::shared_mutex> writeLock(m_mutex);

        if (_offset >= m_capacity)
            throw std::out_of_range("Offset out of range!");
        else if (m_size >= m_capacity)
            throw std::runtime_error("No free offsets available in the memory pool.");
        else if (m_inUse[_offset])
            throw std::runtime_error("Memory at index " + std::to_string(_offset) + " already in use!");

        m_inUse[_offset] = true;
        m_pool[_offset] = _data;
        m_size++;

        return &m_pool[_offset];
    }

    template <DefaultConstructible T>
    template <typename... Args>
    T *MemoryPool<T>::Construct(Args &&..._args)
    {
        std::unique_lock<std::shared_mutex> writeLock(m_mutex);

        if (m_size >= m_capacity)
            throw std::runtime_error("No free offsets available in the memory pool.");

        for (size_t i = 0; i < m_capacity; ++i)
        {
            if (m_inUse[i])
                continue;

            m_inUse[i] = true;
            new (&m_pool[i]) T(std::forward<Args>(_args)...);
            m_size++;

            return &m_pool[i];
        }
    }

    template <DefaultConstructible T>
    template <typename... Args>
    T *MemoryPool<T>::ConstructAt(size_t _offset, Args &&..._args)
    {
        std::unique_lock<std::shared_mutex> writeLock(m_mutex);

        if (_offset >= m_capacity)
            throw std::out_of_range("Offset out of range!");
        else if (m_size >= m_capacity)
            throw std::runtime_error("No free offsets available in the memory pool.");
        else if (m_inUse[_offset])
            throw std::runtime_error("Memory at index " + std::to_string(_offset) + " already in use!");

        m_inUse[_offset] = true;
        new (&m_pool[_offset]) T(std::forward<Args>(_args)...);
        m_size++;

        return &m_pool[_offset];
    }

    template <DefaultConstructible T>
    void MemoryPool<T>::Deallocate(T *_ptr) noexcept
    {
        std::unique_lock<std::shared_mutex> writeLock(m_mutex);

        if (_ptr && _ptr >= m_pool && _ptr < m_pool + m_capacity)
        {
            size_t offset = _ptr - m_pool;

            if (offset < m_capacity && m_inUse[offset])
            {
                m_inUse[offset] = false;
                m_size--;
            }
        }
    }

    template <DefaultConstructible T>
    T *MemoryPool<T>::Reallocate(size_t _srcOffset, size_t _dstOffset) noexcept
    {
        std::unique_lock<std::shared_mutex> writeLock(m_mutex);

        if (_srcOffset > m_capacity || _dstOffset > m_capacity)
            throw std::out_of_range("Offset out of range!");
        else if (!m_inUse[_srcOffset] && m_inUse[_dstOffset])
            throw std::runtime_error("Memory at index " + std::to_string(_dstOffset) + " already in use!");

        m_pool[_dstOffset] = std::move(m_pool[_srcOffset]);
        m_inUse[_dstOffset] = true;
        m_inUse[_srcOffset] = false;

        return &m_pool[_dstOffset];
    }

    template <DefaultConstructible T>
    void MemoryPool<T>::Reserve(size_t _capacity)
    {
        std::unique_lock<std::shared_mutex> writeLock(m_mutex);

        if (_capacity > std::numeric_limits<size_t>::max() / sizeof(T))
            throw std::bad_alloc();

        T *newPool = new T[_capacity];
        std::memset(newPool, NULL, sizeof(T) * _capacity);
        bool *newInUse = new bool[_capacity];
        std::memset(newInUse, false, sizeof(bool) * _capacity);

        const size_t totalPoolSize = m_size * sizeof(T);
        const size_t elementsToCopy = std::min(m_size, _capacity);

        std::memcpy(newPool, m_pool, elementsToCopy * sizeof(T));
        std::memcpy(newInUse, m_inUse, elementsToCopy * sizeof(bool));

        std::swap(m_pool, newPool);
        std::swap(m_inUse, newInUse);

        delete[] newPool;
        delete[] newInUse;

        m_capacity = _capacity;
        m_size = elementsToCopy;
    }

    template <DefaultConstructible T>
    void MemoryPool<T>::Compact() noexcept
    {
        size_t nextFreeSlot = 0;

        for (size_t i = 0; i < m_capacity; ++i)
        {
            if (!m_inUse[i])
            {
                continue;
            }

            if (i != nextFreeSlot)
            {
                m_pool[nextFreeSlot] = std::move(m_pool[i]);
                m_inUse[nextFreeSlot] = true;
                m_inUse[i] = false;
            }

            ++nextFreeSlot;
        }
    }

    template <DefaultConstructible T>
    void MemoryPool<T>::Clear() noexcept
    {
        std::memset(m_pool, NULL, sizeof(T) * m_capacity);
        std::memset(m_inUse, false, sizeof(bool) * m_capacity);

        m_size = 0;
    }

    template <DefaultConstructible T>
    template <class ExPo>
    void MemoryPool<T>::Map(ExPo &&_policy, std::function<void(T &)> &&_function)
    {
        std::unique_lock<std::shared_mutex> lock(m_mutex);

        std::for_each(_policy, m_pool, m_pool + m_size, _function);
    }

} // namespace Rake::libraries
