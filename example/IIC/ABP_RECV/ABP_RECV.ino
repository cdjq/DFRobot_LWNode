/*!
 *@file ABP_RECV.ino
 *@brief LoRaWan节点 ABP入网后,从网关接受数据
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

DFRobot_LWNode_IIC node(devAddr,NWKSKEY,APPSKEY);

void setup(void){

   Serial.begin(115200);
   Serial1.begin(115200);
   node.begin(/*通信com*/&Wire,/*调试dbg com*/Serial);
   Serial.println("join success");
   //这个包会成功发送
   node.sendPacket("hello");

}


void loop(){
    //读取缓冲区是否接到数据
    String data = node.readData();
    if(data != "NULL"){
     Serial.println(data);
    }

    delay(600);
}