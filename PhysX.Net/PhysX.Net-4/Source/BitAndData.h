#pragma once


namespace PhysX
{
	//template <typename storageType, storageType bitMask>
	//class PxBitAndDataT
	//{
	//public:
	//	PX_FORCE_INLINE	PxBitAndDataT()									{}
	//	PX_FORCE_INLINE	PxBitAndDataT(storageType data, bool bit=false)	{ mData = bit ? data | bitMask : data;	}

	//	PX_CUDA_CALLABLE PX_FORCE_INLINE	operator storageType()		const	{ return mData & ~bitMask;	}
	//	PX_CUDA_CALLABLE PX_FORCE_INLINE	void			setBit()			{ mData |= bitMask;			}
	//	PX_CUDA_CALLABLE PX_FORCE_INLINE	void			clearBit()			{ mData &= ~bitMask;		}
	//	PX_CUDA_CALLABLE PX_FORCE_INLINE	storageType		isBitSet()	const	{ return mData & bitMask;	}

	//protected:
	//	storageType					mData;
	//};
	//typedef PxBitAndDataT<unsigned char, 0x80>		PxBitAndByte;
	//typedef PxBitAndDataT<unsigned short, 0x8000>	PxBitAndWord;
	//typedef PxBitAndDataT<unsigned int, 0x80000000>	PxBitAndDword;

	public value class BitAndByte
	{
		private:
			Byte _data;

		public:
			BitAndByte(Byte data, bool bit);

			const static Byte BitMask = 0x80;

			Byte GetData() { return _data & ~BitMask; }
			void SetBit() { _data |= BitMask; }
			void ClearBit() { _data &= ~BitMask; }
			bool IsBitSet()	{ return _data & BitMask; }

		internal:
			static PxBitAndByte ToUnmanaged(BitAndByte b);
	};
};