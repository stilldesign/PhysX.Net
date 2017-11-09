PhysX.Net
=========

Nuget
-----
PM> Install-Package PhysX.Net -Prerelease

Build all the things!
--------------
A zip of all relevant DLLs and samples - http://stilldesign.co.nz/PhysX

Development
-----------
### PhysX.Net 0.7.2 for NVIDIA PhysX 3.4.0
* Targets PhysX 3.4.0
* 64 bit version only
* Dependencies
	* .NET 4.6.2
	* CRT 2017 - https://go.microsoft.com/fwlink/?LinkId=746572
* Remaining:
    * Vehicle sample and a few related classes
    * Attach/Detach shape from an actor (recently added, but needs testing)
    * Getting started guide for people
    * Serialization
    * Broad Phase
    * Deletion Listener

# Building
## Dependencies
* Visual Studio 2017
* VC++ 2015.3 v140 toolset for desktop (x86,x64) - needed to build PhysX itself. If you've built PhysX already, this could be ignored.

## Compiling
### Compile PhysX
* Clone the [PhysX repo](https://github.com/NVIDIAGameWorks/PhysX-3.4.git)
* Open the solution and select the **debug** configuration
* You'll need to change all the projects to use **Multi-threaded Debug DLL** in order for them to be consumed by .NET
  * Select all the projects in the solution explorer, right click, properties, C/C++, Code Generation and change **Runtime Library** to **Multi-threaded Debug DLL (/MDd)**
### Compile PhysX.Net
* Clone this repo
* The default location of the PhysX 3.4 repo directory is *F:\PhysX-3.4\PhysX_3.4*
  * To specify an alternative location on your computer: define the environment variable **NVIDIAPhysX34SDK**. You can do this by running ```setx NVIDIAPhysX34SDK "C:\PhysX-3.4\PhysX_3.4" /M``` (as administrator).
