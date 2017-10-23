#include <unistd.h>
#include <fcntl.h>
#include<stdio.h>


int main()
{
   int fd=open("a.txt",O_RDWR,0764);
   int flag=0;
   char arr[100]="+++++";
   struct flock lock;
	lock.l_type = F_WRLCK;
    lock.l_start = 0;
    lock.l_whence = SEEK_SET;
    lock.l_len = 0;
    fcntl(fd, F_SETLKW, &lock);
 
   if(fcntl(fd,F_SETLK,&lock)<0)
   {
     printf("SETLsK FAILURE\n");
   }   

  while(1)
  {
  printf("ok\n");
    if(write(fd,arr,5)<0)
    {
          printf("ERROR\n");
    }
    sleep(1);
  } 


}