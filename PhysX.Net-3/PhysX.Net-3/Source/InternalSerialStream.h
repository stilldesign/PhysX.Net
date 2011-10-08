#pragma once

#include <PxStream.h> 

class InternalSerialStream : public PxSerialStream
{
	private:
		InternalMemoryStream* _memoryStream;

	public:
		InternalSerialStream();
		~InternalSerialStream();

		virtual void storeBuffer(const void *buffer, PxU32 size);
		virtual PxU32 getTotalStoredSize();

		InternalMemoryStream* GetMemoryStream();
};