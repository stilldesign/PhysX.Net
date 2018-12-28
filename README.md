PhysX.Net
=========

Nuget
-----
PM> Install-Package PhysX.Net-4 -Prerelease

Build all the things!
--------------
A zip of all relevant DLLs and samples - http://stilldesign.co.nz/PhysX

Development
-----------
### PhysX.Net 0.1.0-alpha for NVIDIA PhysX 4.0.0
* Targets PhysX 4.0.0
* 64 bit version only
* Dependencies
	* .NET 4.7.1
	* C runtime 2017 - https://aka.ms/vs/15/release/vc_redist.x64.exe
* Remaining:
    * Vehicle sample and a few related classes
    * Attach/Detach shape from an actor
    * Getting started guide for people
    * Serialization
    * Broad Phase
    * Deletion Listener

# Building
## Dependencies
* Visual Studio 2017
* VC++ 2015.4 v140 toolset for desktop (x86,x64) - needed to build PhysX itself. If you've built PhysX already, this could be ignored.

## Compiling
### Compile PhysX
* Clone the [PhysX repo](https://github.com/NVIDIAGameWorks/PhysX)
* Run ```generate_projects.bat``` from the ```physx``` directory
* Open the solution and select the **debug** configuration
* You'll need to change all the PhysX projects to use **Multi-threaded Debug DLL** in order for them to be consumed by .NET
  * Select the projects in the solution explorer, right click, properties, C/C++, Code Generation and change **Runtime Library** to **Multi-threaded Debug DLL (/MDd)**
### Compile PhysX.Net
* Clone this repo
* The default location of the PhysX 4.0 repo directory is *C:\NVIDIAGameWorks\PhysX-4.0*
  * To specify an alternative location on your computer: define the environment variable **NVIDIAPhysX40SDK**. You can do this by running ```setx NVIDIAPhysX40SDK "C:\NVIDIAGameWorks\PhysX-4.0" /M``` (as *administrator*).
