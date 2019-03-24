#pragma once

namespace PhysX
{
	public ref class InputStream abstract
	{
	protected:
		InputStream();

	public:
		/// <summary>
		/// Read from the stream. The number of bytes written may be less than the number requested
		/// </summary>
		/// <returns>
		/// The number of bytes read from the stream.
		/// </returns>
		virtual int Read(array<Byte>^ buffer, int count) abstract;
	};
};