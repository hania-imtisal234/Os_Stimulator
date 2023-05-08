#include<stdio.h>
#include <iostream>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdlib.h>
using namespace std;

 int pro,arrival[100],burst[100],sec=0,wait,final_time,waiting[100],turn,l=0,ans,pos[10],prior[10],minimum,maximum,qt,rm[10],b;
 
int last_execution[100];  // taking variable in this ways allows us to use them anywhere in the code as they are declared
 
double throughput,avgwait,avgturn;
 
bool ok;
void FCFS()
 
{
    
    int i,j,k,n;
 
   cout<<"enter the number of processes: ";
 
   cin>>pro;
 
   cout<<"enter the arrival time: ";
 
   for(i=0;i<pro;i++)
 
   {
 
       cin>>arrival[i];
 
   }
 
   cout<<"enter the burst time: ";
 
   for(i=0;i<pro;i++)
 
   {
 
       cin>>burst[i];
 

 
 
   }
 
   for(i=0;i<pro;i++)
 
   {
 
       if(i==0)
 
       {
 
           sec=sec+burst[i];
 
       }
 
       else
 
       {
 
           wait=sec-arrival[i];
 
           sec=sec+burst[i];
 
           cout<<"sec "<<sec<<endl;
 
           cout<<"wait "<<wait<<endl;
 
           k++;
 
           waiting[k]=wait;
 
       }
 
   }
 
   wait=0;
 
   turn=0;
 
   for(i=0;i<pro;i++)
 
   {
 
       wait=wait+waiting[i];
 
       turn=turn+(burst[i]+waiting[i]);
 
   }
 
 avgwait=wait/pro;
 
 avgturn=turn/pro;
 
 throughput=(double)pro/(double)sec;
 
 cout<<"Average Waiting Time   : "<< avgwait<<endl;
 

 cout<<"Average Turnaround Time: " <<avgturn<<endl;
 

 cout<<"Throughput             : "<<throughput<<endl;
 

 
 
 for(i=0;i<pro;i++)
 
 {
 
   waiting[i]=0;
 
 }
 
 for(i=0;i<pro;i++)
 
 {
 
   burst[i]=0;
 
 }
 
 for(i=0;i<pro;i++)
 
 {
 
   arrival[i]=0;
 
 }
 
}
 

 
 
void SJF()
 
{
        int i,j,k,n;

 
   cout<<"enter the number of processes: ";
 
   cin>>pro;
 
   cout<<"enter the burst time: ";
 
   for(i=0;i<pro;i++)
 
   {
 
       waiting[i]=0;
 
       cin>>burst[i];
 

 
 
   }
 
   minimum=burst[0];
 
   for(j=1;j<pro;j++)
 
   {
 
      if(minimum>burst[j])
 
      {
 
          minimum=burst[j];
 
      }
 
   }
 

 
 
   maximum=burst[0];
 
   for(j=1;j<pro;j++)
 
   {
 
      if(maximum<burst[j])
 
      {
 
          maximum=burst[j];
 
      }
 
   }
 

 
 
   ans=0;
 
   l=0;
 
   k=0;
 
   for(n=minimum;n<=maximum;n++)
 
   {
 
       for(i=0;i<pro;i++)
 
       {
 
           if(burst[i]==n)
 
           {
 
               waiting[l]=ans;
 
               l++;
 
               ans=ans+burst[i];
 
               pos[k]=i;
 
               k++;
 
           }
 

 
 
       }
 
   }
 
   turn=0;
 
   for(i=0;i<l;i++)
 
   {
 
       wait=wait+waiting[i];
 
       cout<<"wait " <<wait<<endl;
 
       turn=turn+(waiting[i]+burst[i]);
 
       cout<<"turn "<< turn<<endl;
 
   }
 
   avgwait=(double)wait/(double)pro;
 
   avgturn=(double)turn/(double)pro;
 
   throughput=(double)pro/(double)ans;
 
   cout<<"average waiting time : "<<avgwait<<endl;
 
   cout<<"average turnaround time : "<<avgturn<<endl;
 
   cout<<"throughput : "<< throughput<<endl;
 
}
 

 
 

 
 
void RR()
 
