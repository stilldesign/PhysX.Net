#pragma once

namespace StillDesign
{
	namespace PhysX
	{
		class UserMemoryReaderStream : public NxStream
		{
			private:
				const NxU8* _startBuffer;
				
			public:
				UserMemoryReaderStream( const NxU8* data );
				virtual ~UserMemoryReaderStream();
			
				virtual NxU8 readByte() const;
				virtual NxU16 readWord() const;
				virtual NxU32 readDword() const;
				virtual float readFloat() const;
				virtual double readDouble() const;
				virtual void readBuffer( void* buffer, NxU32 size ) const;
				
				virtual		NxStream&		storeByte(NxU8 b)							{ NX_ASSERT(0);	return *this;	}
				virtual		NxStream&		storeWord(NxU16 w)							{ NX_ASSERT(0);	return *this;	}
				virtual		NxStream&		storeDword(NxU32 d)							{ NX_ASSERT(0);	return *this;	}
				virtual		NxStream&		storeFloat(NxReal f)						{ NX_ASSERT(0);	return *this;	}
				virtual		NxStream&		storeDouble(NxF64 f)						{ NX_ASSERT(0);	return *this;	}
				virtual		NxStream&		storeBuffer(const void* buffer, NxU32 size)	{ NX_ASSERT(0);	return *this;	}
				
				mutable const NxU8* buffer;
				
				const NxU8* GetStartBuffer();
				void Reset();
		};
	};
};