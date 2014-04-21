#pragma once

#include "Actor.h"

using namespace System;
using namespace StillDesign::PhysX;

class NxContactReport;

namespace StillDesign
{
	namespace PhysX
	{
		ref class ContactPair;
		class InternalUserContactReport;
		
		public ref class UserContactReport abstract
		{
			private:
				InternalUserContactReport* _contactReport;
				
				StillDesign::PhysX::Scene^ _scene;
				
			protected:
				UserContactReport();
			public:
				~UserContactReport();
			protected:
				!UserContactReport();
				
			public:
				virtual void OnContactNotify( ContactPair^ contactInformation, ContactPairFlag events ) abstract;
				
			internal:
				property InternalUserContactReport* UnmanagedPointer
				{
					InternalUserContactReport* get();
				}
		};
		
		class InternalUserContactReport : public NxUserContactReport
		{
			private:
				gcroot< StillDesign::PhysX::UserContactReport^ > _userContactReport;

			public:
				InternalUserContactReport( UserContactReport^ userContactReport );
				
				virtual void onContactNotify( NxContactPair& pair, NxU32 events );
		};
	};
};