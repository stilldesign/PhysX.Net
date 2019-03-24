#pragma once


namespace PhysX
{
	public ref class DefaultMemoryInputData abstract
	{
	private:
		PxDefaultMemoryInputData* _defaultMemoryInputData;

	protected:
		DefaultMemoryInputData(int size);

	public:
		virtual int Read(array<Byte>^ buffer, int count);

		virtual void Seek(int offset);

		property int Length
		{
			virtual int get();
		}

		property int Offset
		{
			virtual int get();
		}
	};
};