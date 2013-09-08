//
//  Node.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 08/09/13.
//
//

#include "Node.h"

namespace Utilities
{
    Binary_tree::Binary_tree()
    {
        root = NULL;
    }
    
    tree* Binary_tree::insert2(tree *temp,tree *newnode)
    {
        if(temp==NULL)
        {
            temp=newnode;
        }
        else if(temp->info < newnode->info)
        {
            insert2(temp->Right,newnode);
            if(temp->Right==NULL)
                temp->Right=newnode;
        }
        else
        {
            insert2(temp->Left,newnode);
            if(temp->Left==NULL)
                temp->Left=newnode;
        }
        return temp;
    }
    
    void Binary_tree::insert1(int n)
    {
        tree *temp=root,*newnode;
        newnode=new tree;
        newnode->Left=NULL;
        newnode->Right=NULL;
        newnode->info=n;
        root=insert2(temp,newnode);
    }
    
    void Binary_tree::pretrav(tree *t)
    {
        if(root == NULL)
        {
            std::cout<<"Nothing to display";
        }
        else
            if(t != NULL)
            {
                std::cout<<t->info<<" ";
                pretrav(t->Left);
                pretrav(t->Right);
            }
    }
    
    void Binary_tree::intrav(tree *t)
    {
        if(root==NULL)
        {
            std::cout<<"Nothing to display";
        }
        else
            if(t!=NULL)
            {
                intrav(t->Left);
                std::cout<<t->info<<" ";
                intrav(t->Right);
            }
    }
    void Binary_tree::posttrav(tree *t)
    {
        if(root==NULL)
        {
            std::cout<<"Nothing to display";
        }
        else
            if(t!=NULL)
            {
                posttrav(t->Left);
                posttrav(t->Right);
                std::cout<<t->info<<" ";
            }
    }
    void Binary_tree::Delete(int key)
    {
        tree *temp = root,*parent = root, *marker;
        if(temp==NULL)
            std::cout<<"The tree is empty"<<std::endl;
        else
        {
            while(temp!=NULL && temp->info!=key)
            {
                parent=temp;
                if(temp->info<key)
                {
                    temp=temp->Right;
                }
                else
                {
                    temp=temp->Left;
                }
            }
        }
        
        marker=temp;
        if(temp==NULL)
            std::cout<<"No node present";
        else if(temp==root)
        {
            if(temp->Right==NULL && temp->Left==NULL)
            {
                root=NULL;
            }
            else if(temp->Left==NULL)
            {
                root=temp->Right;
            }
            else if(temp->Right==NULL)
            {
                root=temp->Left;
            }
            else
            {
                tree *temp1;
                temp1 = temp->Right;
                while(temp1->Left!=NULL)
                {
                    temp=temp1;
                    temp1=temp1->Left;
                }
                if(temp1!=temp->Right)
                {
                    temp->Left=temp1->Right;
                    temp1->Right=root->Right;
                }
                temp1->Left=root->Left;
                root=temp1;
            }
        }
        else
        {
            if(temp->Right==NULL && temp->Left==NULL)
            {
                if(parent->Right==temp)
                    parent->Right=NULL;
                else
                    parent->Left=NULL;
            }
            else if(temp->Left==NULL)
            {
                if(parent->Right==temp)
                    parent->Right=temp->Right;
                else
                    parent->Left=temp->Right;
            }
            else if(temp->Right==NULL)
            {
                if(parent->Right==temp)
                    parent->Right=temp->Left;
                else
                    parent->Left=temp->Left;
            }
            else
            {
                tree *temp1;
                parent=temp;
                temp1=temp->Right;
                while(temp1->Left!=NULL)
                {
                    parent=temp1;
                    temp1=temp1->Left;
                }
                if(temp1!=temp->Right)
                {
                    temp->Left=temp1->Right;
                    temp1->Right=parent->Right;
                }
                temp1->Left=parent->Left;
                parent=temp1;
            }
        }
        delete marker;
    }

}