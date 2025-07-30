#include "ASerial_core/ASerial_ErrorCodeList.h"
#include "ASerial_core/ASerial_packet.h"
#include <Arduino.h>
#include <stdint.h>

class ASerial_Lib_MCU : public ASerialPacket {
  public:
    
    /// @brief ASerial_Lib_MCUコンストラクタ(deviceモード)
    /// @param device_id デバイスID
    /// @param device_ver デバイスVer
    ASerial_Lib_MCU(uint8_t device_id, uint8_t device_ver);
    
    /// @brief ASerial_Lib_MCUコンストラクタ(controllerモード)
    /// @param target_device_id ターゲットデバイスID
    ASerial_Lib_MCU(uint8_t target_device_id);

    /// @brief 通信のインターフェースのポインタを設定
    /// @param _interface インターフェイスのポインタ
    void SetInterfacePt(Stream *_interface);

    /// @brief リセット関数のポインタを設定
    /// @param func_pt リセット関数のポインタ
    void SetResetFuncPt(void (*func_pt)(void));

    /// @brief パケットデータを読み取り
    /// @param read_data_buf データを格納するバッファへのポインタ
    /// @return 読み取り中は0、エラーが発生した場合は-1、読み取り完了で1を返す。
    int ReadDataProcess(ASerialDataStruct::ASerialData *read_data_buf);

    /// @brief パケット送信
    /// @param command コマンド
    /// @param data データ配列
    /// @param data_num データ数
    /// @return 正常時は0、エラー時は-1を返す。
    int WriteData(uint8_t command, uint8_t *data, uint8_t data_num);

    /// @brief パケット送信
    /// @param data データ配列
    /// @param data_num データ数
    /// @return 正常時は0、エラー時は-1を返す。
    int WriteData(uint8_t *data, uint8_t data_num);

  private:
    Stream *m_interface = nullptr;          // ストリームクラスのポインタ格納
    void (*m_reset_func)(void) = nullptr;   // リセット関数のポインタ

    /// @brief デバイス情報を送信
    /// @return 正常時は0、エラー時は-1を返す。
    int WriteDeviceInfo(void);
};
