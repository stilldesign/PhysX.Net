PhysX.Net
=========
A .NET wrapper for NVIDIA PhysX 4.1.2 written using C++/CLI.

Nuget
-----
PM> Install-Package PhysX.Net -Prerelease

Build all the things!
--------------
A zip of all relevant DLLs and samples - https://github.com/stilldesign/PhysX.Net/releases

# Usage
## Runtime files
You must have `PhysX_64.dll`, `PhysXCommon_64.dll`, `PhysXCooking_64.dll`, `PhysXFoundation_64.dll` and `Ijwhost.dll` in the same directory as your executable.

There is a helper `.targets` file which will add links of these to the root of your project. Each file has `Copy to Output Directory` set.

In your `.csproj` file:
1. Set the `GeneratePathProperty="true"` attribute on the PhysX.Net `<PackageReference />` node.
    * e.g. `<PackageReference Include="PhysX.Net" Version="4.0.0-alpha1" GeneratePathProperty="true" />`
2. Add the follow to your `.csproj` file:
```xml
<ImportGroup>
    <Import Project="$(PkgPhysX_Net)\lib\RuntimeFiles.targets"/>
</ImportGroup>
```

Development
-----------
### PhysX.Net 4.0.0-alpha1 for NVIDIA PhysX 4.1.2
* Targets PhysX 4.1.2
* 64 bit version only
* Dependencies
	* .NET 6
	* C runtime 2022 - https://aka.ms/vs/17/release/vc_redist.x64.exe
* Remaining:
    * Vehicle sample and a few related classes
    * Attach/Detach shape from an actor
    * Getting started guide for people
    * Serialization
    * Broad Phase
    * Deletion Listener

# Building
## Dependencies
* Visual Studio 2022
* VC++ v143 toolset for desktop - needed to build PhysX itself. If you've built PhysX already, this could be ignored.

## Compiling
### Compile PhysX
* Clone the [PhysX repo](https://github.com/NVIDIAGameWorks/PhysX)
* Run ```generate_projects.bat``` from the ```physx``` directory
* Open the solution and select the **debug** configuration
* You'll need to change all the PhysX projects to use **Multi-threaded Debug DLL** in order for them to be consumed by .NET
  * Select the projects in the solution explorer, right click, properties, C/C++, Code Generation and change **Runtime Library** to **Multi-threaded Debug DLL (/MDd)**
### Compile PhysX.Net
* Clone this repo
* The default location of the PhysX 4.1.2 repo directory is *C:\NVIDIAGameWorks\PhysX*
  * To specify an alternative location on your computer: define the environment variable **NVIDIAPhysX411SDK**. You can do this by running ```setx NVIDIAPhysX411SDK "C:\NVIDIAGameWorks\PhysX" /M``` (as *administrator*).
