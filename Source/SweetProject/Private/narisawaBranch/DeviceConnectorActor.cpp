#include "narisawaBranch/DeviceConnectorActor.h"
#include "Misc/MemoryRead.h"

ADeviceConnectorActor::ADeviceConnectorActor()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ADeviceConnectorActor::BeginPlay()
{
    Super::BeginPlay();
    // ゲーム開始時に自動でデバイスへの接続を試みる
    ConnectToDevice();
}

void ADeviceConnectorActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    // ゲーム終了時に接続を切断する
    DisconnectFromDevice();
    Super::EndPlay(EndPlayReason);
}

void ADeviceConnectorActor::ConnectToDevice()
{
    // デバイスID:0x01, デバイスバージョン:0x01 のデバイスを探す
    // このIDはデバイス側のプログラムと一致させる必要あり
    ASerialController = MakeUnique<ASerial_Controller>(0x01, 0x01);
    SerialInterface = MakeUnique<WindowsSerial>();
    ASerialController->SetInterfacePt(SerialInterface.Get());

    // 利用可能なCOMポートを自動で探査して接続
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
    // 接続中であれば、毎フレームデータ受信処理を呼び出す
    if (ASerialController.IsValid() && ASerialController->GetConnectionState())
    {
        ReadAndProcessData();
    }
}

void ADeviceConnectorActor::ReadAndProcessData()
{
    static ASerialDataStruct::ASerialData receivedData;
    int status = ASerialController->ReadDataProcess(&receivedData);

    // パケットの受信が正常に完了した場合 (statusが1になる)
    if (status == 1)
    {
        // ここで受信データを解析し、ブループリント用の変数に格納

        if (receivedData.command == 0x20 && receivedData.data_num >= 17)
        {
            // バイト配列の先頭16バイトをFQuatにコピー
            FMemory::Memcpy(&DeviceRotation, receivedData.data, sizeof(float) * 4);

            // 17バイト目をボタン状態として解釈
            bIsActionButtonPressed = (receivedData.data[16] == 1);
        }
    }
}