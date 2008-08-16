#pragma once

#include "IDisposable.h"

using namespace System;
using namespace System::IO;

namespace StillDesign
{
	namespace PhysX
	{
		public ref class PhysicsStream : System::IO::UnmanagedMemoryStream, StillDesign::PhysX::IDisposable
		{
			public:
				virtual event EventHandler^ onDisposing;
				virtual event EventHandler^ onDisposed;
			
			public:
				PhysicsStream( int byteSize );
				PhysicsStream( BYTE* data, int length );
				~PhysicsStream();
			protected:
				!PhysicsStream();
			public:
				property bool IsDisposed
				{
					virtual bool get();
				}
			
			internal:
				generic<typename T> where T : ValueType void CopyData( int offsetInBytes, int strideSize, array<T>^ data, int startIndex, int elementCount, bool isSetting );
			
			public:
				generic<typename T> where T : ValueType array<T>^ GetData();
				generic<typename T> where T : ValueType void GetData( array<T>^ data );
				generic<typename T> where T : ValueType void GetData( array<T>^ data, int startIndex, int elementCount );
				generic<typename T> where T : ValueType void GetData( int offsetInBytes, int strideSize, array<T>^ data, int startIndex, int elementCount );
				
				generic<typename T> where T: ValueType void SetData( array<T>^ data );
				generic<typename T> where T: ValueType void SetData( array<T>^ data, int startIndex, int elementCount );
				generic<typename T> where T: ValueType void SetData( int offsetInBytes, int strideSize, array<T>^ data, int startIndex, int elementCount );
				
				generic<typename T> where T : ValueType T Read();
				generic<typename T> where T : ValueType void Write( T data );
		};
	};
};