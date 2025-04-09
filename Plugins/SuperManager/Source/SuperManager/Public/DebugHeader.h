#pragma once

#include "Misc/MessageDialog.h"
#include "Widgets/Notifications/SNotificationList.h"
#include "Framework/Notifications/NotificationManager.h"

// This file contains utility functions for debugging and displaying messages in Unreal Engine.
// It includes functions to print messages to the screen, log messages, show message dialogs,
// and display notifications. The functions are designed to be used in the Unreal Engine editor environment.
// The functions utilize Unreal Engine's built-in logging and notification systems to provide
// feedback to the user during development and debugging.

void Print(const FString& Message, const FColor& Color)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 8.f, Color, Message);
	}
}

void PrintLog(const FString& Message)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Message);
}

EAppReturnType::Type ShowMsgDialog(EAppMsgType::Type MsgType, const FString& Message,
	bool bShowMsgAsWarning = true)
{
	if (bShowMsgAsWarning)
	{
		FText MsgTitle = FText::FromString(TEXT("Warning"));

		return FMessageDialog::Open(MsgType, FText::FromString(Message), &MsgTitle);
	}
	else
	{
		return FMessageDialog::Open(MsgType, FText::FromString(Message));
	}
}

void ShowNotifyInfo(const FString& Message)
{
	FNotificationInfo NotifyInfo(FText::FromString(Message));
	NotifyInfo.bUseLargeFont = true;
	NotifyInfo.FadeOutDuration = 7.f;

	FSlateNotificationManager::Get().AddNotification(NotifyInfo);
}