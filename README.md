# SPI-communication-
 In order to test the SPI communication between the  Raspberry Pi and Arduino, you will need a Raspberry Pi, Arduino and 4 wires.  In our trial the Arduino will be a slave whereas the Raspberry Pi is going to be the master. 
You should upload the Arduino code ‘ArduinoSlave.ino’  to you Arduino and you are going to run the c++ code ‘user.cpp’  from your Raspberry Pi. 
You should connect the Raspberry Pi and Arduino pins in the following manner.
MOSI to MOSI
MISO to MISO
SCLK to SCLK
SS to SS


                 If you are using Arduino mega   Raspberry PI pin number(BOARD numbering)  If you are using Arduino uno
    Pin of MOSI            51                              19                                  11
    Pin of MISO            50                              21                                  12
    Pin of SCLK            52                              23                                  13
    Pin of SS or CE        53                              24                                  10

 When you run the code 'user.cpp ', it asks you to enter the command  and sends it to Arduino via SPI. According to the communication protocol you are expected to send 8 bytes header follow with the packet body.  Since the use of the first 8 bytes header is not described well on the protocol, I chose to assume them as a redundant bytes. So you don’t have to care about what you should write on the first 8 characters. The characters you write after the 9th character must be written according to the communication protocol between Raspberry Pi and Dr. Roboto.  
 The Arduino(slave) code will receive the characters you send and display a message on the serial monitor screen of Arduino. The message is a verification to the command you send.  Even though there are some amount of commands for the different kinds of the robot body listed in the protocol,i only make the Arduino to understand the head motor and speaking commands for the time being. See the following portion of text I take from the protocol
   
         “……...Take this as example
          <MO=HT,1,0.5>
          All motor command start with "<MO="
           and ended with >
           After "=" it is the motor name. "HT" is head turn motor.
           after "HT" wound be the motor position. This example is 1, This number could be 0, 0.1, 0.2, …0.9, 1 responsible for different position
           If it is 1, it will turn to right. If it is 0, it will turn to left. If it is 0.5, it will turn to center.
          after motor position would be the time required to reach that position. This example is 0.5 means it would take 0.5 second to move the motor from current position to that position
          This number could be from 0, 0.1, 0.2…….1, 2, 2.3, 2.5……..to maximum 9, the smaller number is, the faster speed……...”

          While HT is for head turn HN is for head up or down. For example  If it is <MO=HN,1,0.5>, it is head up while  If it is <MO=HN,0,0.5>, it is head down.

            Below is another example including speaking command..							
            master send out the following to let robot do some motion and talk									
            "abcdefgh<MO=HT,1,1><MO=HN,1,1>Just for testing."
										
After sending these command robot will turn the head to right and up and speak Just for testing.										

Additional things you should(must) do
    * You should also add 'P' at the end of your command since it stops sending after it got the character 'P'(a protocol i added for the ease of your testing).
     * You should also add ‘*” at the end of a speaking command instead of a full stop.
      So the above example should be

      "abcdefgh<MO=HT,1,1><MO=HN,1,1>Just for testing*P"


     NB:
     *The first 8 character , in this case “abcdefgh”, doesn't have to make sense 
     *You can add a speaking command in the middle of two head commands or in the beginning of a command.
