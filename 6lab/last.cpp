#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct postruct{
	char state;
	int val,pronum;
	postruct *next;
	postruct *down;
};
postruct* cpq[10]={NULL};
bool isemptycpuq(){
	for(int i=0;i<10;i++)
	{
		if(cpq[i]!=NULL)
		{
			return false;
		}
	}
	return true;
}
	
void addtocpuq(postruct* p)
{
	int i=0;
	while(i<10)
	{
		if(cpq[i]==NULL)
		{
			cpq[i]=p;
			break;
		}
		i++;
	}
}
int enqcpu()
{
	int i=0,small;
	small=0;
	for(i=0;i<10;i++)
	{
		if(cpq[i]==NULL)
		continue;
		else
		{
			if((cpq[small]->val)>(cpq[i]->val))
			{
				small=i;
			}	
		}
	}
	//cpq[small]=NULL;
	return small;
}
	
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
	postruct* firstinioq()
	{
		if (frnt==NULL)
		{
		return NULL;
		}
		else{
				return frnt->data;
			}
	}
	void insert(postruct *k)
	{
		struct qnode *ptr;
		ptr=new qnode;
		ptr->data=k;
		//cout<<ptr->data->val;
		ptr->next=NULL;
		if(frnt==NULL)
		frnt=ptr;
		else
		rear->next=ptr;
		rear=ptr;
	}
	postruct* deq()
	{
		if(frnt==NULL)
		return NULL;
		struct qnode *temp;
		temp=frnt;
		frnt=frnt->next;
		return temp->data->next;
		delete temp;
	}
};
postruct* whoisfirst(postruct *top)
{
	postruct *temp,*ret;
	temp=top;
	ret=top;
	while(temp!=NULL)
	{
		//cout<<"!"<<endl;
		if((temp->next->val)<(ret->next->val))
		{
		//	cout<<"!"<<endl;
			ret=temp;
		}
		temp=temp->down;
	}
	return ret->next;
	
	
}
int main()
{
	int counter;
	string line;
	postruct *temp,*thed,*phed,*head,*top;
	int count,i,nop=0,just,nopt;
	
	ifstream myfile0 ("test");
	while (!myfile0.eof())
    {
		getline (myfile0,line);
		nop++;
	}
	nop--;
	nopt=nop;
	head=NULL;
	for(int vr=0;vr<nop;vr++)
	{
		temp=new postruct;
		temp->state='n';
		temp->val=vr+1;
		temp->next=NULL;
		temp->down=NULL;
		if(head==NULL)
		{
			head=temp;
		}
		else
		{
			top=head;
			while(top->down!=NULL)
			{
				top=top->down;
			}
			top->down=temp;
		}
	
	}	
int countarray[nop];
ifstream myfile ("test");
int cou=0;
while (nop)
    {
		getline (myfile,line);
		count=i=0;
		while(line[i]!='\0')
		{
			if(line[i]==' ')
			count++;
			i++;
		}
		countarray[cou]=count+1;
		nop--;
		cou++; 
		}
ifstream myfile2 ("test");
phed=thed=head;
for(int x=0;x<nopt;x++)
	{	
		for(int z=0;z<countarray[x];z++ )
		{ 
			myfile2>>just;
			if(z==0)
				{
					continue;
				}
			else if(z==1)
				{
					temp=new postruct;
					temp->state='a';
					temp->val=just;
					temp->next=NULL;
					temp->down=NULL;
					temp->pronum=x;
					phed->next=temp;
					phed=phed->next;
				}
			else if(z%2==0)
				{
					temp=new postruct;
					temp->state='p';
					temp->val=just;
					temp->next=NULL;
					temp->pronum=x;
					temp->down=NULL;
					phed->next=temp;
					phed=phed->next;
				}
			else if(z%2==1)
				{
					temp=new postruct;
					temp->state='i';
					temp->val=just;
					temp->next=NULL;
					temp->pronum=x;
					temp->down=NULL;
					phed->next=temp;
					phed=phed->next;
				}
		}
	phed=thed->down;
	thed=thed->down;
}
phed=head;
temp=thed=head;
int tottime=0;
while(temp!=NULL)
{
	while(thed!=NULL)
	{
		if(thed->state=='p'||thed->state=='i')
		{
			tottime=tottime+thed->val;
		}
		thed=thed->next;
	}
	thed=temp->down;
	temp=temp->down;
}
/*-----to find length of while loop------*/
queue ioq;
int time=0;
postruct *active;
time=whoisfirst(head)->val;
whoisfirst(head)->val=0;
active=whoisfirst(head)->next;
counter=0;
while(time<tottime)
{
	temp=head;
	while(temp!=NULL)
	{
		if(((temp->next->val)<=time)&&(temp->next->val!=0))
		{																		//Adding jobs arrived to ready array..
			addtocpuq(temp->next->next);
			temp->next->val=0;
		}
		temp=temp->down;
	}
/*---------------------------------------------------------------------------------------------------------------------------------*/
	if(active!=NULL)
	{
		active->val--;
		counter++;
		if(active->val==0)
		{
			cout<<active->pronum+1<<" "<<counter<<endl;
			if(active->next!=NULL)
			{
				ioq.insert(active->next);
				active=NULL;
			}
		}
		if(ioq.firstinioq()!=NULL)
		{
			ioq.firstinioq()->val--;
			if(ioq.firstinioq()->val==0)
			{
				phed=ioq.deq();
				if(phed!=NULL)
				{
					addtocpuq(phed);
				}
			}	
		}
	}
	else
	{
		if(!(isemptycpuq()))
		{
			active=cpq[enqcpu()];
			cpq[enqcpu()]=NULL;
			counter=0;
			active->val--;
			counter++;
		}
		if(ioq.firstinioq()!=NULL)
		{
			ioq.firstinioq()->val--;
			if(ioq.firstinioq()->val==0)
			{
				phed=ioq.deq();
				if(phed!=NULL)
				{
					addtocpuq(phed);
				}
			}
		}
	}
	
	
	time++;
	
}
}	

