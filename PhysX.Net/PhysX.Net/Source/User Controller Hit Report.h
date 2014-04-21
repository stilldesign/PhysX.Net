#pragma once

#include "Enums.h"
#include "Controller Enums.h"

using namespace System;

namespace StillDesign
{
	namespace PhysX
	{
		ref class Scene;
	
		ref class UserControllerHitReport;
		ref class ControllerShapeHit;
		ref class ControllersHit;
		
		class InternalUserControllerHitReport : public NxUserControllerHitReport
		{
			private:
				gcroot<UserControllerHitReport^> _hitReport;
			
			public:
				InternalUserControllerHitReport( UserControllerHitReport^ hitReport );
				
				NxControllerAction onShapeHit( const NxControllerShapeHit &hit );
				NxControllerAction onControllerHit( const NxControllersHit &hit );
		};
		
		public ref class UserControllerHitReport abstract
		{
			private:
				InternalUserControllerHitReport* _hitReport;
			
			protected:
				UserControllerHitReport();
			public:
				~UserControllerHitReport();
			protected:
				!UserControllerHitReport();
				
			public:
				/// <summary></summary>
				virtual ControllerAction OnShapeHit( ControllerShapeHit^ hit ) abstract;
				/// <summary></summary>
				virtual ControllerAction OnControllerHit( ControllersHit^ hit ) abstract;
			
			internal:
				property InternalUserControllerHitReport* UnmanagedPointer
				{
					InternalUserControllerHitReport* get();
				}
		};
	};
};