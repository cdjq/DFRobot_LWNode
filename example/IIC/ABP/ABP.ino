/*!
 *@file ABP.ino
 *@brief LoRaWan节点 ABP入网流程
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

  node.begin(/*通信com*/ &Wire, /*调试dbg com*/ Serial);
  if (!node.setAppSKey(APPSKEY)) {
    Serial.println("APPSKEY set fail");
  }
  if (!node.setNwkSKey(NWKSKEY)) {
    Serial.println("NWKSKEY set fail");
  }
  if (!node.setDevAddr(devAddr)) {
    Serial.println("devAddr set fail");
  }

  if (!node.setDataRate(DR5)) {
    Serial.println("DataRate set fail");
  }
  if (!node.setTXPower(TX_POWER_6)) {
    Serial.println("TXPower set fail");
  }

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

  Serial.print("TxPower: ");
  Serial.println(node.getTxPower());
}

void loop() {
  node.sendPacket("hello");
  delay(10 * 1000);

  uint8_t buf[3] = {1, 2, 3};
  node.sendPacket(buf, 3);
  delay(10 * 1000);
}
