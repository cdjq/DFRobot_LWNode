/*!
 *@file ABP_RECV.ino
 *@brief LoRaWan节点 ABP入网后,通过回调函数方式从网关接收数据
 *@details  
 *@copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 *@license     The MIT license (MIT)
 *@author [fengli](li.feng@dfrobot.com)
 *@version  V1.0
 *@date  2023-12-26
 *@https://github.com/DFRobot/DFRobot_LWNode
*/
#include "DFRobot_LWNode.h"
const char NWKSKEY[]={"87888888888888888888888888888888"} ;
const char APPSKEY[]={"89888888888888888888888888888888"};

uint32_t devAddr = 0xDF000011;
uint8_t _DEVEUI[16]={0x0};
uint8_t buf[256];
DFRobot_LWNode_IIC node(devAddr,NWKSKEY,APPSKEY);

void LWRxCB(void *buf, uint16_t size){
  uint8_t *data = (uint8_t *)buf;
  Serial.print("\nsize = ");Serial.println(size);
  for(uint8_t i=0;i<size;i++){
    Serial.print(data[i],HEX);
  }
  Serial.println();
  Serial.println("Text:");  
  Serial.println((char *)buf);
}

void setup(void){
  Serial.begin(115200);
  delay(5000);
  node.begin(/*communication IIC*/&Wire,/*debug UART*/&Serial);
  Serial.println("join success");
  node.setRxCB(LWRxCB);
  //这个包会成功发送
  node.sendPacket("hello");
}


void loop(){
  //读取缓冲区是否接到数据
  node.Sleep(5000);
}