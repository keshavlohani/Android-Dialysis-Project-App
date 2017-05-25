
 #define CMD_LENGTH 64
 #define FRAME_LENGTH 50
 #define HEALTH 0
 #define ACK 1
 #define STAT 2
 #define ERR 3
 #define TYPE_ELM 2
 #define DATA_SIZE 27
 #define RT_MIN   25
 #define RT_MAX   35
 #define CRB_MIN  25 
 #define CRB_MAX  45
 #define CRA_MIN  25
 #define CRA_MAX  45
 #define ON     1
 #define OFF    0
 #define OPEN   1
 #define CLOSE  0
 
 int APT;
 int TMP;
 int Dialysat_Flow;
 int Uf_Goal;
 int Uf_Rate;
 int Blood_Flow;
 int Heparin_Rate;
 int Bolus_Volume;
 int Current_Status = 0;
 int ErrorNo;

 

  char command[CMD_LENGTH];
  int Frame[FRAME_LENGTH];
  int Freq ;
  int RTmax;
  int RTmin;
  int CRBmax;
  int CRBmin; 
  int CRAmax;
  int CRAmin;

  int CD1_Cur = 28;
  int CD2_Cur = 35;
  int CD3_Cur = 28;
  int CD4_Cur = 32;
  // Temperatur sensor value read in recent cycle
  int T1_Cur = 30;
  int T3_Cur = 33;
  int T2_Cur = 30;
  int T4_Cur = 30;
  int T5_Cur = 30;
  int T6_Cur = 29;
  int Stat_Flag;

  int Cur_Cmd;
  int Last_Cmd;


void setup()
{
  
   Serial.begin(9600);
   
   SerialUSB.begin(9600);
    // Initialize the Serial Port 
    CommandReceive();
}


void loop()//schedule of all modules can be done in timer base
{
 CommandReceive();
 CommandHandler();
// DataAquisition();
 //CreateFrame();
 //SendInfo();
 CommandReceive();
 delay(2000);
 CommandReceive();
}
// command receiving routine.
void CommandReceive(){ // command receive
  if(Serial.available() > 0)// Is command receive in serial port.
  {
    int j;
    for( j = 0; j < CMD_LENGTH; j++)
    {
        while(!(Serial.available() > 0)); // read the command till last byte of command
        SerialUSB.print(Serial.read());   // reading position of the serial port frame,i.e 50,49,....
        command[j] = Serial.read();   // reading value of the serial port frame i.e 1,2,.....
         SerialUSB.print(command[j]); 
    }           // Initializing a sample buffer
    command[j]= '\0';
    Cur_Cmd = atoi(command); // command received is of string formate, convert it to int in order to make it compatible with switch.
    return;
  }
  else
    return;
}

// Frame sending routine.
void SendInfo(){ // Send the most recently aquired frame.
  int i;
  for( i = 0; i < DATA_SIZE - 1; i++){// sende the frame to serial port till end of the frame one element at a time.
    Serial.print(Frame[i]); 
    Serial.print(' ');// This is for display formating in serial terminal
    Serial.print(' ');// This is for display formating in serial terminal
  }
  Serial.write("\n");
  return;
}

