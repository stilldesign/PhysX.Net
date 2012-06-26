#pragma once

#include "PhysicsEnum.h"
#include <PxSimulationEventCallback.h> 

namespace PhysX
{
	ref class Shape;

	public ref class TriggerPair
	{
		internal:
			static PxTriggerPair ToUnmanaged(TriggerPair^ pair);
			static TriggerPair^ ToManaged(PxTriggerPair pair);

		public:
			/// <summary>
			/// Gets or sets the shape that has been marked as a trigger.
			/// </summary>
			property Shape^ TriggerShape;

			/// <summary>
			/// Gets or sets the shape causing the trigger event.
			/// </summary>
			property Shape^ OtherShape;

			/// <summary>
			/// Gets or sets the type of trigger event (eNOTIFY_TOUCH_FOUND, eNOTIFY_TOUCH_PERSISTS or eNOTIFY_TOUCH_LOST).
			/// </summary>
			property PairFlag Status;
	};
};