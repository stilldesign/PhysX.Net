#pragma once

namespace PhysX
{
	public ref class SceneLimits
	{
	internal:
		static PxSceneLimits ToUnmanaged(SceneLimits^ managed);
		static SceneLimits^ ToManaged(PxSceneLimits unmanaged);

	public:
		void SetToDefault();
		bool IsValid();

		property int MaxActors;			//!< Expected maximum number of actors
		property int MaxBodies;			//!< Expected maximum number of dynamic rigid bodies
		property int MaxStaticShapes;		//!< Expected maximum number of static shapes
		property int MaxDynamicShapes;		//!< Expected maximum number of dynamic shapes
		property int MaxConstraints;		//!< Expected maximum number of constraint shaders
		property int MaxRegions;			//!< Expected maximum number of broad-phase regions
		property int MaxObjectsPerRegion;	//!< Expected maximum number of objects in one broad-phase region
	};
}