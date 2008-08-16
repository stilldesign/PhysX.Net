#pragma once

#include "Sweep Query Hit.h"

#include <NxUserEntityReport.h> 

namespace StillDesign
{
	namespace PhysX
	{
		ref class Shape;
		ref class Scene;
		
		class EntityShapeReport;
		class EntitySweepQueryHitReport;
		
		public ref class UserEntityShapeReport abstract
		{
			private:
				EntityShapeReport* _entityReport;
				Scene^ _scene;
			
			protected:
				UserEntityShapeReport();
			public:
				~UserEntityShapeReport();
			protected:
				!UserEntityShapeReport();
			
			public:
				virtual bool OnEvent( array<Shape^>^ entities ) abstract;
				
			internal:
				property EntityShapeReport* UnmanagedPointer
				{
					EntityShapeReport* get();
				}
		};
		class EntityShapeReport : public NxUserEntityReport<NxShape*>
		{
			private:
				gcroot<UserEntityShapeReport^> _userEntityShapeReport;
			
			public:
				EntityShapeReport( UserEntityShapeReport^ userEntityShapeReport );
				~EntityShapeReport();
				
				virtual bool onEvent( NxU32 nbEntities, NxShape** entities );
		};
		
		//
		
		public ref class UserEntitySweepQueryHitReport abstract
		{
			private:
				EntitySweepQueryHitReport* _entityReport;
				Scene^ _scene;
			
			protected:
				UserEntitySweepQueryHitReport();
			public:
				~UserEntitySweepQueryHitReport();
			protected:
				!UserEntitySweepQueryHitReport();
			
			public:
				virtual bool OnEvent( array<SweepQueryHit^>^ entities ) abstract;
				
			internal:
				property EntitySweepQueryHitReport* UnmanagedPointer
				{
					EntitySweepQueryHitReport* get();
				}
		};
		class EntitySweepQueryHitReport : public NxUserEntityReport<NxSweepQueryHit>
		{
			private:
				gcroot<UserEntitySweepQueryHitReport^> _userEntitySweepQueryHitReport;
			
			public:
				EntitySweepQueryHitReport( UserEntitySweepQueryHitReport^ userEntitySweepQueryHitReport );
				~EntitySweepQueryHitReport();
				
				virtual bool onEvent( NxU32 nbEntities, NxSweepQueryHit* entities );
		};
	};
};