$projRoot = Get-Location


$skipPhysX = Read-Host -Prompt 'Skip PhysX Gen? (y/n)'
if ($skipPhysX -ne 'y') {
    
    $fullPath = Join-Path -Path $projRoot -ChildPath "\PhysX"
    if ($env:NVIDIAPhysX41SDK -ne $fullPath) {
        Write-Output "Please run the Set-NvidiaEnv.ps1 script first.
        You may have to restart your powershell session."
    }

    Write-Output "Generating PhysX..."
    git submodule update --init --recursive
    Set-Location .\PhysX\physx
    .\generate_projects.bat vc16win64

    Set-Location .\compiler\vc16win64\sdk_source_bin

    .\PhysX.sln
    Write-Output "Set all PhysX projects RuntimeLibrary to MultiThreadedDLL (/MDd), compile those projects and press Enter"
    Read-Host -Prompt 'Press Enter to continue'
}

Set-Location $projRoot\PhysX.Net

.\PhysX.Net.sln
Read-Host -Prompt 'Now compile PhysX.Net.sln then press Enter'

.\.nuget\NuGet.exe pack .\PhysX.Net.nuspec

Write-Output "You can use the following nupkg to ref this to your project"
Read-Host -Prompt 'Press Enter to continue'