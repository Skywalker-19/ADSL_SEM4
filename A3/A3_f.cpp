/*Problem Statement-:Convert given binary tree into inordered and preordered threaded binary tree.
Analyze time and space  complexity of the algorithm*/
#include <iostream>

using namespace std;

class node
{
public:
    int flag;
    int data;
    node *left;
    node *right;
    node(){}
    node(int d)
    {
        data=d;
        left=NULL;
        right=NULL;
        flag=0;
    }
friend class tree;
};

class tree
{
    node *start;
public:
       tree(){
              start=NULL;
              }
              
    node* search_rec(int ,node* );
    void create_inorder(int );
    void display_inorder();
    void create_preorder();
    void display_preorder();
    void dis_pre();
};
node* tree::search_rec(int key, node *temp)
{
    if(temp==NULL)
    {
        return NULL;
    }

    if((temp->data>key) && (temp->left==NULL))
    {
        return temp;
    }
    else if(((temp->data<key)&&(temp->right==NULL))||((temp->data<key)&&(temp->flag==1)))
    {
        return temp;
    }
    else if(temp->data>key)
    {
        return search_rec(key,temp->left);
    }

    else if(temp->data<key)
    {
        return search_rec(key,temp->right);
    }
    else if(temp->data==key)
    {
        return temp;
    }

}

void tree::create_inorder(int dat)
{
    node *temp=new node(dat);

    if(start==NULL)
    {
        start=temp;
    }
    else
    {
       node *q=search_rec(dat,start);

            if(q->data>=dat)
            {
            	temp->right=q;
            	temp->flag=1;
                q->left=temp;
             }
            else if((q->data<dat))
            {
                if(q->flag==1)
                {
                node *tem=q->right;
                temp->right=tem;
                q->right=temp;
                temp->flag=1;
                q->flag=0;
                }
                else
                {
                    q->right=temp;
                }
            }
    }
}

void tree::display_inorder()
{
 node *q=start;
if(start==NULL)
{
	cout<<"\nTree is Empty!!";
}
else
 {
    label:while(q->left!=NULL)
    {
        q=q->left;
    }
    cout<<"\n"<<q->data;
    while(q->right!=NULL)
    {
    if(q->flag==1)
    {
        q=q->right;
        cout<<"\n"<<q->data;
    }
    else if(q->flag==0&&q->right!=NULL)
    {
        q=q->right;
        goto label;

    }
    }
}
}

void tree::create_preorder()
{

node *t=start;
  while(t)
    {
      while(t->left)
        t=t->left;
      if(t->flag==1)
	{
	  node *temp=t;
	  while(temp->flag==1)
	    {
	      node *temp2=temp;
	      temp->flag=0;
	      temp=temp->right;
	      temp2->right=NULL;
	    }

	  t->right=temp->right;
	  t->flag=1;
	  t=t->right;
	}
      else
	t=t->right;
    }

}
void tree::display_preorder()
{
	node *t=start;
  while(1)
    {
      while(t->left)
	{
	  cout<<"\n"<<t->data;
	  t=t->left;
	}
      cout<<"\n"<<t->data;
      t=t->right;
      if(t==NULL)
	break;
    }
   cout<<endl;
}


int main()
{
    tree t,t1;
    int no,n,ch;


		for(; ; ){

		cout<<"***********THREADED BINARY TREE**************"<<endl;
		cout<<endl;
		cout<<"1. Read the elements of the tree "<<endl;
		cout<<"2. Inorder Traversal "<<endl;
		cout<<"3. Preorder Traversal "<<endl;
		cin>>ch;

		switch(ch){
		case 1:  cout<<"\nEnter no of Entries to be added-: ";
                 cin>>n;

    //Inorder Tree
                  for(int i=0;i<n;i++)
                  {
                   cin>>no;
                   t.create_inorder(no);
                   t1.create_inorder(no);
                  }
		          break;

		case 2:  cout<<"\nInorder Sequence is - ";
                 t.display_inorder();
		         break;

		case 3:     //Preorder Tree
                 t1.create_preorder();
                 cout<<"\nPreorder Sequence is - ";
                 t1.display_preorder();
			        break;
			        
	    default:
			 cout<<"Enter from the above menu!"<<endl;
		}
        cout<<endl;
		cout<<"Do you want to continue?(1 if yes/0 if no)"<<endl;
		cin>>ch;
		if(ch==1)
		{continue;}
		else
		{break;}
	}

return 0;
}
