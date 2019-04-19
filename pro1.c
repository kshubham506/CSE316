/*
	Ques. 1. Considering 4 processes with the arrival time and the burst time requirement of the
processes the scheduler schedules the processes by interrupting the processor after every 3 units
of time and does consider the completion of the process in this iteration. The schedulers then
checks for the number of processes waiting for the processor and allots the processor to the
process but interrupting the processor after every 6 units of time and considers the completion of
the process in this iteration. The scheduler after the second iteration checks for the number of
processes waiting for the processor and now provides the processor to the process with the least
time requirement to go in the terminated state.
The inputs for the number of requirements, arrival time and burst time should be provided by the
user.
Consider the following units for reference.
Process Arrival time Burst time
P1 0 18
P2 2 23
P3 4 13
P4 13 10

*/

#include<stdio.h>
#define MAX 300
struct process{
	int arrivalTime;
	int burstTime;
	char processName[10];
	int processNum;
	int fetched;
	
	int tempburstTime;
	int completionTime;
	int waitingTime;
	int turnaroundTime;
};
struct process pro[4]; 
int prefinalTotal;
int totalturnAroundTime,totalWaitTime;
int n,minartime;



void printques()
{
	printf("Ques. 1. Considering 4 processes with the arrival time and the burst time requirement of the \nprocesses the scheduler schedules the processes by interrupting the processor after every 3 units\nof time and does consider the completion of the process in this iteration. The schedulers then\nchecks for the number of processes waiting for the processor and allots the processor to the\nprocess but interrupting the processor after every 6 units of time and considers the completion of\nthe process in this iteration. The scheduler after the second iteration checks for the number of\nprocesses waiting for the processor and now provides the processor to the process with the least\ntime requirement to go in the terminated state.\nThe inputs for the number of requirements, arrival time and burst time should be provided by the user.\nConsider the following units for reference.\nProcess Arrival time Burst time\nP1 0 1\nP2 2 23\nP3 4 13\nP4 13 10");
}

//for maintaining the ready queue
int queue[MAX];
int rear = - 1;
int front = - 1;
int  insert(int val)
{
    int add_item;
    if (rear == MAX - 1)
    {
    	//	printf("Queue Overflow \n");
    		return 0;
	}
    else
    {
        if (front == - 1)
        front = 0;
        rear = rear + 1;
        queue[rear] = val;
        pro[val].fetched=1;
        //display();
        return 1;
    }
}
int delete()
{
    if (front == - 1 || front > rear)
    {
       // printf("Queue Underflow \n");
        return 0;
    }
    else
    {
        //printf("\nElement deleted from queue is : %d\n", queue[front]);
        front = front + 1;
        return  queue[front-1];
    }
}
int display()
{
    int i,ret=0;
    if (front == - 1){}
	
       // printf("Queue is empty \n");
    else
    {
    	int f=0,j=0;
    	for (j = front; j <= rear; j++)
        {
        	if(pro[queue[j]].burstTime!=0)
        	{
        		printf("\n\n\tReady Queue : ");
        		ret=1;
        		break;
			}
        	
		}
		
		
        for (i = front; i <= rear; i++)
        {
        	if(pro[queue[i]].burstTime!=0)
        		printf("%s ", (pro[queue[i]].processName));
		}
		 
    }
    return ret;
}
int find(int val)
{
    int i;
    if (front == - 1){
	}
        //printf("Queue is empty \n");
    else
    {
        for (i = front; i <= rear; i++)
        {
        	if(queue[i]==val)
        		return 1;
		}
    }
    return 0;
}
void insertIntoReadyQueue(int currentTime)
{
	int i; 
    for (i = 0; i < n; i++)
	 { 
        
        if (pro[i].arrivalTime <= currentTime && find(i)!=1 && pro[i].fetched==0) 
        {
        //	printf("\nInserted i:%d , pro arrival :%d,current, : %d \n",i,pro[i].arrivalTime, currentTime);
        	insert(i); 
		}
    } 
}
int findLeastBurstTime()
{
	int min;
	int pr,i;
	for (i = front; i <= rear; i++)
        {
        		if(pro[queue[i]].burstTime!=0)
        		{
        			min=pro[queue[i]].burstTime;
        			pr=queue[i];
				}
        }
	
	 for (i = front; i <= rear; i++)
        {
        	if(pro[queue[i]].burstTime<min && pro[queue[i]].burstTime!=0 )
        	{
        		min=pro[queue[i]].burstTime	;
        		pr=queue[i];
			}		
		}
		//printf("\nLEast: %d : %d\n",pr,min);
		return pr;
}
void findCompletionTime()
{
	printf("\n\n\tProcess Execeution Chart\n\t-----------------------------\n");
	int currentTime=0,count=1,execTill=0;
	int pno,pno1;
	//currentTime=pro[0].arrivalTime;
	currentTime=minartime;
	prefinalTotal+=minartime;
	//printf("\nCurrent time :%d , Pre final : %d",currentTime,prefinalTotal);
	insertIntoReadyQueue(currentTime);
	while( count<=20)
	{
		//printf("\nCuuernert time : %d\n",currentTime);
		
		int val= display();
		if(val==0)
		{
			currentTime++;	
			insertIntoReadyQueue(currentTime);
			continue;
		}
		execTill=0;
		if(count==1)
		{
			pno=pro[delete()].processNum;
			if(pro[pno-1].burstTime<3)
				execTill=pro[pno-1].burstTime;
			else
				execTill=3;
		//	printf("\ncount 1 : %d , process : %s\n",execTill,pro[pno-1].processName);
			printf("\n\nProcess executing at time %d till %d is :P %d \t", currentTime,(currentTime+execTill),pno ); 
			pro[pno-1].burstTime -=execTill;
			currentTime = currentTime+execTill;
		}
		else if(count==2)
		{
			
			pno=pro[delete()].processNum;
			if(pro[pno-1].burstTime<6)
				execTill=pro[pno-1].burstTime;
			else
				execTill=6;
			//printf("\ncount 2 : %d , process : %s\n",execTill,pro[pno-1].processName);
			printf("\n\nProcess executing at time %d till %d is :P %d \t", currentTime,(currentTime+execTill),pno ); 
			pro[pno-1].burstTime -=execTill;
			currentTime = currentTime+execTill;
		}
		else
		{
		//	printf("\nelse\n");
			pno1=findLeastBurstTime();
			pno=pno1+1;
		/*	if(pno1>=n)
			{
				currentTime++;	
				insertIntoReadyQueue(currentTime);
				continue;
			}*/
				
			printf("\n\nProcess executing at time %d till %d is :P %d \t", currentTime,(currentTime+pro[pno-1].burstTime),pno ); 
			currentTime = currentTime+pro[pno-1].burstTime;
			pro[pno-1].burstTime =0;
		}
		
		insertIntoReadyQueue(currentTime);
		if(pro[pno-1].burstTime<=0)
		{
			pro[pno-1].completionTime = currentTime; 
            printf("  Process  %d is completed at %d ", pno, currentTime); 
		}
		else
		{
			insert(pno-1);
		}
		
		if (currentTime >= prefinalTotal) 
            break; 
	count++;
	}
}

