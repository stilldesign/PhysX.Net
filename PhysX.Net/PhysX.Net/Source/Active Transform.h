#pragma once

struct NxActiveTransform;

namespace StillDesign
{
	namespace PhysX
	{
		ref class Scene;
		ref class Actor;
		
		public ref class ActiveTransform
		{
			private:
				Matrix _actorToWorld;
				
				StillDesign::PhysX::Actor^ _actor;
				
			internal:
				ActiveTransform( NxActiveTransform activeTransform );
			
			public:
				property StillDesign::PhysX::Actor^ Actor
				{
					StillDesign::PhysX::Actor^ get();
				}
				property Matrix ActorToWorld
				{
					Matrix get();
				}
		};
	};
};