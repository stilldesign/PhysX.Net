#pragma once

namespace StillDesign
{
	namespace PhysX
	{
		ref class Scene;
		
		public ref class SceneStatistics
		{
			private:
				NxSceneStats* _stats;
			
			public:
				SceneStatistics( Scene^ scene );
				~SceneStatistics();
			protected:
				!SceneStatistics();
				
			public:
				property int Contacts
				{
					int get();
				}
				property int MaximumContacts
				{
					int get();
				}
				property int Pairs
				{
					int get();
				}
				property int MaximumPairs
				{
					int get();
				}
				property int DynamicActorsInAwakeGroups
				{
					int get();
				}
				property int MaximumDynamicActorsInAwakeGroups
				{
					int get();
				}
				property int AxisConstraints
				{
					int get();
				}
				property int MaximumAxisConstraints
				{
					int get();
				}
				property int SolverBodies
				{
					int get();
				}
				property int MaximumSolverBodies
				{
					int get();
				}
				property int Actors
				{
					int get();
				}
				property int DynamicActors
				{
					int get();
				}
				property int MaximumDynamicActors
				{
					int get();
				}
				property int StaticShapes
				{
					int get();
				}
				property int MaximumStaticShapes
				{
					int get();
				}
				property int DynamicShapes
				{
					int get();
				}
				property int MaximumDynamicShapes
				{
					int get();
				}
				property int Joints
				{
					int get();
				}
				property int MaximumJoints
				{
					int get();
				}
			
			internal:
				property NxSceneStats* UnmanagedPointer
				{
					NxSceneStats* get();
				}
		};
	};
};