#pragma once

namespace StillDesign
{
	namespace PhysX
	{
		ref class Scene;
		class InternalUserNotify;
		ref class Joint;
		ref class Actor;
		
		public ref class UserNotify abstract
		{
			private:
				InternalUserNotify* _userNotify;
				
			protected:
				UserNotify();
			public:
				~UserNotify();
			protected:
				!UserNotify();
			
			public:
				virtual bool OnJointBreak( float breakingForce, Joint^ brokenJoint ) abstract;
				virtual bool OnWake( array<Actor^>^ actors ) abstract;
				virtual bool OnSleep( array<Actor^>^ actors ) abstract;
				
			internal:
				property InternalUserNotify* UnmanagedPointer
				{
					InternalUserNotify* get();
				}
		};
		
		class InternalUserNotify : public NxUserNotify
		{
			private:
				gcroot<UserNotify^> _userNotify;
			
			public:
				InternalUserNotify( gcroot<UserNotify^> userNotify );
				
				virtual bool onJointBreak( NxReal breakingForce, NxJoint &brokenJoint );
				virtual void onWake( NxActor** actors, NxU32 count );
				virtual void onSleep( NxActor** actors, NxU32 count );
		};
	};
};