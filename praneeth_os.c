#include<stdio.h>
#include<conio.h>
int A1,A2,A3;
int Round_Robin(int a, int b);
int First_come_First_serve(int a, int b);
int Priority(int a , int b);
int waiting_time[20];
int main()
{
	//int A1,A2,A3;
	printf("\nEnter number of processes in queue 1:: ");
	scanf("%d",&A1);
	printf("\nEnter number of processes in queue 2:: ");
	scanf("%d",&A2);
	printf("\nEnter number of processes in queue 3:: ");
	scanf("%d",&A3);
	int po1,po2,po3;
	
	char name[3];
	printf("\nEnter priority of queue 1:: ");
	scanf("%d",&po1);
	while(1)
	{
	printf("\nEnter priority of queue 2:: ");
	scanf("%d",&po2);
	if(po1!=po2)
	{
		break;
	}
	else
	{
		printf("priorities cannot be equal");
	}
	}
	while(1)
	{
	printf("\nEnter priority of queue 3:: ");
	scanf("%d",&po3);
	if(po1!=po3&&po2!=po3)
	{
		break;
	}
	else
	{
		printf("priorities cannot be equal");
	}
	}
	if (po1<po2&&po1<po3)
	{
		Round_Robin(A1,1);
		if(po2<po3)
		{
			Priority(A2,2);
			First_come_First_serve(A3,3);
		}
		else
		{
			Priority(A3,3);
			First_come_First_serve(A2,2);
		}
	}
	else if(po2<po1&&po2<po3)
	{
		Round_Robin(A2,2);
		if(po1<po3)
		{
			Priority(A1,1);
			First_come_First_serve(A3,3);
		}
		else
		{
			Priority(A3,3);
			First_come_First_serve(A1,1);
		}
	}
	else
	{
		Round_Robin(A3,3);
		if(po1<po2)
		{
			Priority(A1,1);
			First_come_First_serve(A2,2);
		}
		else
		{
			Priority(A2,2);
			First_come_First_serve(A1,1);
		}
	}
}

