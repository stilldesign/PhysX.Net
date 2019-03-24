#pragma once

namespace PhysX
{
	public ref class DefaultMemoryOutputStream
	{
	private:
		PxDefaultMemoryOutputStream* _defaultMemoryOutputStream;

	public:
		DefaultMemoryOutputStream();
		DefaultMemoryOutputStream(array<Byte>^ buffer);
		~DefaultMemoryOutputStream();
	protected:
		!DefaultMemoryOutputStream();
		
	public:
		/// <summary>
		/// Writes the contents of the buffer argument into the stream.
		/// </summary>
		virtual int Write(array<Byte>^ buffer);

		/// <summary>
		/// Returns a copy of the buffer.
		/// </summary>
		array<Byte>^ GetData();

		/// <summary>
		/// Gets the number of bytes in the buffer.
		/// </summary>
		property int Size
		{
			int get();
		}
	};
};