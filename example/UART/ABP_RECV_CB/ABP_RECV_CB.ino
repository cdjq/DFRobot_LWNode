/*!
 *@file ABP_RECV.ino
 *@brief LoRaWan节点 ABP入网后,通过回调函数方式从网关接受数据
 *@details  
 *@copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 *@license     The MIT license (MIT)
 *@author [fengli](li.feng@dfrobot.com)
 *@version  V1.0
 *@date  2023-12-26
 *@https://github.com/DFRobot/DFRobot_LWNode
*/
#include "DFRobot_LWNode.h"
uint8_t NWKSKEY[16]={0x87,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88} ;
uint8_t APPSKEY[16]={0x89,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88};

uint32_t devAddr = 0xDF000011;
uint8_t _DEVEUI[16]={0x0};

void uartRxCB(void *buf, uint16_t size){
  uint8_t *data = (uint8_t *)buf;
  Serial.print("\nsize = ");Serial.println(size);
  for(uint8_t i=0;i<size;i++){
    Serial.print(data[i],HEX);
  }
  Serial.println();
  Serial.println("Text:");  
  Serial.println((char *)buf);
}

DFRobot_LWNode_UART node(devAddr,NWKSKEY,APPSKEY);

void setup(void){
   Serial.begin(115200);
   Serial1.begin(9600);
   node.begin(/*communication uart*/&Serial1,/*debug uart*/&Serial);
   node.setRxCB(uartRxCB);

   Serial.println("join success");

   node.sendPacket("hello");
}


void loop(){
  //读取缓冲区是否接到数据
  node.Sleep(10 * 1000);
}