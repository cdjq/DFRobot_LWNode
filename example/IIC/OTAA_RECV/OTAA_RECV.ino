/*!
 *@file OTAA_RECV.ino
 *@brief LoRaWan节点 OTAA 入网后从网关接收数据
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
uint8_t _DEVEUI[16]={0x0};


DFRobot_LWNode_IIC node(_APPEUI,_APPKEY);

void setup(void){

   Serial.begin(115200);

   node.begin(/*通信com*/&Wire,/*调试dbg com*/Serial);
   
   //入网
   if(node.join()){
      Serial.println("JOIN......");
   }
   
   while(!node.isJoined()){
     delay(5000);
   }   
   Serial.println("join success");
   
   //接受数据前必须要上发一个包
   node.sendPacket("hello");
}


void loop(){
  
    //avr的中断服务函数是在 main函数里面轮询，这里不能卡死 
    delay(100);
    //读取缓冲区是否接到数据
    String data = node.readData();
    if(data != "NULL"){
     Serial.println(data);
    }

    delay(600);
  
}