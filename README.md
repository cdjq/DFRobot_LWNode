# DFRobot_LWNode

LoRaWan  arduino 节点

![Product Image](./resources/images/SEN0486.png)

## 产品链接（https://www.dfrobot.com.cn/goods-3398.html)
    DFR1115：Gravity
## Table of Contents

* [Summary](#summary)
* [Installation](#installation)
* [Methods](#methods)
* [Compatibility](#compatibility)
* [History](#history)
* [Credits](#credits)

## Summary


Provide an Arduino library to get Humidity and Temperature by reading data from DFR1115

## Installation

To use this library, first download the library file, paste it into the \Arduino\libraries directory, then open the examples folder and run the demo in the folder.

## Methods
```C++

  /**
   * @brief 设置 LoRaWAN 区域。
   * @param region 区域枚举值
   * @return 设置成功返回 true，否则返回 false
   */
  bool setRegion(eRegion_t region);

  /**
   * @brief 设置接收回调函数。网关主动给节点发送数据时，此回调函数将被调用。
   * @param callback 回调函数指针
   */
  void setRxCB(rxCB *callback);

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
   * @param txPower 发射功率值
   * @return 设置成功返回 true，否则返回 false
   */
  bool setTXPower(uint8_t txPower);
  
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
  bool sendPacket(void *buffer, uint8_t size);
  
  /**
   * @brief 发送字符串数据包。
   * @param data 要发送的数据字符串
   * @return true 发送成功，false 发送失败
   */
  bool sendPacket(String data);
  
  /**
   * @brief 发送通用 AT 指令。
   * @param cmd 已经封装的 AT 指令，不带\r\n
   * @return AT 指令的返回值
   */
  String sendATCmd(String cmd);
  
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
  uint8_t getTxPower();
```

## Compatibility

MCU                | Work Well    | Work Wrong   | Untested    | Remarks
------------------ | :----------: | :----------: | :---------: | -----
Arduino Leonardo|      √       |              |             | 
Arduino uno|      √       |              |             | 
Arduino MEGA2560|      √       |              |             | 
FireBeetle-ESP32|      √       |              |             | 
Microbit|      √       |              |             | 


## History

- 2020/07/02 - Version 1.0.0 released.

## Credits

Written by fengli(li.feng@dfrobot.com), 2021.7.2 (Welcome to our [website](https://www.dfrobot.com/))





