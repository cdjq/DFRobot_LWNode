#include "DFRobot_LWNode.h"

static rxCB *_rxCB =NULL;
static rxCB3 *_rxCB3 =NULL;
uint8_t IntEnable = true;
LWNode *loranode = NULL;

LWNode::LWNode(const uint8_t *appEui,const uint8_t *appKey, eDeviceClass_t classType, eDataRate_t dataRate, etxPower_t txPower,bool adr, uint8_t subBand){

}

LWNode::LWNode(const uint8_t devAddr){
  this->_from = devAddr;
}

int findNthOccurrence(String str, char character, int n) {
  int index = -1;
  for(int i = 0; i < n; ++i) {
    index = str.indexOf(character, index + 1);
    if (index == -1) {
        break;
    }
  }
  return index+1;
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
  String cmd = "AT";
  ack = sendATCmd( cmd );

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
      _region = EU868;
    break;
    case US915 :
      ack = sendATCmd("AT+REGION=US915");
      _region = US915;
    break;
    case CN470 :
      ack = sendATCmd("AT+REGION=CN470");
      _region = CN470;
    break;
    default : 
      LDBG("unsupported region");
  }

   LDBG(ack);
  if(ack == "+REGION=OK\r\n"){
    return true;
  } else {
    return false;
  }
}

bool LWNode::setFreq(uint32_t freq){
  String ack;
  String cmd("AT+FREQS=");
  cmd += String(freq);
  ack = sendATCmd(cmd);
  LDBG(ack);
  
  if(ack == "+FREQS=OK\r\n"){
    return true;
  } else {
    return false;
  }
}

bool LWNode::setBW(uint32_t bw){
  String ack;
  String cmd("AT+BW=");
  cmd += String(bw);
  ack = sendATCmd(cmd);
  LDBG(ack);

  if(ack == "+BW=OK\r\n"){
    return true;
  } else {
    return false;
  }
}

bool LWNode::setSF(uint8_t sf){
  String ack;
  String cmd("AT+SF=");
  cmd += String(sf);
  ack = sendATCmd(cmd);
  LDBG(ack);

  if(ack == "+SF=OK\r\n"){
    return true;
  } else {
    return false;
  }
}

Stream *uarts;
static uint8_t data[128];
#if defined(HAVE_HWSERIAL0)
void serialEvent(){
  if(uarts == &Serial) {
    uint8_t i = 0;
    if((_rxCB || _rxCB3) && IntEnable){ 
      while(uarts->available()){
        data[i] = uarts->read();
        i++;
        if(!uarts->available()) delay(5);
      }
      data[i] = 0;
      if(_rxCB) {
        if(i <= 2) return;
        for(uint8_t j = 0 ;j<i;j++ ){

         Serial.println(data[j]);
        }
        
        _rxCB(data+2, i-2,  -((int8_t)data[0]), ((int8_t)data[1])-50);
      } else if (_rxCB3) {
        if(i <= 4) return;
        if((data[0] == 0xff) || (data[0] == loranode->_from)){
          _rxCB3(data[1], &data[4], i-4, -((int8_t)data[2]), ((int8_t)data[3])-50);
        }
      }
    }
  }
}
#endif

#if defined(HAVE_HWSERIAL1)
void serialEvent1(){
  // Serial.print("_rxCB=");Serial.println((uint16_t)_rxCB);
  // Serial.print("_rxCB3=");Serial.println((uint16_t)_rxCB3);
  // Serial.print("IntEnable=");Serial.println((uint16_t)IntEnable);
  // Serial.print("uarts=");Serial.println((uint16_t)uarts);
  if(uarts == &Serial1) {
    uint8_t i = 0;
    if((_rxCB || _rxCB3) && IntEnable){
      while(uarts->available()){
        data[i] = uarts->read();
        i++;
        if(!uarts->available()) delay(5);
      }
      data[i] = 0;
      if(_rxCB) {
        if(i <= 2) return;

        
        _rxCB(data+2, i-2,  -((int8_t)data[0]), ((int8_t)data[1])-50);
      } else if (_rxCB3) {
        if(i <= 4) return;
        if((data[0] == 0xff) || (data[0] == loranode->_from)){
          _rxCB3(data[1], &data[4], i-4, -((int8_t)data[2]), ((int8_t)data[3])-50);
        }
      }
    }
  }
}
#endif

