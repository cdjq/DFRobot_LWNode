/*!
 *@file LoRa.ino
 *@brief LoRa节点 设置节点地址为3，向地址为4的节点发射数据
 *@details  
 *@copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 *@license     The MIT license (MIT)
 *@author [fengli](li.feng@dfrobot.com)
 *@version  V1.0
 *@date  2023-12-26
 *@https://github.com/DFRobot/DFRobot_LWNode
*/
#include <DFRobot_LWNode.h>

#define REGION_EU868
//#define REGION_US915
//#define REGION_CN470

#ifdef REGION_EU868
	#define FREQ  868100000
#elif defined(REGION_US915)
	#define REGION    914900000
#elif defined(REGION_CN470)
	#define REGION    470300000
#endif

DFRobot_LWNode_IIC node(3);

void rxCBFunc(uint8_t from, void *buffer, uint16_t size) {
    uint8_t *p = (uint8_t *)buffer;
    Serial.print("recv from: ");
    Serial.println(from, HEX);
    Serial.print("recv data: ");
    for(uint8_t i = 0; i < size; i++){
        Serial.print(p[i], HEX);
    }
    Serial.println();

    int16_t rssi = node.getRSSI();
    int8_t snr = node.getSNR();
    Serial.print("rssi=");Serial.println(rssi);
    Serial.print("snr=");Serial.println(snr);
}

void setup( void ) {
    Serial.begin(115200);
    delay(5000);
    node.begin(/*communication IIC*/&Wire,/*debug UART*/&Serial);

    while(!node.setFreq(FREQ)){
        delay(2000);
        Serial.println("Failed to set Freq ");
    }

    while (!node.setEIRP(DBM16)) {
        delay(2000);
        Serial.println("Failed to set EIRP");
    }

    while (!node.setBW(125000)) {
        delay(2000);
        Serial.println("Failed to set BW");
    }
    
    while (!node.setSF(12)) {
        delay(2000);
        Serial.println("Failed to set SF");
    }

    node.setRxCB(rxCBFunc);
    
    if (!node.join()) {
        delay(2000);
        Serial.println("Failed to Join");
    }
}

void loop( void ){
    node.sendPacket(4, "hello");
    node.Sleep(5000);
    
    uint8_t buf[3]={1,2,3};
    node.sendPacket(4, buf, 3);
    node.Sleep(5000);
}