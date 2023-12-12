using UnrealBuildTool;

public class CustomAssetEditor : ModuleRules
{
    public CustomAssetEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core", "UnrealEd",
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore", 
                "CustomAsset",
                "AssetTools",
                "UnrealEd", "AdvancedPreviewScene", "EditorStyle","RenderCore"
            }
        );
    }
}