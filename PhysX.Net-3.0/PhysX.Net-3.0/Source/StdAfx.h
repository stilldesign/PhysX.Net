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

#include <PxTransform.h>
#include <PxVec2.h>
#include <PxVec3.h>
#include <PxVec4.h>
#include <PxQuat.h>
#include <PxMat33.h>

// .NET namespaces
using namespace System;
using namespace System::Collections::Generic;
using namespace System::Linq;
using namespace System::Diagnostics;
using namespace System::Runtime::InteropServices;

#include "Util.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Quaternion.h"
#include "Matrix.h"
#include "MathUtil.h"
#include "ObjectTable.h"

// Our namespaces
using namespace PhysX;
using namespace PhysX::Math;

// Native PhysX namespaces
using namespace physx;
using namespace physx::pubfnd3; // Math/Primitive types namespace

// Enum conversion
#define ToManagedEnum(managedType, e) ((managedType)(PxU32)e)
#define ToUnmanagedEnum(unmanagedType, e) ((unmanagedType::Enum)(PxU32)e)
#define ToUnmanagedEnum2(unmanagedType, e) ((unmanagedType)(PxU32)e)

#define SAFE_DELETE(p) { if((p) != NULL){ delete (p); (p) = NULL; } }
#define SAFE_FREE(p) { if((p) != NULL){ free(p); (p) = NULL; } }

#define GetPointerOrNull(obj) (obj == nullptr ? NULL : obj->UnmanagedPointer)

#define ThrowIfNull( var, varName )\
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

template <class T, class U>
bool IsInstanceOf(U u)
{
	return dynamic_cast<T>(u) != nullptr;
}