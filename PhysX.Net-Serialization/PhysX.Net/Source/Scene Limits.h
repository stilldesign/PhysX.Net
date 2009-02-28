#pragma once


namespace StillDesign
{
	namespace PhysX
	{
		ref class Scene;
		
		public ref class SceneLimits
		{
			private:
				NxSceneLimits* _sceneLimits;
			
				SceneLimits();
			public:
				~SceneLimits();
			protected:
				!SceneLimits();
			
			public:
				static SceneLimits^ FromScene( Scene^ scene );
			
			internal:
				static explicit operator NxSceneLimits( SceneLimits^ sceneLimits );
				static explicit operator SceneLimits^( NxSceneLimits sceneLimits );
				
			public:
				property  int MaximumActors
				{
					int get();
					void set( int value );
				}
				property int MaximumBodies
				{
					int get();
					void set( int value );
				}
				property int MaximumStaticShapes
				{
					int get();
					void set( int value );
				}
				property int MaximumDynamicShapes
				{
					int get();
					void set( int value );
				}
				property int MaximumJoints
				{
					int get();
					void set( int value );
				}
				
				property NxSceneLimits* UnmanagedPointer
				{
					NxSceneLimits* get();
				}
		};
	};
};