#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "ASerial_Controller.h"
#include "WindowsSerial.h"
#include "DeviceConnectorActor.generated.h"

// �O���錾
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
    // �ʐM�������s���N���X�̃C���X�^���X��ێ�����|�C���^
    TUniquePtr<WindowsSerial> SerialInterface;
    TUniquePtr<ASerial_Controller> ASerialController;

    // �f�[�^��M�Ə������s�������֐�
    void ReadAndProcessData();

public:
    // �u���[�v�����g����ڑ���Ԃ��m�F���邽�߂̕ϐ�
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ASerial|Status")
    FString ConnectionStatus;

    // �ȉ��A�u���[�v�����g�Ɍ��J����f�[�^�p�̕ϐ�
    // (��) �f�o�C�X�̉�]�i�N�H�[�^�j�I���j
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ASerial|Data")
    FQuat DeviceRotation;

    // (��) �f�o�C�X�̉����x
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ASerial|Data")
    FVector DeviceAcceleration;

    // (��) �{�^���̏��
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ASerial|Data")
    bool bIsActionButtonPressed;

    // --- �ȉ��A�u���[�v�����g����Ăяo���֐� ---
    UFUNCTION(BlueprintCallable, Category = "ASerial|Connection")
    void ConnectToDevice();

    UFUNCTION(BlueprintCallable, Category = "ASerial|Connection")
    void DisconnectFromDevice();
};