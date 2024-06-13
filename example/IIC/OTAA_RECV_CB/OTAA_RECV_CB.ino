/*!
 *@file OTAA_RECV.ino
 *@brief LoRaWan节点 OTAA 入网后通过回调函数方式从网关接收数据
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
uint8_t buf[256]={0x0};

DFRobot_LWNode_IIC node(_APPEUI,_APPKEY);

void setup(void){

  Serial.begin(115200);

  node.begin(/*communication IIC*/&Wire,/*debug UART*/&Serial);
  
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
  
  //读取缓冲区是否接到数据
  uint8_t len = node.readData(buf);

  if(len > 0){
    for(uint8_t i = 0;i<len;i++){
      Serial.println(buf[i],HEX);  
    }
  }
  //String data = node.readData();
  //if(data != ""){
  // Serial.println(data);
  //}

  delay(600);
  
}