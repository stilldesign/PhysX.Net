#pragma once


namespace PhysX
{
	/// <summary>
	/// FilterData is user-definable data which gets passed into the collision filtering shader and/or callback.
	/// </summary>
	public value class FilterData
	{
		public:
			FilterData(unsigned int word0, unsigned int word1, unsigned int word2, unsigned int word3);

		internal:
			static PxFilterData ToUnmanaged(FilterData data);
			static FilterData ToManaged(PxFilterData data);

		public:
			void SetToDefault();

			property unsigned int Word0;
			property unsigned int Word1;
			property unsigned int Word2;
			property unsigned int Word3;
	};
};