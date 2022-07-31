/*****************************************************************/ /**
 * \file   LinkedList.h
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   March 2022
 *********************************************************************/

#pragma once

#include "Core/Base.hpp"

namespace Rake::Containers
{

template <typename _Type> class LinkedList
{
  private:
    struct Node
    {
        B32 index;
        _Type *data;
        Node *next, *previous;

        Node(Node *_next = nullptr, Node *_previous = nullptr) : next(_next), previous(_previous){};

        Node &operator=(const Node &_oldObj)
        {
            data = _oldObj.data;
            next = _oldObj.next;
            previous = _oldObj.previous;
            return *this;
        }
    };

    U32 m_nodesCount;
    Node *m_head;
    Node *m_tail;

  public:
    LinkedList()
    {
    }
    ~LinkedList()
    {
    }

  public:
    void AddNode(_Type _data)
    {
    }
    void RemoveNode(B32 _index)
    {
    }
};

} // namespace Rake::Containers
