
#include <iostream>
using namespace std;
class node{
	int data;
	node* next;
public:
	node(int x)
{
		data=x;
		next=NULL;
}
	friend class Set;
};

class Set{
	node* head;
public:
	Set()
{
		head=NULL;
}
	void create();
	void insert(int x);
	void display();
	void deletenode();
	bool find(int x);
	void size();
	Set intersection(Set a);
	Set unionset(Set a);
	Set difference(Set a);
	bool subset(Set a);

};
void Set::create()
{
	int x;
	while(1)
	{
		cout<<"Enter element to insert in set :";
		cin>>x;
		if(x<0)
			break;
		insert(x);
	}
}
void Set::insert(int x)
{
	if(!find(x))
	{
		if(head==NULL)
		{
			head=new node(x);
			return;
		}
		node* t=head;
		while(t->next!=NULL)
			t=t->next;
		t->next= new node(x);
	}
	else
	{
		cout<<"Element already present\n";
	}
}
void Set::display()
{
	cout<<"Elements in Set are:\n";
	node* t=head;
	if(t==NULL)
	{
		cout<<"Set is empty\n";
		return;
	}
	while(t!=NULL)
	{
		cout<<t->data<<"\t";
		t=t->next;
	}
	cout<<endl;
}
void Set::deletenode()
{
	int x;
	cout<<"Enter element to delete:";
	cin>>x;
	node* t=head;
	if(t->data==x)
	{
		head=t->next;
		delete t;
		return;
	}
	while(t->next!=NULL)
	{
		if(t->next->data==x)
		{
			node* p=t->next;
			t->next=p->next;
			delete p;
			return;
		}
		t=t->next;
	}
}
bool Set::find(int x){
	node* t=head;
	while(t!=NULL)
	{
		if(t->data==x)
			return true;
		t=t->next;
	}
	return false;
}
void Set::size()
{
	node* t=head;
	int count=0;
	while(t)
	{
		count++;
		t=t->next;
	}
	cout<<"Size of set is "<<count<<endl;
}
Set Set::intersection(Set a)
{
	Set b;
	node* t=head;
	while(t!=NULL)
	{
		if(a.find(t->data))
		{
			b.insert(t->data);
		}
		t=t->next;
	}
	return b;
}
Set Set::unionset(Set a)
{
	node* t=head;
	Set c;
	while(t!=NULL)
	{
		c.insert(t->data);
		t=t->next;
	}
	t=a.head;
	while(t!=NULL)
	{
		if(!c.find(t->data))
		{
			c.insert(t->data);
		}
		t=t->next;
	}
	return c;
}
Set Set::difference(Set a)
{
	Set c;
	node* t=head;
	while(t)
	{
		if(!a.find(t->data))
		{
			c.insert(t->data);
		}
		t=t->next;
	}
	return c;
}
bool Set::subset(Set sub)
{
	node* t=sub.head;
	while(t!=NULL)
	{
		if(find(t->data))
		{
			t=t->next;
		}
		else
		{
			cout<<"Not a subset\n";
			return false;
		}
	}
	return true;
}
int main() {
	Set t,a,c,d,l,m,r,q,sub;
	int choice,x;
	do{
		cout<<"Enter\n1.Create Set\n2.Insert in set\n3.Delete element\n4.Display\n5.Intersection\n6.Union\n7.Subset\n8.Size of set\n9.Find\n10.Difference\n";
		cin>>choice;
		switch(choice){
		case 1:
			t.create();
			break;
		case 2:
			cout<<"Enter element to insert:";
			cin>>x;
			t.insert(x);
			break;
		case 3:
			t.deletenode();
			break;
		case 4:
			t.display();
			break;
		case 5:
             cout<<"Enter elements of 2nd set - "<<endl;
			a.create();
			c=t.intersection(a);
			c.display();
			break;
		case 6:
             cout<<"Enter elements of 2nd set - "<<endl;
			r.create();
			q=t.unionset(r);
			q.display();
			break;
		case 7:
             cout<<"Enter elements of 2nd set - "<<endl;
			sub.create();
			if(t.subset(sub))
			{
				cout<<"Is a subset\n";
			}
			break;
		case 8:
			t.size();
			break;
		case 9:
			cout<<"Enter element to find:";
			cin>>x;
			if(t.find(x))
			{
				cout<<"Element found\n";
			}
			else
				cout<<"Element not found\n";
			break;
		case 10:
			l.create();
			m=t.difference(l);
			m.display();
			break;
		}
	}while(choice!=0);
	return 0;
}
