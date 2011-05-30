#pragma once

#include "ActorDesc.h"
#include "DeformableEnum.h"
#include "Bounds3.h"
#include "FilterData.h"
#include "TolerancesScale.h"

class PxDeformableDesc;

namespace PhysX
{
	ref class DeformableMesh;

	public ref class DeformableDesc : ActorDesc
	{
		public:
			DeformableDesc([Optional] Nullable<TolerancesScale> scale);

		internal:
			static PxDeformableDesc ToUnmanaged(DeformableDesc^ desc);
			static DeformableDesc^ ToManaged(PxDeformableDesc desc);

		public:
			void SetToDefault();
			bool IsValid();

			/// <summary>
			/// Gets or sets the corresponding deformable mesh.
			/// </summary>
			property PhysX::DeformableMesh^ DeformableMesh;

			/// <summary>
			/// Gets or sets the bending stiffness in the range from 0 to 1. Ineffective for soft bodies.
			/// </summary>
			property float BendingStiffness;

			/// <summary>
			/// Gets or sets the deformable volume stiffness in the range from 0 to 1. Ineffective for cloth.
			/// </summary>
			property float VolumeStiffness;

			/// <summary>
			/// Gets or sets the deformable stretching stiffness in the range from 0 to 1.
			/// </summary>
			property float StretchingStiffness;

			/// <summary>
			/// Gets or sets the damping coefficient in the range from 0 to 1. 
			/// </summary>
			property float DampingCoefficient;

			/// <summary>
			/// Gets or sets the deformable static friction coefficient in the range from 0 to +inf.
			/// </summary>
			property float StaticFriction;

			/// <summary>
			/// Gets or sets the deformable dynamic friction coefficient in the range from 0 to +inf.
			/// </summary>
			property float DynamicFriction;

			/// <summary>
			/// Gets or sets the deformable pressure coefficient (must be non negative). Ineffective for soft bodies.
			/// </summary>
			property float Pressure;

			/// <summary>
			/// Gets or sets the deformable tear factor (must be larger than one).
			/// </summary>
			property float TearFactor;

			/// <summary>
			/// Gets or sets the deformable attachment tear factor (must be larger than one).
			/// </summary>
			property float AttachmentTearFactor;

			/// <summary>
			/// Gets or sets the deformable mass.
			/// </summary>
			property float Mass;

			/// <summary>
			/// Gets or sets the relative grid spacing for the broad phase.
			/// The deformable is represented by a set of world aligned cubical cells in broad phase.
			/// The size of these cells is determined by multiplying the length of the diagonal of
			/// the AABB of the initial deformable size with this constant.
			/// </summary>
			property float RelativeGridSpacing;

			/// <summary>
			/// Gets or sets the deformable solver iterations.
			/// </summary>
			property int SolverIterations;

			/// <summary>
			/// Gets or sets the number of iterations of the hierarchical deformable solver.
			/// </summary>
			property int HierarchicalSolverIterations;

			/// <summary>
			/// Gets or sets the world space AABB enclosing all deformable points.
			/// </summary>
			property Bounds3 WorldBounds;

			/// <summary>
			/// Gets or sets the valid bounds of the deformable in world space.
			/// </summary>
			property Bounds3 ValidBounds;

			/// <summary>
			///  Gets the current number of deformable vertices.
			/// </summary>
			property int NumberOfVertices;

			/// <summary>
			///  Gets the maximum number of deformable vertices.
			/// </summary>
			property int MaximumVertices;

			/// <summary>
			/// Gets or sets the collision stiffness.
			/// </summary>
			property float CollisionStiffness;

			/// <summary>
			/// Gets or sets the attachment stiffness.
			/// </summary>
			property float AttachmentStiffness;

			/// <summary>
			/// Gets or sets the contact offset.
			/// </summary>
			property float ContactOffset;

			/// <summary>
			/// Gets or sets the rest offset.
			/// </summary>
			property float RestOffset;

			/// <summary>
			/// Gets or sets the penetration offset.
			/// </summary>
			property float PenetrationOffset;

			/// <summary>
			/// Gets or sets the self collision offset.
			/// </summary>
			property float SelfCollisionOffset;

			/// <summary>
			/// Gets or sets the external acceleration which affects all non attached vertices of the deformable.
			/// </summary>
			property Vector3 ExternalAcceleration;

			/// <summary>
			/// Gets or sets the acceleration acting normal to the deformable surface at each vertex.
			/// </summary>
			property Vector3 WindAcceleration;

			/// <summary>
			/// Gets or sets the linear velocity below which a deformable may go to sleep.
			/// </summary>
			property float SleepLinearVelocity;

			/// <summary>
			/// Gets or sets the user definable collision filter data.
			/// </summary>
			property FilterData SimulationFilterData;

			/// <summary>
			/// Gets or sets the deformable flags.
			/// </summary>
			property DeformableFlag DeformableFlags;

			/// <summary>
			/// Flags to control which data can be read from the SDK.
			/// </summary>
			property PhysX::DeformableReadDataFlag DeformableReadDataFlags;

			/// <summary>
			/// The global pose of the deformable in the world.
			/// </summary>
			property Matrix GlobalPose;

			/// <summary>
			/// Maximum number of primitive split pairs reported for torn deformables.
			/// </summary>
			property int MaximumPrimitiveSplitPairs;

			/// <summary>
			/// The deformable wake up counter.
			/// </summary>
			property float WakeUpCounter;
	};
};