int findTimes()
{
	int i;
	for(i=0;i<n;i++)
	{
		pro[i].turnaroundTime = pro[i].completionTime - pro[i].arrivalTime;
		pro[i].waitingTime = pro[i].turnaroundTime - pro[i].tempburstTime;
		totalWaitTime += pro[i].waitingTime;
		totalturnAroundTime += pro[i].turnaroundTime;
	}
}

int main()
{	
	//printf("Program 1 ");
	printques();
	//initializing all the Processes
	
	printf("\n\nEnter the number of processes : ");
	scanf("%d",&n);
	int i=0,j=0;
	minartime=9999999;
	for(i =0;i<n;i++)
	{
		printf("\nFor Process %d :\n----------------------- ",(i+1));
		printf("\n\nEnter the Arrival Time  : ");
		scanf("%d",&pro[i].arrivalTime);
		if(pro[i].arrivalTime<minartime)
			minartime=pro[i].arrivalTime;
		
		printf("Enter the Burst Time : ");
		scanf("%d",&pro[i].burstTime);
		pro[i].processNum=(i+1);
		pro[i].fetched=0;
		sprintf(pro[i].processName,"P%d",(i+1));
		
	}

/*	pro[0].arrivalTime=1;pro[0].burstTime=18;pro[0].processNum=1;pro[0].fetched=0;pro[0].processName=1;
	pro[1].arrivalTime=2;pro[1].burstTime=23;pro[1].processNum=2;pro[1].fetched=0;pro[1].processName=2;
	pro[2].arrivalTime=4;pro[2].burstTime=13;pro[2].processNum=3;pro[2].fetched=0;pro[2].processName=3;
	pro[3].arrivalTime=13;pro[3].burstTime=10;pro[3].processNum=4;pro[2].fetched=0;pro[3].processName=4;*/
		

	
	
	printf("\n\n\t\tGiven State: \n\nProcess \tArrivalTime\tBurstTime\n");
	printf("------------------------------------------\n");
	for(i=0;i<n;i++)
	{
		pro[i].tempburstTime=pro[i].burstTime;
		printf("%s\t\t%d\t\t%d\n",pro[i].processName,pro[i].arrivalTime,pro[i].burstTime);
		prefinalTotal += pro[i].burstTime;
	}
	
	//sort the processes according to their process id
/*	struct process temp;
	for(i=0;i<n-1;i++){
		for(j=i+1;j<n;j++){
			if(pro[i].arrivalTime>pro[j].arrivalTime){
				temp=pro[i];
				pro[i]=pro[j];
				pro[j]=temp;
			}
		}
	}
	*/
		
	/*printf("\n\n\t\tAfter sorting: \n\nProcess \tArrivalTime\tBurstTime\n");
	printf("------------------------------------------\n");
	for(i=0;i<n;i++)
	{
		pro[i].tempburstTime=pro[i].burstTime;
		printf("%s\t\t%d\t\t%d\n",pro[i].processName,pro[i].arrivalTime,pro[i].burstTime);
		prefinalTotal += pro[i].burstTime;
	}*/
	
	findCompletionTime();
	findTimes();
	
	printf("\n\n\n\t\t\tFinal Result: \n\nProcess\tArrivalTime\tBurstTime\tCompletionTime\tTurnAroundTime\tWaitingTime\n");
	
	printf("---------------------------------------------------------------------------------------------\n");

	for(i=0;i<n;i++){
		printf("%s",pro[i].processName);
		printf("\t\t%d",pro[i].arrivalTime);
		printf("\t\t%d",pro[i].tempburstTime);
		printf("\t\t%d",pro[i].completionTime);
		printf("\t\t%d",pro[i].turnaroundTime);
		printf("\t\t%d\n",pro[i].waitingTime);
		
	}
	
	
	printf("\n\nTotal Turn Around Time : %d",totalturnAroundTime);
	printf("\nTotal Waiting Time : %d",totalWaitTime);
	printf("\nAverage Turn Around Time : %.2f",(totalturnAroundTime/(float)n));
	printf("\nAverage Waiting Time : %.2f",(totalWaitTime/(float)n));
}
