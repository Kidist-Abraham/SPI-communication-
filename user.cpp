


#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <fcntl.h>
#include <cstring>
#include <iostream>
//#include <thread>
//#include <chrono>
//#include <errno.h>

#include <unistd.h>
using namespace std;


int fd;

unsigned char  command[100];

int spiTxRx(unsigned char txDat);
int g;


int main (void)
{
bool goodToGo;
unsigned char resultByte;

   fd = open("/dev/spidev0.0", O_RDWR);

   unsigned int speed = 1000000;
   unsigned int delay=10000;
   ioctl (fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);

   while (1)
   { g=0;
      cout<<"please enter"<<endl;
   cin>>command;
   cout<<command<<endl;
   
   int size=(((int)command[2]-48)*10)+((int)command[3]-48);
   
   
  // do
   //{
     // goodToGo=false;
      //spiTxRx('R');
      //usleep(900);
      
      //resultByte=spiTxRx(command[0]);
      //if(resultByte=='A')
      //{
        // goodToGo=true;
         
        // }
         //usleep(900);
         
         //}
 //while(goodToGo==false);
 
 
     for (int i = 0; i < 100; i++)
      { 
          do
   {  cout<<"I am checking"<<endl;
      goodToGo=false;
      spiTxRx('R');
      
      
     usleep(delay);
      
      resultByte=spiTxRx(command[i]);
      cout<<g<<" :";
      g++;
      cout<<command[i]<<endl;
      
      cout<<"from arduino :"<<resultByte<<endl;
      if(resultByte=='A')
      {
         goodToGo=true;
         
         }
        sleep(0.5);
         
         }
 while(goodToGo==false);
 
 if (command[i]=='P')
 break;
         
         
         
     //if(command[i]=='P') {
        //spiTxRx(command[i]);
      //cout<<command[i]<<endl;
      //sleep(5);
        
        //}   
      //else {    
     //spiTxRx(command[i]);
     // cout<<command[i]<<endl;
   //  sleep(1);
 // }
     
    }
    
   // resultByte=spiTxRx(0);
    

}
}


int spiTxRx(unsigned char txDat)
{
 
  unsigned char rxDat;

  struct spi_ioc_transfer spi;

  memset (&spi, 0, sizeof (spi));

  spi.tx_buf        = (unsigned long)&txDat;
  spi.rx_buf        = (unsigned long)&rxDat;
  spi.len           = 1;

  ioctl (fd, SPI_IOC_MESSAGE(1), &spi);

  return rxDat;
}
