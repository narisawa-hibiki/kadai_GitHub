#include <Arduino.h>
#include "ASerial_Lib_MCU.h"

/*
    通信テスト用プログラム
    設定したモードでマイコンが動きます。
    マイコンがデバイスモードならToDeviceパケットで送り、ToControllerパケットで返って来ます。
    逆にマイコンがコントローラモードならToControllerパケットで送り、ToDeviceパケットで返って来ます。(コマンドはダミー値が返ってきます)
*/

#define  CONTROLLER_TEST //DEVICE_TEST

#ifdef DEVICE_TEST
ASerial_Lib_MCU test(0x01, 0x01);
#endif

#ifdef CONTROLLER_TEST
ASerial_Lib_MCU test(0x01);
#endif

void setup() {
    Serial.begin(115200);
    test.SetInterfacePt(&Serial);
    test.SetConnectionState(true);
}

void loop() {
    static ASerialDataStruct::ASerialData out_data_buf;
    int st = test.ReadDataProcess(&out_data_buf);

    if(st == 1) {
        #ifdef DEVICE_TEST
            test.WriteData(out_data_buf.data, out_data_buf.data_num);
        #endif

        #ifdef CONTROLLER_TEST
            test.WriteData(0x03, out_data_buf.data, out_data_buf.data_num);
        #endif
        
    }
}