/*****************************************************************/ /**
 * \file   BinaryTree.h
 * \brief  
 * 
 * \author Di Cioccio William Karol
 * \date   March 2022
 *********************************************************************/

#pragma once

#include "Core/Base.hpp"

namespace Rake::Containers
{

template <typename _Type> class BinaryTree
{
  private:
    struct Node
    {
        _Type data;
        Node *childLeft, *childRight;

        Node(Node *_childLeft = nullptr, Node *_childRight = nullptr) : childLeft(_childLeft), childRight(_childRight){};

        Node &operator=(const Node &_oldObj)
        {
            data = _oldObj.data;
            childLeft = _oldObj.childLeft;
            childRight = _oldObj.childRight;
            return *this;
        }
    };

    U32 m_nodesCount;
    U32 m_layersCount;
    Node *m_root;

  public:
    BinaryTree()
    {
        m_nodesCount = 0;
        m_layersCount = 0;
        m_root = nullptr;
    }
    ~BinaryTree()
    {
        delete (m_root);
    }

  public:
    Node *AddNode(_Type _data)
    {
        Node *newNode = new Node();
        newNode->data = _data;
        newNode->childLeft = newNode->childRight = nullptr;

        if (m_root == nullptr)
        {
            m_root = newNode;
            return nullptr;
        }

        ++m_nodesCount;

        return newNode;
    }
    B8 RemoveNode(Node *&_deletedNode, Node *&_newRoot)
    {
        Node *tempLeftChild = _deletedNode->childLeft;
        Node *tempRightChild = _deletedNode->childRight;

        delete (_deletedNode);

        if (tempLeftChild != nullptr)
        {
            if (_newRoot->childLeft == nullptr)
                _newRoot->childLeft = tempLeftChild;
            else
                return false;
        }

        if (tempRightChild != nullptr)
        {
            if (_newRoot->childRight == nullptr)
                _newRoot->childRight = tempRightChild;
            else
                return false;
        }

        --m_nodesCount;

        return true;
    }

  public:
    Node *GetRoot()
    {
        return m_root;
    }
};

} // namespace Rake::Containers
