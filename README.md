PhysX.Net
=========
A .NET wrapper for NVIDIA PhysX 4.1.1 written using C++/CLI.

Nuget
-----
PM> Install-Package PhysX.Net -Prerelease

Build all the things!
--------------
A zip of all relevant DLLs and samples - https://github.com/stilldesign/PhysX.Net/releases

Development
-----------
### PhysX.Net 2.0.0-alpha for NVIDIA PhysX 4.1.1
* Targets PhysX 4.1.1
* 64 bit version only
* Dependencies
	* .NET Core 3.1
	* C runtime 2019 - https://aka.ms/vs/16/release/VC_redist.x64.exe
* Remaining:
    * Vehicle sample and a few related classes
    * Attach/Detach shape from an actor
    * Getting started guide for people
    * Serialization
    * Broad Phase
    * Deletion Listener

# Building
## Dependencies
* Visual Studio 2019
* VC++ v142 toolset for desktop - needed to build PhysX itself. If you've built PhysX already, this could be ignored.

## Compiling
### Compile PhysX
* Clone the [PhysX repo](https://github.com/NVIDIAGameWorks/PhysX)
* Run ```generate_projects.bat``` from the ```physx``` directory
* Open the solution and select the **debug** configuration
* You'll need to change all the PhysX projects to use **Multi-threaded Debug DLL** in order for them to be consumed by .NET
  * Select the projects in the solution explorer, right click, properties, C/C++, Code Generation and change **Runtime Library** to **Multi-threaded Debug DLL (/MDd)**
### Compile PhysX.Net
* Clone this repo
* The default location of the PhysX 4.1.1 repo directory is *C:\NVIDIAGameWorks\PhysX*
  * To specify an alternative location on your computer: define the environment variable **NVIDIAPhysX411SDK**. You can do this by running ```setx NVIDIAPhysX411SDK "C:\NVIDIAGameWorks\PhysX" /M``` (as *administrator*).

# PhysX 3.4.2 vs 4.1.0
Change log: https://github.com/NVIDIAGameWorks/PhysX/blob/4.1/physx/release_notes.html

The main changes are:
* New solver for accuracy
* ```RigidActor.CreateShape``` is removed
  * Use ```RigidActorExt.CreateExclusiveShape``` instead (or create a simple C# extension method to provide backward compatibility)
* Particles have been removed
  * This is now provided by [FleX](https://github.com/NVIDIAGameWorks/FleX)
* Cloth has been removed
  * This is now provided by [NvCloth](https://github.com/NVIDIAGameWorks/NvCloth)
