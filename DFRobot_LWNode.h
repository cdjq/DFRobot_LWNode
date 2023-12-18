



#ifndef _DFROBOT_LORANWANNODE_H
#define _DFROBOT_LORANWANNODE_H

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include <Wire.h>
#include <stdint.h>
//#define ENABLE_DBG
#ifdef ENABLE_DBG
#define LDBG(...)  {Serial.print("["); Serial.print(__FUNCTION__); Serial.print("(): "); Serial.print(__LINE__); Serial.print(" ] "); Serial.println(__VA_ARGS__);}
#else
#define LDBG(...)
#endif

typedef void joinCallback(bool isOk, int16_t rssi, int8_t snr);
typedef void rxCB(void *buffer, uint16_t size);
typedef void buttonCallback(void);
typedef void sendCallback(void);


typedef enum{
  CLASS_A,
  CLASS_C,
} eDeviceClass_t;

typedef enum{
  CONFIRMED_PACKET,
  UNCONFIRMED_PACKET,
} ePacketType_t;

typedef enum{
  TX_POWER_0,
  TX_POWER_1,
  TX_POWER_2,
  TX_POWER_3,
  TX_POWER_4,
  TX_POWER_5,
  TX_POWER_6,
  TX_POWER_7,
  TX_POWER_8,
  TX_POWER_9,
  TX_POWER_10,
  TX_POWER_11,
  TX_POWER_12,
  TX_POWER_13,
  TX_POWER_14,
} etxPower_t;
typedef enum{
  EU868,
  US915,
  CN470,
} eRegion_t;
typedef enum{
  DR0,
  DR1,
  DR2,
  DR3,  
  DR4,
  DR5,
  DR6,
  DR7,
  DR8,
  DR9,
  DR10,
  DR11,
  DR12,
} eDataRate_t;

class LWNode
{
  public:
    //OTAA优势：每个设备的appEui和appKey都可以一样
	//subBand：CN470和US915需要，EU868不支持这个功能
    LWNode(const uint8_t *appEui=NULL,const uint8_t *appKey=NULL, eDeviceClass_t classType=CLASS_C, eDataRate_t dataRate=DR6, etxPower_t txPower=TX_POWER_4,bool adr = true, uint8_t subBand=11);
    LWNode(const uint32_t devAddr ,const uint8_t *nwkSKey,const uint8_t *appSKey, eDeviceClass_t classType=CLASS_C, eDataRate_t dataRate=0,etxPower_t txPower=16,bool adr = true, uint8_t subBand=11);
    //ABP设备构造函数，建议不支持ABP设备
    //缺点：每个设备的devAddr都必须不同，ABP能够支持的功能OTAA都能支持。和OTAA功能很重叠，又没有OTAA好用
    //LWNode(const uint32_t devAddr ,const uint8_t *nwkSKey,const uint8_t *appSKey, eDeviceClass_t classType=CLASS_C, int8_t dataRate=0,int8_t txPower=16,bool adr = true, uint8_t subBand=11);

  /*设置接收回调函数  网关主动给节点发送数据，callback将被调用
    callback: 回调函数
    返回值：无
  */
    bool setRegion(eRegion_t region);
    void setRxCB(rxCB *callback);
    bool setAppEUI(const uint8_t *appeui);
    bool setAppKEY(const uint8_t *appkey);
    bool setDevType(eDeviceClass_t classType);
    bool setDataRate(eDataRate_t dataRate);
    bool setTXPower(uint8_t txPower);
    bool setSubBand(uint8_t subBand);
    bool enableADR(bool adr);


    bool setDevAddr(const uint32_t devAddr);
    bool setAppSKey(const uint8_t * appSKey);
    bool setNwkSKey(const uint8_t * nwkSKey);



    /*发起入网  设备自动发起入网   设备会重启，发起入网
	callback: 入网回调函数
	返回值：true 已经成功发起入网 false 未能成功发起入网
    */
    bool join();
	
    /*
    查询是否已经入网
    返回值：true 已经入网   false 没有入网
    */
    bool isJoined();
	
    /*
	函数功能：发送数据包
	buffer: 要发送的数据地址
	size： 要发送的数据长度
	返回值：true 设置成功   false 设置失败
    */
    bool sendPacket(void *buffer, uint8_t size);
    bool sendPacket(String data);
	
