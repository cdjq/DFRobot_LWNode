#include "DFRobot_LWNode.h"


static rxCB *_rxCB =NULL;
uint8_t IntEnable = true;
LWNode::LWNode(const uint8_t *appEui,const uint8_t *appKey, eDeviceClass_t classType, eDataRate_t dataRate, etxPower_t txPower,bool adr, uint8_t subBand){


}


String uint8ArrayToHexString(const uint8_t arr[], int length) {
    String str = "";
    for(int i = 0; i < length; i++) {
        if (arr[i] < 16) {
            str.concat("0");
        }
        str.concat(String(arr[i], HEX));
    }
    str.toUpperCase();
    return str;
}
bool LWNode::atTest(){
  String ack;
  ack = sendATCmd("AT");

  if(ack == "OK\r\n"){
    return true;
  }else{
    return false;
  }
}
bool LWNode::setRegion(eRegion_t region){
   String ack;
   switch (region){

     case EU868 :
        ack = sendATCmd("AT+REGION=EU868");
      break;
     case US915 :
        ack = sendATCmd("AT+REGION=US915");
      break;
     case CN470 :
        ack = sendATCmd("AT+REGION=CN470");
      break;
     default : 
      LDBG("unsupported region");
   }
   LDBG(ack);
  if(ack == "+REGION=OK\r\n"){
   return true;
  }else{
   return false;
  }
}
bool LWNode:: enTrans(){
  String ack;
  ack = sendATCmd("AT+LOOP=0");
  if(ack != "+LOOP=OK\r\n"){
    return false;
  }
  
  ack = sendATCmd("AT+EXIT");
  if(ack == "+EXIT=OK\r\n"){
    return true;
  }else{
    return false;
  }
}
Stream *uarts;
void serialEvent(){
  if(uarts == &Serial){
  uint8_t data[256];
  uint8_t i = 0;
  if(_rxCB && IntEnable){
     while(uarts->available()){
        data[i] = uarts->read();
        i++;
     }
     data[i] =0;
     _rxCB(data,i);
  }
  }
}
void serialEvent1(){
  if(uarts == &Serial1){
  uint8_t data[256];
  uint8_t i = 0;
  if(_rxCB && IntEnable){
     while(uarts->available()){
        data[i] = uarts->read();
        i++;
     }
     data[i] =0;
     _rxCB(data,i);
  }
  }
}

void LWNode::setRxCB(rxCB *callback){

  _rxCB = callback;
  
}

bool LWNode::setAppEUI(const uint8_t *appeui){

  String AT = "AT+JOINEUI="+uint8ArrayToHexString(appeui,8);
  String ack;
  ack = sendATCmd(AT);
  if(ack == "+JOINEUI=OK\r\n"){
   return true;
  }else{
   return false;
  }
}
bool LWNode::setAppKEY(const uint8_t *appkey){

  String AT = "AT+APPKEY="+uint8ArrayToHexString(appkey,16);
  String ack;
  ack = sendATCmd(AT);
  if (ack == "+APPKEY=OK\r\n"){
   return true;
   
  }else{
   return false;
  }
}


bool LWNode::setDevType(eDeviceClass_t classType){

  String ack;
  if(classType == CLASS_A){
    ack = sendATCmd("AT+CLASS=CLASS_A");
  }else{
    ack = sendATCmd("AT+CLASS=CLASS_C");
  }
  if(ack == "+CLASS=OK\r\n"){
   return true;
  }else{
   return false;
  }
}

bool LWNode::setDataRate(eDataRate_t dataRate){
  String AT = "AT+DATARATE="+String(dataRate);
  String ack;
  ack = sendATCmd(AT);
  if(ack == "+DATARATE=OK\r\n"){
   return true;
  }else{
   return false;
  }
}
bool LWNode::setTXPower(uint8_t txPower){
  String AT = "AT+EIRP="+String(txPower);
  String ack;
  ack = sendATCmd(AT);
  if(ack == "+EIRP=OK\r\n"){
   return true;
  }else{
   return false;
  }
}

