/*!
 *@file OTAA_SEND.ino
 *@brief LoRaWan OTAA模式节点 入网并向网关发送数据
 *@details  
 *@copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 *@license     The MIT license (MIT)
 *@author [fengli](li.feng@dfrobot.com)
 *@version  V1.0
 *@date  2023-12-26
 *@https://github.com/DFRobot/DFRobot_LWNode
*/
#include "DFRobot_LWNode.h"

#define REGION_EU868
//#define REGION_US915
//#define REGION_CN470

#ifdef REGION_EU868
	#define DATARATE  DR5
	#define REGION EU868
#elif defined(REGION_US915)
	#define REGION    US915
	#define DATARATE  DR3
	#define SUBBAND   2
#elif defined(REGION_CN470)
	#define REGION    CN470
	#define DATARATE  DR5
	#define SUBBAND   11
#endif

const char _APPEUI[]={"DFDFDFDF00000000"} ;
const char _APPKEY[]={"0102030405060708090A0B0C0D0E0F10"};
uint8_t _DEVEUI[16]={0x0};

DFRobot_LWNode_IIC node(_APPEUI,_APPKEY);

void setup(void){
    Serial.begin(115200);

    node.begin(/*communication IIC*/&Wire,/*debug UART*/&Serial);

    while(!node.setRegion(REGION)){
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
    //US915 DR0  - DR3
    //CN470 DR0  - DR5
    while (!node.setDataRate(DATARATE)) {
        delay(2000);
        Serial.println("DataRate set fail");
    }

    //EU868 DBM0  DBM2 DBM4 DBM6 DBM8 DBM10 DBM12 DBM14 DBM16
    //US915 DBM0  DBM2 DBM4 DBM6 DBM8 DBM10 DBM12 DBM14 DBM16 DBM18 DBM20 DBM22
    //CN470 DBM0  DBM2 DBM4 DBM6 DBM8 DBM10 DBM12 DBM14 DBM16 DBM18 
    while (!node.setEIRP(DBM16)) {
        delay(2000);
        Serial.println("EIRP set fail");
    }

    #ifdef SUBBAND
    while(!node.setSubBand(SUBBAND)){
        Serial.println("SubBand set fail");
    }
    #endif

    while(!node.enableADR(false)){
        delay(2000);
        Serial.println("ADR set fail");
    }

    while(!node.setPacketType(UNCONFIRMED_PACKET)){
        delay(2000);
        Serial.println("Packet type set fail");
    }

    Serial.print("DEVEUI: ");
    Serial.println(node.getDevEUI());
    
    Serial.print("DATARATE: ");
    Serial.println(node.getDataRate());
    
    Serial.print("EIRP: ");
    Serial.println(node.getEIRP());
    
    //入网
    if(node.join()){
        Serial.println("JOIN......");
    }
    
    while(!node.isJoined()){
      delay(5000);
    }   
    
    Serial.print("netid: 0x");
    Serial.println(node.getNetID(),HEX);
    
    Serial.print("DEVADDR: 0x");
    Serial.println(node.getDevAddr(),HEX);
    
    delay(2000);
}


void loop(){
   node.sendPacket("hello");
   node.sleep(10 * 1000);

   uint8_t buf[3]={1,2,3};
   node.sendPacket(buf,3);
   node.sleep(10 * 1000);
}