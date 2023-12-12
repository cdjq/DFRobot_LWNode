

#include "DFRobot_LorawanNode.h"
uint8_t _APPEUI[16]={0xDF,0x00,0x00,0x00,0x00,0x00,0x00,0x00} ;
uint8_t _APPKEY[32]={0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88};


void uartRxCB(void *buffer, uint16_t size){
    uint8_t *data = (uint8_t*)buffer;
    for(uint8_t i=0;i<size;i++){
      
        Serial.print(data[i],HEX);
      }
}

DFRobot_LorawanNode_UART node(_APPEUI,_APPKEY);
void setup(void){

   Serial.begin(115200);
   node.begin();
   node.setDevType(CLASS_C);
   node.setRxCB(uartRxCB);

   while(!node.isJoined()){
     delay(5000);
   }
   node.enTrans();
   node.sendPacket("hello");
}


void loop(){
  
  delay(1);
  
  
}