bool LWNode::setSubBand(uint8_t subBand){


  String AT = "AT+SUBBAND="+String(subBand);
  String ack;
  if(_region == EU868) return false;
  
  ack = sendATCmd(AT);
  if(ack == "+SUBBAND=OK\r\n"){
   return true;
  }else{
   return false;
  }

}
bool LWNode::setADR(bool adr){
  String AT = "AT+ADR="+String(adr);
  String ack;
  ack = sendATCmd(AT);
  if(ack == "+ADR=OK\r\n"){
   return true;
  }else{
   return false;
  }
}

bool LWNode::setDevAddr(const uint32_t devAddr){

  String AT = "AT+DEVADDR="+String(devAddr,HEX);
  String ack;
  ack = sendATCmd(AT);
  if(ack == "+DEVADDR=OK\r\n"){
   return true;
  }else{
   return false;
  }
}
bool LWNode::setAppSKey(const uint8_t * appSKey){
  String AT = "AT+APPSKEY="+uint8ArrayToHexString(appSKey,16);
  String ack;
  ack = sendATCmd(AT);
  if (ack == "+APPSKEY=OK\r\n"){
   return true;
   
  }else{
   return false;
  }
}
bool LWNode::setNwkSKey(const uint8_t * nwkSKey){
  String AT = "AT+NWKSKEY="+uint8ArrayToHexString(nwkSKey,16);
  String ack;
  ack = sendATCmd(AT);
  if (ack == "+NWKSKEY=OK\r\n"){
   return true;
   
  }else{
   return false;
  }
}

bool LWNode::setPacketType(ePacketType_t type){


  String ack;
  if(type == UNCONFIRMED_PACKET){
    ack = sendATCmd("AT+UPLINKTYPE=UNCONFIRMED");
  }else{
    ack = sendATCmd("AT+UPLINKTYPE=CONFIRMED");
  }
  if(ack == "++UPLINKTYPE=OK\r\n"){
   return true;
  }else{
   return false;
  }
}

bool LWNode::join(){
  String AT = "AT+JOIN=1";
  String ack;
  ack = sendATCmd(AT);
  if(ack == "+JOIN=OK\r\n"){
   return true;
  }else{
   return false;
  }
}
bool LWNode::isJoined(){
  String AT = "AT+JOIN?";
  String ack;
  ack = sendATCmd(AT);
  if(ack == "+JOIN=1\r\n"){
   return true;
  }else{
   return false;
  }
}
bool LWNode::sendPacket(void *buffer, uint8_t size){
  String AT = "AT+SEND=";
  String ack;
  uint8_t *data = (uint8_t *)buffer;
  for(uint8_t i = 0;i<size;i++){
      AT+=data[i];

  }
  ack = sendATCmd(AT);
  if(ack == "AT+SEND=OK\r\n"){
    return true;
  }else{
    return false;
  }
}
bool LWNode::sendPacket(String data){
  

  String AT = "AT+SEND="+data;
  String ack;
  ack = sendATCmd(AT);
  //sendData((uint8_t *)data.c_str(),data.length());
  if(ack == "AT+SEND=OK\r\n"){
    return true;
  }else{
    return false;
  }
}
void hexStringToByteArray(String hexString, uint8_t* byteArray, int length) {
  for (int i = 0; i < hexString.length(); i+=2) {
    String byteString = hexString.substring(i, i+2);
    byteArray[i/2] = (uint8_t) strtol(byteString.c_str(), NULL, 16);
  }
}
bool LWNode::getDevEUI(uint8_t *eui){

  String AT = "AT+DEVEUI?";
  String ack;
  ack = sendATCmd(AT).substring(8, 27);;
  

  hexStringToByteArray(ack,eui,8);
  return true;
  
}

