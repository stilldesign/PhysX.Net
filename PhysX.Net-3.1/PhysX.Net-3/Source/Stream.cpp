#include "StdAfx.h"
#include "Stream.h"

Stream::Stream()
	: UnmanagedMemoryStream()
{
	
}
Stream::Stream(int byteSize)
	: UnmanagedMemoryStream((BYTE*)malloc(byteSize), byteSize, byteSize, System::IO::FileAccess::ReadWrite)
{

}
Stream::Stream(BYTE* data, int length)
	: UnmanagedMemoryStream(data, length, length, System::IO::FileAccess::ReadWrite)
{

}
Stream::~Stream()
{
	this->!Stream();
}
Stream::!Stream()
{
	OnDisposing(this, nullptr);

	OnDisposed(this, nullptr);
}

bool Stream::Disposed::get()
{
	return (this->PositionPointer == NULL);
}

//

generic<typename T> where T : value class
void Stream::CopyData(int offsetInBytes, int strideSize, array<T>^ data, int startIndex, int elementCount, bool isSetting)
{
	if (data == nullptr)
		throw gcnew ArgumentNullException("data");

	if (data->Length == 0 || elementCount == 0 || startIndex == data->Length)
		return;

	if (this->CanRead == false)
		throw gcnew InvalidOperationException("Cannot read from stream. The CanRead property must be set to true");
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
	if (offsetInBytes < 0 || offsetInBytes > this->Length)
		throw gcnew ArgumentException("The offset must be greater than or equal to 0 and less than or equal to the length of the stream", "offsetInBytes");

	int bufferSizeToCopy = (int)this->Length - offsetInBytes;

	if (bufferSizeToCopy < 0)
		throw gcnew InvalidOperationException("The requested buffer size to copy cannot be less than 0");
	if (PhysX::MathUtil::IsMultipleOf(bufferSizeToCopy, strideSize) == false)
		throw gcnew InvalidOperationException("Stride size must be a multiple of the size of the data array");

	//

	if (elementCount > data->Length)
		throw gcnew InvalidOperationException("Requested element count exceeds the array data size");
	if (offsetInBytes >= this->Length)
		throw gcnew InvalidOperationException("Offset is at or passed the end of the stream");

	int dataSize = sizeof(T) * data->Length;

	int originalPosition = (int)this->Position;
	this->Position = 0;

	try
	{
		for (int x = 0; x < elementCount; x++)
		{
			pin_ptr<T> item = &data[ startIndex + x ];

			if ((isSetting))
			{
				memcpy_s(this->PositionPointer + offsetInBytes + (strideSize *x), (int)this->Length - offsetInBytes, item, sizeof(T));
			}
			else
			{
				memcpy_s(item, sizeof(T), this->PositionPointer + offsetInBytes + (strideSize * x), sizeof(T));
			}
		}
	}
	catch(...)
	{
		throw gcnew Exception("Failed to copy data");
	}

	this->Position = originalPosition;
}

generic<typename T> where T : value class
	array<T>^ Stream::GetData()
{
	array<T>^ data = gcnew array<T>((int)this->Length / sizeof(T));

	GetData(data);

	return data;
}
generic<typename T> where T : value class
void Stream::GetData(array<T>^ data)
{
	if (data == nullptr)
		throw gcnew ArgumentNullException("data");

	GetData(data, 0, data->Length);
}
generic<typename T> where T : value class
void Stream::GetData(array<T>^ data, int startIndex, int elementCount)
{
	GetData(0, sizeof(T), data, startIndex, elementCount);
}
generic<typename T> where T : value class
void Stream::GetData(int offsetInBytes, int strideSize, array<T>^ data, int startIndex, int elementCount)
{
	CopyData(offsetInBytes, strideSize, data, startIndex, elementCount, false);
}

generic<typename T> where T : value class
void Stream::SetData(array<T>^ data)
{
	if (data == nullptr)
		throw gcnew ArgumentNullException("data", "Cannot be null");

	SetData(data, 0, data->Length);
}
generic<typename T> where T : value class
void Stream::SetData(array<T>^ data, int startIndex, int elementCount)
{
	SetData(0, sizeof(T), data, startIndex, elementCount);
}
generic<typename T> where T : value class
void Stream::SetData(int offsetInBytes, int strideSize, array<T>^ data, int startIndex, int elementCount)
{
	CopyData(offsetInBytes, strideSize, data, startIndex, elementCount, true);
}

generic<typename T> where T : value class
T Stream::Read()
{
	array<T>^ data = gcnew array<T>(1);

	GetData((int)this->Position, sizeof(T), data, 0, 1);

	this->Position += sizeof(T);

	return data[0];
}
generic<typename T> where T : value class
void Stream::Write(T data)
{
	array<T>^ dataArray = gcnew array<T>(1);
	dataArray[0] = data;

	SetData((int)this->Position, sizeof(T), dataArray, 0, 1);

	this->Position += sizeof(T);
}