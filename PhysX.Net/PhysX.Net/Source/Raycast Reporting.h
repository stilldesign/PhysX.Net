#pragma once

#include "Raycast Hit.h"

namespace StillDesign
{
	namespace PhysX
	{
		class InternalUserRaycastReport;
		
		public ref class UserRaycastReport abstract
		{
			private:
				InternalUserRaycastReport* _rayCastReport;
			
			protected:
				UserRaycastReport();
			public:
				~UserRaycastReport();
			protected:
				!UserRaycastReport();
			
			public:
				virtual bool OnHit( RaycastHit^ hits ) abstract;
				
			internal:
				property InternalUserRaycastReport* UnmanagedPointer
				{
					InternalUserRaycastReport* get();
				}
		};

		class InternalUserRaycastReport : public NxUserRaycastReport
		{
			private:
				gcroot<UserRaycastReport^> _rayCastReport;
			
			public:
				InternalUserRaycastReport( UserRaycastReport^ rayCastReport );
			
			private:
				virtual bool onHit( const NxRaycastHit &hits );
		};
	};
};