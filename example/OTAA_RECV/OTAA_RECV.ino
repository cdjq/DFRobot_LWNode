
#include "DFRobot_LWNode.h"
uint8_t _APPEUI[8]={0xDF,0xDF,0xDF,0xDF,0x00,0x00,0x00,0x00} ;
uint8_t _APPKEY[16]={0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55};
uint8_t _DEVEUI[8]={0x0};

void uartRxCB(void *buffer, uint16_t size){
    char *data = (char*)buffer;
    //for(uint8_t i=0;i<size;i++){
      
        Serial.print(data);
    //  }
}
DFRobot_LWNode_UART node(devAddr,NWKSKEY,APPSKEY);

void setup(void){

   Serial.begin(115200);
   Serial1.begin(115200);
   node.begin(/*通信com*/Serial1,/*调试dbg com*/Serial);
   node.setRxCB(uartRxCB);


   
   //入网
   if(node.join()){
      Serial.println("JOIN......");
   }
   
   while(!node.isJoined()){
     delay(5000);
   }   
   Serial.println("join success");
}


void loop(){
  
    //avr的中断服务函数是在 main函数里面轮询，这里不能卡死 
    delay(100);
   
  
}