{
        int i,j,k,n;

 
   cout<<"enter the number of processes: ";
 
   cin>>pro;
 
   cout<<"enter the burst time: ";
 
   for(i=0;i<pro;i++)
 
   {
 
       waiting[i]=0;
 
       last_execution[i]=0;
 
       cin>>burst[i];
 
   }
 
   cout<<"enter the time quantum:";
 
   cin>>qt;
 
   b=pro;
 
   ans=0;
 
   k=0;
 
   while(b!=0)
 
   {
 
       for(i=0;i<pro;i++)
 
       {
 
           if(burst[i]<=qt&&burst[i]!=0)
 
           {
 
               waiting[i]+=(ans-last_execution[i]);
 
               ans=ans+burst[i];
 
               burst[i]=0;
 
               b--;
 
               last_execution[i]=ans;
 
           }
 
           else if(burst[i]>qt)
 
           {
 
               waiting[i]+=(ans-last_execution[i]);
 
               ans=ans+qt;
 
               burst[i]=burst[i]-qt;
 
               last_execution[i]=ans;
 
           }
 
       }
 
   }
 
   wait=0;
 
   turn=0;
 
   for(i=0;i<pro;i++)
 
   {
 
       wait+=waiting[i];
 
       turn+=last_execution[i];
 
   }
 
        avgwait=(double)wait/(double)pro;
 
        avgturn=(double)turn/(double)pro;
 
        throughput=(double)pro/(double)ans;
 
        cout<<"average waiting time : "<< avgwait<<endl;
 
        cout<<"average turnaround time : "<< avgturn<<endl;
 
        cout<<"throughput : "<< throughput<<endl;
 
}
 
void multilevel()
{
int p[20],bt[20], su[20], wt[20],tat[20],i, k, n, temp;
float wtavg, tatavg;
cout<<"Enter the number of processes:";
cin>>n;
for(i=0;i<n;i++)
{
p[i] = i;
cout<<"Enter the Burst Time of Process:"<< i<<endl;
cin>>bt[i];
cout<<"System/User Process (0/1) ? "<<endl;;
cin>>su[i];
}
for(i=0;i<n;i++)
for(k=i+1;k<n;k++)
if(su[i] > su[k])
{
temp=p[i];
p[i]=p[k];
p[k]=temp;
temp=bt[i];
bt[i]=bt[k];
bt[k]=temp;
temp=su[i];
su[i]=su[k];
su[k]=temp;
}
wtavg = wt[0] = 0;
tatavg = tat[0] = bt[0];
for(i=1;i<n;i++)
{
wt[i] = wt[i-1] + bt[i-1];
tat[i] = tat[i-1] + bt[i];
wtavg = wtavg + wt[i];
tatavg = tatavg + tat[i];
}
cout<<"\nPROCESS\t SYSTEM/USER PROCESS \tBURST TIME\tWAITING TIME\tTURNAROUND TIME"<<endl;
for(i=0;i<n;i++)
cout<<p[i]<<"\t"<<"\t"<<su[i]<<"\t"<<"\t"<<bt[i]<<"\t"<<"\t"<<wt[i]<<"\t"<<"\t"<<tat[i]<<endl;
cout<<"\nAverage Waiting Time is --- "<<wtavg/n;
cout<<"\nAverage Turnaround Time is --- "<<tatavg/n;

}
int n,nf;
int in[100];
int p[50];
int hit=0;
int i,j,k;
int pgfaultcnt=0;
void getData()
{
    cout<<"\nEnter length of page reference sequence:";
    cin>>n;
    cout<<"\nEnter the page reference sequence:";
    for(i=0; i<n; i++)
        cin>>in[i];
    cout<<"\nEnter no of frames:";
    cin>>nf;
}
 
void initialize()
{
    pgfaultcnt=0;
    for(i=0; i<nf; i++)
        p[i]=9999;
}
void dispPages()
{
    for (k=0; k<nf; k++)
    {
        if(p[k]!=9999)
            cout<<p[k]<<" ";
    }
 
}
 
void dispPgFaultCnt()
{
    cout<<"\nTotal no of page faults:"<<pgfaultcnt;
}
int isHit(int data)
{
    hit=0;
    for(j=0; j<nf; j++)
    {
        if(p[j]==data)
        {
            hit=1;
            break;
        }
 
    }
 
    return hit;
}
int getHitIndex(int data)
{
    int hitind;
    for(k=0; k<nf; k++)
    {
        if(p[k]==data)
        {
            hitind=k;
            break;
        }
    }
    return hitind;
}
void pageReplacement()
{
    int usedbit[50];
    int victimptr=0;
    initialize();
    for(i=0; i<nf; i++)
        usedbit[i]=0;
    for(i=0; i<n; i++)
    {
        cout<<"\nFor ",in[i];
        if(isHit(in[i]))
        {
            cout<<"No page fault!";
            int hitindex=getHitIndex(in[i]);
            if(usedbit[hitindex]==0)
                usedbit[hitindex]=1;
        }
        else
        {
            pgfaultcnt++;
            if(usedbit[victimptr]==1)
            {
                do
                {
                    usedbit[victimptr]=0;
                    victimptr++;
                    if(victimptr==nf)
                        victimptr=0;
                }
                while(usedbit[victimptr]!=0);
            }
            if(usedbit[victimptr]==0)
            {
                p[victimptr]=in[i];
                usedbit[victimptr]=1;
                victimptr++;
            }
            dispPages();
 
        }
        if(victimptr==nf)
            victimptr=0;
    }
    dispPgFaultCnt();
}
                 
    pthread_t *Students;
