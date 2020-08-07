//============================================================================
// Name        : Assignment5.cpp
// Author      : 
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
//#include<chrono>
using namespace std;
class MST
{
	int arr[10][10],n,cost;
	string a[10],adja[10];
	int key[10];

public:
	MST()
	{
		n=0;
		for(int i=0;i<9;i++)
		{
			for(int j=0;j<9;j++)
			{
				arr[i][j]=999;
			}
		}
		for(int i=0;i<9;i++)
		{
			key[i]=999;
		}
		cost=0;
	}
	void create(){
		cout<<"Enter Number of Offices: ";
		cin>>n;
		cout<<"Enter the Office Names:\n";
		for(int i=0;i<n;i++)
		{
			cout<<"Enter: ";
			cin>>a[i];
		}
	}
	void graph()
	{
		string l1,l2;
		int st,dest;
		cout<<"Enter Starting Office: ";
		getline(cin>>ws,l1);
		cout<<"Enter Destination Office: ";
		getline(cin>>ws,l2);
		for(int i=0;i<n;i++)
		{
			if(a[i]==l1)
				st=i;
			if(a[i]==l2)
				dest=i;
		}
		cout<<"Enter Cost: ";
		cin>>cost;
		arr[st][dest]=cost;
		arr[dest][st]=cost;
	}
	void print()
	{
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				if(arr[i][j]!=999)
				{
					cout<<a[i]<<"-"<<a[j]<<": "<<arr[i][j]<<endl;
				}
			}
		}
	}
	void prims()
	{
		bool valid[n];
		for(int i=0;i<n;i++)
		{
			valid[i]=false;
		}
		int count=0,sum=0;
		key[0]=0;
		while(count<n)
		{
			int select;
			int min=999;
			for(int i=0;i<n;i++)
			{
				if(key[i]<min && !valid[i])
				{
					min=key[i];
					select=i;
				}
			}
			valid[select]=true;
			sum+=min;
			count++;
			for(int i=0;i<n;i++)
			{
				if(arr[select][i]!=999 && !valid[i])
				{
					if(arr[select][i]<key[i])
					{
						key[i]=arr[select][i];
					}
				}
			}
		}
		cout<<"Minimum Cost is: "<<sum;
	}
};
int main() {
	MST obj;
	int choice,flag=0;
	cout<<"1)Enter Nodes\n2)Add Edges\n3)Prims\n4)Print Graph\n5)Exit";
	do
	{
		cout<<"\nEnter Your Choice: ";
		cin>>choice;
		switch(choice)
		{
			case 1: obj.create();
					break;
			case 2: obj.graph();
					break;
			case 3: obj.prims();
					break;
			case 4: obj.print();
					break;
			case 5: flag=1;
					break;
		}
	}while(flag==0);
	return 0;
}
