//
//  Node.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 08/09/13.
//
//

#ifndef __CVATools__Node__
#define __CVATools__Node__

#include <iostream>
#include "Variant.h"

namespace Utilities
{
    struct tree
    {
        int info;
        tree *Left, *Right;
    };
    
    class Binary_tree
    {
    protected:
        tree *root;
        
    public:
        Binary_tree();
        void insert1(int);
        tree *insert2(tree *, tree *);
        void Delete(int);
        void pretrav(tree *);
        void intrav(tree *);
        void posttrav(tree *);
    };
    
    void printLevelOrder(tree *root);
}

#endif /* defined(__CVATools__Node__) */
