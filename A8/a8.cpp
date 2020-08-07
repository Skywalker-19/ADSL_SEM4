#include <iostream>
using namespace std;

class Node{
	Node *left, *right;
	string keyword, meaning;
	int balance;
public:
	Node(string keyword, string meaning){
		left = NULL;
		right = NULL;
		this->keyword = keyword;
		this->meaning = meaning;
		balance = 0;
	}
	friend class Tree;
};

class Tree{
	Node *q, *root;
public:
	Tree(){
		q = NULL;
		root = NULL;
	}
	void initializeAdd(){
		string key, meaning;
		cout<<"\nKey : ";
		cin>>key;
		cout<<"Meaning : ";
		cin>>meaning;
		cout<<endl;
		root = add(root, key, meaning);
	}
	Node *add(Node *t, string key, string meaning){
		if(t == NULL)
			t = new Node(key, meaning);
		else{
			if(key.compare(t->keyword) > 0){
				t->right = add(t->right, key, meaning);
				if(findBalance(t) == -2){
					if(key.compare(t->right->keyword) > 0)
						t = RR(t);
					else
						t = RL(t);
				}
			}

			else if(key.compare(t->keyword) < 0){
				t->left = add(t->left, key, meaning);
				if(findBalance(t) == 2){
					if( key.compare(t->left->keyword) < 0 )
						t = LL(t);
					else
						t = LR(t);
				}
			}
			else{
				cout<<"---Already Present---"<<endl<<endl;
				return 0;
			}
		}
		t->balance = height(t);
		return t;
	}
	int findBalance(Node *t){
		int lh, rh;
		if(t==NULL)
			return 0;
		//next
		if(t->left == NULL)
			lh = 0;
		else
			lh = (t->left->balance) + 1;
		// next
		if(t->right == NULL)
			rh = 0;
		else
			rh = t->right->balance + 1;
		//end
		return (lh - rh);
	}
	int height(Node *t){
		int lh, rh;
		if(t==NULL)
			return 0;
		//next
		if(t->left == NULL)
			lh = 0;
		else
			lh = (t->left->balance) + 1;
		// next
		if(t->right == NULL)
			rh = 0;
		else
			rh = t->right->balance + 1;
		//end
		return (lh>rh ? lh : rh);
	}
	Node *RR(Node *t){
		t = rotateLeft(t);
		return t;
	}
	Node *LR(Node *t){
		t->left = rotateLeft(t->left);
		t = rotateRight(t);
		return t;
	}
	Node *RL(Node *t){
		t->right = rotateRight(t->right);
		t = rotateLeft(t);
		return t;
	}
	Node *LL(Node *t){
		t = rotateRight(t);
		return t;
	}
	Node *rotateLeft(Node *t){
		Node *r = t->right;
		t->right = r->left;
		r->left = t;
		t->balance = height(t);
		r->balance = height(r);
		return r;
	}
	Node *rotateRight(Node *t){
		Node *r = t->left;
		t->left = r->right;
		r->right = t;
		t->balance = height(t);
		r->balance = height(r);
		return r;
	}
	void traversal(int choice){
		int i=1;
		if(root == NULL){
			cout<<"empty tree";
			return;
		}
		if(choice == 1)
			inorder_recursive(root,i);
		if(choice == 2)
			rev_inorder_recursive(root,i);
		cout<<endl;
	}
	void inorder_recursive(Node *rt, int i){
		if(rt != NULL){
			inorder_recursive(rt->left, i);
			cout<<rt->keyword << " : "<<rt->meaning<<endl;
			inorder_recursive(rt->right, i);
		}
	}
	void rev_inorder_recursive(Node *rt, int i){
		if(rt != NULL){
			rev_inorder_recursive(rt->right, i);
			cout<<rt->keyword << " : "<<rt->meaning<<endl;
			rev_inorder_recursive(rt->left,  i);
		}
	}
	void update(){
		int found = 0;
		string keyword, meaning;
		cout<<"enter keyword to search: ";
		cin>>keyword;
		cout<<"enter new meaning : ";
		cin>>meaning;
		q = root;
		if(root == NULL){
			cout<<"\n~empty tree";
			return;
		}
		else{
			while(q != NULL){
				int comparison = q->keyword.compare(keyword);
				if(comparison > 0){
					q = q-> left;
				}
				else if(comparison < 0){
					q = q-> right;
				}
				else if (comparison == 0){
					q->meaning = meaning;
					cout<<"---Keyword found---"<<endl<<endl;
					found = 1;
					break;
				}
			}
			if(found == 0)
				cout<<"---keyword not found---"<<endl<<endl;
		}
	}
	int max_comparisons(){
		string keyword;
		cout<<"enter keyword to search: ";
		cin>>keyword;
		q = root;
		int i = 0;
		if(root == NULL){
			cout<<"\n~empty tree";
			return 0;
		}
		else{
			while(q != NULL){
				int comparison = q->keyword.compare(keyword);
				i++;
				if(comparison > 0){
					q = q-> left;
				}
				else if(comparison < 0){
					q = q-> right;
				}
				else if (comparison == 0){
					return i;
				}
			}
			cout<<"---Keyword not found---"<<endl<<endl;
			return 0;
		}
	}
	Node *deleteNode(Node *root, string key){
		if(root == NULL)
			return root;
		if(root->keyword.compare(key)>0){
			root->left = deleteNode(root->left, key);
			return root;
		}
		else if(root->keyword.compare(key)<0){
			root->right = deleteNode(root->right, key);
			return root;
		}
		if(root->left == NULL)
			return root->right;
		else if(root->right == NULL)
			return root->left;
		else{
			Node* succparent = root->right;
			Node* succ = root->right;
			while(succ->left != NULL){
				succparent = succ;
				succ= succ->left;
			}
			succparent->left = succ->right;
			root->keyword = succ->keyword;
			delete succ;
			return root;
		}
	}
	void inidelete(){
		cout<<"enter keyword to delete : ";
		string key;
		cin>>key;
		cout<<"Deleted"<<endl<<endl;
		deleteNode(root, key);
	}
};
int main(){
	Tree obj,obj2,copy1;
	int i = 1;
	int choice;
	int result;
	while(i){
	cout<<"***********AVL OPERATIONS************"<<endl;
	cout<<"\n1 : Insert Node ";
    cout<<"\n2 : Delete a node";
	cout<<"\n3 : Display in Ascending order";
	cout<<"\n4 : Display in Descending order";
	cout<<"\n5 : Update Meaning";
	cout<<"\n6 : No. of max comparisons to find the keyword.";
	cout<<"\n7 : Stop operations"<<endl;
	cout<<endl;
		cout<<" Enter Choice : ";
		cin>>choice;
		switch(choice){
			case 1:
				obj.initializeAdd();
				break;
			case 2:
				obj.inidelete();
				break;
			case 3:
				obj.traversal(1);
				break;
			case 4:
				obj.traversal(2);
				break;
			case 5:
				obj.update();
				break;
			case 6:
				result = obj.max_comparisons();
				if(result != 0)
					cout<<"Max comparisons : "<<result<<endl<<endl;
				break;

			case 7:
				i = 0;
				break;
			default:break;
		}
	}
}
