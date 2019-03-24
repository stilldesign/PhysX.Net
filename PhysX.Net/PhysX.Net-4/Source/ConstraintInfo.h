#pragma once

#include "Constraint.h"

namespace PhysX
{
	public ref class ConstraintInfo
	{
	internal:
		static ConstraintInfo^ ToManaged(PxConstraintInfo* info);

	public:
		/// <summary>
		/// The broken constraint.
		/// </summary>
		property PhysX::Constraint^ Constraint;

		/// <summary>
		/// Unique type ID of the external object. Allows to cast the provided external reference to the appropriate type.
		/// </summary>
		property int TypeId;

		property Object^ ExternalReference;
	};
};