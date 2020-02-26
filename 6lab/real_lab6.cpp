/*----------------------------------------------------------------/*
/*                        OS lab 6                                */
/* shortest-next-CPU-burst-first process scheduler algorithm      */
/*             Auther VR<vrnithinkumar@gmail.com>                 */
/*----------------------------------------------------------------*/


#include <iostream>
#include <fstream>
#include <string>

using namespace std;
/*Structure of processes*/
struct Process_Structure{
	char state;
	int Value,Process_ID;
	Process_Structure *next;
	Process_Structure *down;
};
/*Array used for making CPU burst time priority queue*/
Process_Structure* CPU_Q[10]={NULL};

bool Is_Empty_CPU_Q()//To check whether  CPU burst time priority queue
{ 
	for(int i=0;i<10;i++)
	{
		if(CPU_Q[i]!=NULL)
		{
			return false;
		}
	}
	return true;
}
	
void Add_CPU_Q(Process_Structure* p)//adding process to CPU burst time priority queue
{
	int i=0;
	while(i<10)
	{
		if(CPU_Q[i]==NULL)
		{
			CPU_Q[i]=p;
			break;
		}
		i++;
	}
}
int Enque_CPU_Q()//enqueing CPU burst time priority queue according to cpu burst time 
{
	int i=0,small;
	small=0;
	for(i=0;i<10;i++)
	{
		if(CPU_Q[i]==NULL)
		continue;
		else
		{
			if((CPU_Q[small]->Value)>(CPU_Q[i]->Value))
			{
				small=i;
			}	
		}
	}
	return small;
}
	
struct Q_Node //Node for io queue implementation 
{
   Process_Structure *data;
   struct Q_Node *next;
};

class queue  //class of io queue
{
	struct Q_Node *frnt,*rear;
	public:
	queue() //Initilizing
	{
		frnt=rear=NULL;
	}
	Process_Structure* Head_IOQ()//finding head of io queue
	{
		if (frnt==NULL)
		{
		return NULL;
		}
		else{
				return frnt->data;
			}
	}
	void Enque_IOQ(Process_Structure *k)//Enqueing process struct to io queue
	{
		struct Q_Node *ptr;
		ptr=new Q_Node;
		ptr->data=k;
		//cout<<ptr->data->Value;
		ptr->next=NULL;
		if(frnt==NULL)
		frnt=ptr;
		else
		rear->next=ptr;
		rear=ptr;
	}
	Process_Structure* Deque_IOQ() // Dequeing io queue
	{
		if(frnt==NULL)
		return NULL;
		struct Q_Node *temp;
		temp=frnt;
		frnt=frnt->next;
		return temp->data->next;
		delete temp;
	}
	
