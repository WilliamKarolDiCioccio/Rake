/*****************************************************************/ /**
 * \file   LinkedList.h
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   March 2022
 *********************************************************************/

#pragma once

#include "Common.def.h"

#include "Core/Tools/Log.inl.hpp"

namespace Rake::Containers
{

template <typename T> class ListNode
{
  public:
    T data;
    U_32 index;
    ListNode<T> *previousNode;
    ListNode<T> *nextNode;

    ListNode()
    {
        index = 0;

        this->nextNode = nullptr;
        this->previousNode = nullptr;
    }
};

template <typename T> class LinkedList
{
  private:
    U_32 m_count;
    const U_32 m_size;
    ListNode<T> *m_head = nullptr;
    ListNode<T> *m_tail = nullptr;

  public:
    LinkedList(U_32 _size)
    {
        m_count = 0;
        m_size = _size;
    }
    ~LinkedList()
    {
        delete (m_head);
        delete (m_tail);
    }

    inline void AddNode(T _item)
    {
        if (m_count < m_size)
        {
            if (m_head == nullptr)
                m_head->data = _item;

            ListNode<T> *temp = new ListNode<T>();

            m_head->nextNode = temp;
            m_head = m_head->nextNode;

            m_count++;
        }
        else
            INFO("List full");
    }

    inline void RemoveNode()
    {
        if (m_head != nullptr)
        {
            m_head = m_head->previousNode;

            delete (m_head->nextNode)
        }
        else
            INFO("List empty");
    }

    inline void AddNodeAt(T _item, U_32 _index)
    {
        if (m_count < m_size)
        {
        }
        else
            INFO("List full");
    }

    inline void RemoveNodeAt(T _item, U_32 _index)
    {
        if (m_head != nullptr)
        {
        }
        else
            INFO("List empty");
    }

    inline void Display() noexcept
    {
        if (m_head != nullptr)
        {
            ListNode<T> *temp = m_head;

            while (temp->previousNode != nullptr)
            {
                std::cout << GetNodeData(temp) << std::endl;

                temp = temp->previousNode;
            }
        }
    }

    inline void Resize(U_32 _newSize) noexcept
    {
        if (m_size < _newSize)
            m_size = _newSize;

        if (m_size > _newSize)
            m_size = m_size - (m_size - _newSize);
    }

    inline ListNode<T> SearchNodeByIndex(B_32 _nodeIndex)
    {
        ListNode<T> *temp = m_head;

        for (m_size != 0; temp->index != _nodeIndex; temp = temp->nextNode)
        {
        }

        return
    }

    inline T GetNodeData(ListNode<T> *_node)
    {
        if (_node != nullptr)
            return _node->data;
    }

    inline U_32 GetCount() const
    {
        return m_count;
    }

    inline U_32 GetSize() const
    {
        return m_size;
    }
};

} // namespace Rake::Containers
