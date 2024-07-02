/*!
 *@file OTAA_RECV_POLL.ino
 *@brief LoRaWan节点 OTAA 入网后通过轮训的方式从网关接收数据
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
	#define DATARATE  5
	#define REGION EU868
#elif defined(REGION_US915)
	#define REGION    US915
	#define DATARATE  3
	#define SUBBAND   2
#elif defined(REGION_CN470)
	#define REGION    CN470
	#define DATARATE  5
	#define SUBBAND   11
#endif

const char _APPEUI[]={"DFDFDFDF00000000"} ;
const char _APPKEY[]={"0102030405060708090A0B0C0D0E0F10"};
uint8_t _DEVEUI[8]={0x0};
uint8_t buf[256];


DFRobot_LWNode_UART node(_APPEUI,_APPKEY);

void setup(void){
    Serial.begin(115200);
    Serial1.begin(9600);

    delay(5000);
    node.begin(/*communication uart*/&Serial1,/*debug uart*/&Serial);
    while(!node.setRegion(REGION)){
        delay(2000);
        Serial.println("REGION set fail");
    }
    #ifdef SUBBAND
    while(!node.setSubBand(SUBBAND)){
        Serial.println("SubBand set fail");
    }
    #endif
    while(!node.setDevType(CLASS_C)){
        delay(2000);
        Serial.println("DevType set fail");
    }

    //EU868 DR0  - DR5
    //US915 DR0  - DR3
    //CN470 DR0  - DR5
    while (!node.setDataRate(DATARATE)) {
        delay(2000);
        Serial.println("DataRate set fail");
    }
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
    //读取缓冲区是否接到数据
    uint8_t len = node.readData(buf);
    
    if(len > 0){
        Serial.print("\nreceive ");Serial.print(len);Serial.println(" bytes  \nHEX:");  
        for(uint8_t i = 0; i < len; i++){
          Serial.print(buf[i],HEX);  
        }
        Serial.println();
        Serial.println("Text:");  
        Serial.println((char *)buf);
    }
    //String data = node.readData();
    //if(data != ""){
    //    Serial.println(data);
    //}
    delay(500);
}