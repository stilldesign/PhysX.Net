#pragma once

#include "ContactPatchBase.h"

namespace PhysX
{
	public ref class ContactPatch : ContactPatchBase
	{
	public:
		/// <summary>
		/// Contact normal.
		/// </summary>
		property Vector3 Normal;

		/// <summary>
		/// Static friction coefficient.
		/// </summary>
		property float StaticFriction;

		/// <summary>
		/// Dynamic friction coefficient.
		/// </summary>
		property float DynamicFriction;

		/// <summary>
		/// Restitution coefficient.
		/// </summary>
		property float Restitution;

		/// <summary>
		/// Shape A's material index. 
		/// </summary>
		property int MaterialIndex0;

		/// <summary>
		/// Shape B's material index.  
		/// </summary>
		property int MaterialIndex1;
	};
};