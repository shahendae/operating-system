#include <stdio.h>
#include <stdlib.h>
typedef struct _PCB
{   int process_id;
    int arrival_time;
    int cpulength;
    int iolength;
    int wait_time;
    int run_time;
    int done;
    int end;
    int rt;
}PCB;

typedef struct _linked_list
{
    PCB pcb;
    struct _linked_list *next;
}*linked_list;


int process_count;
linked_list ready_queue;
int cpu_cycles;
int process_id[256];
int arrival_time[256];
int cpulength[256];
int io_length[256];
int index;
int Total_runtime=0;
float utilization;
int turnaround;
int rt[256];

PrintPCB(PCB pcb)
{
    printf("\tProcess ID: %d, Arrival Time: %d, cpu Length: %d, IO length:%d rt: %d\n", pcb.process_id, pcb.arrival_time, pcb.cpulength,pcb.iolength,pcb.rt);
}

PrintReadyQueue()
{
    linked_list ptr;
    ptr = ready_queue;
    printf("\n\tPrinting Ready Queue\n");
    while(ptr!=NULL)
    {
        PrintPCB(ptr->pcb);
        ptr = ptr->next;
    }
}
Dequeue()
{
    linked_list temp;
    temp = ready_queue;
    ready_queue = ready_queue->next;
    free(temp);

}

/*
Processing()
{
    linked_list ptr;
    ptr=ready_queue;

   if(ready_queue == NULL)
    {
    return;
    }
    if(ptr->pcb.run_time <ptr->pcb.cpulength)
{
      printf("\t%d:%d running\n",cpu_cycles,ptr->pcb.process_id);
      ptr->pcb.run_time++;
}
else if(ptr->pcb.run_time==ptr->pcb.cpulength)
{
    printf("\t%d:%d blocked\n",cpu_cycles,ptr->pcb.process_id);
    ptr->pcb.run_time++;
}
 }
*/
EnqueueProcess(int arrival, int cpulength,int iolength,int pid)
{
    linked_list temp;
    linked_list ptr;
    Total_runtime=Total_runtime+cpulength;
    if (ready_queue == NULL)
    {
        temp = malloc(sizeof(struct _linked_list));
        temp->pcb.arrival_time = arrival;
        temp->pcb.cpulength = cpulength;
        temp->pcb.process_id = pid;
        temp->pcb.iolength=iolength;
        temp->pcb.run_time = 0;
        temp->pcb.wait_time = 0;
        temp->pcb.done=0;
        temp->pcb.end=0;
        temp->pcb.rt=2*cpulength;
        temp->next = NULL;
        ready_queue = temp;


    }
    else
    {
        ptr = ready_queue;

        while(ptr->next != NULL)
        {
            ptr = ptr->next;
        }
        temp = malloc(sizeof(struct _linked_list));
        temp->pcb.arrival_time = arrival;
        temp->pcb.cpulength= cpulength;
        temp->pcb.iolength= iolength;
        temp->pcb.process_id = pid;
        temp->pcb.run_time = 0;
        temp->pcb.wait_time = 0;
        temp->pcb.done=0;
        temp->pcb.end=0;
        temp->pcb.rt=2*cpulength;
        temp->next = NULL;
        ptr->next = temp;
    }
    process_count++;
}
int cycleNo=1;
RunSimulation()
{
    int index2 = 0;
    cpu_cycles = 0;
    int running=0;

    for(index2=0;index2<4;index2++)
        {
            EnqueueProcess(arrival_time[index2], cpulength[index2],io_length[index2],process_id[index2]);
        }
        PrintReadyQueue();
        linked_list ptr;
        ptr=ready_queue;
        int node=0;
        int finished=0;
    while(ptr!=NULL)
    {int a=ptr->pcb.run_time;
    int b=ptr->pcb.cpulength;
    int c=ptr->pcb.arrival_time;
    int d=ptr->pcb.iolength;

    if(ready_queue == NULL)
    {
    return 1;
    }
    if(ptr->pcb.done==0){
    if((ptr->pcb.run_time <ptr->pcb.cpulength&&ptr->pcb.arrival_time<=cpu_cycles)||(ptr->pcb.wait_time==ptr->pcb.iolength&&ptr->pcb.run_time>=ptr->pcb.cpulength))
{

    if(running==0){
      printf("\t%d:%d running\t",cpu_cycles,ptr->pcb.process_id);
      ptr->pcb.run_time++;
      running=1;}
     else{
            printf("\t%d:%d ready\t",cpu_cycles,ptr->pcb.process_id);

      }
}
   else if(ptr->pcb.run_time>=ptr->pcb.cpulength&&ptr->pcb.wait_time<ptr->pcb.iolength)
{
    printf("\t%d:%d blocked\t",cpu_cycles,ptr->pcb.process_id);
    ptr->pcb.run_time++;
    ptr->pcb.wait_time++;

}}

node++;

if(node%process_count==0){
    ptr=ready_queue;
    cpu_cycles++;
    running=0;
    printf("\n");
}

else{
        ptr=ptr->next;}

   if(ptr->pcb.run_time==ptr->pcb.cpulength+ptr->pcb.cpulength+ptr->pcb.iolength&&ptr->pcb.done==0){
        ptr->pcb.done=1;
        ptr->pcb.end=cpu_cycles;
        finished++;

   }
   if(finished==process_count){
    break;
   }

}

 utilization=1.0*(2*Total_runtime)/cpu_cycles;
 cpu_cycles--;
 printf ("\n Finishing time= %d \n",cpu_cycles);

}
ReadFile()
{

    int arrival, length,iolength,pid;
    int sum_bt=0;
    FILE *fp;
    index = 0;
    fp = fopen("sample.txt", "rw");
    while(!feof(fp))
{   fscanf(fp, "%d %d %d %d", &pid, &length,&iolength, &arrival);
    process_id[index]= pid;
    cpulength[index] = length;
    io_length[index]= iolength;
    arrival_time[index] = arrival;

    rt[index]=cpulength[index];
    index++;
}
    fp = NULL;
}
void sortQueue()
{
    int i,j,temp1,temp2,temp3,temp4;
    for (i = 0; i < 4; i++)
        { for (j = i+1; j < 4; j++) {
           if (arrival_time[i] > arrival_time[j]) {
              temp1 = process_id[i];
              process_id[i] = process_id[j];
              process_id[j] = temp1;
              temp2= cpulength[i];
              cpulength[i]=cpulength[j];
              cpulength[j]=temp2;
              temp3= io_length[i];
              io_length[i]=io_length[j];
              io_length[j]=temp3;
              temp4= arrival_time[i];
              arrival_time[i]=arrival_time[j];
              arrival_time[j]=temp4;

         }
      }
    }
}

