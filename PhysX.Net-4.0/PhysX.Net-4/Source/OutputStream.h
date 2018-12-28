#pragma once

namespace PhysX
{
	public ref class OutputStream abstract
	{
	protected:
		OutputStream();

	public:
		/// <summary>
		/// Write to the stream. The number of bytes written may be less than the number sent.
		/// </summary>
		/// <returns>
		/// The number of bytes written to the stream by this call.
		/// </returns>
		virtual int Write(array<Byte>^ buffer) abstract;
	};
};