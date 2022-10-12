$projRoot = Get-Location
git submodule update --init --recursive

cd .\PhysX\physx
.\generate_projects.bat vc16win64

cd .\compiler\vc16win64\sdk_source_bin

.\PhysX.sln
echo "Set all PhysX projects RuntimeLibrary to MultiThreadedDLL (/MDd), compile those projects and press Enter"
Pause

$fullPath = Join-Path -Path $projRoot -ChildPath "\PhysX"
setx NVIDIAPhysX41SDK $fullPath /M

cd $projRoot\PhysX.Net

refreshenv

.\PhysX.Net.sln
echo "Now compile PhysX.Net.sln then press Enter"
Pause
.\.nuget\NuGet.exe pack .\PhysX.Net.nuspec

echo "You can use the following nupkg to ref this to your project"