#pragma once

#include "base.hpp"

#include "pool.hpp"

namespace Rake::libraries {

/**
 * @brief A doubly linked list container class.
 * 
 * This class provides a doubly linked list data structure for storing elements of type T.
 * It allows for efficient insertion and removal of elements at both ends of the list.
 * The list is managed using a MemoryPool for memory efficiency.
 *
 * @tparam T The type of elements to be stored in the list.
 * 
 * @multithreading Inheritly thread-safe.
 */
template <typename T>
class DoublyLinkedList {
   private:
    struct Node {
        Node *next, *prev;
        size_t index;
        T data;

        Node() : data(T{}), prev(nullptr), next(nullptr), index(0) {}
        Node(T _data) : data(_data), prev(nullptr), next(nullptr), index(0) {}
        Node(T _data, Node *_prev, Node *_next, size_t _index) : data(_data), prev(_prev), next(_next), index(_index) {}
    };

    Node *m_head, *m_tail;
    MemoryPool<Node> m_pool;

   public:
    /**
     * @brief Iterator for traversing the DoublyLinkedList.
     */
    class Iterator final : public std::iterator<std::bidirectional_iterator_tag, T> {
       private:
        Node *m_node;

       public:
        explicit Iterator(Node *_node) : m_node(_node) {}

        Iterator &operator+(size_t _iters) {
            if (_iters == 0) return *this;

            Iterator it(*this);

            while (_iters) {
                if (!it.m_node->next) throw std::out_of_range("Iterator out of range!");

                ++it;
                --_iters;
            }

            return it;
        }

        Iterator &operator-(size_t _iters) {
            if (_iters == 0) return *this;

            Iterator it(*this);

            while (_iters) {
                if (!it.m_node->prev) throw std::out_of_range("Iterator out of range!");

                --it;
                --_iters;
            }

            return it;
        }

        Iterator &operator++() {
            m_node = m_node->next;
            return *this;
        }

        Iterator &operator--() {
            m_node = m_node->prev;
            return *this;
        }

        NODISCARD inline bool operator+(const Iterator &_other) const { return m_node + _other.m_node; }
        NODISCARD inline bool operator-(const Iterator &_other) const { return m_node - _other.m_node; }
        NODISCARD inline bool operator==(const Iterator &_other) const { return m_node == _other.m_node; }
        NODISCARD inline bool operator!=(const Iterator &_other) const { return !(*this == _other); }
        NODISCARD inline bool operator<(const Iterator &_other) const { return m_node < _other.m_node; }
        NODISCARD inline bool operator>(const Iterator &_other) const { return m_node > _other.m_node; }
        NODISCARD inline bool operator<=(const Iterator &_other) const { return m_node <= _other.m_node; }
        NODISCARD inline bool operator>=(const Iterator &_other) const { return m_node >= _other.m_node; }

        NODISCARD T &operator*() const {
            if (!m_node) throw std::out_of_range("Dereferencing end() or rend() iterator.");

            return m_node->data;
        }

        NODISCARD Node *GetNode() const noexcept { return m_node; }
    };

   public:
    /**
     * @brief Constructs a DoublyLinkedList with the given capacity.
     *
     * @param _capacity The initial capacity of the list.
     */
    DoublyLinkedList(size_t _capacity);

    /**
     * @brief Destroys the DoublyLinkedList and releases allocated memory.
     */
    DoublyLinkedList(MemoryPool<T> &_pool);

    /**
     * @brief Constructs a DoublyLinkedList using the provided MemoryPool.
     *
     * @param _pool A MemoryPool object to manage the list's memory.
     */
    ~DoublyLinkedList();

   public:
    /**
     * @brief Appends an element to the end of the list.
     *
     * @param _data The element to be added to the end of the list.
     * @return Node* A pointer to the node.
     */
    template <typename... Args>
    Node *PushBack(const T &_data);

    /**
     * @brief Prepends an element to the beginning of the list.
     *
     * @param _data The element to be added to the beginning of the list.
     * @return Node* A pointer to the node.
     */
    template <typename... Args>
    Node *PushFront(const T &_data);

    /**
     * @brief Constructs an object of type T in place and appends it to the end of the list.
     *
     * @tparam Args The types of arguments to be forwarded to the constructor of type T.
     * @param _args The arguments to be forwarded to the constructor of type T.
     * @return Node* A pointer to the node.
     * @throws std::bad_alloc if memory allocation fails.
     */
    template <typename... Args>
    Node *EmplaceBack(Args &&..._args);

    /**
     * @brief Constructs an object of type T in place and prepends it to the beginning of the list.
     *
     * @tparam Args The types of arguments to be forwarded to the constructor of type T.
     * @param _args The arguments to be forwarded to the constructor of type T.
     * @return Node* A pointer to the node.
     * @throws std::bad_alloc if memory allocation fails.
     */
    template <typename... Args>
    Node *EmplaceFront(Args &&..._args);

