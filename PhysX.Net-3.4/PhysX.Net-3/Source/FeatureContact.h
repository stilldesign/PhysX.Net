#pragma once

#include "SimpleContact.h"

namespace PhysX
{
	/// <summary>
	/// Extended contact point data including face (feature) indices.
	/// </summary>
	public ref class FeatureContact : SimpleContact
	{
	internal:
		static PxFeatureContact ToUnmanaged(FeatureContact^ point);
		static FeatureContact^ ToManaged(PxFeatureContact point);

	protected:
		static void PopulateUnmanaged(FeatureContact^ managed, PxFeatureContact& unmanaged);

	public:
		/// <summary>
		/// Face index on shape A.
		/// </summary>
		property int InternalFaceIndex0;
		/// <summary>
		/// Face index on shape B.
		/// </summary>
		property int InternalFaceIndex1;
	};
};