#pragma once

#include "SerializableEnum.h"

namespace PhysX
{
	public ref class Serializable
	{
	private:
		PxBase* _serializable;

	internal:
		Serializable(PxBase* serializable);
	public:
		~Serializable();
	protected:
		!Serializable();

	public:
		property String^ ConcreteTypeName
		{
			String^ get();
		}

		property PhysX::ConcreteType ConcreteType
		{
			PhysX::ConcreteType get();
		}
	};
};