	void Show_IOQ() //to sho io queue for debugging
	{
		struct Q_Node *ptr1=frnt;
		if(frnt==NULL)
		{
			cout<<"The Queue is empty!!";
			return;
		}
		cout<<"\nThe Queue is\n";
		while(ptr1!=NULL)
		{
			cout<<ptr1->data->Value<<"	";
			ptr1=ptr1->next;
		}
		cout<<"END";
	}
};
Process_Structure* First_Arrived_Process(Process_Structure *top)// function to find the process which come firsts 
{
	Process_Structure *temp,*ret;
	temp=top;
	ret=top;
	while(temp!=NULL)
	{
		if((temp->next->Value)<(ret->next->Value))
		{
			ret=temp;
		}
		temp=temp->down;
	}
	return ret->next;
	
	
}
int main()
{
	/* User choice inputing*/
	int Elapsed_Time;
	int flag,flags;
	cout<<"pre-emptive algorithm or non-pre-emptive."<<endl;
	cout<<"Enter Choice 1 0r 2 or 3"<<endl;
	cout<<"1)Non pre-emptive algorithm"<<endl<<"2)Pre-emptive algorithm\n";
	cin>>flag;
	if(flag>3)
	{
		cout<<"Cool man.......Thank you for Running my code........\n";
		cout<<"----------------------VR----------------------------\n";
		cout<<"------------<vrnithinkumar@gmail.com>---------------\n";
		return 0;
	}
	flags=flag;
	if(flag==3)
		flag=1;
	label:
	string line;
	Process_Structure *temp,*thed,*phed,*head,*top;
	int count,i,nop=0,just,nopt,min;
	
	/*Starting reading from the file to linked list*/
	ifstream MyFile_0 ("test");
	while (!MyFile_0.eof())
    {
		getline (MyFile_0,line);
		nop++;
	}
	nop--;
	nopt=nop;
	head=NULL;
	for(int Loop_V1=0;Loop_V1<nop;Loop_V1++)
	{
		temp=new Process_Structure;
		temp->state='n';
		temp->Value=Loop_V1+1;
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
int Elements_Line[nop];
ifstream MyFile_1 ("test");
int cou=0;
while (nop)
    {
		getline (MyFile_1,line);
		count=i=0;
		while(line[i]!='\0')
		{
			if(line[i]==' ')
			count++;
			i++;
		}
		Elements_Line[cou]=count+1;
		nop--;
		cou++; 
		}
ifstream MyFile_2 ("test");
phed=thed=head;
for(int x=0;x<nopt;x++)
	{	
		for(int z=0;z<Elements_Line[x];z++ )
		{ 
			MyFile_2>>just;
			if(z==0)
				{
					continue;
				}
			else if(z==1)
				{
					temp=new Process_Structure;
					temp->state='a';
					temp->Value=just;
					temp->next=NULL;
					temp->down=NULL;
					temp->Process_ID=x;
					phed->next=temp;
					phed=phed->next;
				}
			else if(z%2==0)
				{
					temp=new Process_Structure;
					temp->state='p';
					temp->Value=just;
					temp->next=NULL;
					temp->Process_ID=x;
					temp->down=NULL;
					phed->next=temp;
					phed=phed->next;
				}
			else if(z%2==1)
				{
					temp=new Process_Structure;
					temp->state='i';
					temp->Value=just;
					temp->next=NULL;
					temp->Process_ID=x;
					temp->down=NULL;
					phed->next=temp;
					phed=phed->next;
				}
		}
	phed=thed->down;
	thed=thed->down;
}
phed=head;
/*Upto this for making input from a file and save it in queue...Its done*/
temp=thed=head;
int Expecting_Time=0;
while(temp!=NULL)
{
	while(thed!=NULL)
	{
		if(thed->state=='p'||thed->state=='i')
		{
			Expecting_Time=Expecting_Time+thed->Value;
		}
		thed=thed->next;
	}
	thed=temp->down;
	temp=temp->down;
}
/*-----to find length of while loop------and found..*/
if(flag==2)
	{
		cout<<"----------Pre-emptive algorithm------------\n"<<endl;
		cout<<"Process ID  Elapsed Time\n";
	}
	else
	{
		cout<<"----------Non Pre-emptive algorithm------------\n"<<endl;
		cout<<"Process ID  Elapsed Time\n";
	}
queue IOQ;
int time=0;
Process_Structure *Current_Process;
time=First_Arrived_Process(head)->Value;
First_Arrived_Process(head)->Value=0;
Current_Process=First_Arrived_Process(head)->next;
Elapsed_Time=0;
/*---------------------Implementing Virtual machine for checking cpu burst time -------------------*/
while(time<Expecting_Time*2)//looping almost as time required for whole process to run....
{
	temp=head;
	while(temp!=NULL)
	{
		if(((temp->next->Value)<=time)&&(temp->next->Value!=0))
		{																		//Adding jobs arrived to ready array..
			Add_CPU_Q(temp->next->next);
			temp->next->Value=0;
		}
		temp=temp->down;
	}
/*---------------------------------------------------------------------------------------------------------------------------------*/
	
	
	if(Current_Process!=NULL)
	{
		
		if(flag==2)
		{
			
			if(!(Is_Empty_CPU_Q()))
			{
				if(Current_Process->Value>CPU_Q[Enque_CPU_Q()]->Value)
				{
					
					cout<<Current_Process->Process_ID+1<<"\t\t"<<Elapsed_Time<<endl;
					temp=Current_Process;
					Current_Process=CPU_Q[Enque_CPU_Q()];
					CPU_Q[Enque_CPU_Q()]=NULL;
					Add_CPU_Q(temp);
					Elapsed_Time=0;
					/*if(Current_Process!=NULL)
					{
						Current_Process->Value--;
						Elapsed_Time++;
					}*/
					
					
				}
				else
				{
					Current_Process->Value--;
					Elapsed_Time++;
				}
				
			}
			else
			{
				Current_Process->Value--;
				Elapsed_Time++;
			}
		}
		else
		{
			Current_Process->Value--;
			Elapsed_Time++;
		}
			
		
		if(Current_Process->Value==0)
		{
			cout<<Current_Process->Process_ID+1<<"\t\t"<<Elapsed_Time<<endl;
			if(Current_Process->next!=NULL)
			{
				IOQ.Enque_IOQ(Current_Process->next);
				Current_Process=NULL;
			}
		}
		if(IOQ.Head_IOQ()!=NULL)
		{
			IOQ.Head_IOQ()->Value--;
			if(IOQ.Head_IOQ()->Value==0)
			{
				phed=IOQ.Deque_IOQ();
				if(phed!=NULL)
				{
					Add_CPU_Q(phed);
				}
			}	
		}
	}
	else
	{
		if(!(Is_Empty_CPU_Q()))
		{
			Current_Process=CPU_Q[Enque_CPU_Q()];
			CPU_Q[Enque_CPU_Q()]=NULL;
			Elapsed_Time=0;
			Current_Process->Value--;
			Elapsed_Time++;
		}
		if(IOQ.Head_IOQ()!=NULL)
		{
			IOQ.Head_IOQ()->Value--;
			if(IOQ.Head_IOQ()->Value==0)
			{
				phed=IOQ.Deque_IOQ();
				if(phed!=NULL)
				{
					Add_CPU_Q(phed);
				}
			}
		}
	}
	time++;
}
if(flags==3)
	{
		flag=2;
		flags++;
		goto label;
	}
}	

