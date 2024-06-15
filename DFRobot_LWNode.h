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
typedef void rxCB3(uint8_t from, void *buffer, uint16_t size);
typedef void buttonCallback(void);
typedef void sendCallback(void);
#define REG_WRITE_AT_LONG       0x39
#define REG_WRITE_AT            0x40
#define REG_READ_AT_LEN         0x41
#define REG_READ_AT             0x42
#define REG_READ_AT_LONG        0x43

/**
 * @brief 设备类别的 LoRaWAN 枚举。
 */
typedef enum {
  CLASS_A, ///< A 类设备
  CLASS_C  ///< C 类设备
} eDeviceClass_t;

/**
 * @brief LoRaWAN 中数据包类型的枚举。
 */
typedef enum {
  CONFIRMED_PACKET,   ///< 确认数据包
  UNCONFIRMED_PACKET  ///< 非确认数据包
} ePacketType_t;

/**
 * @brief 发射功率的枚举。
 */
typedef enum {
  DBM0 =0,
  DBM2 = 2,
  DBM4 = 4,
  DBM6 = 6,
  DBM8 = 8,
  DBM10 = 10,
  DBM12 = 12,
  DBM14 = 14,
  DBM16 = 16,
  DBM18 = 18,
  DBM20 = 20,
  DBM22 = 22,
  DBM24 = 24,
  DBM26 = 26,
  DBM28 = 28,
} etxPower_t;

/**
 * @brief LoRaWAN 区域的枚举。
 */
typedef enum {
  EU868, ///< 欧洲 868MHz
  US915, ///< 美国 915MHz
  CN470  ///< 中国 470MHz
} eRegion_t;

/**
 * @brief 数据速率的枚举。
 */
typedef enum {
  DR0, DR1, DR2, DR3, DR4, DR5, DR6, DR7, DR8, DR9, DR10, DR11, DR12
} eDataRate_t;

/**
 * @brief 表示 LoRaWAN 节点的类。
 */
class LWNode {
public:
  /**
   * @brief 用于 OTAA 设备的构造函数。
   * @param appEui 应用 EUI
   * @param appKey 应用密钥
   * @param classType 设备类别（默认：CLASS_C）
   * @param dataRate 数据速率（默认：DR5）
   * @param txPower 发射功率（默认：DBM8）
   * @param adr 自适应数据速率（默认：true）
   * @param subBand 用于 CN470 和 US915 的子频段（默认：11）
   */
  LWNode(const uint8_t *appEui = nullptr, const uint8_t *appKey = nullptr,
         eDeviceClass_t classType = CLASS_C, eDataRate_t dataRate = DR5,
         etxPower_t txPower = DBM8, bool adr = true, uint8_t subBand = 11);

  /**
   * @brief 用于 ABP 设备的构造函数。
   * @param devAddr 设备地址
   * @param nwkSKey 网络会话密钥
   * @param appSKey 应用会话密钥
   * @param classType 设备类别（默认：CLASS_C）
   * @param dataRate 数据速率（默认：DR5）
   * @param txPower 发射功率（默认：DBM8）
   * @param adr 自适应数据速率（默认：true）
   * @param subBand 用于 CN470 和 US915 的子频段（默认：11）
   */
  LWNode(const uint32_t devAddr, const uint8_t *nwkSKey, const uint8_t *appSKey,
         eDeviceClass_t classType = CLASS_C, eDataRate_t dataRate = DR5,
         etxPower_t txPower = DBM8, bool adr = true, uint8_t subBand = 11);


  LWNode(const uint8_t devAddr);

  /**
   * @brief 设置 LoRaWAN 区域。
   * @param region 区域枚举值
   * @return 设置成功返回 true，否则返回 false
   */
  bool setRegion(eRegion_t region);

