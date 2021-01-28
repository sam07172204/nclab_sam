#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define Reverse_String 1

int main(){
   char buf[512];
   int choice,exit=0;
   
   int fp = open("/dev/demo", O_RDWR);
   if(fp == 0) {
      printf("can't open device!\n");
      return -1;
   }
   while(!exit){
   printf("input <1>write <2>read  <3>exit: ");
   scanf("%d",&choice);
   switch(choice){
                  
   case 1: 
           printf("please input a string: ");
	   scanf(" %[^\n]",&buf);
	   write(fp, buf, strlen(buf));
           bzero(buf,sizeof(buf));
           break;
   case 2:                  
        printf("read a string from driver >\n");                     
        read(fp, buf, strlen(buf));          
        printf("%s\n",buf);
        bzero(buf,sizeof(buf));
        break;	

	
   case 3:
           exit = 1;
	   break;	
   default:
           break;        
   
   }
 }
   close(fp); 
   return 0;
}
