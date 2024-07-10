/*!
 *@file getDEVEUI.ino
 *@brief LoRaWan节点 获取设备的 DEVEUI
 *@details  
 *@copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 *@license     The MIT license (MIT)
 *@author [fengli](li.feng@dfrobot.com)
 *@version  V1.0
 *@date  2023-12-26
 *@https://github.com/DFRobot/DFRobot_LWNode
*/


#include "DFRobot_LWNode.h"
const char _APPEUI[]={"DFDFDFDF00000000"} ;
const char _APPKEY[]={"0102030405060708090A0B0C0D0E0F10"};
uint8_t _DEVEUI[8]={0x0};



DFRobot_LWNode_UART node(_APPEUI,_APPKEY);
void setup(void){
   Serial.begin(115200);
   Serial1.begin(9600);
    node.begin(/*communication uart*/&Serial1,/*debug uart*/&Serial);
   
   if(node.getDevEUI(_DEVEUI)){
     Serial.print("deveui:");
     for(uint8_t i=0;i<8;i++){
       Serial.print(_DEVEUI[i],HEX);
     }
     Serial.println();
   }
   

}


void loop(){
    delay(10*1000);
}