#pragma once

#include <PxFields.h> 

namespace PhysX
{
	public enum class Field
	{
		Undefined = PxField::eUNDEFINED, 
		Byte = PxField::eBYTE, 
		Word = PxField::eWORD, 
		DWord = PxField::eDWORD, 
		Float = PxField::eFLOAT, 
		Vector3 = PxField::eVEC3, 
		String = PxField::eSTRING, 
		SerialPointer = PxField::eSERIAL_PTR, 
		SerialEmbedded = PxField::eSERIAL_EMBEDDED, 
		PhysXArray = PxField::ePX_ARRAY, 
		Last = PxField::eLAST
	};
};