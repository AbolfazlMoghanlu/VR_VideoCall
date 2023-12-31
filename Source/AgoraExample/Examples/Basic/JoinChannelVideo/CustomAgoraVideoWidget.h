// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "../../BaseAgoraUserWidget.h"
#include "AgoraPluginInterface.h"

#if PLATFORM_ANDROID
#include "AndroidPermission/Classes/AndroidPermissionFunctionLibrary.h"
#endif

// UI
#include "Components/CanvasPanel.h"
#include "Components/ComboBoxString.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/EditableText.h"

//UI Utility
#include "../../../Utility/BFL_VideoViewManager.h"
#include "../../../Utility/BFL_Logger.h"

#include "CustomAgoraVideoWidget.generated.h"

using namespace agora::rtc;
using namespace agora;

/**
 * 
 */
UCLASS(Abstract)
class AGORAEXAMPLE_API UCustomAgoraVideoWidget : public UBaseAgoraUserWidget
{
	GENERATED_BODY()

public:

#pragma region Event Handler

	class FUserRtcEventHandler : public agora::rtc::IRtcEngineEventHandler
	{
	public:

		FUserRtcEventHandler(UCustomAgoraVideoWidget* InVideoWidget) : WidgetPtr(InVideoWidget) {};

#pragma region AgoraCallback - IRtcEngineEventHandler

		void onJoinChannelSuccess(const char* channel, agora::rtc::uid_t uid, int elapsed);

		void onLeaveChannel(const agora::rtc::RtcStats& stats) override;

		void onUserJoined(agora::rtc::uid_t uid, int elapsed) override;

		void onUserOffline(agora::rtc::uid_t uid, agora::rtc::USER_OFFLINE_REASON_TYPE reason) override;

		void onVideoSizeChanged(VIDEO_SOURCE_TYPE sourceType, uid_t uid, int width, int height, int rotation) override;

		void onLocalVideoStateChanged(VIDEO_SOURCE_TYPE source, LOCAL_VIDEO_STREAM_STATE state, LOCAL_VIDEO_STREAM_ERROR error) override;

		void onRemoteVideoStateChanged(uid_t uid, REMOTE_VIDEO_STATE state, REMOTE_VIDEO_STATE_REASON reason, int elapsed) override;

#pragma endregion

		inline bool IsWidgetValid() { return WidgetPtr.IsValid(); }

	private:

		TWeakObjectPtr<UCustomAgoraVideoWidget> WidgetPtr;

	};
#pragma endregion

public:
	UFUNCTION(BlueprintCallable)
	void OnBtnJoinChannelClicked();

	UFUNCTION(BlueprintCallable)
	void OnBtnLeaveChannelClicked();

	UFUNCTION(BlueprintCallable)
	void InitAgoraWidget(FString APP_ID, FString TOKEN, FString CHANNEL_NAME) override;



#pragma region UI Utility - Log Msg View
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* CallView = nullptr;



protected:

	int MakeVideoView(uint32 uid, agora::rtc::VIDEO_SOURCE_TYPE sourceType = VIDEO_SOURCE_CAMERA_PRIMARY, FString channelId = "");
	int ReleaseVideoView(uint32 uid, agora::rtc::VIDEO_SOURCE_TYPE sourceType = VIDEO_SOURCE_CAMERA_PRIMARY, FString channelId = "");
#pragma endregion


public:
	inline FString GetAppId() { return AppId; };
	inline FString GetToken() { return Token; };
	inline FString GetChannelName() { return ChannelName; };
	
	UFUNCTION(BLueprintCallable)
	void EnableAudio(bool Enable);

	UFUNCTION(BLueprintCallable)
	void EnableVideo(bool Enable);

	UFUNCTION(BlueprintImplementableEvent)
	void LocalVideoStoped();

	UFUNCTION(BlueprintImplementableEvent)
	void LocalVideoStarted();

	UFUNCTION(BlueprintImplementableEvent)
	void RemoteVideoStoped();

	UFUNCTION(BlueprintImplementableEvent)
	void RemoteVideoStarted();

	UFUNCTION(BlueprintImplementableEvent)
	void OnRemoteJoined();

	UFUNCTION(BlueprintImplementableEvent)
	void OnRemoteLeave();

	UFUNCTION(BLueprintCallable)
	void RenewToken(FString NewToken);

	UFUNCTION(BLueprintCallable)
	void ChangeVideoConfig(int32 ResX, int32 ResY, int BitRate);

protected:

	IRtcEngine* RtcEngineProxy;

	FString AppId;
	FString Token;
	FString ChannelName;

	void CheckPermission();

	UFUNCTION(BlueprintCallable)
	void InitAgoraEngine(FString APP_ID, FString TOKEN, FString CHANNEL_NAME);
	UFUNCTION(BlueprintCallable)
	void UnInitAgoraEngine();
	void NativeDestruct() override;


	TSharedPtr<FUserRtcEventHandler> UserRtcEventHandler;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bMobileUser;
};