uint32_t LWNode::getNetID(){
  String AT = "AT+NETID?";
  String ack;
  uint32_t netid = 0;
  
  ack = sendATCmd(AT).substring(7, 17);
  

  netid = ack.toInt();
  return netid;
}
uint32_t LWNode::getDevAddr(){
  String AT = "AT+DEVADDR?";
  String ack;
  uint32_t devaddr = 0;
  ack = sendATCmd(AT).substring(9, 17);
  
  
  devaddr = ack.toInt();


  char buf[8];  // 为 '\0' 结尾的字符串分配空间
  ack.toCharArray(buf, sizeof(buf));  // 将 String 转换为 char 数组
  devaddr = strtol(buf, NULL, 16);  // 将 16 进制的 char 数组转换为 int

  return devaddr;
}
uint8_t LWNode::getDataRate(){
  String AT = "AT+DATARATE?";
  String tmp,ack;
  uint8_t dataRate = 0;
  ack = sendATCmd(AT).substring(10, 11);
  dataRate = ack.toInt();
  return dataRate;
}
uint8_t LWNode::getTxPower(){

  String AT = "AT+EIRP?";
  String ack;
  uint8_t eirp = 0;
  ack = sendATCmd(AT).substring(6, 7);
  

  eirp = ack.toInt();
  return eirp;
}

String LWNode::sendATCmd(String cmd){
   String ack;
   cmd = cmd + "\r\n";
   delay(300);
   IntEnable = false;
   sendData((uint8_t*) cmd.c_str(),cmd.length());
   
   ack = readACK();
   delay(300);
   IntEnable = true;
   return ack;
}

DFRobot_LWNode_UART::DFRobot_LWNode_UART(const uint8_t *appEui,const uint8_t *appKey, eDeviceClass_t classType, eDataRate_t dataRate, etxPower_t txPower,bool adr, uint8_t subBand)
{
  memcpy(_appeui,appEui,8);
  memcpy(_appKey,appKey,16);
  _dataRate = dataRate;
  
  _classType = classType;
  _txPower = txPower;
  _adr = adr;
  _subBand = subBand;
}

DFRobot_LWNode_UART::DFRobot_LWNode_UART(const uint32_t devAddr ,const uint8_t *nwkSKey,const uint8_t *appSKey, eDeviceClass_t classType, eDataRate_t dataRate,etxPower_t txPower,bool adr , uint8_t subBand){
  
  memcpy(_appeSKey,appSKey,16);
  memcpy(_nwkSKey,nwkSKey,16);
  _devAddr = devAddr;
  isOtaa = false;
  _dataRate = dataRate;
  _classType = classType;
  _txPower = txPower;
  _adr = adr;
  _subBand = subBand;
}

bool DFRobot_LWNode_UART::begin(Stream &s_, Stream &dbgs_){
    String ack;
    uint8_t timeout = 100;
    s = &s_;
    dbgs = &dbgs_;
    uarts = &s_;
    //sendATCmd("+++");
    //delay(500);
    sendATCmd("AT+REBOOT\r\n");

    while(!atTest()){
         timeout--;
         if(timeout == 0) return false;
    }
    
    if(isOtaa == false){
        ack = sendATCmd("AT+JOINTYPE=ABP");
        if(ack == "+JOINTYPE=OK\r\n"){
          setAppSKey(_appeSKey);
          setNwkSKey(_nwkSKey);
          setDevAddr(_devAddr);
          return true;
        }else{
          return false;
        }
    }else{
        ack = sendATCmd("AT+JOINTYPE=OTAA");
        if(_appKey !=NULL)
        setAppKEY(_appKey);
    }
    return true;
}

void DFRobot_LWNode_UART::sendData(uint8_t *data ,uint8_t len ){
    s->flush();
    s->write(data,len);
    if(dbgs){
        dbgs->flush();
        dbgs->write(data,len);
    }
}

String DFRobot_LWNode_UART::readACK(){
   uint16_t timeout = 100;
   uint16_t i = 0;
   String ack;
   while(timeout--){
     delay(1);
     while (s->available()) {
    // 读取并处理新的串行数据
       //Serial.print((char)s->read());
       ack += (char)s->read();
       timeout = 250;
       delay(1);
     }
     if(timeout == 250) break;
   }
   if(timeout == 0 ) ack =  "NULL";
   delay(150);
    if(dbgs){
     //   dbgs->flush();
        dbgs->write(ack.c_str(),ack.length());
    }
   
   return ack;
}