#pragma once

using namespace System::IO;
using namespace System::Runtime::CompilerServices;

namespace PhysX
{
	[ExtensionAttribute]
	public ref class StreamExtensions abstract sealed
	{
		internal:
			generic<typename T> where T : value class
			static void CopyData(UnmanagedMemoryStream^ stream, int offsetInBytes, int strideSize, array<T>^ data, int startIndex, int elementCount, bool isSetting);

		public:
			/// <summary>Gets all the data from the begining of the stream (Position 0)</summary>
			generic<typename T> where T : value class
			[ExtensionAttribute]
			static array<T>^ GetData(UnmanagedMemoryStream^ stream);
			/// <summary>Gets all the data from the begining of the stream (Position 0)</summary>
			/// <param name="data">An array of structs to copy the data into</param>
			generic<typename T> where T : value class
			[ExtensionAttribute]
			static void GetData(UnmanagedMemoryStream^ stream, array<T>^ data);
			/// <summary>Gets all the data from the begining of the stream (Position 0)</summary>
			/// <param name="data">An array of structs to copy the data into</param>
			/// <param name="startIndex">The index in the data array to begin copying in the data</param>
			/// <param name="elementCount">The maximum number of elements (T) to copy in to the array</param>
			generic<typename T> where T : value class
			[ExtensionAttribute]
			static void GetData(UnmanagedMemoryStream^ stream, array<T>^ data, int startIndex, int elementCount);
			/// <summary>Gets all the data from the begining of the stream (Position 0)</summary>
			/// <param name="offsetInBytes">An offset in bytes from the begining source data</param>
			/// <param name="strideSize">The size (in bytes) of between each element in the source data (used for interleaved storage)</param>
			/// <param name="startIndex">The index in the data array to begin copying in the data</param>
			/// <param name="elementCount">The maximum number of elements (T) to copy in to the array</param>
			generic<typename T> where T : value class
			[ExtensionAttribute]
			static void GetData(UnmanagedMemoryStream^ stream, int offsetInBytes, int strideSize, array<T>^ data, int startIndex, int elementCount);

			generic<typename T> where T: value class
			[ExtensionAttribute]
			static void SetData(UnmanagedMemoryStream^ stream, array<T>^ data);
			generic<typename T> where T: value class
			[ExtensionAttribute]
			static void SetData(UnmanagedMemoryStream^ stream, array<T>^ data, int startIndex, int elementCount);
			generic<typename T> where T: value class
			[ExtensionAttribute]
			static void SetData(UnmanagedMemoryStream^ stream, int offsetInBytes, int strideSize, array<T>^ data, int startIndex, int elementCount);

			/// <summary>Reads the next element (T) from the stream and advances the stream Position by the size of T</summary>
			generic<typename T> where T : value class
			[ExtensionAttribute]
			static T Read(UnmanagedMemoryStream^ stream);
			/// <summary>Writes a data element to the stream and advances the stream Position by the size of T</summary>
			/// <param name="data">The element to write to the stream</param>
			generic<typename T> where T : value class
			[ExtensionAttribute]
			static void Write(UnmanagedMemoryStream^ stream, T data);
	};
};