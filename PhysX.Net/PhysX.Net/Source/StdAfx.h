#pragma once

/*
Copyright (c) 2011 PhysX.Net

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

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <vcclr.h>
#include <memory.h>
#include <assert.h>
#include <vector>

#include <PxPhysicsAPI.h>
// TODO: I think this include is missing from either the main PxPhysicsAPI.h or PxExtensionsAPI.h
// It wasn't in beta2, perhaps they just missed it. To the forums, posthaste!
#include <extensions\PxCollectionExt.h>


// Native PhysX namespaces
using namespace physx;

// .NET namespaces
using namespace System;
using namespace System::Collections::Generic;
using namespace System::Linq;
using namespace System::Diagnostics;
using namespace System::Runtime::InteropServices;

#pragma warning(disable:4691) // System.Numerics.Vectors relys on the new (and currently pre release) System.Runtime
using namespace System::Numerics;

#define Matrix Matrix4x4

#include "IPhysXEntity.h"
#include "OperationFailedException.h"
#include "Util.h"
#include "Transform.h"
#include "MathUtil.h"
#include "ObjectTable.h"

// Our namespaces
using namespace PhysX;

// Enum conversion
#define ToManagedEnum(managedType, e) ((managedType)(PxU32)e)
#define ToUnmanagedEnum(unmanagedType, e) ((unmanagedType::Enum)(PxU32)e)
#define ToUnmanagedEnum2(unmanagedType, e) ((unmanagedType)(PxU32)e)

#define SAFE_DELETE(p) { if((p) != NULL){ delete (p); (p) = NULL; } }
#define SAFE_FREE(p) { if((p) != NULL){ free(p); (p) = NULL; } }

#define GetPointerOrNull(obj) (obj == nullptr ? NULL : obj->UnmanagedPointer)

#define MV(v) (MathUtil::PxVec3ToVector3(v))
#define UV(v) (MathUtil::Vector3ToPxVec3(v))
#define MM(m) (MathUtil::PxTransformToMatrix(m))
#define UM(m) (MathUtil::MatrixToPxTransform(m))

#define ThrowIfNull(var, varName)\
{\
	if (var == nullptr)\
	throw gcnew ArgumentNullException(varName);\
}
#define ThrowIfNullOrDisposed(var, varName)\
{\
	if (var == nullptr)\
	throw gcnew ArgumentNullException(varName);\
	if (var->Disposed)\
	throw gcnew ArgumentException("Argument is disposed", varName);\
}
#define ThrowIfDisposed(var, varName)\
{\
	if (var != nullptr && var->IsDisposed)\
	throw gcnew ArgumentException("Argument is disposed", varName);\
}
#define ThrowIfDescriptionIsNullOrInvalid(var, varName)\
{\
	ThrowIfNull(var, varName);\
	\
	if(!var->IsValid())\
	throw gcnew ArgumentException("Description is invalid", varName);\
}
#define ThrowIfThisDisposed() { if (this->Disposed) throw gcnew InvalidOperationException("The instance has been disposed of, no further operations should be performed."); }

template <class T, class U>
bool IsInstanceOf(U u)
{
	return dynamic_cast<T>(u) != nullptr;
}