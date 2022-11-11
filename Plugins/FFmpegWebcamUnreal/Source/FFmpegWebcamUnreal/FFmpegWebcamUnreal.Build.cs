// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class FFmpegWebcamUnreal : ModuleRules
{
	private string ModulePath { get { return ModuleDirectory; } }
	private string ThirdPartyPath { get { return Path.GetFullPath(Path.Combine(ModulePath,"../../ThirdParty/")); } }
	
	public bool LoadffmpegLib(ReadOnlyTargetRules Target)
	{
		bool isLibararySupported = false;
		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			isLibararySupported = true;
			PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "ffmpeg", "include"));
            PrivateIncludePaths.Add(Path.Combine(ThirdPartyPath, "ffmpeg", "include"));
            
			string LibraryPath = Path.Combine(ThirdPartyPath, "ffmpeg", "lib");

			string[] libs =
			{
				"avcodec.lib", "avdevice.lib", "avfilter.lib", "avformat.lib", "avutil.lib",
				"swresample.lib", "swscale.lib"
			};

			foreach (string lib in libs)
			{
				PublicAdditionalLibraries.Add(Path.Combine(LibraryPath, lib));
			}

			string[] dlls =
			{
				"avcodec-59.dll", "avdevice-59.dll", "avfilter-8.dll", "avformat-59.dll", "avutil-57.dll",
				"swresample-4.dll", "swscale-6.dll"
			};

			foreach (string dll in dlls)
			{
				PublicDelayLoadDLLs.Add(dll);
				RuntimeDependencies.Add(Path.Combine(LibraryPath, dll), StagedFileType.NonUFS);
			}
		}

		return isLibararySupported;
	}
	
	public FFmpegWebcamUnreal(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
			
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);	
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		LoadffmpegLib(Target);
	}
}
