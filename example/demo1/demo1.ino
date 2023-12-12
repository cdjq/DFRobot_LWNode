

#include "DFRobot_LorawanNode.h"
uint8_t _APPEUI[16]={0xDF,0x00,0x00,0x00,0x00,0x00,0x00,0x00} ;
uint8_t _APPKEY[32]={0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55};
uint8_t DEVEUI[16]={0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88};
DFRobot_LorawanNode_UART node(_APPEUI,_APPKEY);
void setup(void){

   Serial.begin(115200);
   node.begin();
   node.setAppKEY(_APPKEY);
   delay(1000);
   //node.getDevEUI(DEVEUI);
   delay(1000);
   node.join();
   while(!node.isJoined()){
     delay(5000);
   }
   node.enTrans();
   Serial.println("join success");
   //这个包会成功发送
   

}


void loop(){
  
  
  node.sendPacket("hello");
  delay(5000);
  
}