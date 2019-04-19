/*
Ques. 2. 
Three students (a, b, c) are arriving in the mess at the same time. The id numbers of these students are 2132, 2102, 2453 and 
the food taken time from the mess table is 2, 4 and 8 minutes. If the two students have same remaining time so it is 
broken by giving priority to the students with the lowest id number. Consider the longest remaining time first (LRTF) scheduling algorithm
 and calculate the average turnaround time and waiting time.
 */

#include<stdio.h>

struct process{
	int processid;
	int arrivalTime;
	int burstTime;
	char processName;

	int tempburstTime;
	int completionTime;
	int waitingTime;
	int turnaroundTime;
};
struct process pro[3]; 
int totalTime=0,prefinalTotal=0;
int tempProcessID=0,totalWaitTime=0,totalturnAroundTime=0;
int n; //for number of process


void printques()
{
	printf("Ques. 12. Three students (a, b, c) are arriving in the mess at the same time. The id numbers of these students are 2132, 2102, 2453 and \nthe food taken time from the mess table is 2, 4 and 8 minutes. If the two students have same remaining time so it is \nbroken by giving priority to the students with the lowest id number. Consider the longest remaining time first (LRTF) scheduling algorithm\nand calculate the average turnaround time and waiting time.");
}
//function to find the largest burst time process
int largestBurstTime(int pid) 
{ 
    int max = 0, i; 
    for (i = 0; i < n; i++)
	 { 
        
        if (pro[i].burstTime > pro[max].burstTime && pro[i].burstTime!=0) 
        {
        	max = i; 
        	tempProcessID = pro[i].processid;
		}
    } 
    return max; 
}

//function to display the ongoing process
int findCompletionTime()
{
	printf("\n\tProcess Execeution Chart\n\t---------------------------\n\n");
	int index; 
    int flag = 0;
	int index1;  
    while (1)
	 { 
        
        index = largestBurstTime(tempProcessID); 
       // printf("\n%d",index);
      /*  if(index==index1)
        {
        	totalTime++;
        	continue;
		}*/
        printf("Process executing at time %d is : %c \t", totalTime, pro[index].processName ); 
        pro[index].burstTime -= 1; 
        totalTime += 1; 
    
        if (pro[index].burstTime == 0) 
		{ 
            pro[index].completionTime = totalTime; 
            printf(" Process  %c is completed at %d ", pro[index].processName, totalTime); 
        } 
        printf("\n");
        index1=index;
        if (totalTime == prefinalTotal) 
            break; 
    } 
}

//function to find TAT,WT 
void findTimes()
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

//driver function
int main()
{
	//printf("Program 12 ");
	printques();
	
	//initializing all the Processes(students)
	//Time taken for taking food is the burst time 
	//as all the students(process) arrive at the same time so it is same for all : 0
	printf("\n\nEnter the number of processes : ");
	scanf("%d",&n);
	int at=0;
	printf("\n\nEnter the Arrival Time this is same for all processess : ");
	scanf("%d",&at);
	int i=0,j=0,pid;
	char ch='A';
	for(i =0;i<n;i++)
	{
		printf("\nFor Process %d :\n----------------------- ",(i+1));
		printf("\nEnter the process id : ");
		scanf("%d",&pid);	
	/*	flag=0;
		for(j=0;j<i;j++)
		{
			if(pro[j].processid==pid)
				flag=1;
		}
		if(flag==1)
		{
			printf("\nNo Two Process can have same Process IDs !")
		}
		esle*/
		pro[i].processid=pid;
			
		printf("Enter the Burst Time : ");
		scanf("%d",&pro[i].burstTime);
		pro[i].processName=ch;
		pro[i].arrivalTime=at;
		ch++;
	}
	/*pro[0].processid=2132;pro[0].arrivalTime=0;pro[0].burstTime=2;pro[0].processName='A';
	pro[1].processid=2102;pro[1].arrivalTime=0;pro[1].burstTime=4;pro[1].processName='B';
	pro[2].processid=2453;pro[2].arrivalTime=0;pro[2].burstTime=8;pro[2].processName='C';*/
	
	printf("\n\n\t\tGiven State: \n\nProcess name\tProcess ID\tArrivalTime\tBurstTime\n");
		printf("-----------------------------------------------------------------\n");

	for(i=0;i<n;i++){
		pro[i].tempburstTime=pro[i].burstTime;
		printf("%c\t\t%d\t\t%d\t\t%d\n",pro[i].processName,pro[i].processid,pro[i].arrivalTime,pro[i].burstTime);
		prefinalTotal+=pro[i].burstTime;	//sum of BurstTime of all the processess
	}
	
	//sort the processes according to their process id
	
	struct process temp;
	for(i=0;i<n-1;i++){
		for(j=i+1;j<n;j++){
			if(pro[i].processid>pro[j].processid){
				temp=pro[i];
				pro[i]=pro[j];
				pro[j]=temp;
			}
		}
	}
	
	totalTime=pro[0].arrivalTime;
	tempProcessID=pro[0].processid;
	prefinalTotal+=pro[0].arrivalTime;
	
	printf("\n\n");
	findCompletionTime();
	
	findTimes();
	
	
	printf("\n\n\t\t\tFinal Result: \n\nProcess\tProcess ID\tArrivalTime\tBurstTime\tCompletionTime\tTurnAroundTime\tWaitingTime\n");
	
	printf("----------------------------------------------------------------------------------------------------------\n");

	for(i=0;i<n;i++){
		printf("%c",pro[i].processName);
		printf("\t%d",pro[i].processid);
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
