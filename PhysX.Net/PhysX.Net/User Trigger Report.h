#pragma once

#include "Enums.h"

#include <NxShape.h> 

namespace StillDesign
{
	namespace PhysX
	{
		ref class Scene;
		class InternalUserTriggerReport;
		ref class Shape;
		
		public ref class UserTriggerReport abstract
		{
			private:
				InternalUserTriggerReport* _internalUserTriggerReport;
				
			protected:
				UserTriggerReport();
			public:
				~UserTriggerReport();
			protected:
				!UserTriggerReport();
			
			public:
				virtual void OnTrigger( Shape^ triggerShape, Shape^ otherShape, TriggerFlag status ) abstract;
				
			internal:
				property InternalUserTriggerReport* UnmanagedPointer
				{
					InternalUserTriggerReport* get();
				}
		};
		
		class InternalUserTriggerReport : public NxUserTriggerReport
		{
			private:
				gcroot<UserTriggerReport^> _userTriggerReport;
			
			public:
				InternalUserTriggerReport( gcroot<UserTriggerReport^> userTriggerReport );
				
				virtual void onTrigger( NxShape &triggerShape, NxShape &otherShape, NxTriggerFlag status );
		};
	};
};