#if defined(HAVE_HWSERIAL2)
void serialEvent2(){
  if(uarts == &Serial2) {
    uint8_t i = 0;
    if((_rxCB || _rxCB3) && IntEnable){
      while(uarts->available()){
        data[i] = uarts->read();
        i++;
        if(!uarts->available()) delay(5);
      }
      data[i] = 0;
      if(_rxCB) {
        if(i <= 2) return;
        _rxCB(data+2, i-2,  -((int8_t)data[0]), ((int8_t)data[1])-50);
      } else if(_rxCB3) {
        if(i <= 4) return;
        if((data[0] == 0xff) || (data[0] == loranode->_from)){
          _rxCB3(data[1], &data[4], i-4, -((int8_t)data[2]), ((int8_t)data[3])-50);
        }
      }
    }
  }
}
#endif
#if defined(HAVE_HWSERIAL3)
void serialEvent3(){
  if(uarts == &Serial3) {
    uint8_t i = 0;
    if((_rxCB || _rxCB3) && IntEnable) {
      while(uarts->available()){
        data[i] = uarts->read();
        i++;
        if(!uarts->available()) delay(5);
      }
      data[i] = 0;
      if(_rxCB) {
        if(i <= 2) return;
        _rxCB(data+2, i-2,  -((int8_t)data[0]), ((int8_t)data[1])-50);
      } else if(_rxCB3) {
        if(i <= 4) return;
        if((data[0] == 0xff) || (data[0] == loranode->_from)){
          _rxCB3(data[1], &data[4], i-4, -((int8_t)data[2]), ((int8_t)data[3])-50);
        }
      }
    }
  }
}
#endif
void LWNode::setRxCB(rxCB *callback){
  _rxCB = callback;
}

void LWNode::setRxCB(rxCB3 *callback){
  _rxCB3 = callback;
}

