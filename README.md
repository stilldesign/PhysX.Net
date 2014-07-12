PhysX.Net
=========

Nuget
-----
PM> Install-Package PhysX.Net-x64

Build all the things!
--------------
A zip of all relevant DLLs and samples - http://stilldesign.co.nz/PhysX

Development
-----------
### PhysX.Net 0.2.0 for NVIDIA PhysX 3.3.1
* Targets PhysX 3.3.1
* 32 and 64 bit version
* .NET 4.5.1 and CRT 12 (2013)
* Remaining:
    * Vehicle sample and a few related classes
    * Attach/Detach shape from an actor
    * Getting started guide for people
    * Serialization
    * Broad Phase
    * Deletion Listener

### PhysX.Net 0.12 for NVIDIA PhysX 2.8.4.5
* Targets PhysX 2.8.4.5
    * 2.8.4.x doesn't require system software to run anymore! yay! (CPU mode only though :P)
* 32 bit and 64 bit versions
* Remove the dependencies on graphics libraries
    * Although it's convenient, a physics library shouldn't rely on specific graphics libraries. Consumers (e.g. graphics engines) should provide their own thin wrappers around types such as Vector3 and Matrix
* .NET 4.0 and CRT 10 (2010)
