

#include "DFRobot_LWNode.h"
uint8_t NWKSKEY[16]={0x87,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88} ;
uint8_t APPSKEY[16]={0x89,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88};

uint32_t devAddr = 0xDF000011;
uint8_t _DEVEUI[8]={0x0};

DFRobot_LWNode_UART node(devAddr,NWKSKEY,APPSKEY);
void setup(void){

   Serial.begin(115200);
   Serial1.begin(115200);
   node.begin(Serial1,Serial);
   if(!node.setAppSKey(APPSKEY)){
      Serial.println("APPSKEY set fail");
   }
   if(!node.setNwkSKey(NWKSKEY)){
      Serial.println("NWKSKEY set fail");
   }
   if(!node.setDevAddr(devAddr)){
      Serial.println("devAddr set fail");
   }

   if(!node.setDataRate(DR5)){
      Serial.println("DataRate set fail");
   }
   if(!node.setTXPower(TX_POWER_6)){
      Serial.println("TXPower set fail");
   }
   //if(!node.setSubBand(11)){
   //   Serial.println("SubBand set fail");
   //}
   if(!node.enableADR(false)){
      Serial.println("ADR set fail");
   }
   if(node.getDevEUI(_DEVEUI)){
     Serial.print("deveui:");
     for(uint8_t i=0;i<8;i++){
       Serial.print(_DEVEUI[i],HEX);
     }
     Serial.println();
   }
   
   Serial.print("DATARATE: ");
   Serial.println(node.getDataRate());
   
   Serial.print("TxPower: ");
   Serial.println(node.getTxPower());


   node.sendPacket("hello");
}


void loop(){
delay(10000);
node.sendPacket("hello");

uint8_t buf[3]={1,2,3};
delay(10000);
node.sendPacket(buf,3);

}