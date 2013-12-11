#pragma once

//#include <PxScene.h>

namespace PhysX
{
	ref class Actor;

	/// <summary>
	/// Data struct for use with Active Transform Notification.
	/// </summary>
	public ref class ActiveTransform
	{
		internal:
			static ActiveTransform^ ToManaged(PxActiveTransform transform);

		public:
			property PhysX::Actor^ Actor;
			property Matrix ActorToWorldTransform;
	};
};