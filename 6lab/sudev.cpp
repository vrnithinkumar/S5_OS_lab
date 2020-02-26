#include <iostream>
#include <fstream>
#include <string>

using namespace std;
//universal array containing all the info 
int array[10][10]={{},{}};
//PCB for process 
int iowait=0;
int * readyqueue();
int over();
void readandsave();
void ioqueuer(int *,int *);
int ptime=0,noofprocess;
//keeps track of the current process 

int current=0;
int printarray[1000];
struct process
{
	int cpu[10];
	int io[10];
	int arival;
	int numcpu;
	int numio;
	int signal[3];
	int currentcpu;
	int currentio;
	//the status array is used to get the status of any process which 
	//like working cpu 1st bit = 1 , io 2nd bit = 1; finished 3rd bit = 1  
};
//all values are intialized to zero using new constructor 
struct process *proc = new struct process[10];

void readandsave(){

int count,i;
int nop=0,just,nopt;
string procline;
ifstream test0 ("inputfile");
while (!test0.eof())
    {
		getline (test0,procline);
		nop++;
	}
nop--;
nopt=nop;
noofprocess=nop;
cout<<"Total no fo process  "<<nop<<endl;
int stuffinprocess[nop];
ifstream test ("inputfile");
int cou=0;
while (nop)
    {
	getline (test,procline);
	count=i=0;
	while(procline[i]!='\0')
		{
			if(procline[i]==' ')
			count++;
			i++;

		}
	stuffinprocess[cou]=count+1;
	nop--;
	cou++; 
    }
ifstream test2 ("inputfile");
for(int x=0;x<nopt;x++)
	{
	for(int z=0;z<stuffinprocess[x];z++ )
		{ 
		test2>>just;
		array[x][z]=just;
		}
	}
for(int a=0;a<nopt;a++)
	{
	int t=1;
	for(int b=0;b<stuffinprocess[a];b++ )
		{ 
		cout<<array[a][b]<<" ";\
		//taking values into arival array 
		if(b==1)
		proc[a].arival = array[a][b];
		//taking values into job queue and i/o queue				
		if( b > 1)
		{ 
			if(t)
			{
			proc[a].cpu[proc[a].numcpu]=array[a][b];
			proc[a].numcpu++;
			t=0;		
			}
			else
			{				
			proc[a].io[proc[a].numio]=array[a][b];
			proc[a].numio++;	
			t=1;
			}				
		}				
		}
		//testing results using sample outputs 
		cout<<endl;
		cout<<"arrival time  "<<proc[a].arival<<endl; 
		cout<<"Cpu Bursts";
		for(int i=0;i<proc[a].numcpu;i++)
		cout<<"\t"<<proc[a].cpu[i]<<"\t";
		cout<<endl<<"number of cpu process "<<proc[a].numcpu<<endl;
		cout<<"IO Bursts";
		for(int i=0;i<proc[a].numio;i++)
		cout<<"\t"<<proc[a].io[i]<<"\t";
		cout<<endl<<"number of io process "<<proc[a].numio<<endl;
		cout<<endl<<"-------------------------------------------"<<endl;
}

}



int main () 
{
	readandsave();
	//we have all the details of the process t 	he process structure now we have to 
	//manipulate the data using suitable methods 
//time 
//print point 
int pp=0,ch=1;
while(ch)
{
cout<<"Enter your choice "<<"1.Pre emptive \t 2.emptive "<<endl;
cin>>ch;

//select the process with least cpu burst 
while(over())
	{	
	int * tem = readyqueue();
	//cout<<endl<<"process to be executed is "<<*tem;
	//now to take record of all the happenings
	/* trying to keep print the whole stuff */
	cout << "the process executed at time\t " <<ptime<<"\twas\t"<<current+1<<" its "<<proc[current].currentcpu + 1<<" cpu burst  was executed"<<endl;
	//to get all the stuff into an array 
	/*
	if(ptime==0)
	{ 
		printarray[pp] = current;
		printarray[pp+1] = 1;
	}
	else
	{
		if(printarray[pp - 1] == current )
			{
			printarray[pp]++;
			}
		else
			{
			pp++;
			printarray[pp] = current;
			pp++;
			printarray[pp] = 1;
			}
	}
	*/
	if(ch<2)
	{
	(*tem)--;
	ptime++;
	if(iowait > 0 )
	iowait--;
	}
	else
	{
		ptime = ptime + *tem;
		
		if(iowait > 0)
		{
		if( iowait > *tem ) 
			iowait = iowait - *tem;
		else
			iowait = 0;
		}
		*tem = 0;
	}
	/* in case of other process 
	 * the change is just the ptime = ptime + *tem
	 * and temp = 0'
	 */
	//iowait--;
	}
	for(int i; i < pp+1;i=i+2)
		cout<<printarray[i]<<" : "<<printarray[i+1]<<"\t";
	return 1;
}
}



//function to check completion of all the process 
int over()
{
	for(int i =0 ; i < noofprocess; i++)
	{
		if(proc[i].numcpu >proc[i].currentcpu)
		{
		return 1;
		}
	}
	return 0;
}
int * readyqueue()
{
	//to find the minimum 
	int * temp = NULL;
	for(int i=0;i<noofprocess;i++)
	{
	//checking for the completion of the process 
	if(proc[i].cpu[proc[i].currentcpu] <=0)
		{
		if(proc[i].numcpu>proc[i].currentcpu )
			proc[i].currentcpu++;
			//calling io opertion to complete
			ioqueuer(&proc[i].arival, &proc[i].currentio);
		}
	//set the process completion signal 
	if(proc[i].numcpu < proc[i].currentcpu )
		proc[i].signal[1]=-1;
	//now add the same to jobqueue considering arrival time and signal 
	if(proc[i].arival<=ptime && proc[i].signal[1]==0)
		{
		//this gives out a pointer to minimum process
		if(temp == NULL)
			{
			temp = &proc[i].cpu[proc[i].currentcpu];
			current = i;
			}
		else 	
			{
			if(*temp > proc[i].cpu[proc[i].currentcpu])
			temp = &proc[i].cpu[proc[i].currentcpu];
			current = i;
			}
		}
	}
	return temp;
}
void ioqueuer(int *a,int *b)
{
	*a = *a + ptime + iowait;
	iowait = *a + iowait;
	*b = *b + 1;
}
