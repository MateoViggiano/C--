#include<iostream>
template<typename T>
class Tree{
	private:
		struct Node{
			T data;
			Node* left=nullptr;
			Node* right=nullptr;
			Node(T dat):data(dat){}
			Node(){}
		};
		Node* root;
		void clr(Node* father){
			if(father==nullptr)
				return;
			else{
				clr(father->left);
				clr(father->right);
				delete father;
			}
		}
		void prnt(Node* father){
			if(father==nullptr)
				return;
			std::cout<<father->data<<',';
			prnt(father->left);
			prnt(father->right);
		}
		void insert_node(Node* node){
			Node* ptr=root;
			while(true){
				if(node->data<ptr->data){
					if(ptr->left==nullptr){
						ptr->left=node;
						break;
					}
					else 
						ptr=ptr->left;
				}
				if(node->data>ptr->data){
					if(ptr->right==nullptr){
						ptr->right=node;
						break;
					}
					else
						ptr=ptr->right;
				}
			}
		}
	public:
		Tree(){INCTREES}
		Tree(T data):root(new Node(data)){INCTREES}
		//template<typename D>
		void insert(T data){
			if(root==nullptr)
				root=new Node(data);
			else{
				Node* ptr=root;
				while(data!=ptr->data){
					if(data<ptr->data){
						if(ptr->left==nullptr){
							ptr->left=new Node(data);
							break;							
						}
						else
							ptr=ptr->left;
					}
					if(data>ptr->data){
						if(ptr->right==nullptr){
							ptr->right=new Node(data);
							break;							
						}
						else
							ptr=ptr->right;
					}
					
				}
			}
		}
		bool has(T data){
			if(root==nullptr)
				return false;
			else{
				Node* ptr=root;
				while(true){
					if(data!=ptr->data){
						if(data<ptr->data){
							if(ptr->left==nullptr)
								return false;						
							else
								ptr=ptr->left;
						}
						if(data>ptr->data){
							if(ptr->right==nullptr)
								return false;							
							else
								ptr=ptr->right;
						}
					}
					else return true;
				}
			}	
		}
		bool del(T data){
			if(root==nullptr)
				return false;
			else{
				Node* ptr=root,* father;
				while(true){
					if(data!=ptr->data){
						if(data<ptr->data){
							if(ptr->left==nullptr)
								return false;						
							else{
								father=ptr;
								ptr=ptr->left;
							}
						}
						if(data>ptr->data){
							if(ptr->right==nullptr)
								return false;							
							else{
								father=ptr;
								ptr=ptr->right;
							}
						}
					}
					else{		//Eliminar ptr(que contiene el valor que se busca eliminar) y reordenar sus nodos hijos
						if(ptr==root){
							if(ptr->right!=nullptr and ptr->left!=nullptr){
								root=ptr->right;
								insert_node(ptr->left);								
							}
							else if(ptr->left!=nullptr)
								root=ptr->left;
							else if(ptr->right!=nullptr)
								root=ptr->right;
							else
								root=nullptr;
						}
						else{
							if(ptr==father->left){
								if(ptr->left!=nullptr and ptr->right!=nullptr){
									father->left=ptr->left;
									insert_node(ptr->right);
								}
								else if(ptr->left!=nullptr)
									father->left=ptr->left;
								else if(ptr->right!=nullptr)
									father->left=ptr->right;
								else
									father->left=nullptr;
							}
							else{//ptr==father->right
								if(ptr->right!=nullptr and ptr->left!=nullptr){
									father->right=ptr->right;
									insert_node(ptr->left);
								}
								else if(ptr->right!=nullptr)
									father->right=ptr->right;
								else if(ptr->left!=nullptr)
									father->right=ptr->left;
								else
									father->right=nullptr;
							}
						}
						delete ptr;
						return true;
					}
				}
			}	
		}
		void print(){
			std::cout<<'[';
			prnt(root);
			std::cout<<']';
		}
		void clear(){
			clr(root);
		}
		~Tree(){
			clr(root);
			DECTREES
			REMAININGTREES
		}
};
