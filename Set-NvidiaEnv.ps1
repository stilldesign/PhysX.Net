$projRoot = Get-Location

if ($skipEnv -ne 'y') {
    $fullPath = Join-Path -Path $projRoot -ChildPath "\PhysX"
    Write-Output "NvidiaPath is $fullPath"
    setx NVIDIAPhysX41SDK $fullPath /M
}

refreshenv