/*
Copyright (c) 2009 PhysX.Net

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#pragma once

#pragma warning( disable : 4635 4800 4793 )

#define NoGraphicsTargetSpecified #error No Graphics Target Specified

// If you are using a 64 bit version of Windows; change the paths below to "Program Files (x86)" or symlink the PhysX SDK dir into "Program Files"

#if GRAPHICS_XNA31
	#using <C:\Program Files\Microsoft XNA\XNA Game Studio\v3.1\References\Windows\x86\Microsoft.Xna.Framework.dll>
#elif GRAPHICS_SLIMDX
	#if WIN32
		#using <C:\Program Files\SlimDX SDK (March 2009)\Bin\x86\SlimDX.dll>
	#elif WIN64
		#using <C:\Program Files\SlimDX SDK (March 2009)\Bin\x64\SlimDX.dll>
	#endif
#else
	NoGraphicsTargetSpecified
#endif

#if GRAPHICS_XNA31
	#define UsingFrameworkNamespace using namespace Microsoft::Xna::Framework;
	#define UsingGraphicsNamespace using namespace Microsoft::Xna::Framework::Graphics;
#elif GRAPHICS_SLIMDX
	#define UsingFrameworkNamespace using namespace SlimDX;
	#define UsingGraphicsNamespace using namespace SlimDX::Direct3D9;
#else
	NoGraphicsTargetSpecified
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
#define _WIN32_WINDOWS 0x0501 // Windows XP
#endif

#define SAFE_DELETE(p)	{ if( (p) != NULL){ (p) = NULL; delete (p); } }
#define SAFE_FREE_MANY( void_ptrs )\
{\
	int count = sizeof( void_ptrs ) / sizeof( void* );\
	for( int x = 0; x < count; x++ )\
	{\
		if( void_ptrs[ x ] != NULL )\
			free( (void*)void_ptrs[ x ] );\
	}\
}

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
#include <NxCloth.h>
#include <NxFluid.h>
#include <NxActor.h>

#include "NXU_Helper.h"
#include "nxu_schema.h"

#include "Functions.h"
#include "Math.h"
#include "Object Table.h"
#include "PhysX Exception.h"
#include "List Base.h"
#include "Graphics Library Wrapper.h"

#define _CRT_SECURE_NO_DEPRECATE

using namespace System;
using namespace System::IO;
using namespace System::Diagnostics;

using namespace StillDesign;

#define StdPhysicsStreamAlloc( localStreamVar, localMem, localStrideVar )\
{\
	StdPhysicsStreamAllocEx( localStreamVar, localMem, localStrideVar, void* );\
}
#define StdPhysicsStreamAllocEx( localStreamVar, localMem, localStrideVar, memType )\
{\
	if( localStreamVar != nullptr )\
		throw gcnew InvalidOperationException( "Buffer already allocated" );\
	\
	if( size <= 0 || strideSize <= 0 )\
		throw gcnew ArgumentException( "Size and stride size must be greater than zero" );\
	\
	void* m = malloc( size );\
	Debug::Assert( m != NULL, String::Format( "Failed to allocate {0} bytes", size ) );\
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