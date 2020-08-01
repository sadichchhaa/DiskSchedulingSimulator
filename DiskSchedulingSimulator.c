/*DISK SCHEDULING SIMULATOR*/

#include<stdio.h>
#include<math.h>
#include<stdlib.h>

int printline();
int fcfs(int max, int head, int n, int value[]);
int sstf(int max, int head, int n, int value[]);
int scan(int max, int head, int n, int value[]);
int cscan(int max, int head, int n, int value[]);
int look(int max, int head, int n, int value[]);
int clook(int max, int head, int n, int value[]);

int main()
{
  int n,head,i,max,best;
  int static value[20], s[20];
  // Accepting required inputs
  printf("Enter the max range of disk: ");
  scanf("%d",&max);
  printf("Enter the initial head position: ");
  scanf("%d",&head);
  printf("Enter the size of queue request: ");
  scanf("%d",&n);
  printf("Enter the queue of disk positions to be read:\n");
  for(i=1;i<=n;i++)
  {
    scanf("%d", &value[i]);
  }
  printline();
  printf("\n\n\tTEST FOR THE BEST!\n\n");
  s[1] = fcfs(max,head,n,value);
  s[2] = sstf(max,head,n,value);
  s[3] = scan(max,head,n,value);
  s[4] = cscan(max,head,n,value);
  s[5] = look(max,head,n,value);
  s[6] = clook(max,head,n,value);
  printline();
  // Selection of the best suited algorithm
  for(i=2;i<7;i++)
  {
    if(s[i-1]>s[i])
    {
      best = i;
    }
  }
  if(best==1)
  {
    printf("\n\nTHE BEST: FCFS Algorithm\nwith seek time %d ns", s[1]);
  }
  else if(best==2)
  {
    printf("\n\nTHE BEST: SSTF Algorithm\nwith seek time %d ns", s[2]);
  }
  else if(best==3)
  {
    printf("\n\nTHE BEST: SCAN Algorithm\nwith seek time %d ns", s[3]);
  }
  else if(best==4)
  {
    printf("\n\nTHE BEST: CSCAN Algorithm\nwith seek time %d ns", s[4]);
  }
  else if(best==5)
  {
    printf("\n\nTHE BEST: LOOK Algorithm\nwith seek time %d ns", s[5]);
  }
  else
  {
    printf("\n\nTHE BEST: CLOOK Algorithm\nwith seek time %d ns", s[6]);
  }
  printf("\n\n");
  printline();
  return 0;
}

int printline()
{
  int i;
  for(i=1;i<=30;i++)
    printf("*");
  return 0;
  printf("\n");
}

// FCFS Disk Scheduling Algorithm
int fcfs(int max, int head, int n, int value[])
{
  int i,j,seek=0,diff;
  float avg;
  value[0]=head;
  for(j=0;j<=n-1;j++)
  {
    // Calculating the absolute distance
    diff=abs(value[j+1]-value[j]);
    // Increase the total count
    seek+=diff;
  }
  printline();
  printf("\nFCFS ALGORITHM\n");
  printf("Total seek time is %d\n",seek);
  // Calculating the average time
  avg=seek/(float)n;
  printf("Average seek time is %.2f\n",avg);
  return seek;
}

// SSTF Disk Scheduling Algorithm
int sstf(int max, int head, int n, int value[])
{
  int i, j,diff = 0, seek = 0, t=n, h=head;
  int least = value[1], least_index=1;
  int queue[20];
  for(i=1;i<=n;i++)
    queue[i] = value[i];
  float avg;

  for(i=1;i<n;i++)
  {
    // Fetches the element with least difference
    for(j=1;j<t;j++)
    {
      if((abs(h-least))>(abs(h-queue[j+1])))
      {
        least = queue[j+1];
        least_index = j+1;
      }
    }
    // Calculates the difference
    diff = abs(h-least);
    // Increases the total seek time
    seek = seek + diff;
    // Removes the accessed element from the queue
    if(least_index!=t)
    {
      for(j=least_index;j<t;j++)
      {
        queue[j] = queue[j+1];
      }
    }
    // Updates the count of elements in request queue
    t=t-1;
    h = least;
    least = queue[1];
    least_index = 1;
  }
  diff = abs(h-least);
  seek = seek + diff;
  printline();
  printf("\nSSTF ALGORITHM\n");
  printf("Total seek time is: %d\n",seek);
  avg=seek/(float)n;
  printf("Average seek time is :%.2f\n",avg); 
  return seek;
}

// SCAN Disk Scheduling Algorithm
int scan(int max, int head, int n, int value[])
{
  int a[20],i,j,k,seek=0,diff,temp,b[20],c[20],temp1=0,temp2=0;
  float avg;
  // Seperating and arranging seek values in two different arrays
  for(i=1;i<=n;i++)
  {
    temp = value[i];
    // smaller than head value
    if(temp<=head)
    {
      b[temp1]=temp;
      temp1++;
    }
    else
    // greater than head value
    {
      c[temp2]=temp;
      temp2++;
    }
  }
  // shifting of head values
  for(i=0;i<temp1-1;i++)
  {
    for(j=i+1;j<temp1;j++)
    {
      if(b[i]<b[j])
      {
        temp=b[i];
        b[i]=b[j];
        b[j]=temp;
      }
    }
  }
  // Combining both array
  for(i=0;i<temp2-1;i++)
  {
    for(j=i+1;j<temp2;j++)
    {
      if(c[i]>c[j])
      {
        temp=c[i];
        c[i]=c[j];
        c[j]=temp;
      }
    }
  }
  for(i=1,j=0;j<temp1;i++,j++)
    a[i]=b[j];
    // here after completing right side head value become 0
  a[i]=0;
  a[i+1]=0;
  for(i=temp1+3,j=0;j<temp2;i++,j++)
  a[i]=c[j];
  a[0]=head;
  for(j=0;j<=n+1;j++)
  {
    // Calculating the absolute difference
    diff=abs(a[j+1]-a[j]);
    // Increase the total count
    seek+=diff;
  }
  printline();
  printf("\nSCAN ALGORITHM");
  printf("\nTotal seek time is: %d\n",seek);
  // Calculating average seek time
  avg=seek/(float)n;
  printf("Average seek time: %.2f\n",avg);
  return seek;
}

