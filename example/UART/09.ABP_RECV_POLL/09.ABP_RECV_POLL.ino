/*!
 *@file ABP_RECV_POLL.ino
 *@brief LoRaWan ABP模式节点 通过轮询方式从网关接收数据
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
DFRobot_LWNode_UART node(devAddr,NWKSKEY,APPSKEY);

void setup(void){
    Serial.begin(115200);
    Serial1.begin(9600);
    node.begin(/*communication uart*/&Serial1,/*debug uart*/&Serial);
    while(!node.setRegion(REGION)){
        delay(2000);
        Serial.println("REGION set fail");
    }
    while(!node.setDevType(CLASS_C)){
        delay(2000);
        Serial.println("DevType set fail");
    }
    #ifdef SUBBAND
    while(!node.setSubBand(SUBBAND)){
         Serial.println("SubBand set fail");
    }
    #endif
}


void loop(){
  //读取缓冲区是否接到数据
  uint8_t len = node.readData(buf);
  
  if(len > 0){
    Serial.print("\nreceive ");Serial.print(len,HEX);Serial.println(" bytes  \nHEX:");  
    for(uint8_t i = 0; i < len; i++){
      Serial.print(buf[i],HEX);
    }
    Serial.println();
    Serial.println("Text:");  
    Serial.println((char *)buf);
  }
  //String data = node.readData();
  //if(data != ""){
  //  Serial.println(data);
  //}
  delay(500);
}