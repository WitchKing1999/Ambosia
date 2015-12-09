// (C) Flumminard 2015

using UnrealBuildTool;
using System.Collections.Generic;

public class AmbosiaEditorTarget : TargetRules
{
	public AmbosiaEditorTarget(TargetInfo Target)
	{
		Type = TargetType.Editor;
	}

	//
	// TargetRules interface.
	//

	public override void SetupBinaries(
		TargetInfo Target,
		ref List<UEBuildBinaryConfiguration> OutBuildBinaryConfigurations,
		ref List<string> OutExtraModuleNames
		)
	{
		OutExtraModuleNames.AddRange( new string[] { "Ambosia" } );
	}
}
