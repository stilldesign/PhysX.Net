#include "StdAfx.h"
#include "StreamExtensions.h"

generic<typename T> where T : value class
void StreamExtensions::CopyData(UnmanagedMemoryStream^ stream, int offsetInBytes, int strideSize, array<T>^ data, int startIndex, int elementCount, bool isSetting)
{
	if (data == nullptr)
		throw gcnew ArgumentNullException("data");
	if (stream == nullptr)
		throw gcnew ArgumentNullException("stream");

	if (data->Length == 0 || elementCount == 0 || startIndex == data->Length)
		return;

	if (!stream->CanRead)
		throw gcnew InvalidOperationException("Cannot read from stream. The CanRead property must be set to true.");
	if (strideSize <= 0)
		throw gcnew ArgumentException("Stride size must be greater than 0", "strideSize");
	if (sizeof(T) == 0)
		throw gcnew ArgumentException("Generic type argument T cannot be of size 0", "T");
	if (startIndex < 0)
		throw gcnew ArgumentException("Start index must be greater than 0", "startIndex");
	if (elementCount < 0)
		throw gcnew ArgumentException("Element count must be greater than 0", "elementCount");
	if ((startIndex + elementCount) > data->Length)
		throw gcnew InvalidOperationException("Request elements exceeds the size of the data array");
	if (offsetInBytes < 0 || offsetInBytes > stream->Length)
		throw gcnew ArgumentException("The offset must be greater than or equal to 0 and less than or equal to the length of the stream", "offsetInBytes");

	int bufferSizeToCopy = (int)stream->Length - offsetInBytes;

	if (bufferSizeToCopy < 0)
		throw gcnew InvalidOperationException("The requested buffer size to copy cannot be less than 0");
	if (!PhysX::MathUtil::IsMultipleOf(bufferSizeToCopy, strideSize))
		throw gcnew InvalidOperationException("Stride size must be a multiple of the size of the data array");

	//

	if (elementCount > data->Length)
		throw gcnew InvalidOperationException("Requested element count exceeds the array data size");
	if (offsetInBytes >= stream->Length)
		throw gcnew InvalidOperationException("Offset is at or passed the end of the stream");

	int dataSize = sizeof(T) * data->Length;

	int originalPosition = (int)stream->Position;
	stream->Position = 0;

	try
	{
		for (int x = 0; x < elementCount; x++)
		{
			pin_ptr<T> item = &data[startIndex + x];

			if ((isSetting))
			{
				memcpy_s(stream->PositionPointer + offsetInBytes + (strideSize *x), (int)stream->Length - offsetInBytes, item, sizeof(T));
			}
			else
			{
				memcpy_s(item, sizeof(T), stream->PositionPointer + offsetInBytes + (strideSize * x), sizeof(T));
			}
		}
	}
	catch(Exception^ ex)
	{
		throw gcnew Exception("Failed to copy data", ex);
	}
}

generic<typename T>
array<T>^ StreamExtensions::GetData(UnmanagedMemoryStream^ stream)
{
	array<T>^ data = gcnew array<T>((int)stream->Length / sizeof(T));

	GetData(stream, data);

	return data;
}
generic<typename T>
void StreamExtensions::GetData(UnmanagedMemoryStream^ stream, array<T>^ data)
{
	if (data == nullptr)
		throw gcnew ArgumentNullException("data");

	GetData(stream, data, 0, data->Length);
}
generic<typename T>
void StreamExtensions::GetData(UnmanagedMemoryStream^ stream, array<T>^ data, int startIndex, int elementCount)
{
	GetData(stream, 0, sizeof(T), data, startIndex, elementCount);
}
generic<typename T>
void StreamExtensions::GetData(UnmanagedMemoryStream^ stream, int offsetInBytes, int strideSize, array<T>^ data, int startIndex, int elementCount)
{
	CopyData(stream, offsetInBytes, strideSize, data, startIndex, elementCount, false);
}

generic<typename T>
void StreamExtensions::SetData(UnmanagedMemoryStream^ stream, array<T>^ data)
{
	if (data == nullptr)
		throw gcnew ArgumentNullException("data", "Cannot be null");

	SetData(stream, data, 0, data->Length);
}
generic<typename T>
void StreamExtensions::SetData(UnmanagedMemoryStream^ stream, array<T>^ data, int startIndex, int elementCount)
{
	SetData(stream, 0, sizeof(T), data, startIndex, elementCount);
}
generic<typename T>
void StreamExtensions::SetData(UnmanagedMemoryStream^ stream, int offsetInBytes, int strideSize, array<T>^ data, int startIndex, int elementCount)
{
	CopyData(stream, offsetInBytes, strideSize, data, startIndex, elementCount, true);
}

generic<typename T>
T StreamExtensions::Read(UnmanagedMemoryStream^ stream)
{
	array<T>^ data = gcnew array<T>(1);

	GetData(stream, (int)stream->Position, sizeof(T), data, 0, 1);

	stream->Position += sizeof(T);

	return data[0];
}
generic<typename T>
void StreamExtensions::Write(UnmanagedMemoryStream^ stream, T data)
{
	array<T>^ dataArray = gcnew array<T>(1);
	dataArray[0] = data;

	SetData(stream, (int)stream->Position, sizeof(T), dataArray, 0, 1);

	stream->Position += sizeof(T);
}