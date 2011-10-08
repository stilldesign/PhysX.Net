#pragma once

#include <PxStream.h>

class MemoryStream : public physx::PxStream
{
	private:
		const PxU8* _memory;
		mutable const PxU8* _seek;
		size_t _capacity;

	public:
		MemoryStream();
		MemoryStream(const PxU8* memory, int size);
		MemoryStream(long byteSize);
		virtual ~MemoryStream();

		virtual PxU8 readByte() const;
		virtual PxU16 readWord() const;
		virtual PxU32 readDword() const;
		virtual PxF32 readFloat() const;
		virtual PxF64 readDouble() const;
		virtual void readBuffer(void* buffer, PxU32 size) const;
		    
		virtual PxStream& storeByte(PxU8 b);
		virtual PxStream& storeWord(PxU16 w);
		virtual PxStream& storeDword(PxU32 d);
		virtual PxStream& storeFloat(PxF32 f);
		virtual PxStream& storeDouble(PxF64 f);
		virtual PxStream& storeBuffer(const void* buffer, PxU32 size);

		const PxU8* GetMemory()
		{
			return _memory;
		}
		size_t getMemorySize()
		{
			size_t size = _seek - _memory;
			assert(size >= 0);
			
			return size;
		}

		void ResetSeek()
		{
			_seek = _memory;
		}
};

typedef MemoryStream InternalMemoryStream;