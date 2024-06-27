/*!
 *@file OTAA_RECV_CB.ino
 *@brief LoRaWan节点 OTAA 入网后以回调函数方式从网关接收数据
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

void uartRxCB(void *buffer, uint16_t size){
    uint8_t *data = (uint8_t *)buffer;
    Serial.print("\nsize = ");Serial.println(size);
    for(uint8_t i=0;i<size;i++){
        Serial.print(data[i],HEX);
    }
    Serial.println();
    Serial.println("Text:");  
    Serial.println((char *)buffer);
}

DFRobot_LWNode_UART node(_APPEUI,_APPKEY);

void setup(void){
    Serial.begin(115200);
    Serial1.begin(9600);
    delay(5000);
    node.begin(/*communication uart*/&Serial1,/*debug uart*/&Serial);
    
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
    
    //EU868 DR0  - DR5
    //US915 DR5  - DR7
    //CN470 DR0  - DR5
    if (!node.setDataRate(DR5)) {
        Serial.println("DataRate set fail");
    }
    
    //EU868 DBM0  DBM2 DBM4 DBM6 DBM8 DBM10 DBM12 DBM14 DBM16
    //US915 DBM0  DBM2 DBM4 DBM6 DBM8 DBM10 DBM12 DBM14 DBM16 DBM18 DBM20 DBM22 DBM24 DBM26 DBM28
    //CN470 DBM0  DBM2 DBM4 DBM6 DBM8 DBM10 DBM12 DBM14 DBM16 DBM18 
    if (!node.setEIRP(DBM6)) {
      Serial.println("EIRP set fail");
    }
    if (!node.setPacketType(UNCONFIRMED_PACKET)) {
      Serial.println("Packet type set fail");
    }
    if(node.getDevEUI(_DEVEUI)){
        Serial.print("deveui:");
        for(uint8_t i=0;i<8;i++){
            Serial.print(_DEVEUI[i],HEX);
        }
        Serial.println();
    }
    
    node.setRxCB(uartRxCB);
    //join
    if(node.join()){
        Serial.println("JOIN......");
    }
    
    while(!node.isJoined()){
        delay(5000);
    }
    Serial.println("join success");
}


void loop(){
  node.Sleep(9000);
}