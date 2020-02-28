//============================================================================
// Name        : A7.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;
#define MAX 10

class Symbol{
	string name;
	string attribute;
	int chain;
    public:
	Symbol();
	Symbol(string,string);
	friend class Table;
};

Symbol::Symbol(){
	name="\0";
    attribute="\0";
    chain=-1;
}

class Table{
	Symbol table[MAX];
public:
	void insert_withoutreplacement(string key,string mean);
	void insert_withreplacement(string key,string mean);
	int hash_generator(string key);
	void del_key(string key);
	int find(string key);
	void display_Table();
};

int Table::hash_generator(string key){
	int sum=0;

	     for(int i=0;i<key.length();i++){
	    	 sum+=key[i];
	     }

	     int index=sum%MAX;

	     return index;
}

void Table::insert_withoutreplacement(string key,string mean){
	 int index=hash_generator(key);

     if((table[index].name).length()==0){
    	 table[index].name=key;
    	 table[index].attribute=mean;
    	 return;
     }


     else{                           //WITHOUT REPLACEMENT CONDITION
    	 int i,flag;
    	  for(i=index+1; ;i++){
    		  if(i==MAX){
    			  i=0;
    		  }
    		  if(i==index){
    			  flag=0;
    			  break;
    		  }
    		  if((table[i].name).length()==0){
    			  flag=1;
    			  break;
    		  }
    	  }
    	  if(flag==1){
    		  int f=index;

    		  /*for(int j=0; ;j++){
    			  if()
    		  }*/

    		  while(table[f].chain!=-1){
    			  f=table[index].chain;
    		  }
    		  table[f].chain=i;
    		  table[i].name=key;
    		  table[i].attribute=mean;

    	  }
    	  else{
    		  cout<<endl;
    		  cout<<"HASH TABLE FULL!!"<<endl;
    	  }
     }
}

void Table::insert_withreplacement(string key,string mean){
	 int index=hash_generator(key);
	 int relinking_chain=0;
	 if((table[index].name).length()==0){
	    	 table[index].name=key;
	    	 table[index].attribute=mean;
	    	 return;
	  }
	 else if(table[index].name==key){
		 cout<<"Enter Unique Name!"<<endl;
	 }
	     else if(table[index].name!=key){              //REPLACEMENT CONDITION
	    	 int index2=hash_generator(table[index].name);
	    	 if(index!=index2){
	    	 string tempkey=key;
	    	 string tempmean=mean;
	    	 key=table[index].name;
	    	 mean=table[index].attribute;
	    	 table[index].name=tempkey;
	    	 table[index].attribute=tempmean;
	    	 relinking_chain=table[index].chain;
	    	 }

	    	 int i,flag;
	        	  for(i=index+1; ;i++){
	        		  if(i==MAX){
	        			  i=0;
	        		  }
	        		  if(i==index){
	        			  flag=0;
	        			  break;
	        		  }
	        		  if((table[i].name).length()==0){
	        			  flag=1;
	        			  break;
	        		  }
	        	  }

	        	  if(flag==1){
	        		  int f=index2;

	        		  while(table[f].chain!=index && table[f].chain!=-1){
	        			  f=table[f].chain;
	        		  }
	        		  table[index].chain=-1;
	        		  table[f].chain=i;

	        		  f=index2;
	        		    while(table[f].chain!=i){
	        		      f=table[index].chain;
	        		     }
	        		  table[f].chain=i;
	        		  table[i].name=key;
	        		  table[i].attribute=mean;
	        	  }
	        	  else{
	        		  cout<<endl;
	        		  cout<<"HASH TABLE FULL!!"<<endl;
	        	  }


	 }
}

void Table::display_Table(){
	cout<<"Index \t Key\tValue \t Chain "<<endl;
	for(int i=0;i<MAX;i++){
		//if((table[i].name).length()!=0){
			cout<<i<<"\t"<<table[i].name<<"\t"<<table[i].attribute<<"\t"<<table[i].chain<<endl;
		//}

}
}

int Table::find(string key){
	int index=hash_generator(key);
    int count=0;
	for(int i=index;i!=-1;){
                 ++count;
	    		  if(table[i].name==key){
                         cout<<"No. of Comparisons are - "<<count<<endl;
	    		  			  return i;
	    		  		  }
	    		  i=table[i].chain;
	    	 }
	  cout<<"Keyword not present in Hash Table!"<<endl;
	  cout<<"No. of Comparisons are - "<<count<<endl;
	  return -1;

}

void Table::del_key(string key){
	int index=find(key);
	if(index==-1){
		cout<<"Key not present in Hash Table!"<<endl;
	}
	else{
		int i=hash_generator(key);
		cout<<"Keyword "<<table[index].name<<" deleted!"<<endl;

		if(table[i].chain==index){
			table[i].chain=table[table[i].chain].chain;
		}
		else{
		while(table[table[i].chain].chain!=index){
			i=table[i].chain;
		}
		table[table[i].chain].chain=table[index].chain;
		}
		table[index].name="";
		table[index].attribute="";
		table[index].chain=-1;
	}
}

int main() {
	string key,attribute;
	Table obj;
	int ch,flag;
    for(; ;){
    	cout<<"***********SYMBOL TABLE**************"<<endl;
    				cout<<endl;
    				cout<<"1. Insert the Data "<<endl;
    				cout<<"2. Display the hash table "<<endl;
    				cout<<"3. Deleting a Keyword from the Dictionary "<<endl;
    				cout<<"4. Finding a Keyword and No. of Comparisons"<<endl;
    				cin>>ch;

    				switch(ch){

    				case 1:  	cout<<"1.Without Replacement"<<endl;
    				            cout<<"2.With Replacement"<<endl;
    				            cin>>flag;
    					        cout<<"Enter the Word (Key)"<<endl;
    				            cin>>key;
    				            cout<<"Enter the Meaning (Value)"<<endl;
    				            cin>>attribute;
    				            if(flag==1)
    					            obj.insert_withoutreplacement(key,attribute);
    				            else
    				            	obj.insert_withreplacement(key,attribute);

    				            break;

    				case 2:  obj.display_Table();
    				         break;

    				case 3: cout<<"Enter the keyword to be deleted - "<<endl;
    				        cin.ignore();
    				        getline(cin,key);
    				        obj.del_key(key);
    	                    break;

    				case 4: cout<<"Enter the keyword to be searched - "<<endl;
    				        cin>>key;
    				         flag=obj.find(key);
    				        if(flag!=-1){
    				        	cout<<"Keyword found at index "<<flag<<endl;
    				        }
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
}
