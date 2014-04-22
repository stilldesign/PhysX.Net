PhysX.Net Readme
---------------------------------------------------------------------------------------------------------------------------

Add the following files as references to your project
	StillDesign.PhysX.Net.dll

Copy the following PhysX 2.8.4 runtime files into your application path:
	NxCharacter.dll
	PhysXCooking.dll
	PhysXCore.dll
	PhysXDevice.dll
	PhysXLoader.dll

	These are usually in -
		x86: C:\Program Files (x86)\NVIDIA Corporation\NVIDIA PhysX SDK\v2.8.4_win\Bin\win32
		x64: C:\Program Files (x86)\NVIDIA Corporation\NVIDIA PhysX SDK\v2.8.4_win\Bin\win64
Create a new StillDesign.PhysX.Core instance in your code.

Most of the class and function names are the same as in the official PhysX documentation, minus the 'Nx' prefix

Bugs or issues:
Use the forums at http://www.github.com/stilldesign/physx.net

Differences between PhysX.Net and the official PhysX Lib:
	The empty constructors for Bounds3 and NxBounds3 create different results.
	Bounds3 is a ValueType (struct) so calling the empty constructor can only leave the Min and Max properties
	as ( 0, 0, 0 ) where as in 
	NxBounds3 they are effectively set to Min=(MaxFloat, MaxFloat, MaxFloat) and Max=(MinFloat, MinFloat, MinFloat).
	Use Bounds3 mybounds = Bounds3.Extremes; instead.
	
	Change in the naming, NxPhysicsSDK is called Core.