void DataAquisition(){ // commented for manual testing, uncomment in atomated testing and while testing on actual board and configure pin according to board pin configuration
     /* T1_Cur = (analogRead(A2) * (3.3 / 1023.0));
      T2_Cur = (analogRead(A3) * (3.3 / 1023.0));
      T3_Cur = (analogRead(A4) * (3.3 / 1023.0));
      T4_Cur = (analogRead(A5) * (3.3 / 1023.0));
      T5_Cur = (analogRead(A6) * (3.3 / 1023.0));
      T6_Cur = (analogRead(A7) * (3.3 / 1023.0));
      CD1_Cur = (analogRead(A2) * (3.3 / 1023.0));
      CD2_Cur = (analogRead(A3) * (3.3 / 1023.0));
      CD3_Cur = (analogRead(A4) * (3.3 / 1023.0));
      CD4_Cur = (analogRead(A5) * (3.3 / 1023.0));
     */
      
    }
  //Creation of data frame   
  void CreateFrame(){// Fill currently read information in frame.
  Frame[0] = 0xCCDD;
  Frame[1] = HEALTH;
  Frame[2] = Cur_Cmd;
  Frame[3] = DATA_SIZE;
  Frame[4] = T1_Cur;
  Frame[5] = T2_Cur;
  Frame[6] = T3_Cur;
  Frame[7] = T4_Cur;
  Frame[8] = T5_Cur;
  Frame[9] = T6_Cur;
  Frame[10] = CD1_Cur;
  Frame[11] = CD2_Cur;
  Frame[12] = CD3_Cur;
  Frame[13] = CD4_Cur;
  Frame[14] = APT;
  Frame[15] = TMP;
  Frame[16] = Dialysat_Flow;
  Frame[17] = Uf_Goal;
  Frame[18] = Uf_Rate;
  Frame[19] = Blood_Flow;
  Frame[20] = Heparin_Rate;
  Frame[21] = Bolus_Volume;
  Frame[22] = ErrorNo;
  Frame[23] = Current_Status;
  Frame[24] = Stat_Flag;
  Frame[25] = 0xEEBB;
  
}
void CreateAckFrame(){
  Frame[0] = 0xCCDD;
  Frame[1] = Cur_Cmd;
  Frame[2] = ACK;
  Frame[3] = DATA_SIZE;
  Frame[4] = 0;
  Frame[5] = 0;
  Frame[6] = 0;
  Frame[7] = 0;
  Frame[8] = 0;
  Frame[9] = 0;
  Frame[10] = 0;
  Frame[11] = 0;
  Frame[12] = 0;
  Frame[13] = 0;
  Frame[14] = 0;
  Frame[15] = 0;
  Frame[16] = 0;
  Frame[17] = 0;
  Frame[18] = 0;
  Frame[19] = 0;
  Frame[20] = 0;
  Frame[21] = 0;
  Frame[22] = ErrorNo;
  Frame[23] = Current_Status;
  Frame[24] = Stat_Flag;
  Frame[25] = 0xEEBB;
  
}
void CreateStatFrame(){
  Frame[0] = 0xCCDD;
  Frame[1] = Cur_Cmd;
  Frame[2] = STAT;
  Frame[3] = DATA_SIZE;
  Frame[4] = 0;
  Frame[5] = 0;
  Frame[6] = 0;
  Frame[7] = 0;
  Frame[8] = 0;
  Frame[9] = 0;
  Frame[10] = 0;
  Frame[11] = 0;
  Frame[12] = 0;
  Frame[13] = 0;
  Frame[14] = 0;
  Frame[15] = 0;
  Frame[16] = 0;
  Frame[17] = 0;
  Frame[18] = 0;
  Frame[19] = 0;
  Frame[20] = 0;
  Frame[21] = 0;
  Frame[22] = ErrorNo;
  Frame[23] = Current_Status;
  Frame[24] = Stat_Flag;
  Frame[25] = 0xEEBB;
  
}


void Rinse(){// put rinse module here.
  
}
void Prime(){// put prime module here.
 SerialUSB.println("Priming on process.");
}
void Dialysis(){//put dialysis module
  
}

// command handler
void CommandHandler(){
  //if(!(Cur_Cmd == Last_Cmd)){// check if last command is same as the corrent command.
      switch(Cur_Cmd){
        case 'RINSE':// command for rinse.
                  CreateAckFrame();
                  SendInfo();
                  Rinse();
                  Current_Status = 1;
                  CreateStatFrame();
                  SendInfo();
                  //Last_Cmd = Cur_Cmd; // initialise last command to current command.
                  break;
        case 'PRIME':// command for prime
                  CreateAckFrame();
                  SendInfo();
                  Prime();
                  Current_Status = 1;
                  CreateStatFrame();
                  SendInfo();
                  //Last_Cmd = Cur_Cmd;
                  break;
        case 'DIALYSIS':// command for dialysis
                  
                  CreateAckFrame();
                  SendInfo();
                  Dialysis();
                  Last_Cmd = Cur_Cmd;
                  Current_Status = 1;
                  CreateStatFrame();
                  SendInfo();
                  break;
        case 'RESET_LAST_CMD':// reset the last command 
                  Last_Cmd = 0;
                  break;        
        
        
      }
  }