bool LWNode::setAppEUI(const char *appeui){
  String AT = String("AT+JOINEUI=") + appeui;
  AT.toUpperCase();
  String ack;
  ack = sendATCmd(AT);
  if(ack == "+JOINEUI=OK\r\n"){
    return true;
  }else{
    return false;
  }
}
bool LWNode::setAppKEY(const char *appkey){
  String AT = String("AT+APPKEY=") + appkey;
  String ack;
  AT.toUpperCase();
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
bool LWNode::setEIRP(uint8_t EIRP){
  String AT = "AT+EIRP="+String(EIRP);
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
bool LWNode::enableADR(bool adr){
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
  String AT = String("AT+DEVADDR=")+String(devAddr,HEX);
  String ack;
  ack = sendATCmd(AT);
  if(ack == "+DEVADDR=OK\r\n"){
   return true;
  }else{
   return false;
  }
}

bool LWNode::setAppSKey(const char * appSKey){
  String AT = String("AT+APPSKEY=")+ appSKey;
  AT.toUpperCase();
  String ack;
  ack = sendATCmd(AT);
  if (ack == "+APPSKEY=OK\r\n"){
   return true;
   
  }else{
   return false;
  }
}

bool LWNode::setNwkSKey(const char * nwkSKey){
  String AT = String("AT+NWKSKEY=")+ nwkSKey;
  AT.toUpperCase();
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
  if(ack == "+UPLINKTYPE=OK\r\n"){
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

bool LWNode::start(){
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

bool LWNode::setLoRaAddr(uint8_t addr){
  String AT = "AT+LORAADDR=" + String(addr);
  String ack;
  ack = sendATCmd(AT);
  if(ack == "+LORAADDR=OK\r\n"){
    return true;
  }else{
    return false;
  }
}

bool LWNode::sendPacket(double v){
  char buf[20]={0};
  sprintf(buf, "%.3lf", v);
  return sendPacket(buf, strlen(buf));
}

bool LWNode::sendPacket(int32_t v){
  char buf[20]={0};
  itoa(v,buf,10);
  return sendPacket(buf, strlen(buf));
}

bool LWNode::sendPacket(uint32_t v){
	char buf[20]={0};
	itoa(v,buf,10);
	return sendPacket(buf, strlen(buf));
}

bool LWNode::sendPacket(void *buffer, uint8_t size){
  String AT = "AT+SEND=";
  String ack;
  uint8_t *data = (uint8_t *)buffer;
  char *output = (char*)malloc(size*2+2);
  int i, len;

  for (i = 0; i < size; i++) {
      //Serial.println(data[i],HEX);
      sprintf(output + i * 2, "%02X", data[i]);
  }
     
  for(uint8_t i = 0; i<size*2; i++) {
      AT += output[i];
  }
  ack = sendATCmd(AT);
  free(output);
  if(ack == "AT+SEND=OK\r\n") {
    return true;
  } else {
    return false;
  }
}

bool LWNode::sendPacket(String data){
  String AT = "AT+SEND=";
  String ack;

  char *output = (char*)malloc(data.length()*2+2);
  int i, len;

  for (i = 0; i < data.length(); i++) {
    sprintf(output + i * 2, "%02X", data[i]);
  }

  for(uint8_t i = 0;i<data.length()*2;i++){
    AT+=output[i];
  }

  ack = sendATCmd(AT);
  //sendData((uint8_t *)data.c_str(),data.length());
  free(output);
  if(ack == "AT+SEND=OK\r\n"){
    return true;
  }else{
    return false;
  }
}

bool LWNode::sendPacket(uint8_t to, void *buffer, uint8_t size){
  String AT = "AT+SEND=";
  String ack;
  uint8_t *data = (uint8_t *)buffer;
  char *output = (char*)malloc(size*2 + 2 + 4);
  int i, len;
  
  sprintf(output, "%02X", to);
  sprintf(output + 2, "%02X", _from);

  for (i = 0; i < size; i++) {
    //Serial.println(data[i],HEX);
    sprintf(output + 4 + i * 2, "%02X", data[i]);
  }
     
  for(uint8_t i = 0;i<size*2 + 4;i++){
    AT+=output[i];
  }
  ack = sendATCmd(AT);
  free(output);
  if(ack == "AT+SEND=OK\r\n"){
    return true;
  }else{
    return false;
  }
}

bool LWNode::sendPacket(uint8_t to, String data){
    String AT = "AT+SEND=";
    String ack;

    char *output = (char*)malloc(data.length()*2 + 2 + 4);
    int i, len;

    sprintf(output, "%02X", to);
    sprintf(output + 2, "%02X", _from);

    for (i = 0; i < data.length(); i++) {
        sprintf(output + 4 + i * 2, "%02X", data[i]);
    }

    for(uint8_t i = 0; i<data.length()*2+4; i++){
        AT+=output[i];
    }

    ack = sendATCmd(AT);
    //sendData((uint8_t *)data.c_str(),data.length());
    free(output);
    if(ack == "AT+SEND=OK\r\n"){
        return true;
    }else{
        return false;
    }
}

bool LWNode::getDevEUI(uint8_t *eui){
  String AT = "AT+DEVEUI?";
  String ack;
  ack = sendATCmd(AT).substring(8, 27);;
  
  for (int i = 0; i < ack.length(); i+=2) {
     String byteString = ack.substring(i, i+2);
      eui[i/2] = (uint8_t) strtol(byteString.c_str(), NULL, 16);
   }
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
  String ack;

  uint8_t dataRate = 0;
  ack = sendATCmd(AT).substring(10, 11);

  dataRate = ack.toInt();
  return dataRate;
}

uint8_t LWNode::getEIRP(){
  String AT = "AT+EIRP?";
  String ack;
  uint8_t eirp = 0;
  ack = sendATCmd(AT).substring(6, 7);

  eirp = ack.toInt();
  return eirp;
}

int16_t LWNode::getRSSI(){
  String AT = "AT+RSSI?";
  String ack;
  int16_t rssi = 0;
  ack = sendATCmd(AT);
  ack = ack.substring(6, ack.length()-2);

  rssi = ack.toInt();
  return rssi;
}

int8_t LWNode::getSNR(){
  String AT = "AT+SNR?";
  String ack;
  int8_t snr = 0;
  ack = sendATCmd(AT);
  ack = ack.substring(5, ack.length()-2);
  snr = ack.toInt();
  return snr;
}


String LWNode::sendATCmd(String cmd){
   String ack;
   cmd = cmd + "\r\n";
   IntEnable = false;
   sendData((uint8_t*) cmd.c_str(),cmd.length());
   delay(800);
   ack = readACK();

   IntEnable = true;
   return ack;
}

String LWNode::sendATCmdTest(char* cmd){
   char ack[20]={0} ;
   strcat(cmd,"\r\n");
   Serial.print(cmd);
   Serial.print("OK\r\n");
   delay(100);
   return "OK\r\n";
}

DFRobot_LWNode_UART::DFRobot_LWNode_UART(const char *appEui,const char *appKey, eDeviceClass_t classType, eDataRate_t dataRate, etxPower_t txPower,bool adr, uint8_t subBand)
{
  memcpy(_appeui, appEui, 16);
  memcpy(_appKey, appKey, 32);
  _appeui[16] = 0;
  _appKey[32] = 0;
  _dataRate = dataRate;
  joinType = 1;
  _classType = classType;
  _txPower = txPower;
  _adr = adr;
  _subBand = subBand;
}

DFRobot_LWNode_UART::DFRobot_LWNode_UART(const uint32_t devAddr ,const char *nwkSKey,const char *appSKey, eDeviceClass_t classType, eDataRate_t dataRate,etxPower_t txPower,bool adr , uint8_t subBand){
  memcpy(_appeSKey,appSKey,32);
  memcpy(_nwkSKey,nwkSKey,32);
  _appeSKey[32] = 0;
  _nwkSKey[32] = 0;

  _devAddr = devAddr;
  joinType = 0;
  _dataRate = dataRate;
  _classType = classType;
  _txPower = txPower;
  _adr = adr;
  _subBand = subBand;
}

DFRobot_LWNode_UART::DFRobot_LWNode_UART( const uint8_t from ):LWNode(from){
  joinType = 2;
}

void DFRobot_LWNode_UART::sleep(uint32_t ms){
    while(ms--){
      delay(1);
      if (serialEventRun) serialEventRun();
    }
}

bool DFRobot_LWNode_UART::begin(Stream *s_, Stream *dbgs_){
    String ack;
    uint8_t timeout = 100;
    s = s_;
    dbgs = dbgs_;
    uarts = s_;
    loranode = this;
    //sendATCmd("+++");
    //delay(500);
    sendATCmd("AT+REBOOT\r\n");

    while(!atTest()){
         timeout--;
         if(timeout == 0) return false;
    }
    //sendATCmd("AT+RECV=1");
    if(joinType == 0){ //ABP
        sendATCmd("AT+LORAMODE=LORAWAN");
        ack = sendATCmd("AT+JOINTYPE=ABP");
        if(ack == "+JOINTYPE=OK\r\n"){
          setAppSKey(_appeSKey);
          setNwkSKey(_nwkSKey);
          setDevAddr(_devAddr);
          join();
          return true;
        }else{
          return false;
        }
    }else if(joinType == 1){   //OTAA
        sendATCmd("AT+LORAMODE=LORAWAN");
        ack = sendATCmd("AT+JOINTYPE=OTAA");
        if(_appKey !=NULL)
        setAppKEY(_appKey);
    }else{
        sendATCmd("AT+LORAMODE=LORA\r\n");
        setLoRaAddr(_from);
    }
    return true;
}

void DFRobot_LWNode_UART::sendData(uint8_t *data ,uint8_t len ){
    s->write(data,len);
    s->flush();
    delay(100);
    if(dbgs){
        dbgs->write(data, len);
        dbgs->flush();
        delay(100);
    }
}

String DFRobot_LWNode_UART::readData(){
    String str  = readACK();
    if(str == "") return "";
    return str.substring(2,255);
    //int  len ,index,j;
    //len = str.length();
    //index = findNthOccurrence(str,':',6);
    //String msg ;
    //for (int i = index; i < len; i += 2) {
    //   String byteString = str.substring(i, i+2);
       //buf[(i-index)/2] = (uint8_t) 
    //   msg += (char)strtol(byteString.c_str(), NULL, 16);
    // }
    //return msg;
}

size_t DFRobot_LWNode_UART::readData(uint8_t *buf){
  String str  = readACK();
  if((str == "") || (str.length()<=2)) return 0;
  strcpy((char*)buf, str.c_str()+2);
  return str.length()-2;
}

String DFRobot_LWNode_UART::readACK(){
  uint16_t timeout = 100;
  uint16_t i = 0;
  String ack("");
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
  //delay(150);
  if(dbgs){
    dbgs->flush();
    dbgs->write(ack.c_str(),ack.length());
    delay(100);
  }
  return ack;
}

DFRobot_LWNode_IIC::DFRobot_LWNode_IIC( const uint8_t from ):LWNode(from) {
  joinType = 2;
  _deviceAddr = 0x20;
}

DFRobot_LWNode_IIC::DFRobot_LWNode_IIC(const char *appEui,const char *appKey, eDeviceClass_t classType, eDataRate_t dataRate, etxPower_t txPower,bool adr, uint8_t subBand) {
  memcpy(_appeui,appEui,16);
  memcpy(_appKey,appKey,32);
  _appeui[16] = 0;
  _appKey[32] = 0;
  _dataRate = dataRate;
  joinType = 1;
  _classType = classType;
  _txPower = txPower;
  _adr = adr;
  _subBand = subBand;

  _deviceAddr = 0x20;
}

DFRobot_LWNode_IIC::DFRobot_LWNode_IIC(const uint32_t devAddr ,const char *nwkSKey,const char *appSKey, eDeviceClass_t classType, eDataRate_t dataRate,etxPower_t txPower,bool adr , uint8_t subBand) {
  memcpy(_appeSKey,appSKey,32);
  memcpy(_nwkSKey,nwkSKey,32);
  _appeSKey[32] = 0;
  _nwkSKey[32] = 0;
  _devAddr = devAddr;
  joinType = 0;
  _dataRate = dataRate;
  _classType = classType;
  _txPower = txPower;
  _adr = adr;
  _subBand = subBand;

  _deviceAddr = 0x20;
}

void DFRobot_LWNode_IIC::sleep(uint32_t ms){
  unsigned long tick = millis();
  while(millis() - tick < ms){
    if((!_rxCB)  && (!_rxCB3)) {
      delay(ms);
      continue;
    }
    String str  = readACK();
    uint16_t len = str.length();
    if(len == 0 ) continue;

    if(_rxCB != NULL){
      if(str.length() > 2)
        _rxCB((void *)str.c_str()+2, (unsigned int)str.length()-2, -str.c_str()[0], str.c_str()[1]-50);
    }
    if(_rxCB3 != NULL){
      if(str.length() > 4)
        if(((uint8_t)(str.c_str()[0]) == _from) || (((uint8_t)str.c_str()[0] == 0xFF)))
          _rxCB3(str.c_str()[1], (void *)&str.c_str()[4], (unsigned int)str.length()-4, -str.c_str()[2], str.c_str()[3]-50);
    }
  }
}

bool DFRobot_LWNode_IIC::begin(TwoWire *pWire,Stream *dbgs_){
  _pWire  = pWire;
  String ack;
  dbgs = dbgs_;
  _pWire->begin();
  delay(100);
  sendATCmd("AT+REBOOT\r\n");

  while(!atTest());
  sendATCmd("AT+RECV=1");
  
  if(joinType == 0){
      sendATCmd("AT+LORAMODE=LORAWAN");
      ack = sendATCmd("AT+JOINTYPE=ABP");
      if(ack == "+JOINTYPE=OK\r\n"){
        setAppSKey(_appeSKey);
        setNwkSKey(_nwkSKey);
        setDevAddr(_devAddr);
        join();
        return true;
      }else{
        return false;
      }
  }else if(joinType == 1){
    sendATCmd("AT+LORAMODE=LORAWAN");
    ack = sendATCmd("AT+JOINTYPE=OTAA");
    if(_appKey !=NULL)
    setAppKEY(_appKey);
  }else{
    sendATCmd("AT+LORAMODE=LORA\r\n");
    setLoRaAddr(_from);
  }
  return true;
}

void DFRobot_LWNode_IIC::sendData(uint8_t *data ,uint8_t len ){
  uint8_t dataLen = len;
  uint8_t * dataP = data ;

  while(dataLen > 30){
    writeReg(REG_WRITE_AT_LONG,data,30);
    dataLen -=30;
    data +=30;

    delay(100);
  }
  writeReg(REG_WRITE_AT,data,dataLen);
}

String DFRobot_LWNode_IIC::readACK(){
  static char data[256];
  uint8_t * dataP = (uint8_t *)data ;
  String ack;
  uint8_t dataLen = readReg(REG_READ_AT_LEN);
  uint8_t len = dataLen;
  //Serial.print("ack dataLen:");
  //Serial.println(dataLen);
  if(len == 0){
    return "";
  }
  while(dataLen > 30){
    readReg(REG_READ_AT,dataP,30);
    dataP+=30;
    dataLen = dataLen-30;
  }
  readReg(REG_READ_AT,dataP,dataLen);
  
  for(uint8_t i =0;i<len;i++){
    ack += data[i];
  }
  //if(dbgs){
  //  dbgs->write(ack.c_str(),ack.length());
  //  dbgs->flush();
  //}

  return ack;
}

String DFRobot_LWNode_IIC::readData(){
  String str  = readACK();
  if((str == "") || (str.length()<=2)) return "";
  return str.substring(2,255);
  //if(str == "") return "";
  //int  len ,index,j;
  //len = str.length();
  //index = findNthOccurrence(str,':',6);
  //String msg ;
  //for (int i = index; i < len; i+=2) {
  //  String byteString = str.substring(i, i+2);
  //  //buf[(i-index)/2] = (uint8_t) 
  //  msg += (char)strtol(byteString.c_str(), NULL, 16);
  // }
  //return msg;
}

size_t DFRobot_LWNode_IIC::readData(uint8_t *buf) {
  String str  = readACK();
  if((str == "") || (str.length()<=2)) return 0;
  strcpy((char*)buf, str.c_str()+2);
  return str.length()-2;
  //int  len ,index,j;
  //len = str.length();
  //index = findNthOccurrence(str,':',6);
  //for (int i = index; i < len; i+=2) {
  //   String byteString = str.substring(i, i+2);
  //   buf[(i-index)/2] = (uint8_t) strtol(byteString.c_str(), NULL, 16);
  // }
  //
  //return (len-index)/2;
}

void DFRobot_LWNode_IIC::writeReg(uint8_t reg ,uint8_t * data,uint8_t len) {
  _pWire->beginTransmission(_deviceAddr);
  _pWire->write(reg);

  for(uint8_t i = 0 ; i < len ; i++){
    _pWire->write(data[i]);
  }
   if(dbgs){
      dbgs->flush();
      dbgs->write(data,len);
    }
  _pWire->endTransmission();

}

uint8_t DFRobot_LWNode_IIC::readReg(uint8_t reg){
  uint8_t value;
  _pWire->beginTransmission(_deviceAddr);
  _pWire->write(reg);
  _pWire->endTransmission();
  
  _pWire->requestFrom(_deviceAddr,(uint8_t)1);
  value = _pWire->read();
  return value;
}
uint8_t DFRobot_LWNode_IIC::readReg(uint16_t reg,uint8_t data[],uint8_t length)
{

  _pWire->beginTransmission(_deviceAddr);
  _pWire->write(reg);
  _pWire->endTransmission();
  _pWire->requestFrom(_deviceAddr,length);

  for(uint8_t i = 0 ; i < length ;i++){
    data[i] = _pWire->read();
  }

  return 0;
}