// Fill out your copyright notice in the Description page of Project Settings.


#include "QuickAssetAction.h"
#include "DebugHeader.h"
#include "EditorUtilityLibrary.h"
#include "EditorAssetLibrary.h"


void UQuickAssetAction::DuplicateAssets(int32 NumOfDuplicates)
{
	// Duplicates selected assets a specified number of times.
	// Displays a message if the input is invalid or shows a notification upon successful duplication.
	if (NumOfDuplicates <= 0)
	{
		ShowMsgDialog(EAppMsgType::Ok, TEXT("Please enter a VALID number"));
		return;
	}

	TArray<FAssetData> SelectedAssetsData = UEditorUtilityLibrary::GetSelectedAssetData();
	uint32 Counter = 0;

	// Check if any assets are selected
	for (const FAssetData& SelectedAssetData : SelectedAssetsData)
	{
		for (int32 i = 0; i < NumOfDuplicates; i++)
		{
			// Get the source asset path and create a new name for the duplicated asset
			const FString SourceAssetPath = SelectedAssetData.ObjectPath.ToString();
			const FString NewDuplicatedAssetName = SelectedAssetData.AssetName.ToString() + TEXT("_") + FString::FromInt(i + 1);
			const FString NewPathName = FPaths::Combine(SelectedAssetData.PackagePath.ToString(), NewDuplicatedAssetName);

			// Duplicate Asset with new path that contains new name
			if (UEditorAssetLibrary::DuplicateAsset(SourceAssetPath, NewPathName))
			{
				UEditorAssetLibrary::SaveAsset(NewPathName, false);
				++Counter;
			}
		}
	}

	if (Counter > 0)
	{
		ShowNotifyInfo(TEXT("Successfully duplicated " + FString::FromInt(Counter) + " files"));
	}
}

void UQuickAssetAction::AddPrefixes()
{
	// Adds predefined prefixes to the names of selected assets based on their class.
	// Skips assets that already have the prefix or if no prefix is found for the class.

	TArray<UObject*>SelectedObjects = UEditorUtilityLibrary::GetSelectedAssets();
	uint32 Counter = 0;

	for (UObject* SelectedObject : SelectedObjects)
	{
		if (!SelectedObject) continue;
		FString* PrefixFound = PrefixMap.Find(SelectedObject->GetClass());

		if (!PrefixFound || PrefixFound->IsEmpty())
		{
			Print(TEXT("Failed to find prefix for class ") + SelectedObject->GetClass()->GetName(), FColor::Red);
			continue;
		}

		// Get the old name from object
		FString OldName = SelectedObject->GetName();
		
		// Check if the prefix already exists
		if (OldName.StartsWith(*PrefixFound))
		{
			Print(OldName + TEXT(" already has prefix added"), FColor::Red);
			continue;
		} 
		
		// Remove the prefix and suffix if it exists for MaterialInstanceConstant
		if (SelectedObject->IsA<UMaterialInstanceConstant>())
		{
			OldName.RemoveFromStart(TEXT("M_"));
			OldName.RemoveFromEnd(TEXT("_inst"));
		}

		const FString NewNameWithPrefix = *PrefixFound + OldName;
		UEditorUtilityLibrary::RenameAsset(SelectedObject, NewNameWithPrefix);
		++Counter;
	}

	if (Counter > 0)
	{
		ShowNotifyInfo(TEXT("Successfully renamed " + FString::FromInt(Counter) + " assets"));
	}
}

void UQuickAssetAction::RemoveUnusedAssets()
{	
	// Identifies and processes unused assets from the selected ones.
	// An asset is considered unused if it has no references.

	TArray<FAssetData> SelectedAssetsData = UEditorUtilityLibrary::GetSelectedAssetData();
	TArray<FAssetData> UnusedAssetsData;

	// Check if any assets are selected, by using package referencers
	for (const FAssetData& SelectedAssetData : SelectedAssetsData)
	{
		TArray<FString> AssetReferencers = UEditorAssetLibrary::FindPackageReferencersForAsset(SelectedAssetData.ObjectPath.ToString());
		if (AssetReferencers.Num() == 0)
		{
			UnusedAssetsData.Add(SelectedAssetData);
		}
	}

	// If no unused assets are found, show a message dialog
	if (UnusedAssetsData.Num() == 0)
	{
		ShowMsgDialog(EAppMsgType::Ok, TEXT("No unused asset found among selected assets"), false);
		return;
	}
}