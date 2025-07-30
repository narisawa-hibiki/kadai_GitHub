#include "narisawaBranch/DeviceConnectorActor.h"
#include "Misc/MemoryRead.h"

ADeviceConnectorActor::ADeviceConnectorActor()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ADeviceConnectorActor::BeginPlay()
{
    Super::BeginPlay();
    // �Q�[���J�n���Ɏ����Ńf�o�C�X�ւ̐ڑ������݂�
    ConnectToDevice();
}

void ADeviceConnectorActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    // �Q�[���I�����ɐڑ���ؒf����
    DisconnectFromDevice();
    Super::EndPlay(EndPlayReason);
}

void ADeviceConnectorActor::ConnectToDevice()
{
    // �f�o�C�XID:0x01, �f�o�C�X�o�[�W����:0x01 �̃f�o�C�X��T��
    // ����ID�̓f�o�C�X���̃v���O�����ƈ�v������K�v����
    ASerialController = MakeUnique<ASerial_Controller>(0x01, 0x01);
    SerialInterface = MakeUnique<WindowsSerial>();
    ASerialController->SetInterfacePt(SerialInterface.Get());

    // ���p�\��COM�|�[�g�������ŒT�����Đڑ�
    int connectedPort = ASerialController->AutoConnectDevice();

    if (connectedPort != -1)
    {
        ConnectionStatus = FString::Printf(TEXT("Successfully connected to COM%d"), connectedPort);
    }
    else
    {
        ConnectionStatus = TEXT("Failed to connect. Is the device connected?");
    }
}

void ADeviceConnectorActor::DisconnectFromDevice()
{
    if (ASerialController.IsValid())
    {
        ASerialController->DisConnectDevice();
        ConnectionStatus = TEXT("Disconnected");
    }
}

void ADeviceConnectorActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    // �ڑ����ł���΁A���t���[���f�[�^��M�������Ăяo��
    if (ASerialController.IsValid() && ASerialController->GetConnectionState())
    {
        ReadAndProcessData();
    }
}

void ADeviceConnectorActor::ReadAndProcessData()
{
    static ASerialDataStruct::ASerialData receivedData;
    int status = ASerialController->ReadDataProcess(&receivedData);

    // �p�P�b�g�̎�M������Ɋ��������ꍇ (status��1�ɂȂ�)
    if (status == 1)
    {
        // �����Ŏ�M�f�[�^����͂��A�u���[�v�����g�p�̕ϐ��Ɋi�[

        if (receivedData.command == 0x20 && receivedData.data_num >= 17)
        {
            // �o�C�g�z��̐擪16�o�C�g��FQuat�ɃR�s�[
            FMemory::Memcpy(&DeviceRotation, receivedData.data, sizeof(float) * 4);

            // 17�o�C�g�ڂ��{�^����ԂƂ��ĉ���
            bIsActionButtonPressed = (receivedData.data[16] == 1);
        }
    }
}