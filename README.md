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
* Progress:
    * ~75% done
    * I'll be creating a vehicle sample as well
    * New for 3.3 is that Cloth can interact with scene geometry once again (like it did in v2 of PhysX)
    * I'll package up and change the main download to the 3.3.1 package, no point keeping v2 around much longer
    * There's plenty of breaking API changes from 3.2 to 3.3, so look forward to lots of build errors :P Nothing seems to of been removed from the API, just moved around and renamed.

### PhysX.Net 0.12 for NVIDIA PhysX 2.8.4.5
* Targets PhysX 2.8.4.5
    * 2.8.4.x doesn't require system software to run anymore! yay! (CPU mode only though :P)
* 32 bit and 64 bit versions
* Remove the dependencies on graphics libraries
    * Although it's convenient, a physics library shouldn't rely on specific graphics libraries. Consumers (e.g. graphics engines) should provide their own thin wrappers around types such as Vector3 and Matrix
* .NET 4.0 and CRT 10 (2010)
