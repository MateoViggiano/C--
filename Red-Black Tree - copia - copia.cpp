#include<iostream>
#define RED 1
#define BLACK 0
template<typename T>
class Tree{
	private:
		struct Node{
			T data;
			Node* left=nullptr;
			Node* right=nullptr;
			Node* prev=nullptr;
			bool color=RED;
			Node(T dat):data(dat){}
			Node(){}
		};
		Node* root=nullptr;
		void clr(Node* node){
			if(node==nullptr)
				return;
			else{
				clr(node->left);
				clr(node->right);
				delete node;
			}
		}
		void print_(Node* node){
			if(node==nullptr)
				return;
			std::cout<<node->data<<',';
			print_(node->left);
			print_(node->right);
		}
		void insert_fixup(Node* x){
			while(x->prev!=nullptr and x->prev->color==RED){
				if(x->prev==x->prev->prev->left){															//If the father is a left node
					if(x->prev->prev->right!= nullptr and x->prev->prev->right->color==RED){				//case 1:X.uncle==RED
						x->prev->color=BLACK;
						x->prev->prev->right->color=BLACK;
						x->prev->prev->color=RED;
						x=x->prev->prev;
					}
					else/*(x->prev->prev->right==nullptr or x->prev->prev->right->color==BLACK)*/{			//case 2 & 3:x.uncle==BLACK
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
					if(x->prev->prev->left!= nullptr and x->prev->prev->left->color==RED){					//case 1:X.uncle==RED
						x->prev->color=BLACK;
						x->prev->prev->left->color=BLACK;
						x->prev->prev->color=RED;
						x=x->prev->prev;
					}
					else/*(x->prev->prev->left==nullptr or x->prev->prev->left->color==BLACK)*/{			//case 2 & 3:x.uncle==BLACK
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
					if(w!=nullptr and w->color==RED){
						w->color=BLACK;
						x->prev->color=RED;
						left_rotate(x->prev);
						w=x->prev->right;
					}
					if(w!=nullptr and(w->right==nullptr or w->right->color==BLACK) and (w->left==nullptr or w->left->color==BLACK)){
						w->color=RED;
						x=x->prev;
					}
					else{
						if((w->left!=nullptr and w->left->color==RED) and (w->right==nullptr or w->right->color==BLACK)){
							w->left->color=BLACK;
							w->color=RED;
							right_rotate(w);
							w=x->prev->right;
						}
						w->color=x->prev->color;
						x->prev->color=BLACK;
						if(w->right!=nullptr)
							w->right->color=BLACK;
						left_rotate(x->prev);
						x=root;
					}
				}
				else{
					Node* w=x->prev->left;
					if(w!=nullptr and w->color==RED){
						w->color=BLACK;
						x->prev->color=RED;
						right_rotate(x->prev);
						w=x->prev->left;
					}
					if(w!=nullptr and w->left==nullptr or w->left->color==BLACK and w->right==nullptr or w->left->color==BLACK){
						w->color=RED;
						x=x->prev;
					}
					else{
						if((w->right!=nullptr and w->right->color==RED) and w->left==nullptr or w->left->color==BLACK){
							w->right->color=BLACK;
							w->color=RED;
							left_rotate(w);
							w=x->prev->left;
						}
						w->color=x->prev->color;
						x->prev->color=BLACK;
						if(w->left!=nullptr)
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
			if(y->right!=nullptr)
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
			if(y->left!=nullptr)
				y->left->prev=x;
			y->left=x;
			x->prev=y;
		}
		Node* min(Node* x){
			while(x->left!=nullptr)
				x=x->left;
			return x;
		}
	public:
		Tree(){}
		Tree(T data):root(new Node(data)){}
		void insert(T data){
			Node* x;
			if(root==nullptr){
				root=new Node(data);
				x=root;
			}
			else{
				x=root;
				while(data!=x->data){
					if(data<x->data){
						if(x->left==nullptr){
							x->left=new Node(data);
							x->left->prev=x;
							x=x->left;
							break;							
						}
						else
							x=x->left;
					}
					if(data>x->data){
						if(x->right==nullptr){
							x->right=new Node(data);
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
			if(root==nullptr)
				return false;
			else{
				Node* x=root;
				while(true){
					if(data!=x->data){
						if(data<x->data){
							if(x->left==nullptr)
								return false;						
							else
								x=x->left;
						}
						if(data>x->data){
							if(x->right==nullptr)
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
			if(root==nullptr)
				return false;
			Node* z=root;
			do{
				if(data<z->data){
					if(z->left==nullptr)
						return false;
					else
						z=z->left;
				}
				if(data>z->data){
					if(z->right==nullptr)
						return false;
					else
						z=z->right;
				}
			}while(data!=z->data);
			Node* y = z,* x;
			bool z_original_color = z->color;
			if(z->left!=nullptr and z->right!=nullptr){
				y = min(z->right);
				z_original_color = y->color;
				x=y->right;
				if(y->prev==z){
					std::cout<<"PASA POR ACA"<<std::endl;
					//x->prev=y;
				}
				else{
					transplant(y,x);
					y->right=z->right;
					y->right->prev = y;
				}
				transplant(z,y);
				y->left=z->left;
				y->left->prev=y;
				y->color=z->color;
			}
			else if(z->right!=nullptr) {
				x=z->right;
				transplant(z,x);
			}
			else if(z->left!=nullptr) {
				x=z->left;
				transplant(z,x);
			}
			else{
				if(z==root)
					root=nullptr;	
				else{
					Node nullnode;
					transplant(z,&nullnode);
					if(z_original_color==BLACK)
						delete_fixup(&nullnode);
					if(&nullnode==nullnode.prev->right)
						nullnode.prev->right=nullptr;
					else if(&nullnode==nullnode.prev->left)
						nullnode.prev->left=nullptr;
				}
				z_original_color=1;
			}
			delete z;
			if (z_original_color==BLACK)
				delete_fixup(x);
			return true;
		}
		bool delet(T data){
		 	if(root==nullptr)
		 		return false;
		 	else{
		 		Node* x=root;
		 		while(true){
		 			if(data<x->data){
		 				if(x->left==nullptr)
		 					return false;						
		 				else
		 					x=x->left;
		 			}
		 			if(data>x->data){
		 				if(x->right==nullptr)
		 					return false;							
		 				else
		 					x=x->right;
		 			}
		 			else{		//Eliminar x(que contiene el valor que se busca eliminar) y reordenar sus nodos hijos
		 				if(x==root){
		 					if(x->right!=nullptr and x->left!=nullptr){
		 						Node* y=min(x->right);
		 						Node* z=y->right,* z_p=y->prev;
		 						z_p->left=z;
		 						if(z)
		 							z->prev=z_p;
		 						y->prev=nullptr;
		 						y->left=x->left;
		 						y->right=x->right;
		 						y->left->prev=y;
		 						y->right->prev=y;
		 						root=y;
		 						if(y->color==BLACK){
		 							if(z)
		 								delete_fixup(z);
		 							else{//crear nodo nulo para poder llamar a delete_fixup
		 								z=new Node;
		 								z->color=BLACK;
		 								z_p->left=z;
		 								z->prev=z_p;
		 								delete_fixup(z);
		 								z->prev->left=nullptr;
		 								delete z;
		 							}
		 						}
		 					}
		 					else if(x->left!=nullptr){
		 						root=x->left;
		 						root->prev=nullptr;
		 						root->color=BLACK;
		 					}
		 					else if(x->right!=nullptr){
		 						root=x->right;
		 						root->prev=nullptr;
		 						root->color=BLACK;
		 					}
		 					else
		 						root=nullptr;
		 				}
		 				else if(x==x->prev->left){
		 					if(x->left!=nullptr and x->right!=nullptr){
		 						Node* y=min(x->right);
		 						Node* z=y->right,* z_p=y->prev;
		 						z_p->left=z;
		 						if(z)
		 							z->prev=z_p;
		 						y->prev=x->prev;
		 						y->prev->left=y;
		 						y->left=x->left;
		 						y->right=x->right;
		 						y->left->prev=y;
		 						y->right->prev=y;
		 						if(y->color==BLACK){
		 							if(z)
		 								delete_fixup(z);
		 							else{//crear nodo nulo para poder llamar a delete_fixup
		 								z=new Node;
		 								z->color=BLACK;
		 								z_p->left=z;
		 								z->prev=z_p;
		 								delete_fixup(z);
		 								z->prev->left=nullptr;
		 								delete z;
		 							}
		 						}
		 					}
		 					else if(x->left!=nullptr){
		 						Node* y=x->left;
		 						x->prev->left=y;
		 						y->prev=x->prev;
		 						if(x->color==BLACK)
		 							delete_fixup(y);
		 					}
		 					else if(x->right!=nullptr){
		 						Node* y=x->right;
		 						x->prev->left=y;
		 						y->prev=x->prev;
		 						if(x->color==BLACK)
		 							delete_fixup(y);
		 					}
		 					else{
		 						if(x->color==BLACK){
		 							Node* y=new Node;
		 							y->color=BLACK;
		 							x->prev->left=y;
		 							y->prev=x;
		 							delete_fixup(y);
		 							y->prev->left=nullptr;
		 							delete y;
		 						}
		 						else
		 							x->prev->left=nullptr;
		 					}
		 				}
		 				else{//x==x->prev->right
		 					if(x->right!=nullptr and x->left!=nullptr){
		 						Node* y=min(x->right);
		 						Node* z=y->right,* z_p=y->prev;
		 						z_p->left=z;
		 						if(z)
		 							z->prev=z_p;
		 						y->prev=x->prev;
		 						y->prev->right=y;
		 						y->left=x->left;
		 						y->right=x->right;
		 						y->left->prev=y;
		 						y->right->prev=y;
		 						if(y->color==BLACK){
		 							if(z)
		 								delete_fixup(z);
		 							else{//crear nodo nulo para poder llamar a delete_fixup
		 								z=new Node;
		 								z->color=BLACK;
		 								z_p->left=z;
		 								z->prev=z_p;
		 								delete_fixup(z);
		 								z_p->left=nullptr;
		 								delete z;
		 							}
		 						}
		 					}
		 					else if(x->left!=nullptr){
		 						Node* y=x->left;
		 						x->prev->right=y;
		 						y->prev=x->prev;
		 						if(x->color==BLACK)
		 							delete_fixup(y);
		 					}
		 					else if(x->right!=nullptr){
		 						Node* y=x->right;
		 						x->prev->right=y;
		 						y->prev=x->prev;
		 						if(x->color==BLACK)
		 							delete_fixup(y);
		 					}
		 					else{
		 						if(x->color==BLACK){
		 							Node* y=new Node;
		 							y->color=BLACK;
		 							x->prev->right=y;
		 							y->prev=x->prev;
		 							delete_fixup(y);
		 							y->prev->right=nullptr;
		 							delete y;
		 						}
		 						else
		 							x->prev->right=nullptr;
		 					}
		 				}
		 				delete x;
		 				return true;
		 			}
		 		}
		 	}	
		 }
		void print(){
			std::cout<<'[';
			print_(root);
			std::cout<<']';
		}
		void clear(){
			clr(root);
		}
		~Tree(){
			clr(root);
		}
};
using namespace std;
int main(){
	Tree<int> tree;
/*	for(int i=0;i<60;i++){
		tree.insert(i);tree.print();cout<<endl;
	}
	cout<<"\n\n\n";
	for(int i=60;i>=30;i--){
		tree.del(i);tree.print();cout<<endl;
	}
	for(int i=0;i<=30;i++){
		tree.del(i);tree.print();cout<<endl;
	}*/
	tree.insert(12);tree.print();cout<<endl;
	tree.insert(8);tree.print();cout<<endl;
	tree.insert(15);tree.print();cout<<endl;
	tree.insert(1);tree.print();cout<<endl;
	tree.insert(9);tree.print();cout<<endl;
	tree.insert(13);tree.print();cout<<endl;
	tree.insert(23);tree.print();cout<<endl;
	tree.insert(10);tree.print();cout<<endl;

	tree.del(12);tree.print();cout<<endl;
	std::cout<<"FIN";
	return 0;
}