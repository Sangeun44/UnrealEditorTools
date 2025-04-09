// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetActionUtility.h"

#include "Materials/Material.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Particles/ParticleSystem.h"	
#include "Sound/SoundCue.h"
#include "Sound/SoundWave.h"
#include "Engine/Texture.h"
#include "Blueprint/UserWidget.h"
#include "Components/SkeletalMeshComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraEmitter.h"	
#include "EditorUtilityBlueprint.h"

#include "QuickAssetAction.generated.h"

/**
 *
 */
UCLASS()
class SUPERMANAGER_API UQuickAssetAction : public UAssetActionUtility
{
	GENERATED_BODY()

public:
    /**
     * Duplicates selected assets a specified number of times.
     * @param NumOfDuplicates - Number of duplicates to create for each selected asset.
     */
	UFUNCTION(CallInEditor)
	void DuplicateAssets(int32 NumOfDuplicates);

    /**
     * Adds predefined prefixes to the names of selected assets based on their class.
     * Skips assets that already have the prefix or if no prefix is found for the class.
     */
	UFUNCTION(CallInEditor)
	void AddPrefixes();

    /**
     * Identifies and processes unused assets from the selected ones.
     * An asset is considered unused if it has no references.
     */
    UFUNCTION(CallInEditor)
    void RemoveUnusedAssets();

private:
    TMap<UClass*, FString>PrefixMap =
    {
        {UBlueprint::StaticClass(),TEXT("BP_")},
        {UEditorUtilityBlueprint::StaticClass(),TEXT("EUBP_")},
        {UStaticMesh::StaticClass(),TEXT("SM_")},
        {UMaterial::StaticClass(), TEXT("M_")},
        {UMaterialInstanceConstant::StaticClass(),TEXT("MI_")},
        {UMaterialFunctionInterface::StaticClass(), TEXT("MF_")},
        {UParticleSystem::StaticClass(), TEXT("PS_")},
        {USoundCue::StaticClass(), TEXT("SC_")},
        {USoundWave::StaticClass(), TEXT("SW_")},
        {UTexture::StaticClass(), TEXT("T_")},
        {UTexture2D::StaticClass(), TEXT("T_")},
        {UUserWidget::StaticClass(), TEXT("WBP_")},
        {USkeletalMeshComponent::StaticClass(), TEXT("SK_")},
        {UNiagaraSystem::StaticClass(), TEXT("NS_")},
        {UNiagaraEmitter::StaticClass(), TEXT("NE_")}
    };
};