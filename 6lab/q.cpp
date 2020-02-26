
#include<iostream>

using namespace std;

struct postruct{
	char state;
	int val;
	postruct *next;
	postruct *down;
	
};

struct qnode
{
   postruct *data;
   struct qnode *next;
};

class queue
{
   struct qnode *frnt,*rear;
   public:
      queue()
      {
			frnt=rear=NULL;
      }
      
      void insert(postruct *k)
        {
            struct qnode *ptr;
            ptr=new qnode;
            ptr->data=k;
			cout<<ptr->data->val;
            ptr->next=NULL;
			if(frnt==NULL)
			frnt=ptr;
			else
			rear->next=ptr;
			rear=ptr;
		}
      void del()
		{
			if(frnt==NULL)
			{
				cout<<"\nQueue is empty!!";
				return;
			}
			struct qnode *temp;
			temp=frnt;
			frnt=frnt->next;
			delete temp;
	}
      void show()
	{
		struct qnode *ptr1=frnt;
		if(frnt==NULL)
		{
			cout<<"The Queue is empty!!";
			return;
		}
		cout<<"\nThe Queue is\n";
		while(ptr1!=NULL)
		{
			cout<<ptr1->data->val<<"	";
			ptr1=ptr1->next;
		}
		cout<<"END";
}
};

int main()
{
   queue cpuq,ioq;
   postruct *temp,*temp1,*temp2;
   temp=new postruct;
   temp1=new postruct;
   temp2=new postruct;
   temp->val=1;
   temp1->val=2;
   temp2->val=3;
   cpuq.insert(temp);
   cpuq.insert(temp1);
   cpuq.insert(temp2);
   cpuq.show();
   cpuq.del();
   cpuq.show();
   return 0;
}
