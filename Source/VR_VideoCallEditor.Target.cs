// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class VR_VideoCallEditorTarget : TargetRules
{
	public VR_VideoCallEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "VR_VideoCall" } );
		
		if (Target.Platform == UnrealTargetPlatform.IOS || Target.Platform == UnrealTargetPlatform.Mac)
        {
            bOverrideBuildEnvironment = true;
            // -Wno-unused-but-set-variable£º fix error "variable 'layerNames' set but not used"
            //  -Wno-gcc-compat: gcc does not allow an atrribute in this position on a function declaration
            // -Wno-reorder-ctor: fix error "field 'eventHandler' will be initialized after field 'mccUid'"
            AdditionalCompilerArguments = "-Wno-unused-but-set-variable -Wno-gcc-compat -Wno-reorder-ctor";
        }
	}
}
