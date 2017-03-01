param($installPath, $toolsPath, $package, $project)

"Installing [{0}] to project [{1}]" -f $package.Id, $project.FullName | Write-Host

# The native PhysX DLLs (x64) are needed
# They are set to 'Copy if newer', so when the project is built, they will copied out to your bin\xyz directory
$nativePhysXDllsX64 = "nvToolsExt64_1.dll", 
	"PhysX3CharacterKinematicCHECKED_x64.dll", 
	"PhysX3CHECKED_x64.dll",
	"PhysX3CommonCHECKED_x64.dll",
	"PhysX3CookingCHECKED_x64.dll"
	#"PhysX3GpuCHECKED_x64.dll" GPU support isn't possible in VS2015, NVIDIA hasn't finised this off yet.

ForEach ($dll in $nativePhysXDllsX64)
{
	# Set 'Copy To Output Directory' to 'Copy if newer'
		# 0 = Do not copy
		# 1 = Copy always
		# 2 = Copy if newer

	$handle = $project.ProjectItems.Item($dll)

	$copyToOutput = $handle.Properties.Item("CopyToOutputDirectory")
	$copyToOutput.Value = 2
}

# Save the project
$project.Save()