void sortByArrival()
{
int temp;
int i,j;
for(i=0;i<4-1;i++)
for(j=i+1;j<4;j++)
{
 if(arrival_time[i]>arrival_time[j])
 {
  temp=arrival_time[i];
  arrival_time[i]=arrival_time[j];
  arrival_time[j]=temp;

 }
}
}


void RR()
{
 int i,j,tslice,ttime;

ReadFile();

sortQueue();
for(i=0;i<4;i++){
  rt[i]=cpulength[i];
 //printf("pid %d cpu time %d arrival %d\n",process_id[i],rt[i],arrival_time[i]);
 }

printf("\nEnter the time quantum:");
scanf("%d",&tslice);

printf("pid\t remain time");
for(j=0;j<4;j++)
            {
      for(i=0;i<4;i++)
{
      if(rt[i]>0)
{
if(rt[i]>=tslice)
{
ttime+=tslice;
rt[i]=rt[i]-tslice;
printf("\n%d\t\t %d \t\t",process_id[i],rt[i]);
if(rt[i]==0)
j++;
}

else
{
ttime+=rt[i];
rt[i]=0;
printf("\n%d\t\t %d \t\t",process_id[i],rt[i]);
}
}
 }
       }



 int index2 = 0;
    cpu_cycles = 0;
    int running=0;

    for(index2=0;index2<4;index2++)
        {
            EnqueueProcess(arrival_time[index2], cpulength[index2],io_length[index2],process_id[index2]);
        }
        PrintReadyQueue();

        linked_list ptr;
        ptr=ready_queue;
        int node=0;
        int finished=0;
    while(ptr!=NULL)
    {
    int a=ptr->pcb.run_time;
    int b=ptr->pcb.cpulength;
    int c=ptr->pcb.arrival_time;
    int d=ptr->pcb.iolength;

linked_list p=ready_queue;
    while(p)
    {
   // printf("nouran");
      if(p->pcb.done==0){
      if((ptr->pcb.run_time <ptr->pcb.cpulength&&ptr->pcb.arrival_time<=cpu_cycles)||(ptr->pcb.wait_time==ptr->pcb.iolength&&ptr->pcb.run_time>=ptr->pcb.cpulength))
      {
           //int a=p->pcb.rt;
           //printf("%d",p->pcb.rt);
           if(p->pcb.cpulength<tslice&&p->pcb.rt>=tslice){
            cycleNo=p->pcb.cpulength;
           }
            else if(p->pcb.rt<tslice){
            cycleNo=p->pcb.rt;
            }
            else{
            cycleNo=tslice;

            }
            break;
      }

      }

        p=p->next;

    }



    if(ready_queue == NULL)
    {
    return 1;
    }
    if(ptr->pcb.done==0){
    if((ptr->pcb.run_time <ptr->pcb.cpulength&&ptr->pcb.arrival_time<=cpu_cycles)||(ptr->pcb.wait_time==ptr->pcb.iolength&&ptr->pcb.run_time>=ptr->pcb.cpulength))
{

        if(running==0){
    int s;
    for(s=0;s<cycleNo;s++){
      printf("\t%d:%d running\t",cpu_cycles+s,ptr->pcb.process_id);
      ptr->pcb.run_time++;
      ptr->pcb.rt--;
      //Total_runtime=Total_runtime+ptr->pcb.run_time;
      running=1;
      }}
     else{
     int s;
     for(s=0;s<cycleNo;s++){
            printf("\t%d:%d ready\t",cpu_cycles+s,ptr->pcb.process_id);
}
      }
}
   else if(ptr->pcb.run_time>=ptr->pcb.cpulength&&ptr->pcb.wait_time<ptr->pcb.iolength)
{   int s;
    for(s=0;s<cycleNo;s++){
    printf("\t%d:%d blocked\t",cpu_cycles+s,ptr->pcb.process_id);
    ptr->pcb.run_time++;
    ptr->pcb.wait_time++;
    //Total_runtime=Total_runtime+ptr->pcb.run_time;
    }
}}

node++;

if(node%process_count==0){
    ptr=ready_queue;
    cpu_cycles+=cycleNo;
    running=0;
    printf("\n");
}

else{
        ptr=ptr->next;}

   if(ptr->pcb.run_time==ptr->pcb.cpulength+ptr->pcb.cpulength+ptr->pcb.iolength&&ptr->pcb.done==0){
        ptr->pcb.done=1;
        ptr->pcb.end=cpu_cycles;
        finished++;

   }
   if(finished==process_count){
    break;
   }

}

/*
 utilization=(Total_runtime)/cpu_cycles;
 cpu_cycles--;
 printf ("\n Finishing time= %d \n",cpu_cycles);

*/

/*

printf("pid\t remain time");
for(j=0;j<4;j++)
            {
      for(i=0;i<4;i++)
{
      if(rt[i]>0)
{
if(rt[i]>=tslice)
{
ttime+=tslice;
rt[i]=rt[i]-tslice;
printf("\n%d\t\t %d \t\t",process_id[i],rt[i]);
if(rt[i]==0)
j++;
}

else
{
ttime+=rt[i];
rt[i]=0;
printf("\n%d\t\t %d \t\t",process_id[i],rt[i]);
}
}
 }
       }
*/
utilization=1.0*(2*Total_runtime)/cpu_cycles;
//printf("\n%d",Total_runtime);
 cpu_cycles--;
 printf ("\n Finishing time= %d \n",cpu_cycles);

       }


void FCFS()
{

   ReadFile();
    sortQueue();
    RunSimulation();
    printf("\n CPU Utilization= %.2f \n",utilization);
    linked_list p=ready_queue;
    while(p)
    {
        p->pcb.end=p->pcb.end-1;
        turnaround=p->pcb.end-p->pcb.arrival_time+1;
        printf("Turnaround for process %d = %d\n",p->pcb.process_id,turnaround);
        p=p->next;

    }



}

int main()
{
    ready_queue = NULL;
    process_count = 0;
    int ch;

    printf("\n 0. FCFS");
    printf("\n 1. Round Robin");
    printf("\n 2. Exit");
	printf("\n\n Choose CPU SCHEDULING ALGORITHMS\n");
    scanf("%d", &ch);
      switch (ch)

          {
             case 0:

               FCFS();

    break;


            case 1 :

            RR();
            printf("\n CPU Utilization= %.2f \n",utilization);
    linked_list p=ready_queue;
    while(p)
    {
        p->pcb.end=p->pcb.end-1;
        turnaround=p->pcb.end-p->pcb.arrival_time+1;
        printf("Turnaround for process %d = %d\n",p->pcb.process_id,turnaround);
        p=p->next;

    }

            break;


    }

return 0;

}
