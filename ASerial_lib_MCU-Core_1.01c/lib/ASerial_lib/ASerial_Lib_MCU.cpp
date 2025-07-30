#include "ASerial_Lib_MCU.h"


ASerial_Lib_MCU::ASerial_Lib_MCU(uint8_t device_id, uint8_t device_ver) : ASerialPacket(device_id, device_ver)
{

}

ASerial_Lib_MCU::ASerial_Lib_MCU(uint8_t target_device_id) : ASerialPacket(target_device_id)
{

}

void ASerial_Lib_MCU::SetInterfacePt(Stream *_interface)
{
    if(_interface == nullptr){
        return;
    }
    m_interface = _interface;
}

void ASerial_Lib_MCU::SetResetFuncPt(void (*func_pt)(void))
{   
    if(func_pt == nullptr) {
        return;
    }

    m_reset_func = func_pt;

    return;
}

int ASerial_Lib_MCU::ReadDataProcess(ASerialDataStruct::ASerialData *read_data_buf)
{   
    int st = 0;
    if(m_interface->available() > 0) {
        st = ReadPacketData((uint8_t)m_interface->read(), read_data_buf);
    }

    if(st == 1 && GetMode() == MODE_DEVICE) {
        if(read_data_buf->command == RESERVED_COMMAND_RESET) {
            if(m_reset_func != nullptr){
                m_reset_func();
            }
        }
        else if(read_data_buf->command == RESERVED_COMMAND_GET_INFO) {
            WriteDeviceInfo();
        }
    }

    return st;
}

int ASerial_Lib_MCU::WriteData(uint8_t command, uint8_t *data, uint8_t data_num)
{
    if(GetMode() == MODE_DEVICE) {
        return -1;
    }

    size_t BUF_SIZE = GetNeedPacketBufSize(data, data_num);
    uint8_t *packet_buf = new uint8_t[BUF_SIZE];

    int st = MakePacketData(data, data_num, command, packet_buf);

    if(st == - 1){
        delete [] packet_buf;
        return -1;
    }

    m_interface->write(packet_buf, BUF_SIZE);   //データの送信

    delete [] packet_buf;
    return 0;
}

int ASerial_Lib_MCU::WriteData(uint8_t *data, uint8_t data_num)
{
    if(GetMode() == MODE_CONTROLLER) {
        return -1;
    }

    size_t BUF_SIZE = GetNeedPacketBufSize(data, data_num);
    uint8_t *packet_buf = new uint8_t[BUF_SIZE];

    int st = MakePacketData(data, data_num, packet_buf);

    if(st == - 1){
        delete [] packet_buf;
        return -1;
    }

    m_interface->write(packet_buf, BUF_SIZE);   //データの送信

    delete [] packet_buf;
    
    return st;
}

int ASerial_Lib_MCU::WriteDeviceInfo(void)
{   
    const uint8_t DATA_NUM = 4;
    uint8_t aserial_ver[2] = {(uint8_t)((ASERIAL_VER & 0xFF00) >> 8), (uint8_t)(ASERIAL_VER & 0x00FF)};
    uint8_t device_info_data[DATA_NUM] = {GetID(), GetVer(), aserial_ver[0], aserial_ver[1]};

    int st = WriteData(device_info_data, DATA_NUM);

    return st;
}
