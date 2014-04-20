PhysX.Net Readme:
Add the following files as references to your project.
	'References\<Build Type>\<Graphics API>\StillDesign.PhysX.Net.dll'
Copy the following PhysX 2.8.1.21 runtime files into your application path (these are usually in 'C:\Program Files\NVIDIA Corporation\NVIDIA PhysX SDK\v2.8.1\Bin\win32')
	PhysXLoader.dll
	NxCharacter.dll
	NxCooking.dll
Create a new StillDesign.PhysX.Core instance.

Most of the class and function names are the same as in the offical PhysX documentation minus the 'Nx' prefix

Bugs or issues:
Use the forums at http://www.codeplex.com/physxdotnet

Differences between PhysX.Net and the offical PhysX Lib:
	The empty constructors for Bounds3 and NxBounds3 create different results.
	Bounds3 is a ValueType (struct) so calling the empty constructor can only leave the Min and Max properties as ( 0, 0, 0 ) where as in 
	NxBounds3 they are effectively set to Min=(MaxFloat, MaxFloat, MaxFloat) and Max=(MinFloat, MinFloat, MinFloat).
	Use Bounds3 mybounds = Bounds3.Extremes; instead.
	
	Change in the naming, NxPhysicsSDK is called Core.