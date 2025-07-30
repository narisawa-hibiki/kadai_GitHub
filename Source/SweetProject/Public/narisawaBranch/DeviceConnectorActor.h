#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "ASerial_Controller.h"
#include "WindowsSerial.h"
#include "DeviceConnectorActor.generated.h"

// 前方宣言
class ASerial_Controller;
class WindowsSerial;

UCLASS()
class YOURPROJECTNAME_API ADeviceConnectorActor : public AActor
{
    GENERATED_BODY()

public:
    ADeviceConnectorActor();

protected:
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
    virtual void Tick(float DeltaTime) override;

private:
    // 通信処理を行うクラスのインスタンスを保持するポインタ
    TUniquePtr<WindowsSerial> SerialInterface;
    TUniquePtr<ASerial_Controller> ASerialController;

    // データ受信と処理を行う内部関数
    void ReadAndProcessData();

public:
    // ブループリントから接続状態を確認するための変数
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ASerial|Status")
    FString ConnectionStatus;

    // 以下、ブループリントに公開するデータ用の変数
    // (例) デバイスの回転（クォータニオン）
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ASerial|Data")
    FQuat DeviceRotation;

    // (例) デバイスの加速度
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ASerial|Data")
    FVector DeviceAcceleration;

    // (例) ボタンの状態
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ASerial|Data")
    bool bIsActionButtonPressed;

    // --- 以下、ブループリントから呼び出す関数 ---
    UFUNCTION(BlueprintCallable, Category = "ASerial|Connection")
    void ConnectToDevice();

    UFUNCTION(BlueprintCallable, Category = "ASerial|Connection")
    void DisconnectFromDevice();
};