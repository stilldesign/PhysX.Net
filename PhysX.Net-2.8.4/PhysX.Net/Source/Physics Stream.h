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
				virtual event EventHandler^ OnDisposing;
				virtual event EventHandler^ OnDisposed;
			
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
				/// <summary>Gets all the data from the begining of the stream (Position 0)</summary>
				generic<typename T> where T : ValueType array<T>^ GetData();
				/// <summary>Gets all the data from the begining of the stream (Position 0)</summary>
				/// <param name="data">An array of structs to copy the data into</param>
				generic<typename T> where T : ValueType void GetData( array<T>^ data );
				/// <summary>Gets all the data from the begining of the stream (Position 0)</summary>
				/// <param name="data">An array of structs to copy the data into</param>
				/// <param name="startIndex">The index in the data array to begin copying in the data</param>
				/// <param name="elementCount">The maximum number of elements (T) to copy in to the array</param>
				generic<typename T> where T : ValueType void GetData( array<T>^ data, int startIndex, int elementCount );
				/// <summary>Gets all the data from the begining of the stream (Position 0)</summary>
				/// <param name="offsetInBytes">An offset in bytes from the begining source data</param>
				/// <param name="strideSize">The size (in bytes) of between each element in the source data (used for interleaved storage)</param>
				/// <param name="startIndex">The index in the data array to begin copying in the data</param>
				/// <param name="elementCount">The maximum number of elements (T) to copy in to the array</param>
				generic<typename T> where T : ValueType void GetData( int offsetInBytes, int strideSize, array<T>^ data, int startIndex, int elementCount );
				
				generic<typename T> where T: ValueType void SetData( array<T>^ data );
				generic<typename T> where T: ValueType void SetData( array<T>^ data, int startIndex, int elementCount );
				generic<typename T> where T: ValueType void SetData( int offsetInBytes, int strideSize, array<T>^ data, int startIndex, int elementCount );
				
				/// <summary>Reads the next element (T) from the stream and advances the stream Position by the size of T</summary>
				generic<typename T> where T : ValueType T Read();
				/// <summary>Writes a data element to the stream and advances the stream Position by the size of T</summary>
				/// <param name="data">The element to write to the stream</param>
				generic<typename T> where T : ValueType void Write( T data );
		};
	};
};