pthread_t TA;

int ChairsCount = 0;
int CurrentIndex = 0;


sem_t TA_Work;
sem_t Student_Sem;
sem_t ChairsSem[3];
pthread_mutex_t ChairAccess;


void *TA_Activity(void*);
void *Student_Activity(void *threadID);

int main()//int argc, char* argv[])
{
int menu;

cout<<"Enter 1 for Multilevel Queue Scheduling "<<endl;
    cout<<"Enter 2 for Semaphore "<<endl;
    cout<<"Enter 3 for Deadlock "<<endl;
    cout<<"Enter 4 for Memory Management "<<endl;
    cout<<"Enter 5 for Page Replacement "<<endl;
    cout<<"Enter the number for displaying code: "<<endl;
cin>>menu;
    if(menu==1)
    {
    multilevel();
    }
   
   
    //semaphore();

if(menu==2)
{
int id;
    int number_of_students;


sem_init(&TA_Work, 0, 0);
sem_init(&Student_Sem, 0, 0);
for(id = 0; id < 3; ++id)
sem_init(&ChairsSem[id], 0, 0);

pthread_mutex_init(&ChairAccess, NULL);



cout<<"Number of Students specified:"<< number_of_students<<endl;
//number_of_students = atoi(argv[1]);



Students = (pthread_t*) malloc(sizeof(pthread_t)*number_of_students);

pthread_create(&TA, NULL, TA_Activity, NULL);
for(id = 0; id < number_of_students; id++)
pthread_create(&Students[id], NULL, Student_Activity,(void*)(long)id);


pthread_join(TA, NULL);
for(id = 0; id < number_of_students; id++)
pthread_join(Students[id], NULL);
}
if (menu==5)
{
   getData();
  pageReplacement();
}

if(menu==3)
{
           cout<<endl;

    cout<<"--------SJF-----------"<<endl;
    cout<<endl;
 
   SJF();
            cout<<endl;

        cout<<"--------RR-----------"<<endl;

   RR();
               cout<<endl;

   cout<<"-------FCFS-----------"<<endl;
    cout<<endl;
 
   FCFS();
 
}


//free(Students);

    return 0;

}

void *TA_Activity(void*)
{
while(1)
{
sem_wait(&TA_Work);
cout<<"~~~~~~~~~~~~~~~~~~~~~TA is helping the student.~~~~~~~~~~~~~~~~~~~~~\n";

while(1)
{
pthread_mutex_lock(&ChairAccess);
if(ChairsCount == 0)
{

pthread_mutex_unlock(&ChairAccess);
break;
}
sem_post(&ChairsSem[CurrentIndex]);
ChairsCount--;
cout<<"Student left his/her chair. Remaining Chairs"<< 3 - ChairsCount;
CurrentIndex = (CurrentIndex + 1) % 3;
pthread_mutex_unlock(&ChairAccess);

cout<<"\t TA is currently helping the student.\n";
sleep(5);
sem_post(&Student_Sem);
usleep(1000);
}
}
}

void *Student_Activity(void *threadID)
{
int ProgrammingTime;

while(1)
{

pthread_mutex_lock(&ChairAccess);
int count = ChairsCount;
pthread_mutex_unlock(&ChairAccess);

if(count < 3)
{
if(count == 0)
sem_post(&TA_Work);
else
cout<<"Student sat on a chair waiting for the TA to finish."<<(long)threadID<<endl;

// lock
pthread_mutex_lock(&ChairAccess);
int index = (CurrentIndex + ChairsCount) % 3;
ChairsCount++;
cout<<"Student sat on chair.Chairs Remaining:"<<3 - ChairsCount<<endl;
pthread_mutex_unlock(&ChairAccess);
// unlock

sem_wait(&ChairsSem[index]);
cout<<"\t Student is getting help from the TA."<<(long)threadID<<endl;
sem_wait(&Student_Sem);
cout<<"Student left TA room."<<(long)threadID<<endl;
}
else
cout<<"Student will return at another time. \n"<<(long)threadID<<endl;

}
}

