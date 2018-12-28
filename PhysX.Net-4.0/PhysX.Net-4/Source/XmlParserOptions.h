#pragma once

#include "TolerancesScale.h"

namespace PhysX
{
	public value class XmlParserOptions
	{
	internal:
		static PxSerialization::PxXmlMiscParameter ToUnmanaged(XmlParserOptions managed);

	public:
		property Vector3 UpVector;
		property TolerancesScale Scale;
	};
}