// CSCAN Disk Scheduling Algorithm
int cscan(int max, int head, int n, int value[] )
{
  int i,j,temp,temp1=0,temp2=0,diff,seek=0,a[20],b[20],c[20];
  float avg;
  // Segregating values greater and less that     head in two different arrays
  for(i=1;i<=n;i++)
  {
    temp = value[i];
    if(temp>=head)
    {
      b[temp1]=temp;
      temp1++;
    }
    else
    {
      c[temp2]=temp;
      temp2++;
    }
  }
  // Arranging both arrays in order
  for(i=0;i<temp1-1;i++)
  {
    for(j=i+1;j<temp1;j++)
    {
      if(b[i]>b[j])
      {
        temp=b[i];
        b[i]=b[j];
        b[j]=temp;
      }
    } 
  } 
  for(i=0;i<temp2-1;i++)
  {
    for(j=i+1;j<temp2;j++)
    {
      if(c[i]>c[j]) 
      {
        temp=c[i];
        c[i]=c[j];
        c[j]=temp;
      }
    }
  }
  // Arranging the request queue in the order of its execution 
  for(i=1,j=0;j<temp1;i++,j++)
    a[i]=b[j];
  a[i]=max;
  a[i+1]=0;
  for(i=temp1+3,j=0;j<temp2;i++,j++)
    a[i]=c[j];
  a[0]=head;
  for(j=0;j<=n+1;j++)
  {
    // Calculating the absolute difference
    diff=abs(a[j+1]-a[j]);
    // Increase the total count
    seek+=diff;
  }
  printline();
  printf("\nCSCAN ALGORITHM\n");
  printf("Total seek time is: %d\n",seek);
  // Calculating average seek time
  avg=seek/(float)n;
  printf("Average seek time is :%.2f\n",avg); 
  return seek;
}

// LOOK Disk Scheduling Algorithm
int look(int max, int head, int n, int value[])
{
  int a[20],i,j,k,seek=0,diff,temp,b[20],c[20],temp1=0,temp2=0;
  float avg;
  // Segregating values greater and less than     head in two different arrays
  for(i=1;i<=n;i++)
  {
    temp = value[i];
    if(temp<=head)
    {
      b[temp1]=temp;
      temp1++;
    }
    else
    {
      c[temp2]=temp;
      temp2++;
    }
  }
  // Arranging both arrays in order
  for(i=0;i<temp1-1;i++)
  {
    for(j=i+1;j<temp1;j++)
    {
      if(b[i]<b[j])
      {
        temp=b[i];
        b[i]=b[j];
        b[j]=temp;
      }
    }
  }
  for(i=0;i<temp2-1;i++)
  {
    for(j=i+1;j<temp2;j++)
    {
      if(c[i]>c[j])
      {
        temp=c[i];
        c[i]=c[j];
        c[j]=temp;
      }
    }
  }
  // Combining both arrays to get queue in order of its execution
  for(i=1,j=0;j<temp1;i++,j++)
    a[i]=b[j];
  for(j=0;j<temp2;i++,j++)
    a[i]=c[j];
  a[0]=head;
  for(j=0;j<n;j++)
  {
    // Calculating the absolute difference
    diff=abs(a[j+1]-a[j]);
    // Increase the total count
    seek+=diff;
  }
  printline();
  printf("\nLOOK ALGORITHM\n");
  printf("Total seek time is: %d\n",seek);
  avg=seek/(float)n;
  printf("Average seek time is :%.2f\n",avg); 
  return seek;
}

// CLOOK Disk Scheduling Algorithm
int clook(int max, int head, int n, int value[])
{
  int i,j,temp,temp1=0,temp2=0,diff,seek=0,a[20],b[20],c[20];
  float avg;
  // Segregating values greater and less that     head in two different arrays
  for(i=1;i<=n;i++)
  {
    temp = value[i];
    if(temp>=head)
    {
      b[temp1]=temp;
      temp1++;
    }
    else
    {
      c[temp2]=temp;
      temp2++;
    }
  }
  // Arranging both arrays in order
  for(i=0;i<temp1-1;i++)
  {
    for(j=i+1;j<temp1;j++)
    {
      if(b[i]>b[j])
      {
        temp=b[i];
        b[i]=b[j];
        b[j]=temp;
      }
    } 
  } 
  for(i=0;i<temp2-1;i++)
  {
    for(j=i+1;j<temp2;j++)
    {
      if(c[i]>c[j]) 
      {
        temp=c[i];
        c[i]=c[j];
        c[j]=temp;
      }
    }
  }
  // Arranging the request queue in the order of its execution 
  for(i=1,j=0;j<temp1;i++,j++)
    a[i]=b[j];
  for(j=0;j<temp2;i++,j++)
    a[i]=c[j];
  a[0]=head;
  for(j=0;j<n;j++)
  {
    // Calculating the absolute difference
    diff=abs(a[j+1]-a[j]);
    // Increase total count
    seek+=diff;
  }
  printline();
  printf("\nCLOOK ALGORITHM\n");
  printf("Total seek time is: %d\n",seek);
  // Calculating average seek time
  avg=seek/(float)n;
  printf("Average seek time is :%.2f\n\n",avg); 
  return seek;
}