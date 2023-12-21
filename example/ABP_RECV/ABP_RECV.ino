#include "DFRobot_LWNode.h"
uint8_t NWKSKEY[16]={0x87,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88} ;
uint8_t APPSKEY[16]={0x89,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88};

uint32_t devAddr = 0xDF000011;
uint8_t _DEVEUI[8]={0x0};

void rxCB(void *buffer, uint16_t size){
    char *data = (char*)buffer;
    for(uint8_t i=0;i<size;i++){
        Serial.print(data[i],HEX);
    }
}

DFRobot_LWNode_UART node(devAddr,NWKSKEY,APPSKEY);

void setup(void){
    Serial.begin(115200);
    Serial1.begin(115200);
    node.begin(/*communication uart*/Serial1,/*debug uart*/Serial);
    node.setRxCB(rxCB);
    Serial.println("join success");
}


void loop(){
    delay(100);
}