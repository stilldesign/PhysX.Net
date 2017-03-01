#pragma once

namespace PhysX
{
	public ref class InputData abstract
	{
	protected:
		InputData();

	public:
		virtual void Seek(int offset) abstract;

		property int Length
		{
			virtual int get() abstract;
		}

		property int Offset
		{
			virtual int get() abstract;
		}
	};
};