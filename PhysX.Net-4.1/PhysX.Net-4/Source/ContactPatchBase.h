#pragma once

namespace PhysX
{
	public ref class ContactPatchBase
	{
	public:
		/// <summary>
		/// Number of contacts in this patch.
		/// </summary>
		property int NumberOfContacts;
			
		/// <summary>
		/// Flags for this patch.
		/// </summary>
		property int Flags;
	};
};