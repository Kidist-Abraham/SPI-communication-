#include<SPI.h>
#include<avr/wdt.h>
 char buf[50];
 char say[50];

int amBusy=33;
int dataRdy=31;
volatile int sizee;
volatile int pos;
volatile int posF;
volatile boolean pro;
//volatile boolean process_M;
//volatile boolean process_S;
volatile boolean dataready;
//byte a0=0b10101010;////  0xAA or ª 
//byte a1=0b1010101;//  0x55 or U
//byte a2=0x01; //0x03 or 
volatile int p=0;
volatile int i=0;
volatile int hand=0;
volatile int index=0;
void setup(void)
//ww45cdef<MO=HN,1,1.0><MO=HT,1,1.5>just*<MO=HT,1,3.5>
//ww45cdef<MO=HN,1,1.0><MO=HT,1,1.5>

{
  wdt_disable();
  //wdt_enable(WDTO_8S);
  
  pinMode(amBusy,OUTPUT);
  pinMode(dataRdy,OUTPUT);
  Serial.begin(115200);
  
   Serial.println("Starting");
  pinMode(MISO,OUTPUT);
  digitalWrite(amBusy,LOW);
  digitalWrite(dataRdy,LOW);
  SPCR |= _BV(SPE);
  pos=0;
  posF=8;
  pro=false;
 // process_M=false;
  //process_S=false;
  SPI.attachInterrupt();
}
ISR(SPI_STC_vect)
{
  byte check=SPDR;
Serial.println("Here");
//Serial.println(hand);
//Serial.println(SPDR);
 if(hand==0){
   // byte check=SPDR;
   // Serial.println(check);
    if (check=='R')
      {
        Serial.println("comming is R");
      SPDR='A';
      hand++;
      }
      
    
    }
    
   
  
 else{// if (SPDR!='x'&&SPDR!='R'){
   Serial.println("real here");
 //  byte check=SPDR;
   
   buf[pos++]=check;
  i++;
  
  Serial.println(buf[pos-1]);
  //Serial.println(buf);
  hand=0;
   if(check=='P'){
//      Serial.println(buf);
  pro=true;
//  i=0;
//   pos=0;
//   Serial.println("too");
//   Serial.println(buf);
//   
//
//   SPDR='F';
   }
//  
//   }
//   
//    else if (hand==1&&SPDR=='R'){
//      Serial.println("I just saved it:)");
//    SPDR='A';
//    
//    }
  
  

 }
}

 void loop (void)
{
  if(pro){
    Serial.println("in the loop");
    Serial.print("llllllll :");
    Serial.println(buf[posF]);
if (buf[posF]=='<'){

process_M();
posF=posF+13;
if(buf[posF]=='P'){
 char buf[50];
pro=false;
posF=8;
setWDT(0b00001000);
wdt_reset();

}
}
else{

process_S();
posF=posF+p+1;
if(buf[posF]=='P'){
  char buf[50];
pro=false;
posF=8;
setWDT(0b00001000);
wdt_reset();
}
}

  }
  
}
  
  void sendData(char data){
    digitalWrite(amBusy,LOW);
  digitalWrite(dataRdy,HIGH);
  SPDR=data;
 // Serial.println(data);
  
  }
  
  byte bcdToDec(byte val)
{
  return ( (val/16*10) + (val%16) );
}


//void process(){
//  while(1){
//   
//if (buf[posF]=='<'){
//process_M();
//posF=posF+13;
//Serial.println(buf[posF]);
//if(buf[posF]=='P'){
//break;
//}
//}
//else{
//process_S();
////posF=p+1;
//if(buf[posF]=='P')
//break;
//}
//  }
//}
void process_M()
  {
 //buf[pos]=0;
 Serial.print("i am @ :");
Serial.println(buf[posF]);
 
    if(buf[posF+4]=='H'&& buf[posF+5]=='T'){
    if(buf[posF+7]=='1')
    Serial.print("Robot is turning its head to right in ");
    else
     Serial.print("Robot is turning its head to left in ");
    Serial.print(buf[posF+9]);
    Serial.print(buf[posF+10]);
    Serial.print(buf[posF+11]);
    Serial.println(" second");
    
    }
    else if(buf[posF+4]=='H'&& buf[posF+5]=='N'){
      Serial.println(buf[7]);
      if(buf[posF+7]=='1')
       Serial.print("Robot is turning its head up in ");
      else
     Serial.print("Robot is turning its head down in ");
    Serial.print(buf[posF+9]);
    Serial.print(buf[posF+10]);
    Serial.print(buf[posF+11]);
    Serial.println(" second");
    
    
    
    }
    
   // process_M=false;
    digitalWrite(amBusy,LOW);
     
      


  }
  void process_S(){
     Serial.print("i am @ :");
Serial.println(buf[posF]);
    p=0;
   Serial.println(buf);
  for(int ii=posF; buf[ii]!='*';ii++){
  say[p]=buf[ii];

  p++;
  }
   Serial.println("Speaking: ");
    Serial.println(say);
  
 
   // process_S=false;
    digitalWrite(amBusy,LOW);
    
  }

  void setWDT(byte sWDT) {
  WDTCSR |= 0b00011000;
  WDTCSR = sWDT | WDTO_1S;
  wdt_reset();
  
  }
  



