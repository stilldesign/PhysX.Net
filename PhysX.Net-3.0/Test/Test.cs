using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace PhysX.Test
{
	// Copy out the dependant DLL files needed for each test run
#if x86
	[DeploymentItem(@"Assemblies\x86\PhysX3_x86.dll")]
	[DeploymentItem(@"Assemblies\x86\PhysX3Cooking_x86.dll")]
	[DeploymentItem(@"Assemblies\x86\PhysX3Gpu_x86.dll")]
#elif x64
	[DeploymentItem(@"Assemblies\x64\PhysX3_x64.dll")]
	[DeploymentItem(@"Assemblies\x64\PhysX3Cooking_x64.dll")]
	[DeploymentItem(@"Assemblies\x64\PhysX3Gpu_x64.dll")]
#endif
	[DeploymentItem(@"Assemblies\x86\PxTaskCuda.dll")]
	public abstract class Test
	{

	}
}