  bool setFreq(uint32_t freq);
  bool setBW(uint32_t bw);
  bool setSF(uint8_t  sf);
  /**
   * @brief 设置接收回调函数。网关主动给节点发送数据时，此回调函数将被调用。
   * @param callback 回调函数指针
   */
  void setRxCB(rxCB *callback);
  void setRxCB(rxCB3 *callback);
  /**
   * @brief 设置应用 EUI。
   * @param appeui 应用 EUI
   * @return 设置成功返回 true，否则返回 false
   */
  bool setAppEUI(const uint8_t *appeui);
  /**
   * @brief 设置应用密钥。
   * @param appkey 应用密钥
   * @return 设置成功返回 true，否则返回 false
   */
  bool setAppKEY(const uint8_t *appkey);
  
  /**
   * @brief 设置设备类型。
   * @param classType 设备类别枚举值
   * @return 设置成功返回 true，否则返回 false
   */
  bool setDevType(eDeviceClass_t classType);
  
  /**
   * @brief 设置数据速率。
   * @param dataRate 数据速率枚举值
   * @return 设置成功返回 true，否则返回 false
   */
  bool setDataRate(eDataRate_t dataRate);
  
  /**
   * @brief 设置发射功率。
   * @param EIRP 发射功率值
   * @return 设置成功返回 true，否则返回 false
   */
  bool setEIRP(uint8_t EIRP);
  
  /**
   * @brief 设置子频段。
   * @param subBand 子频段值
   * @return 设置成功返回 true，否则返回 false
   */
  bool setSubBand(uint8_t subBand);
  
  /**
   * @brief 启用或禁用自适应数据速率（ADR）。
   * @param adr 如果为 true，启用 ADR；如果为 false，禁用 ADR
   * @return 设置成功返回 true，否则返回 false
   */
  bool enableADR(bool adr);
  
  /**
   * @brief 设置设备地址。
   * @param devAddr 设备地址
   * @return 设置成功返回 true，否则返回 false
   */
  bool setDevAddr(const uint32_t devAddr);
  
  /**
   * @brief 设置应用会话密钥。
   * @param appSKey 应用会话密钥
   * @return 设置成功返回 true，否则返回 false
   */
  bool setAppSKey(const uint8_t *appSKey);
  
  /**
   * @brief 设置网络会话密钥。
   * @param nwkSKey 网络会话密钥
   * @return 设置成功返回 true，否则返回 false
   */
  bool setNwkSKey(const uint8_t *nwkSKey);



  /**
   * @brief 发起 LoRaWAN 入网。设备自动发起入网.
   * @return true 已成功发起入网，false 未能成功发起入网
   */
  bool join();
  
  /**
   * @brief 查询设备是否已经入网。
   * @return true 已经入网，false 没有入网
   */
  bool isJoined();
  
  /**
   * @brief 发送数据包。
   * @param buffer 要发送的数据地址
   * @param size 要发送的数据长度
   * @return true 发送成功，false 发送失败
   */
  //LoRaWAN
  bool sendPacket(double v);
  bool sendPacket(int32_t v);
  bool sendPacket(uint32_t v);
  bool sendPacket(void *buffer, uint8_t size);

  //LoRa
  bool sendPacket(uint8_t addr, double v);
  bool sendPacket(uint8_t addr, int32_t v);
  bool sendPacket(uint8_t addr, uint32_t v);
  bool sendPacket(uint8_t addr, void *buffer, uint8_t size);

  /**
   * @brief 发送字符串数据包。
   * @param data 要发送的数据字符串
   * @return true 发送成功，false 发送失败
   */
  bool sendPacket(String data);
  
  bool sendPacket(uint8_t addr, String data);

  /**
   * @brief 发送通用 AT 指令。
   * @param cmd 已经封装的 AT 指令，不带\r\n
   * @return AT 指令的返回值
   */
  String sendATCmd(String cmd);
  String sendATCmdTest(char *cmd);
  //void readACKTest(char * buf);
  /**
   * @brief 设置 LoRaWAN 子频段。
   * @param subBand 子频段值
   * @return true 设置成功，false 设置失败
   */
  // bool setSubBand(uint8_t subBand = 11);
  
