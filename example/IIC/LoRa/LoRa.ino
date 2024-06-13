#include <DFRobot_LWNode.h>

DFRobot_LWNode_IIC node(3);

void rxCBFunc(uint8_t from, void *buffer, uint16_t size){
    uint8_t *p = (uint8_t *)buffer;
    Serial.print("recv from: ");
    Serial.println(from, HEX);
    Serial.print("recv data: ");
    for(uint8_t i = 0; i < size; i++){
        Serial.print(p[i], HEX);
    }
    Serial.println();
}

void setup( void ){
    Serial.begin(115200);
    delay(5000);
    node.begin(/*communication IIC*/&Wire,/*debug UART*/&Serial);

    while(!node.setFreq(868100000)){
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