using System;
using System.IO;
using UnrealBuildTool;

public class EpineSDK : ModuleRules
{
    public EpineSDK(ReadOnlyTargetRules Target) : base(Target)
    {
        Type = ModuleType.External;

        // Add the import library
        PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "libepine-sdk.a"));
        PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "lib", "sio", "libsioclient.a"));
        // Delay-load the DLL, so we can load it from the right place first
        PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "libepine-sdk.a"));
        PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "lib", "sio", "libsioclient.a"));
        // Ensure that the DLL is staged along with the executable
        RuntimeDependencies.Add("$(PluginDir)/Binaries/ThirdParty/EpineSDK/Mac/libepine-sdk.a");
        RuntimeDependencies.Add("$(PluginDir)/Binaries/ThirdParty/EpineSDK/Mac/libsioclient.a");
    }
}
