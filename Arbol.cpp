#include"viggianolib/viggiano.h"
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
		Tree(){}
		template<typename D>
		Tree(D data):root(new Node(data)){}
		template<typename D>
		void insert(D data){
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
		template<typename D>
		bool has(D data){
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
		template<typename D>
		bool del(D data){
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
		}
};

/*std::ostream& operator<<(std::ostream& stream,Tree& tree){
	stream<<
	return stream;
}*/
using namespace vgg;
using namespace std;
int main(){
	Tree<Str<>> arbol("Hola");
	arbol.insert(Str<>("Que tal"));
	arbol.insert(Str<>("Que Tal"));
	arbol.insert(Str<>("Buenas tardes"));
	arbol.insert(Str<>("Que TAL"));
	arbol.del(Str<>("Que Tal"));
	arbol.print();
	//arbol.insert(new int(34));
}
/*int main(){
	Tree<int> arbol(443);
	arbol.insert(999);	
	arbol.insert(69);	
	arbol.insert(0);	
	arbol.insert(69);	
	arbol.insert(6);
	arbol.insert(45);
	arbol.insert(72);
	arbol.insert(543);
	arbol.print();
	arbol.del(6);
	arbol.del(999);
	arbol.del(45);
	arbol.del(443);
	arbol.del(443);
	arbol.del(72);
	arbol.del(69);
	arbol.del(543);
	arbol.del(72);
	arbol.del(0);
	arbol.del(0);
	arbol.insert(342);
	arbol.insert(-31);
	arbol.insert(1);
	arbol.insert(-3421);
	arbol.del(-31);
	arbol.print();
}*/