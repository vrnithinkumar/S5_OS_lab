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
	cpq[small]=NULL;
	return small;
}
main()
{
	postruct *a,*b,*c;
	a=new postruct;
	b=new postruct;
	c=new postruct;
	a->val=5;
	b->val=8;
	c->val=2;
	addtocpuq(a);
	addtocpuq(b);
	addtocpuq(c);
	cout<<enqcpu();
	
		
}	
