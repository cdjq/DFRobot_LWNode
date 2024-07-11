/*!
 *@file ABP_SEND.ino
 *@brief LoRaWan ABP节点 向网关发送数据
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

const char NWKSKEY[]={"87888888888888888888888888888888"} ;
const char APPSKEY[]={"89888888888888888888888888888888"};

uint32_t devAddr = 0xDF000011;
uint8_t _DEVEUI[16]={0x0};

DFRobot_LWNode_UART node(devAddr,NWKSKEY,APPSKEY);
void setup(void){
    Serial.begin(115200);
    Serial1.begin(9600);
    node.begin(/*communication uart*/&Serial1,/*debug uart*/&Serial);
    //node.begin(/*communication uart*/Serial, NULL);//Uno
    while(!node.setRegion(REGION)){
        delay(2000);
        Serial.println("REGION set fail");
    }
    while(!node.setAppSKey(APPSKEY)){
         delay(2000);
         Serial.println("APPSKEY set fail");
    }
    while(!node.setNwkSKey(NWKSKEY)){
         delay(2000);
         Serial.println("NWKSKEY set fail");
    }
    while(!node.setDevAddr(devAddr)){
         delay(2000);
         Serial.println("devAddr set fail");
    }

    //EU868 DR0  - DR5
    //US915 DR0  - DR3
    //CN470 DR0  - DR5
    while (!node.setDataRate(DATARATE)) {
        delay(2000);
        Serial.println("DataRate set fail");
    }

    //EU868 DBM0  DBM2 DBM4 DBM6 DBM8 DBM10 DBM12 DBM14 DBM16
    //US915 DBM0  DBM2 DBM4 DBM6 DBM8 DBM10 DBM12 DBM14 DBM16 DBM18 DBM20 DBM22 DBM24 DBM26 DBM28
    //CN470 DBM0  DBM2 DBM4 DBM6 DBM8 DBM10 DBM12 DBM14 DBM16 DBM18 
    if (!node.setEIRP(DBM6)) {
        Serial.println("EIRP set fail");
    }

    #ifdef SUBBAND
    while (!node.setSubBand(SUBBAND)){
         Serial.println("SubBand set fail");
    }
    #endif

    while (!node.enableADR(false)){
        delay(2000);
        Serial.println("ADR set fail");
    }
    if(node.getDevEUI(_DEVEUI)){
        Serial.print("deveui:");
        for(uint8_t i=0;i<8;i++){
            Serial.print(_DEVEUI[i],HEX);
        }
        Serial.println();
    }

    Serial.print("DATARATE: ");
    Serial.println(node.getDataRate());

    Serial.print("EIRP: ");
    Serial.println(node.getEIRP());
}

void loop(){
    node.sendPacket("hello");
    node.Sleep(10*1000);

    uint8_t buf[3]={1,2,3};
    node.sendPacket(buf,3);
    node.Sleep(10*1000);
}