param($installPath, $toolsPath, $package, $project)

"Installing [{0}] to project [{1}]" -f $package.Id, $project.FullName | Write-Host

# The native PhysX DLLs (x64) are needed
# They are set to 'Copy Always', so when the project is built, they will copied out to its bin\Debug|Release directory
$nativePhysXDllsX64 = "nvToolsExt64_1.dll", "PhysX3CharacterKinematicCHECKED_x64.dll", "PhysX3CHECKED_x64.dll", "PhysX3CommonCHECKED_x64.dll", "PhysX3CookingCHECKED_x64.dll", "PhysX3GpuCHECKED_x64.dll"

ForEach ($dll in $nativePhysXDllsX64)
{
	$handle = $project.ProjectItems.Item($dll)
	#set 'Copy To Output Directory' to 'Copy Always'
	$copyToOutput = $handle.Properties.Item("CopyToOutputDirectory")
	$copyToOutput.Value = 1
}

# Save the project
$project.Save()