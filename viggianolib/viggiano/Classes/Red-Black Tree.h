#pragma once
#include<iostream>
#include"Stacks_Queues.h"
#define RED 1
#define BLACK 0
namespace mpv{
    template<typename T>
    class Tree{
        private:
            struct Node{
                T data;
                Node* left=nullptr;
                Node* right=nullptr;
                Node* prev=nullptr;
                bool color=RED;
                Node(T dat,bool color=RED):data(dat),color(color){}
                Node(){}
            };
            Node* root;
            Node TNULL;
            void clr(Node* node){
                if(node==&TNULL)
                    return;
                else{
                    clr(node->left);
                    clr(node->right);
                    delete node;
                }
            }
            void pre_order(Node* node){
                if(node==&TNULL)
                    return;
                std::cout<<node->data<<',';
                pre_order(node->left);
                pre_order(node->right);
            }
            void in_order(Node* node){
                if(node==&TNULL)
                    return;
                in_order(node->left);
                std::cout<<node->data<<',';
                in_order(node->right);
            }
            void post_order(Node* node){
                if(node==&TNULL)
                    return;
                post_order(node->left);
                post_order(node->right);
                std::cout<<node->data<<',';
            }
            void insert_fixup(Node* x){
                while(x->prev!=nullptr and x->prev->color==RED){
                    if(x->prev==x->prev->prev->left){															//If the father is a left node
                        if(x->prev->prev->right->color==RED){				//case 1:X.uncle==RED
                            x->prev->color=BLACK;
                            x->prev->prev->right->color=BLACK;
                            x->prev->prev->color=RED;
                            x=x->prev->prev;
                        }
                        else/*(x->prev->prev->right->color==BLACK)*/{			//case 2 & 3:x.uncle==BLACK
                            if(x==x->prev->right){																//case 2:(triangle)
                                x=x->prev;
                                left_rotate(x);
                            }
                            x->prev->color=BLACK;																//case 3:(line)
                            x->prev->prev->color=RED;
                            right_rotate(x->prev->prev);
                        }
                    }
                    else{																						//If the father is a right node
                        if(x->prev->prev->left->color==RED){					//case 1:X.uncle==RED
                            x->prev->color=BLACK;
                            x->prev->prev->left->color=BLACK;
                            x->prev->prev->color=RED;
                            x=x->prev->prev;
                        }
                        else/*(x->prev->prev->left->color==BLACK)*/{			//case 2 & 3:x.uncle==BLACK
                            if(x==x->prev->left){																//case 2:(triangle)
                                x=x->prev;
                                right_rotate(x);
                            }
                            x->prev->color=BLACK;																//case 3:(line)
                            x->prev->prev->color=RED;
                            left_rotate(x->prev->prev);
                        }
                    }
                }
                this->root->color=BLACK;																		//case 0:root==RED
            }
            void delete_fixup(Node* x){
                while(x!=root and x->color==BLACK){
                    if(x==x->prev->left){
                        Node* w=x->prev->right;
                        if(w->color==RED){
                            w->color=BLACK;
                            x->prev->color=RED;
                            left_rotate(x->prev);
                            w=x->prev->right;
                        }
                        if(w->right->color==BLACK and w->left->color==BLACK){
                            w->color=RED;
                            x=x->prev;
                        }
                        else{
                            if(w->left->color==RED and w->right->color==BLACK){
                                w->left->color=BLACK;
                                w->color=RED;
                                right_rotate(w);
                                w=x->prev->right;
                            }
                            w->color=x->prev->color;
                            x->prev->color=BLACK;
                            w->right->color=BLACK;
                            left_rotate(x->prev);
                            x=root;
                        }
                    }
                    else{
                        Node* w=x->prev->left;
                        if(w->color==RED){
                            w->color=BLACK;
                            x->prev->color=RED;
                            right_rotate(x->prev);
                            w=x->prev->left;
                        }
                        if(w->left->color==BLACK and w->left->color==BLACK){
                            w->color=RED;
                            x=x->prev;
                        }
                        else{
                            if(w->right->color==RED and w->left->color==BLACK){
                                w->right->color=BLACK;
                                w->color=RED;
                                left_rotate(w);
                                w=x->prev->left;
                            }
                            w->color=x->prev->color;
                            x->prev->color=BLACK;
                            w->left->color=BLACK;
                            right_rotate(x->prev);
                            x=root;
                        }
                    }
                }
                x->color=BLACK;
            }
            void right_rotate(Node* x){
                Node* y=x->left;
                if(x->prev==nullptr)
                    this->root=y;
                else{
                    if(x==x->prev->right)
                        x->prev->right=y;
                    else/*(x==x->prev->left)*/
                        x->prev->left=y;
                }
                y->prev=x->prev;
                x->left=y->right;
                if(y->right!=&TNULL)
                    y->right->prev=x;
                y->right=x;
                x->prev=y;
            }
            void left_rotate(Node* x){
                Node* y=x->right;
                if(x->prev==nullptr)
                    this->root=y;	
                else{
                    if(x==x->prev->left)
                        x->prev->left=y;
                    else/*(x==x->prev->right)*/
                        x->prev->right=y;
                }
                y->prev=x->prev;
                x->right=y->left;
                if(y->left!=&TNULL)
                    y->left->prev=x;
                y->left=x;
                x->prev=y;
            }
            Node* min(Node* x){
                while(x->left!=&TNULL)
                    x=x->left;
                return x;
            }
        public:
            Tree(){INCTREES
                TNULL.color=BLACK;
                root=&TNULL;
            }
            Tree(T data):root(new Node(data,BLACK)){INCTREES
                TNULL.color=BLACK;
                root->right=&TNULL;
                root->left=&TNULL;
            }
            void insert(T data){
                Node* x;
                if(root==&TNULL){
                    root=new Node(data);
                    root->right=&TNULL;
                    root->left=&TNULL;
                    x=root;
                }
                else{
                    x=root;
                    while(data!=x->data){
                        if(data<x->data){
                            if(x->left==&TNULL){
                                x->left=new Node(data);
                                x->left->right=&TNULL;
                                x->left->left=&TNULL;
                                x->left->prev=x;
                                x=x->left;
                                break;							
                            }
                            else
                                x=x->left;
                        }
                        if(data>x->data){
                            if(x->right==&TNULL){
                                x->right=new Node(data);
                                x->right->right=&TNULL;
                                x->right->left=&TNULL;
                                x->right->prev=x;
                                x=x->right;
                                break;							
                            }
                            else
                                x=x->right;
                        }
                    }
                }
                this->insert_fixup(x);
            }
            bool has(T data){
                if(root==&TNULL)
                    return false;
                else{
                    Node* x=root;
                    while(true){
                        if(data!=x->data){
                            if(data<x->data){
                                if(x->left==&TNULL)
                                    return false;						
                                else
                                    x=x->left;
                            }
                            if(data>x->data){
                                if(x->right==&TNULL)
                                    return false;							
                                else
                                    x=x->right;
                            }
                        }
                        else return true;
                    }
                }	
            }
            void transplant(Node* u,Node* v){//Desenlaza u con su padre y enlaza al padre con v
                if(u->prev==nullptr)
                    this->root=v;
                else{
                    if(u==u->prev->left)
                        u->prev->left=v;
                    else
                        u->prev->right=v;
                }
                v->prev=u->prev;
            }
            bool del(T data){
                if(root==&TNULL)
                    return false;
                Node* z=root;
                do{
                    if(data<z->data){
                        if(z->left==&TNULL)
                            return false;
                        else
                            z=z->left;
                    }
                    if(data>z->data){
                        if(z->right==&TNULL)
                            return false;
                        else
                            z=z->right;
                    }
                }while(data!=z->data);
                Node* y,* x;
                bool z_original_color=z->color;
                if(z->left==&TNULL){
                    x=z->right;
                    transplant(z,z->right);
                }
                else if(z->right==&TNULL){
                    x=z->left;
                    transplant(z,z->left);
                }
                else{
                    y=min(z->right);
                    z_original_color=y->color;
                    x=y->right;
                    if(y->prev==z) 
                        x->prev=y;
                    else{
                        transplant(y, y->right);
                        y->right=z->right;
                        y->right->prev=y;
                    }
                    transplant(z,y);
                    y->left=z->left;
                    y->left->prev=y;
                    y->color=z->color;
                }
                delete z;
                if (z_original_color==BLACK)
                    delete_fixup(x);
                return true;
            }
            void preOrder(){
                std::cout<<'[';
                pre_order(root);
                std::cout<<']';
            }
            void inOrder(){
                std::cout<<'[';
                in_order(root);
                std::cout<<']';
            }
            void postOrder(){
                std::cout<<'[';
                post_order(root);
                std::cout<<']';
            }
            void clear(){
                clr(root);
            }
            ~Tree(){DECTREES
                clr(root);
                REMAININGTREES
            }
            class iterator{
                private:
                    Node* ptr;
                    Stack<Node*>* stack;
                    int* ref_count;
                public:
                    iterator(Node* p):ptr(p),stack(nullptr),ref_count(nullptr){
                    	if(ptr==nullptr) return;
                    	ref_count=new int(1);
                    	stack=new Stack<Node*>;
                        while(ptr->left->left!=nullptr){
                            stack->push(ptr);
                            ptr=ptr->left;
                        }
                    }
                    iterator(iterator& other):ptr(other.ptr),stack(other.stack),ref_count(other.ref_count){
                        (*ref_count)++;
                    }
                    T& operator*(){
                        return ptr->data;
                    }
                    T* operator->(){
                        return &(ptr->data);
                    }
                    iterator& operator++(){
                        if(ptr->right->right==nullptr and not stack->empty()){
                            ptr=stack->pop();
                        }
                        else if(ptr->right->right!=nullptr){
                            ptr=ptr->right;
                            while(ptr->left->left!=nullptr){
                                stack->push(ptr);
                                ptr=ptr->left;
                            }
                        }
                        else
                            ptr=nullptr;
                        return *this;
                    }
                    iterator operator++(int){
                        iterator aux=*this;
                        if(ptr->right->right==nullptr and not stack->empty()){
                            ptr=stack->pop();
                        }
                        else if(ptr->right->right!=nullptr){
                            ptr=ptr->right;
                            while(ptr->left->left!=nullptr){
                                stack->push(ptr);
                                ptr=ptr->left;
                            }
                        }
                        else
                            ptr=nullptr;
                        return aux;
                    }
                    bool operator==(const iterator& other)const{
                        return this->ptr==other.ptr;
                    }
                    bool operator!=(const iterator& other)const{
                        return this->ptr!=other.ptr;
                    }
                    ~iterator(){
                        if(ref_count!=nullptr and --(*ref_count)==0)
                            delete stack;
                    }
            };
            iterator begin()const{
                return iterator(root);
            }
            iterator end()const{
                return iterator(nullptr);
            }
    };
}