  /**
   * @brief 设置数据包类型。
   * @param type 数据包类型（CONFIRMED_PACKET 或 UNCONFIRMED_PACKET）
   * @return true 设置成功，false 设置失败
   */
  bool setPacketType(ePacketType_t type = UNCONFIRMED_PACKET);
  
  /**
   * @brief 获取设备 EUI。
   * @param eui 存放设备 EUI 的缓冲区，由应用层传入
   * @return true 成功获取，false 获取失败
   */
  bool getDevEUI(uint8_t *eui);
  
  /**
   * @brief 获取网络 ID。
   * @return 3 字节的网络 ID 信息
   */
  uint32_t getNetID();
  
  /**
   * @brief 获取设备地址。在 OTAA 模式下，该地址由网关分配。
   * @return 4 字节的设备地址信息
   */
  uint32_t getDevAddr();
  
  /**
   * @brief 获取设备速率。
   * @return 设备当前的数据速率
   */
  uint8_t getDataRate();
  
  /**
   * @brief 获取当前的发射功率。
   * @return 设备当前的发射功率
   */
  uint8_t getEIRP( void );
  int16_t getRSSI( void );
  int8_t getSNR( void );
  
  /**
   * @brief 执行 AT 测试命令。
   * @return 执行测试命令的结果
   */
  bool atTest();
  
  /**
   * @brief 纯虚函数，用于发送数据。
   * @param data 指向要发送的数据的指针
   * @param len 数据的长度
   */
  virtual void sendData(uint8_t *data, uint8_t len) = 0;
  
  /**
   * @brief 纯虚函数，用于读取确认消息。
   * @return 作为字符串的确认消息
   */
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
    uint8_t joinType = 1; //0 ABP 1 OTAA 2 NONE
  public:
   uint8_t _from;
  protected:
};




/**
 * @brief 通过 UART 通信的 LoRaWAN 节点类。
 */
class DFRobot_LWNode_UART : public LWNode {

public:
  /**
   * @brief 构造函数，用于 OTAA 设备。
   * @param appEui 应用 EUI
   * @param appKey 应用密钥
   * @param classType 设备类别（默认：CLASS_C）
   * @param dataRate 数据速率（默认：DR5）
   * @param txPower 发射功率（默认：DBM8）
   * @param adr 自适应数据速率（默认：true）
   * @param subBand 用于 CN470 和 US915 的子频段（默认：11）
   */
  DFRobot_LWNode_UART(const uint8_t *appEui = nullptr, const uint8_t *appKey = nullptr,
                      eDeviceClass_t classType = CLASS_C, eDataRate_t dataRate = DR5,
                      etxPower_t txPower = DBM8, bool adr = true, uint8_t subBand = 11);

  /**
   * @brief 构造函数，用于 ABP 设备。
   * @param devAddr 设备地址
   * @param nwkSKey 网络会话密钥
   * @param appSKey 应用会话密钥
   * @param classType 设备类别（默认：CLASS_C）
   * @param dataRate 数据速率（默认：DR5）
   * @param txPower 发射功率（默认：DBM8）
   * @param adr 自适应数据速率（默认：true）
   * @param subBand 用于 CN470 和 US915 的子频段（默认：11）
   */
  DFRobot_LWNode_UART(const uint32_t devAddr, const uint8_t *nwkSKey, const uint8_t *appSKey,
                      eDeviceClass_t classType = CLASS_C, eDataRate_t dataRate = DR5,
                      etxPower_t txPower = DBM8, bool adr = true, uint8_t subBand = 11);

  DFRobot_LWNode_UART(const uint8_t from);
  /**
   * @brief 初始化 LoRaWAN 节点。
   * @param s_ 用于通信的 UART 对象
   * @param dbgs 用于调试的串口对象（默认：Serial）
   * @return true 初始化成功，false 初始化失败
   */
  bool begin(Stream *s_, Stream *dbgs_ = &Serial);
  