    /**
     * @brief Inserts an element before the specified position in the list.
     *
     * @param _pos The position before which the element will be inserted.
     * @param _data The element to be inserted.
     */
    void Insert(Iterator _pos, const T &_data);

    /**
     * @brief Removes the element at the specified position from the list.
     *
     * @param _pos The position of the element to be removed.
     */
    void Erase(Iterator _pos);

    /**
     * @brief Clears all elements from the list.
     */
    void Clear() noexcept;

    /**
     * @brief Reserves memory for a specified capacity.
     *
     * @throws std::bad_alloc if memory allocation fails.
     */
    inline void Reserve(size_t _capacity);

    /**
     * @brief Compacts all the elements from the list and shrinks the pool.
     */
    void ShrinkToFit();

   public:
    NODISCARD inline size_t size() noexcept { return m_pool.size(); }

    NODISCARD inline size_t capacity() noexcept { return m_pool.capacity(); }

    NODISCARD inline Iterator begin() noexcept { return Iterator(m_head); }

    NODISCARD inline const Iterator cbegin() const noexcept { return Iterator(m_head); }

    NODISCARD inline Iterator end() noexcept { return Iterator(nullptr); }

    NODISCARD inline const Iterator cend() const noexcept { return Iterator(nullptr); }

    NODISCARD inline Iterator rbegin() noexcept { return Iterator(m_tail); }

    NODISCARD inline const Iterator crbegin() const noexcept { return Iterator(m_tail); }

    NODISCARD inline Iterator rend() noexcept { return Iterator(nullptr); }

    NODISCARD inline const Iterator crend() const noexcept { return Iterator(nullptr); }
};

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(size_t _capacity) : m_head(nullptr), m_tail(nullptr), m_pool(_capacity) {}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(MemoryPool<T> &_pool) : m_head(nullptr), m_tail(nullptr), m_pool(_pool) {}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    Node *current = m_head;
    while (current != nullptr) {
        Node *next = current->next;
        m_pool.Deallocate(current);
        current = next;
    }
}

template <typename T>
template <typename... Args>
DoublyLinkedList<T>::Node *DoublyLinkedList<T>::PushBack(const T &_data) {
    return EmplaceBack(_data);
}

template <typename T>
template <typename... Args>
DoublyLinkedList<T>::Node *DoublyLinkedList<T>::PushFront(const T &_data) {
    return EmplaceFront(_data);
}

template <typename T>
template <typename... Args>
DoublyLinkedList<T>::Node *DoublyLinkedList<T>::EmplaceBack(Args &&..._args) {
    try {
        Node *newNode = m_pool.Construct(std::forward<Args>(_args)...);

        if (!m_tail) {
            m_head = m_tail = newNode;
        } else {
            newNode->prev = m_tail;
            m_tail->next = newNode;
            m_tail = newNode;
        }

        return newNode;
    } catch (const std::exception &ex) {
        throw ex;
    }
}

template <typename T>
template <typename... Args>
DoublyLinkedList<T>::Node *DoublyLinkedList<T>::EmplaceFront(Args &&..._args) {
    try {
        Node *newNode = m_pool.Construct(std::forward<Args>(_args)...);

        if (!m_head) {
            m_head = m_tail = newNode;
        } else {
            newNode->next = m_head;
            m_head->prev = newNode;
            m_head = newNode;
        }

        return newNode;
    } catch (const std::exception &ex) {
        throw ex;
    }
}

template <typename T>
void DoublyLinkedList<T>::Insert(Iterator _pos, const T &_data) {
    if (_pos.GetNode() == m_head) {
        PushFront(_data);
    } else if (_pos.GetNode() == nullptr) {
        PushBack(_data);
    } else {
        Node *prevNode = _pos.GetNode()->prev;
        Node *nextNode = _pos.GetNode();

        Node *newNode = m_pool.Allocate(Node(_data, prevNode, _pos.GetNode(), prevNode->index + 1));

        prevNode->next = newNode;
        _pos.GetNode()->prev = newNode;

        while (_pos.GetNode()) {
            _pos.GetNode()->index++;
            ++_pos;
        }
    }
}

template <typename T>
void DoublyLinkedList<T>::Erase(Iterator _pos) {
    Node *node = _pos.GetNode();

    if (node->prev) node->prev->next = node->next;
    if (node->next) node->next->prev = node->prev;

    if (node == m_head)
        m_head = node->next;
    else if (node == m_tail)
        m_tail = node->prev;

    m_pool.Deallocate(node);
}

template <typename T>
void DoublyLinkedList<T>::Clear() noexcept {
    m_pool.Clear();

    m_head = m_tail = nullptr;
}

template <typename T>
void DoublyLinkedList<T>::Reserve(size_t _capacity) {
    try {
        m_pool.Reserve(_capacity);
    } catch (const std::bad_alloc &ex) {
        throw ex;
    }
}

template <typename T>
void DoublyLinkedList<T>::ShrinkToFit() {
    try {
        m_pool.Compact();

        Reserve(m_pool.size());
    } catch (const std::exception &ex) {
        throw ex;
    }
}

}  // namespace Rake::libraries
