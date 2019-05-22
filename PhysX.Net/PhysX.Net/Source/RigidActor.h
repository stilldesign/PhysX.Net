#pragma once

#include "Actor.h"

namespace PhysX
{
	ref class Shape;
	ref class Geometry;
	ref class Material;
	ref class RigidStatic;

	/// <summary>
	/// RigidActor represents a base class shared between dynamic and static rigid bodies in the physics SDK.
	/// </summary>
	public ref class RigidActor abstract : Actor
	{
		internal:
			RigidActor(PxRigidActor* rigidActor, PhysX::IDisposable^ owner);

		private:
			/// <summary>
			/// Gets a list of shapes attached to this actor.
			/// This method will first lookup the shape in the ObjectTable, then if not found
			/// it will create a managed Shape for it.
			/// </summary>
			List<Shape^>^ GetOrCreateShapesOfActor(PxRigidActor* actor);

		public:
			Shape^ GetShape(int index);

			/// <summary>
			/// Creates a new shape with default properties and a single material adds it to the list of shapes of this actor.
			/// </summary>
			/// <remarks>
			/// Mass properties of dynamic rigid actors will not automatically be recomputed to reflect the new mass distribution
			/// implied by the shape. Follow this call with a call to the PhysX extensions method RigidBodyExt.UpdateMassAndInertia() to do that.
			/// The default shape flags to be set are: Visualization, SimulationShape, SceneQueryShape (see <see cref="ShapeFlag" />).
			/// The only exception are triangle mesh, heightfield or plane geometry shapes if the actor is not a PxRigidStatic.
			/// In these cases the SimulationShape flag is omitted.
			/// Creating compounds with a very large number of shapes may adversly affect performance and stability.
			/// 
			/// Does NOT wake the actor up automatically.
			/// </remarks>
			/// <param name="geometry">The geometry of the shape.</param>
			/// <param name="material">The material for the shape.</param>
			/// <returns>The newly created shape.</returns>
			//[Obsolete("PxRigidActor::createShape() is deprecated, and will be removed in PhysX 3.5. PxRigidActorExt::createExclusiveShape() replaces this method.")]
			//Shape^ CreateShape(Geometry^ geometry, Material^ material);
			//[Obsolete("PxRigidActor::createShape() is deprecated, and will be removed in PhysX 3.5. PxRigidActorExt::createExclusiveShape() replaces this method.")]
			//Shape^ CreateShape(Geometry^ geometry, array<Material^>^ materials);

			void AttachShape(Shape^ shape);

		public:
			/// <summary>
			/// Scale a rigid actor by a uniform scale.
			/// The geometry and relative positions of the actor are multiplied by the given scale value. If the actor is a rigid body or an articulation link and the scaleMassProps value is true, the mass properties are scaled assuming the density is constant: the center of mass is linearly scaled, the mass is multiplied by the cube of the scale, and the inertia tensor by the fifth power of the scale.
			/// </summary>
			/// <param name="scale">The scale by which to multiply the actor.</param>
			void Scale(float scale);
			/// <summary>
			/// Scale a rigid actor by a uniform scale.
			/// The geometry and relative positions of the actor are multiplied by the given scale value. If the actor is a rigid body or an articulation link and the scaleMassProps value is true, the mass properties are scaled assuming the density is constant: the center of mass is linearly scaled, the mass is multiplied by the cube of the scale, and the inertia tensor by the fifth power of the scale.
			/// </summary>
			/// <param name="scale">The scale by which to multiply the actor.</param>
			/// <param name="scaleMassProperties">Whether to scale the mass properties.</param>
			void Scale(float scale, bool scaleMassProperties);

			/// <summary>
			/// Create a static body by copying attributes from another rigid actor.
			/// The function clones a PxRigidDynamic as a PxRigidStatic. A uniform scale is applied.
			/// The following properties are copied: shapes, actor flags, owner client and client behavior bits
			/// The following are not copied and retain their default values: name, joints or observers, aggregate or scene membership, user data.
			/// Note: Transforms are not copied with bit-exact accuracy.
			/// </summary>
			/// <param name="transform">The transform of the new static</param>
			RigidStatic^ CloneStatic(Matrix transform);

			//

			/// <summary>
			/// Retrieves the actors world space transform.
			/// </summary>
			/// <remarks>
			///	The GlobalPose property retrieves the actor's current actor space to world space transformation.
			/// </remarks>
			property Matrix GlobalPose
			{
				Matrix get();
				void set(Matrix value);
			}

			/// <summary>
			/// Gets or sets the position/translation component of the global pose of the actor.
			/// </summary>
			property Vector3 GlobalPosePosition
			{
				Vector3 get();
				void set(Vector3 value);
			}
			/// <summary>
			/// Gets or sets the rotation component of the global pose of the actor.
			/// </summary>
			property Quaternion GlobalPoseQuat
			{
				Quaternion get();
				void set(Quaternion value);
			}

			/// <summary>
			/// Gets the shapes associated to this rigid actor.
			/// </summary>
			property IReadOnlyList<Shape^>^ Shapes
			{
				IReadOnlyList<Shape^>^ get();
			}

			/// <summary>
			/// Is this actor dynamic or static.
			/// </summary>
			property bool IsDynamic
			{
				bool get();
			}

		internal:
			property PxRigidActor* UnmanagedPointer
			{
				PxRigidActor* get();
			}
	};
};