  void Sleep(uint32_t ms);
  /**
   * @brief 读取数据。
   * @return 作为字符串的数据消息
   */
  String readData();
  size_t readData(uint8_t *buf);
  /**
   * @brief 发送数据。
   * @param data 指向要发送的数据的指针
   * @param len 数据的长度
   */
  void sendData(uint8_t *data, uint8_t len);

  /**
   * @brief 读取确认消息。
   * @return 作为字符串的确认消息
   */
  String readACK();

private:
  Stream *s;    ///< UART 通信流
  Stream *dbgs; ///< 调试信息流
};

/**
 * @brief 通过 IIC 通信的 LoRaWAN 节点类。
 */
class DFRobot_LWNode_IIC : public LWNode {

public:
  /**
   * @brief 构造函数，用于 OTAA 设备。
   * @param appEui 应用 EUI
   * @param appKey 应用密钥
   * @param classType 设备类别（默认：CLASS_C）
   * @param dataRate 数据速率（默认：DR5）
   * @param txPower 发射功率（默认：DBM8）
   * @param adr 自适应数据速率（默认：true）
   * @param subBand 用于 CN470 和 US915 的子频段（默认：11）
   */
  DFRobot_LWNode_IIC(const uint8_t *appEui = nullptr, const uint8_t *appKey = nullptr,
                     eDeviceClass_t classType = CLASS_C, eDataRate_t dataRate =DR5,
                     etxPower_t txPower = DBM8, bool adr = true, uint8_t subBand = 11);

  /**
   * @brief 构造函数，用于 ABP 设备。
   * @param devAddr 设备地址
   * @param nwkSKey 网络会话密钥
   * @param appSKey 应用会话密钥
   * @param classType 设备类别（默认：CLASS_C）
   * @param dataRate 数据速率（默认：DR5）
   * @param txPower 发射功率（默认：DBM8）
   * @param adr 自适应数据速率（默认：true）
   * @param subBand 用于 CN470 和 US915 的子频段（默认：11）
   */
  DFRobot_LWNode_IIC(const uint32_t devAddr, const uint8_t *nwkSKey, const uint8_t *appSKey,
                     eDeviceClass_t classType = CLASS_C, eDataRate_t dataRate = DR5,
                     etxPower_t txPower = DBM8, bool adr = true, uint8_t subBand = 11);

  DFRobot_LWNode_IIC( const uint8_t from );
  /**
   * @brief 初始化 LoRaWAN 节点。
   * @param pWire 用于通信的 IIC 对象（默认：Wire）
   * @param dbgs 用于调试的串口对象（默认：Serial）
   * @return true 初始化成功，false 初始化失败
   */
  bool begin(TwoWire *pWire = &Wire, Stream *dbgs_ = &Serial);
  void Sleep(uint32_t ms);
  /**
   * @brief 发送数据。
   * @param data 指向要发送的数据的指针
   * @param len 数据的长度
   */
  void sendData(uint8_t *data, uint8_t len);

  /**
   * @brief 读取确认消息。
   * @return 作为字符串的确认消息
   */
  String readACK();

  /**
   * @brief 读取数据。
   * @return 作为字符串的数据消息
   */
  String readData();
  size_t readData(uint8_t *buf);
  /**
   * @brief 读取寄存器。
   * @param reg 寄存器地址
   * @param data 存放读取数据的缓冲区
   * @param length 读取的数据长度
   * @return 读取成功返回 1，否则返回 0
   */
  uint8_t readReg(uint16_t reg, uint8_t data[], uint8_t length);

  /**
   * @brief 写入寄存器。
   * @param reg 寄存器地址
   * @param data 指向要写入数据的指针
   * @param len 写入的数据长度
   */
  void writeReg(uint8_t reg, uint8_t *data, uint8_t len);

  /**
   * @brief 读取单个寄存器。
   * @param reg 寄存器地址
   * @return 读取的寄存器值
   */
  uint8_t readReg(uint8_t reg);
  
private:
  TwoWire *_pWire; ///< IIC 通信对象
  uint8_t _deviceAddr; ///< IIC 设备地址
  Stream *dbgs; ///< 调试信息流
};


#endif
