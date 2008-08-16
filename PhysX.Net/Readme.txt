PhysX.Net Readme:
Add the following files as references to your project.
	'bin\<API>\StillDesign.PhysX.Net.dll'
	'bin\<API>\StillDesign.CommonLibrary.dll'
Copy the following PhysX 2.7.3 runtime files into your application path (these are in the SDK\2.7.3\bin\win32 directory of the SDK)
	PhysXLoader.dll
	NxCharacter.dll
	NxCooking.dll
	NxExtensions.dll
Create a new StillDesign.PhysX.Core instance.

Most of the class and function names are the same as in the offical PhysX documentation minus the 'Nx' prefix
The Common Library contains a bunch of useful math and collection classes/functions.

Any Bugs or issues:
Use the forums at www.stilldesign.co.nz/forum

General Notes:
Differences between PhysX.Net and the offical PhysX Lib.

The empty constructors for Bounds3 and NxBounds3 create different results.
Bounds3 is a ValueType (struct) so calling the empty constructor can only leave the Min and Max properties as ( 0, 0, 0 ) where as in 
NxBounds3 they are effectively set to Min=(MaxFloat, MaxFloat, MaxFloat ) and Max=(MinFloat, MinFloat, MinFloat).
Use Bounds3 mybounds = Bounds3.Extremes; instead.
So watch out for this.
Reported by christophe loustaunau

Just a change in the nameing, NxPhysicsSDK is called Core.

Calling SetToDefault on Descriptors that have had memory allocated (e.g. AllocateVertices) will not release that memory, first call Dispose().

Instead of extents for boxes I used size, e.g. BoxShape.Size. Size == Extents / 2