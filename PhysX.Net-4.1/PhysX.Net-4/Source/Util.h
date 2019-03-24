#pragma once

#include "EnumUtil.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::ComponentModel;

namespace PhysX
{
	private enum class PrimitiveTypeSize
	{
		Bit16 = 1,
		Bit32 = 2
	};

	private ref class Util
	{
		internal:
			/// <summary>A very specific method to copy an unmanaged struct containing floats to a managed version.</summary>
			generic<typename T> where T : value class
			static T CloneFloatStruct(int numOfFloats, void* p_unmanaged);

			// TODO: Rename to 'To...Array'
			generic<typename T> where T : value class
			static array<T>^ AsManagedArray(const void* memory, int count);
			generic<typename T> where T : value class
			static array<T>^ AsManagedArray(void* memory, int count);

			generic<typename T> where T : value class
			static void AsUnmanagedArray(array<T>^ arr, void* dest);
			generic<typename T> where T : value class
			static void AsUnmanagedArray(array<T>^ arr, void* dest, int requiredCount);

			static String^ ToManagedString(const char* string);
			static char* ToUnmanagedString(String^ string);

			generic<typename T> where T : value class
			static PrimitiveTypeSize Is16Or32Bit();
			static PrimitiveTypeSize Is16Or32Bit(Type^ type);
			static Nullable<bool> Is16Or32Bit(Array^ values);

			// Returns an unmanaged stream clone of the data. The caller is responsible for freeing the allocated memory.
			static PxDefaultMemoryInputData* StreamToUnmanagedInputStream(System::IO::Stream^ stream);
			//static System::IO::MemoryStream^ UnmanagedMemoryStreamToStream(MemoryStream& memoryStream);
			static void CopyIntoStream(PxDefaultMemoryOutputStream* from, System::IO::Stream^ to);

			generic<typename T> where T : value class
			static array<T>^ CopyToValueTypeArray(array<Byte>^ bytes);
	};
};