#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct postruct{
	char state;
	int val;
	postruct *next;
	postruct *down;
	
};































int main()
{
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
		temp->val=vr;
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
					cout<<just<<" ";
					temp->val=just;
					temp->next=NULL;
					temp->down=NULL;
					phed->next=temp;
					phed=phed->next;
				}
			else if(z%2==0)
				{
					temp=new postruct;
					temp->state='p';
					cout<<just<<" ";
					temp->val=just;
					temp->next=NULL;
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
					temp->down=NULL;
					phed->next=temp;
					phed=phed->next;
				}
		}
	phed=thed->down;
	thed=thed->down;
}
phed=head;
while(phed!=NULL)
{
	cout<<phed->val<<"	";
	phed=phed->next;
}
/*Upto this for making input from a file and save it in queue...Its done*/











}
