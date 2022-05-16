/*****************************************************************/ /**
 * \file   BinaryTree.h
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

class TreeNode
{
    TreeNode *left;
    TreeNode *right;
    TreeNode *parent;

    U_32 nodeIndex;
};

class Tree
{
  public:
  private:
    TreeNode *root;
    TreeNode *pastNode;

    U_32 index;
};

} // namespace Rake::Containers
