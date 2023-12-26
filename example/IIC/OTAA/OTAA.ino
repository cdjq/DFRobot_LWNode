
/*!
 *@file OTAA.ino
 *@brief LoRaWan节点 OTAA入网流程
 *@details  
 *@copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 *@license     The MIT license (MIT)
 *@author [fengli](li.feng@dfrobot.com)
 *@version  V1.0
 *@date  2023-12-26
 *@https://github.com/DFRobot/DFRobot_LWNode
*/
#include "DFRobot_LWNode.h"
uint8_t _APPEUI[8]={0xDF,0xDF,0xDF,0xDF,0x00,0x00,0x00,0x00} ;
uint8_t _APPKEY[16]={0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55};
uint8_t _DEVEUI[8]={0x0};



DFRobot_LWNode_IIC node(_APPEUI,_APPKEY);
void setup(void){
   Serial.begin(115200);

   node.begin(/*通信com*/&Wire,/*调试dbg com*/Serial);

   while(!node.setRegion(EU868)){
      delay(2000);
      Serial.println("REGION set fail");
   }
   if(!node.setAppEUI(_APPEUI)){
      Serial.println("AppEUI set fail");
   }
   if(!node.setAppKEY(_APPKEY)){
      Serial.println("AppKEY set fail");
   }
   if(!node.setDevType(CLASS_C)){
      Serial.println("DevType set fail");
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
   
   //入网
   if(node.join()){
      Serial.println("JOIN......");
   }
   
   while(!node.isJoined()){
     delay(5000);
   }   
   
   Serial.print("netid: 0x");
   Serial.println(node.getNetID(),HEX);

   Serial.print("DEVADDR: 0x");
   Serial.println(node.getDevAddr(),HEX);
   //node.enTrans();//高级

}


void loop(){
    node.sendPacket("hello");
    delay(10*1000);

    uint8_t buf[3]={1,2,3};
    node.sendPacket(buf,3);
    delay(10*1000);
}