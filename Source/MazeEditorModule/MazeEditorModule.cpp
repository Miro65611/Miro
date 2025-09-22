// Copyright Epic Games, Inc. All Rights Reserved.


#include "MazeEditorModule.h"
#include "Modules/ModuleManager.h"
#include "Widget/SMIMazeWidget.h"

#include "LevelEditor.h"
#include "ToolMenus.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/SCompoundWidget.h"

#define LOCTEXT_NAMESPACE "FMazeEditorModule"

IMPLEMENT_MODULE(FMazeEditorModule, MazeEditorModule);

static const FName MazeEditorTabName(TEXT("MazeEditor"));

void FMazeEditorModule::StartupModule()
{
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(
		MazeEditorTabName, FOnSpawnTab::CreateRaw(this, &FMazeEditorModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("MazeEditorTabTitle", "Maze Editor"))
		.SetTooltipText(LOCTEXT("MazeEditorTooltip", "Open the Maze Editor window"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

	// 2. ToolMenus로 Window 메뉴 확장
	UToolMenus::RegisterStartupCallback(
		FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FMazeEditorModule::RegisterMenus));
}

void FMazeEditorModule::RegisterMenus()
{
	// "Window" 메인 메뉴 가져오기
	UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");

	// MazeTools Section 추가 
	FToolMenuSection& Section = Menu->AddSection("MazeTools", LOCTEXT("MazeToolsSection", "Maze Tools"));

	// 메뉴 항목 추가
	Section.AddMenuEntry(
		"OpenMazeEditor",
		LOCTEXT("OpenMazeEditor", "Maze Editor"),
		LOCTEXT("OpenMazeEditorTooltip", "Open the Maze Editor window"),
		FSlateIcon(),
		FUIAction(FExecuteAction::CreateLambda([]() {
			FGlobalTabmanager::Get()->TryInvokeTab(MazeEditorTabName);
			}))
	);
}


void FMazeEditorModule::ShutdownModule()
{
	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner("MazeEditor");
}

TSharedRef<SDockTab> FMazeEditorModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	// SCompoundWidget를 상속받은 커스텀 위젯을 탭의 콘텐츠로 설정합니다.
	TSharedRef<SWidget> TabContent = SNew(SMIMazeWidget);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			TabContent
		];

}