	/*
	函数功能：通用AT指令发送
	cmd:已经封装的AT指定，不带\r\n
	返回值：AT指令的返回值
	*/
    String sendATCmd(String cmd);
	
	
	
	/*
	函数功能：设置子频段，CN470和US915需要，EU868不支持这个功能
	返回值：true 设置成功   false 设置失败
	*/
    //bool setSubBand(uint8_t subBand=11);
		
	/*
	函数功能：设置包类型
	type: CONFIRMED_PACKET UNCONFIRMED_PACKET
	返回值：true 设置成功   false 设置失败
	*/
    bool setPacketType(ePacketType_t type=UNCONFIRMED_PACKET);	
	
	/*
	函数功能：获取设备EUI
                eui   deveui存放的buf，应用层传入
	返回值：true 成功获取   false 获取失败
	*/
    bool getDevEUI(uint8_t *eui);

	/*
	函数功能：获取NetID
	返回值：3bytes的网络id信息
	*/
    uint32_t getNetID();
	
	/*
	函数功能：获取设备地址，OTAA模式下，这个地址是由网关分配的
	返回值：4bytes的设备地址信息
	*/
    uint32_t getDevAddr();
	/*
	函数功能：获取设备速率
	返回值：设备当前的DATARATE
	*/
    uint8_t  getDataRate();
	/*
	函数功能：获取当前的发射功率
	返回值：设备当前的DATARATE
	*/
    bool enTrans();
    uint8_t  getTxPower();

    bool atTest();
    virtual void sendData(uint8_t *data ,uint8_t len ) =0 ;
    virtual String readACK() = 0;
    uint8_t _appeui[8],_appKey[16];
    uint8_t _appeSKey[16],_nwkSKey[16];
    bool _isOtaa = true;
    eDeviceClass_t _deviceClass;
    eDataRate_t _dataRate = DR4;
    
    eDeviceClass_t _classType = CLASS_A;
    etxPower_t _txPower;
    bool _adr = false;
    uint8_t _subBand = 0;
    uint8_t _region = EU868;
    uint32_t _devAddr;
    bool isOtaa =true;
  private:
  
  protected:
};




class DFRobot_LWNode_UART : public LWNode
{

public: 
  DFRobot_LWNode_UART(const uint8_t *appEui=NULL,const uint8_t *appKey=NULL, eDeviceClass_t classType=CLASS_C, eDataRate_t dataRate=DR7, etxPower_t txPower=TX_POWER_4,bool adr = true, uint8_t subBand=11);
  DFRobot_LWNode_UART(const uint32_t devAddr ,const uint8_t *nwkSKey,const uint8_t *appSKey, eDeviceClass_t classType=CLASS_C, eDataRate_t dataRate=0,etxPower_t txPower=16,bool adr = true, uint8_t subBand=11);
  bool begin(Stream &s_ =Serial1, Stream &dbgs_ =Serial);

  void sendData(uint8_t *data ,uint8_t len );
  String readACK();

private:

  Stream *s,*dbgs;
};
class DFRobot_LWNode_IIC :public LWNode
{

public: 
  DFRobot_LWNode_IIC(const uint8_t *appEui=NULL,const uint8_t *appKey=NULL, eDeviceClass_t classType=CLASS_C, eDataRate_t dataRate=DR7, etxPower_t txPower=TX_POWER_4,bool adr = true, uint8_t subBand=11);
  
  bool begin(TwoWire *pWire = &Wire);

  void sendData(uint8_t *data ,uint8_t len );
  String readACK();

private:

  TwoWire *_pWire;
  uint8_t _deviceAddr;
};

#endif
#if 0

应用1
LWNode node();
node.join();
while(!node.isJoined()){
   delay(5000);
}
//这个包会成功发送
node.sendPacket("hello");


应用2
void recv(void *buffer, uint16_t size){
   Serial.print("buffer size");
}

LWNode node();
node.setRxCB(callback);
node.join();
while(node.isJoined()){
   delay(5000);
}

//这个包会成功发送
node.sendPacket("hello");


应用3
LWNode node();
node.setDevAddr(0x11223344);
//node.setAppSKey("8da98798a8d7f98a7d8da98798a8d7f9");
//node.setNwkSKey("92837989a8987bcd2343a78678e77f78");

//不能确认这个通信包是否发送成功
node.sendPacket("hello");
#endif 