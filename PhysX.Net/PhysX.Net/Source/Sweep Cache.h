#pragma once



using namespace System;
namespace StillDesign
{
	namespace PhysX
	{
		value class Box;
		ref class Scene;
		
		public ref class SweepCache
		{
			public:
				virtual event EventHandler^ OnDisposing;
				virtual event EventHandler^ OnDisposed;
			
			private:
				NxSweepCache* _sweepCache;
				StillDesign::PhysX::Scene^ _scene;
			
			internal:
				SweepCache( NxSweepCache* sweepCache, StillDesign::PhysX::Scene^ scene );
			public:
				~SweepCache();
			protected:
				!SweepCache();
			public:
				property bool IsDisposed
				{
					virtual bool get();
				}
				
			public:
				/// <summary></summary>
				property StillDesign::PhysX::Scene^ Scene
				{
					StillDesign::PhysX::Scene^ get();
				}
				
				/// <summary></summary>
				void SetVolume( Box volume );
				
			internal:
				property NxSweepCache* UnmanagedPointer
				{
					NxSweepCache* get();
				}
		};
	};
};