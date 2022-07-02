/*****************************************************************/ /**
 * \file   LinkedList.h
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   March 2022
 *********************************************************************/

#pragma once

#include "Core/Base.hpp"
#include "Tools/Log.hpp"

namespace Rake::Containers
{

template <typename T> class ListNode
{
  public:
    T data;
    U32 index = NULL;
    ListNode<T> *previousNode;
    ListNode<T> *nextNode;

    ListNode() : previousNode(nullptr), nextNode(nullptr){};
};

template <typename T> class LinkedList
{
  private:
    U32 m_count = NULL;
    U32 m_size = NULL;
    ListNode<T> *m_head = new ListNode<T>();
    ListNode<T> *m_tail = new ListNode<T>();

  public:
    LinkedList(const U32 _size) : m_size(_size){};
    ~LinkedList()
    {
        delete (m_head);
        delete (m_tail);
    }

    inline void AddNode(const T _item)
    {
        if (m_count < m_size)
        {
            ListNode<T> *temp = new ListNode<T>();

            while (temp->nextNode != nullptr)
                temp = temp->nextNode;

            temp->data = _item;
            temp->index = m_count;

            m_count++;
        }
    }

    inline void RemoveNode()
    {
        if (m_head != nullptr)
        {
            m_count--;
        }
    }

    inline void AddNodeAt(const T _item, const U32 _index)
    {
        if (m_count < m_size)
        {
        }
    }

    inline void RemoveNodeAt(const T _item, const U32 _index)
    {
        if (m_head != nullptr)
        {
        }
    }

    inline void Display() noexcept
    {
        if (m_head != nullptr)
        {
            ListNode<T> *temp = m_head;

            do
            {
                std::cout << temp->data << std::endl;
                temp = temp->nextNode;
            } while (m_tempNode->nextNode != nullptr);
        }
    }

    inline void Resize(const U32 _newSize) noexcept
    {
        if (_newSize >= m_size)
            m_size = _newSize;
        else if (_newSize < m_size)
        {
        }
    }

    inline ListNode<T> GetNode(const U32 _index)
    {
        ListNode<T> *temp = m_head;

        for (U32 i = 1; i <= _index, temp->nextNode != nullptr; i++)
            temp = temp->nextNode;

        return temp;
    }

    inline void SetNodeData(const T _item, const U32 _index)
    {
        ListNode<T> *temp = m_head;

        for (U32 i = 1; i <= _index, temp->nextNode != nullptr; i++)
            temp = temp->nextNode;

        temp->data = _item;
    }

    inline U32 GetCount() const
    {
        return m_count;
    }

    inline U32 GetSize() const
    {
        return m_size;
    }
};

} // namespace Rake::Containers
