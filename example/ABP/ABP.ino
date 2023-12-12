

#include "DFRobot_LorawanNode.h"
uint8_t NWKSKEY[16]={0x87,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88} ;
uint8_t APPSKEY[32]={0x89,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88};

uint32_t devAddr = 0xDF000011;
void uartRxCB(void *buffer, uint16_t size){
    uint8_t *data = (uint8_t*)buffer;
    for(uint8_t i=0;i<size;i++){
      
        Serial.print(data[i],HEX);
      }
}

DFRobot_LorawanNode_UART node(devAddr,NWKSKEY,APPSKEY);
void setup(void){

   Serial.begin(115200);
   node.begin();
   node.setDevType(CLASS_C);
   node.setRxCB(uartRxCB);
   if(node.join()){
      Serial.println("JOIN......");
   }
   while(!node.isJoined()){
     delay(5000);
   }
   node.enTrans();
   node.sendPacket("hello");
}


void loop(){
delay(10000);
node.sendPacket("hello");
}