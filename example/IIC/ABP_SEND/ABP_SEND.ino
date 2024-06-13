/*!
 *@file ABP_SEND.ino
 *@brief LoRaWan节点 ABP入网, 向网关发送数据
 *@details  
 *@copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 *@license     The MIT license (MIT)
 *@author [fengli](li.feng@dfrobot.com)
 *@version  V1.0
 *@date  2023-12-26
 *@https://github.com/DFRobot/DFRobot_LWNode
*/
#include "DFRobot_LWNode.h"

uint8_t NWKSKEY[16] = {0x87, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88};
uint8_t APPSKEY[16] = {0x89, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88};

uint32_t devAddr = 0xDF000011;
uint8_t _DEVEUI[16]={0x0};

DFRobot_LWNode_IIC node(devAddr, NWKSKEY, APPSKEY);

void setup(void) {
  Serial.begin(115200);

  node.begin(/*communication IIC*/&Wire,/*debug UART*/&Serial);

  if (!node.setAppSKey(APPSKEY)) {
    Serial.println("APPSKEY set fail");
  }
  if (!node.setNwkSKey(NWKSKEY)) {
    Serial.println("NWKSKEY set fail");
  }
  if (!node.setDevAddr(devAddr)) {
    Serial.println("devAddr set fail");
  }
    //EU868 DR0  - DR5
    //US915 DR5  - DR7
    //CN470 DR0  - DR5
  if (!node.setDataRate(DR5)) {
    Serial.println("DataRate set fail");
  }

  //EU868   DBM2 DBM4 DBM6 DBM8 DBM10 DBM12 DBM14 DBM16
  //US915   DBM2 DBM4 DBM6 DBM8 DBM10 DBM12 DBM14 DBM16 DBM18 DBM20 DBM22 DBM24 DBM26 DBM28
  //CN470   DBM2 DBM4 DBM6 DBM8 DBM10 DBM12 DBM14 DBM16 DBM18 
  if (!node.setEIRP(DBM6)) {
    Serial.println("EIRP set fail");
  }

  //CN470
  /*if(!node.setSubBand(11)){
       Serial.println("SubBand set fail");
  }*/

  //US915
  /*if(!node.setSubBand(2)){
      Serial.println("SubBand set fail");
  }*/
  if (!node.enableADR(false)) {
    Serial.println("ADR set fail");
  }
  if (node.getDevEUI(_DEVEUI)) {
    Serial.print("deveui:");
    for (uint8_t i = 0; i < 8; i++) {
      Serial.print(_DEVEUI[i], HEX);
    }
    Serial.println();
  }

  Serial.print("DATARATE: ");
  Serial.println(node.getDataRate());

  Serial.print("EIRP: ");
  Serial.println(node.getEIRP());
}

void loop() {
  node.sendPacket("hello");
  node.Sleep(10 * 1000);

  uint8_t buf[3] = {1, 2, 3};
  node.sendPacket(buf, 3);
  node.Sleep(10 * 1000);
}
