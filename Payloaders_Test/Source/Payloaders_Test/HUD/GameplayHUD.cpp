// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameplayHUD.h"
#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"
#include "TextureResource.h"
#include "CanvasItem.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Payloaders_Test/Characters/PlayerCharacter.h"
#include "Payloaders_Test/HUD/GameOverUserWidget.h"
#include "Payloaders_Test/HUD/PlayerUserWidget.h"
#include "UObject/ConstructorHelpers.h"

AGameplayHUD::AGameplayHUD()
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshairTexObj(TEXT("/Game/FirstPerson/Textures/FirstPersonCrosshair"));
	CrosshairTex = CrosshairTexObj.Object;
}


void AGameplayHUD::DrawHUD()
{
	Super::DrawHUD();
	
	const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);
	
	const FVector2D CrosshairDrawPosition( (Center.X),
										   (Center.Y + 20.0f));

	FCanvasTileItem TileItem( CrosshairDrawPosition, CrosshairTex->Resource, FLinearColor::White);
	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem( TileItem );
}

void AGameplayHUD::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	
	if(auto* GameplayGameMode = Cast<AGameplayGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		if(GameplayGameMode->PlayerCharacter)
		{
			GameplayGameMode->PlayerCharacter->OnDeathCharacter.AddDynamic(this, &AGameplayHUD::ActivateGameOverViewport);
		}
	}

	UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController);
	PlayerController->SetShowMouseCursor(false);
}

void AGameplayHUD::ActivateGameOverViewport(ABaseCharacter* Character)
{
	if(!bGameOverInViewport)
	{
		if(GameOverUserWidget)
		{
			if(PlayerUserWidget)
			{
				PlayerUserWidget->RemoveFromParent();
				PlayerUserWidget->RemoveFromViewport();
			}
			GameOverUserWidget->AddToViewport();
			bGameOverInViewport = true;

			UGameplayStatics::SetGamePaused(GetWorld(),true);
			UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(PlayerController, GameOverUserWidget, EMouseLockMode::DoNotLock,false);
			PlayerController->SetShowMouseCursor(true);
		}
	}
}
