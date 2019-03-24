#pragma once

#include "Serializable.h"

namespace PhysX
{
	public interface class ISerializable
	{
		Serializable^ AsSerializable();
	};
};