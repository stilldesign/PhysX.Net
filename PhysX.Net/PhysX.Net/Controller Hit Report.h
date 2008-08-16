#pragma once

#include <NxController.h> 

#include "Enums.h"
#include "Controller Enums.h"

using namespace System;

UsingFrameworkNamespace

namespace StillDesign
{
	namespace PhysX
	{
		ref class Scene;
	
		ref class ControllerHitReport;
		ref class ControllerShapeHit;
		ref class ControllersHit;
		
		class UserControllerHitReport : public NxUserControllerHitReport
		{
			private:
				gcroot< Scene^ > _scene;
				gcroot< ControllerHitReport^ > _hitReport;
			
			public:
				UserControllerHitReport( Scene^ scene, ControllerHitReport^ hitReport );
				
				NxControllerAction onShapeHit( const NxControllerShapeHit &hit );
				NxControllerAction onControllerHit( const NxControllersHit &hit );
		};
		
		public ref class ControllerHitReport abstract
		{
			private:
				UserControllerHitReport* _hitReport;
			
			protected:
				ControllerHitReport( Scene^ scene );
			public:
				~ControllerHitReport();
			protected:
				!ControllerHitReport();
				
			public:
				/// <summary></summary>
				virtual ControllerAction OnShapeHit( ControllerShapeHit^ hit ) abstract;
				/// <summary></summary>
				virtual ControllerAction OnControllerHit( ControllersHit^ hit ) abstract;
			
			internal:
				property UserControllerHitReport* UnmanagedPointer
				{
					UserControllerHitReport* get();
				}
		};
	};
};