int Round_Robin(int e, int f)
{
	int i, limit, total = 0, x, counter = 0, time_quantum; 
      int wait_time = 0, turnaround_time = 0, arrival_time[10], burst_time[10], temp[10]; 
      float average_wait_time, average_turnaround_time;
      printf("applying Round_Robin on queue no. %d ",f);
      /*printf("\nEnter Total Number of Processes:\t"); 
      scanf("%d", &limit);*/
	  limit=e; 
      x = limit; 
      for(i = 0; i < limit; i++) 
      {
            printf("\nEnter Details of Process[%d]\n", i + 1);
            printf("Arrival Time:\t");
            scanf("%d", &arrival_time[i]);
            printf("Burst Time:\t");
            scanf("%d", &burst_time[i]); 
            temp[i] = burst_time[i];
      } 
      printf("\nEnter Time Quantum:\t"); 
      scanf("%d", &time_quantum); 
      printf("\nProcess ID\t\tBurst Time\t Turnaround Time\t Waiting Time\n");
      for(total = 0, i = 0; x != 0;) 
      { 
            if(temp[i] <= time_quantum && temp[i] > 0) 
            { 
                  total = total + temp[i]; 
                  temp[i] = 0; 
                  counter = 1; 
            } 
            else if(temp[i] > 0) 
            { 
                  temp[i] = temp[i] - time_quantum; 
                  total = total + time_quantum; 
            } 
            if(temp[i] == 0 && counter == 1) 
            { 
                  x--; 
                  printf("\nProcess[%d]\t\t%d\t\t %d\t\t\t %d", i + 1, burst_time[i], total - arrival_time[i], total - arrival_time[i] - burst_time[i]);
                  wait_time = wait_time + total - arrival_time[i] - burst_time[i]; 
                  turnaround_time = turnaround_time + total - arrival_time[i]; 
                  counter = 0; 
            } 
            if(i == limit - 1) 
            {
                  i = 0; 
            }
            else if(arrival_time[i + 1] <= total) 
            {
                  i++;
            }
            else 
            {
                  i = 0;
            }
      } 
      average_wait_time = wait_time * 1.0 / limit;
      average_turnaround_time = turnaround_time * 1.0 / limit;
      printf("\n\nAverage Waiting Time:\t%f", average_wait_time); 
      printf("\nAvg Turnaround Time:\t%f\n", average_turnaround_time); 
      return 0; 
}
int Priority(int a,int b)
{
	int burst_time[20], process[20], turnaround_time[20], priority[20];
      int i, j, limit, sum = 0, position, temp;
      float average_wait_time, average_turnaround_time;
      printf("applying priority scheduling algorithm on queue no. %d",b);
      /*printf("Enter Total Number of Processes:\t");
      scanf("%d", &limit);*/
      limit=a;
      int ask=1;
      printf("\nEnter Burst Time and Priority For %d Processes\n", limit);
      if(ask=1)
      {
      	for(i = 0; i < limit; i++)
      {
            printf("\nProcess[%d]\n", i + 1);
            printf("Process Burst Time:\t");
            scanf("%d", &burst_time[i]);
            printf("Process Priority:\t");
            scanf("%d", &priority[i]);
            process[i] = i + 1;
      }
      ask=0;
	  }
      for(i = 0; i < limit; i++)
      {
            position = i;
            for(j = i + 1; j < limit; j++)
            {
                  if(priority[j] < priority[position])
                  {
                        position = j;
                  }
            }
            temp = priority[i];
            priority[i] = priority[position];
            priority[position] = temp; 
            temp = burst_time[i];
            burst_time[i] = burst_time[position];
            burst_time[position] = temp;
            temp = process[i];
            process[i] = process[position];
            process[position] = temp;
      }
      waiting_time[0] = 0;
      for(i = 1; i < limit; i++)
      {
            waiting_time[i] = 0;
            for(j = 0; j < i; j++)
            {
                  waiting_time[i] = waiting_time[i] + burst_time[j];
            }
            sum = sum + waiting_time[i];
      }
      average_wait_time = sum / limit;
      sum = 0;
      printf("\nProcess ID\t\tBurst Time\t Waiting Time\t Turnaround Time\n");
      for(i = 0; i < limit; i++)
      {
            turnaround_time[i] = burst_time[i] + waiting_time[i];
            sum = sum + turnaround_time[i];
            printf("\nProcess[%d]\t\t%d\t\t %d\t\t %d\n", process[i], burst_time[i], waiting_time[i], turnaround_time[i]);
      }
      average_turnaround_time = sum / limit;
      printf("\nAverage Waiting Time:\t%f", average_wait_time);
      printf("\nAverage Turnaround Time:\t%f\n", average_turnaround_time);
      return 0;
}

int First_come_First_serve(int c, int d)
{
	float burst_time[30], waiting_time[30], turnaround_time[30];
        float average_waiting_time = 0.0, average_turnaround_time = 0.0;
        int count, j, total_process;
        printf("applying First_come_First_serve on queue no . %d",d);
        /*printf("Enter The Number of Processes To Execute:\t");
        scanf("%d", &total_process);*/
        total_process=c;
        printf("\nEnter The Burst Time of Processes:\n\n");
        for(count = 0; count < total_process; count++)
        {
                printf("Process [%d]:", count + 1);
                scanf("%f", &burst_time[count]);
        }
        waiting_time[0] = 0;   
        for(count = 1; count < total_process; count++)
        {
                waiting_time[count] = 0;
                for(j = 0; j < count; j++)
                {
                        waiting_time[count] = waiting_time[count] + burst_time[j];
                }
        }
        printf("\nProcess\t\tBurst Time\tWaiting Time\tTurnaround Time\n");
        for(count = 0; count < total_process; count++)
        {
                turnaround_time[count] = burst_time[count] + waiting_time[count];
                average_waiting_time = average_waiting_time + waiting_time[count];
                average_turnaround_time = average_turnaround_time + turnaround_time[count];
                printf("\nProcess [%d]\t\t%.2f\t\t%.2f\t\t%.2f", count + 1, burst_time[count], waiting_time[count], turnaround_time[count]);
        }
        printf("\n");
        average_waiting_time = average_waiting_time / count;
        average_turnaround_time = average_turnaround_time / count;
        printf("\nAverage Waiting Time = %f", average_waiting_time);
        printf("\nAverage Turnaround Time = %f", average_turnaround_time);
        printf("\n");
        return 0;
}


