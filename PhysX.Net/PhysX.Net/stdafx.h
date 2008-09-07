// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#pragma warning( disable : 4635 4800 4793 )

#if GRAPHICS_MDX
	#using <C:\Windows\Microsoft.NET\DirectX for Managed Code\1.0.2902.0\Microsoft.DirectX.dll>
	#using <C:\Windows\Microsoft.NET\DirectX for Managed Code\1.0.2902.0\Microsoft.DirectX.Direct3D.dll>
	#using <C:\Windows\Microsoft.NET\DirectX for Managed Code\1.0.2905.0\Microsoft.DirectX.Direct3DX.dll>
#elif GRAPHICS_XNA2
	#using <C:\Program Files\Microsoft XNA\XNA Game Studio\v2.0\References\Windows\x86\Microsoft.Xna.Framework.dll>
#elif GRAPHICS_XNA3
	#using <C:\Program Files\Microsoft XNA\XNA Game Studio\v3.0\References\Windows\x86\Microsoft.Xna.Framework.dll>
#elif GRAPHICS_SLIMDX
#using <F:\NetAssemblies\SlimDX.dll>
#else
	#error No Graphics Target Specified
#endif

#if GRAPHICS_MDX
#define UsingFrameworkNamespace using namespace Microsoft::DirectX;
#define UsingGraphicsNamespace using namespace Microsoft::DirectX::Direct3D;
#elif GRAPHICS_XNA2
#define UsingFrameworkNamespace using namespace Microsoft::Xna::Framework;
#define UsingGraphicsNamespace using namespace Microsoft::Xna::Framework::Graphics;
#elif GRAPHICS_XNA3
#define UsingFrameworkNamespace using namespace Microsoft::Xna::Framework;
#define UsingGraphicsNamespace using namespace Microsoft::Xna::Framework::Graphics;
#elif GRAPHICS_SLIMDX
#define UsingFrameworkNamespace using namespace SlimDX;
#define UsingGraphicsNamespace using namespace SlimDX::Direct3D9;
#endif

// Modify the following defines if you have to target a platform prior to the ones specified below.
// Refer to MSDN for the latest info on corresponding values for different platforms.
#ifndef WINVER				// Allow use of features specific to Windows XP or later.
#define WINVER 0x0501		// Change this to the appropriate value to target other versions of Windows.
#endif

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows XP or later.                   
#define _WIN32_WINNT 0x0501	// Change this to the appropriate value to target other versions of Windows.
#endif						

#ifndef _WIN32_WINDOWS		// Allow use of features specific to Windows 98 or later.
#define _WIN32_WINDOWS 0x0410 // Change this to the appropriate value to target Windows Me or later.
#endif

#ifndef _WIN32_IE			// Allow use of features specific to IE 6.0 or later.
#define _WIN32_IE 0x0600	// Change this to the appropriate value to target other versions of IE.
#endif

#define null NULL
#define SAFE_DELETE(p)	{ if( (p) != NULL){ (p) = NULL; delete (p); } }
#define SAFE_FREE_MANY( void_ptrs )\
{\
	int count = sizeof( void_ptrs ) / sizeof( void* );\
	for( int x = 0; x < count; x++ )\
	{\
		if( void_ptrs[ x ] != NULL )\
			free( (void*)void_ptrs[ x ] );\
	}\
}\

template < class T, class U > 
bool IsInstanceOf( U u )
{
	return dynamic_cast<T>(u) != nullptr;
}

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#define NOMINMAX
#include <windows.h>

#include <iostream>
#include <stdlib.h>

#include <vcclr.h>

//#define NX_USE_FLUID_API
//#define NX_USE_CLOTH_API
//#define NX_USE_SOFTBODY_API
#include <NxPhysics.h>
#include <NxCharacter.h>
#include <NxCooking.h>
#include <Controller.h>
#include <ControllerManager.h>
#include <NxBoxController.h>
#include <NxCapsuleController.h>
#include <NxStream.h>


#include "Functions.h"
#include "Math.h"
#include "Object Cache.h"

#define _CRT_SECURE_NO_DEPRECATE

using namespace System;
using namespace System::IO;
using namespace System::Diagnostics;

using namespace StillDesign;

#define StdPhysicsStreamAlloc( localStreamVar, localMem, localStrideVar )\
{\
	StdPhysicsStreamAlloc2( localStreamVar, localMem, localStrideVar, void* );\
}
#define StdPhysicsStreamAlloc2( localStreamVar, localMem, localStrideVar, memType )\
{\
	if( localStreamVar != nullptr )\
		throw gcnew InvalidOperationException( "Buffer already allocated" );\
	\
	if( size <= 0 || strideSize <= 0 )\
		throw gcnew ArgumentException( "Size and Stride Size Must be Greater than Zero" );\
	\
	void* m = malloc( size );\
	Debug::Assert( m != NULL );\
	localMem = (memType)m;\
	\
	if( localMem == NULL )\
		throw gcnew OutOfMemoryException( "Could not allocate buffer" );\
	\
	SecureZeroMemory( m, size );\
	\
	localStreamVar = gcnew PhysicsStream( (BYTE*)localMem, size );\
	\
	localStrideVar = strideSize;\
	\
	return localStreamVar;\
}

#define ThrowIfNull( var, varName )\
{\
	if( var == nullptr )\
		throw gcnew ArgumentNullException( varName );\
}
#define ThrowIfNullOrDisposed( var, varName )\
{\
	if( var == nullptr )\
		throw gcnew ArgumentNullException( varName );\
	if( var->IsDisposed == true )\
		throw gcnew ArgumentException( "Argument is disposed", varName );\
}
#define ThrowIfDisposed( var, varName )\
{\
	if( var != nullptr && var->IsDisposed == true )\
		throw gcnew ArgumentException( "Argument is disposed", varName );\
}
#define ThrowIfDescriptionIsNullOrInvalid( var, varName )\
{\
	ThrowIfNull( var, varName );\
	\
	if( var->IsValid() == false )\
		throw gcnew ArgumentException( "Description is invalid", varName );\
}

#define ToManagedString( unmanagedString ) StillDesign::PhysX::Functions::UnmanagedToManagedString( unmanagedString )
#define ToUnmanagedString( managedString ) StillDesign::PhysX::Functions::ManagedToUnmanagedString( managedString )