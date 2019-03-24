#pragma once

namespace PhysX
{
	/// <summary>
	/// Class used to retrieve limits(e.g. maximum number of bodies) for a scene.
	/// The limits are used as a hint to the size of the scene, not as a
	/// hard limit (i.e. it will be possible to create more objects than specified in the scene limits). 
	/// 0 indicates no limit.
	/// </summary>
	public ref class SceneLimits
	{
	internal:
		static PxSceneLimits ToUnmanaged(SceneLimits^ managed);
		static SceneLimits^ ToManaged(PxSceneLimits unmanaged);

	public:
		void SetToDefault();
		bool IsValid();

		/// <summary>
		/// Expected maximum number of actors.
		/// </summary>
		property int MaxActors;

		/// <summary>
		/// Expected maximum number of dynamic rigid bodies.
		/// </summary>
		property int MaxBodies;

		/// <summary>
		/// Expected maximum number of static shapes.
		/// </summary>
		property int MaxStaticShapes;

		/// <summary>
		/// Expected maximum number of dynamic shapes.
		/// </summary>
		property int MaxDynamicShapes;

		/// <summary>
		/// Expected maximum number of aggregates.
		/// </summary>
		property int MaxAggregates;

		/// <summary>
		/// Expected maximum number of constraint shaders.
		/// </summary>
		property int MaxConstraints;

		/// <summary>
		/// Expected maximum number of broad-phase regions.
		/// </summary>
		property int MaxRegions;

		/// <summary>
		/// Expected maximum number of broad-phase overlaps.
		/// </summary>
		property int MaxBroadPhaseOverlaps;
	};
}