#pragma once

#include "GeometryEnum.h"
#include "Bounds3.h"
#include "ShapeFlag.h"
#include "Material.h"
#include "FilterData.h"

namespace PhysX
{
	ref class Actor;
	ref class RigidActor;
	ref class Geometry;
	ref class Serializable;
	ref class BoxGeometry;
	ref class SphereGeometry;
	ref class CapsuleGeometry;
	ref class PlaneGeometry;
	ref class ConvexMeshGeometry;
	ref class TriangleMeshGeometry;
	ref class HeightFieldGeometry;
	ref class Physics;

	/// <summary>
	/// Abstract class for collision shapes.
	/// An instance can be created by calling the CreateShape() method of the RigidActor class, or
	/// by adding the shape descriptors into the RigidActorDesc class before creating the actor.
	/// </summary>
	public ref class Shape : IDisposable
	{
	public:
		/// <summary>Raised before any disposing is performed.</summary>
		virtual event EventHandler^ OnDisposing;
		/// <summary>Raised once all disposing is performed.</summary>
		virtual event EventHandler^ OnDisposed;

	private:
		PxShape* _shape;
		RigidActor^ _actor;

	internal:
		Shape(PxShape* shape, PhysX::RigidActor^ parentActor);
	public:
		~Shape();
	protected:
		!Shape();

	public:
		property bool Disposed
		{
			virtual bool get();
		}

		Shape^ Clone();
		Shape^ Clone(Physics^ physics, bool isExclusive);

		/// <summary>
		/// Gets an object which is responsible for serialization of this type.
		/// </summary>
		Serializable^ AsSerializable();

		Geometry^ GetGeometry();
		BoxGeometry^ GetBoxGeometry();
		SphereGeometry^ GetSphereGeometry();
		CapsuleGeometry^ GetCapsuleGeometry();
		PlaneGeometry^ GetPlaneGeometry();
		ConvexMeshGeometry^ GetConvexMeshGeometry();
		TriangleMeshGeometry^ GetTriangleMeshGeometry();
		HeightFieldGeometry^ GetHeightFieldGeometry();

		/// <summary>
		/// Adjust the geometry of the shape.
		/// </summary>
		void SetGeometry(Geometry^ geometry);

		/// <summary>
		/// Retrieve material from given triangle index.
		/// The input index is the internal triangle index as used inside the SDK.This is the index returned to
		/// users by various SDK functions such as raycasts.
		/// This function is only useful for triangle meshes or heightfields, which have per - triangle materials.
		/// For other shapes the function returns the single material associated with the shape, regardless of the index.
		/// </summary>
		Material^ GetMaterialFromInternalFaceIndex(int faceIndex);

		//

		/// <summary>
		/// Returns true if the shape is exclusive to an actor.
		/// </summary>
		property bool IsExclusive
		{
			bool get();
		}

		/// <summary>
		/// Gets or sets the user definable collision filter data.
		/// </summary>
		property FilterData SimulationFilterData
		{
			FilterData get();
			void set(FilterData value);
		}

		/// <summary>
		/// Gets or sets the user definable query filter data.
		/// </summary>
		property FilterData QueryFilterData
		{
			FilterData get();
			void set(FilterData value);
		}

		//

		/// <summary>
		/// Get the geometry type of the shape.
		/// </summary>
		property PhysX::GeometryType GeometryType
		{
			PhysX::GeometryType get();
		}

		/// <summary>
		/// Retrieves the actor which this shape is associated with. 
		/// </summary>
		property PhysX::RigidActor^ Actor
		{
			PhysX::RigidActor^ get();
		}

		/// <summary>
		/// Retrieves the world space pose of the shape.
		/// </summary>
		property Matrix GlobalPose
		{
			Matrix get();
		}

		property Vector3 GlobalPosePosition
		{
			Vector3 get();
		}

		property Quaternion GlobalPoseQuat
		{
			Quaternion get();
		}

		/// <summary>
		/// Gets or set the name of the shape.
		/// </summary>
		property String^ Name
		{
			String^ get();
			void set(String^ value);
		}

		/// <summary>
		/// Gets or sets the axis aligned bounding box enclosing the shape.
		/// </summary>
		property Bounds3 WorldBounds
		{
			Bounds3 get();
		}

		/// <summary>
		/// Gets or sets the contact offset.
		/// </summary>
		property float ContactOffset
		{
			float get();
			void set(float value);
		}

		/// <summary>
		/// Gets or sets the reset offset.
		/// </summary>
		property float RestOffset
		{
			float get();
			void set(float value);
		}
		
		/// <summary>
		/// Gets or sets the shape flags.
		/// </summary>
		property ShapeFlag Flags
		{
			ShapeFlag get();
			void set(ShapeFlag value);
		}

		/// <summary>
		/// Gets or sets the pose of the shape in actor space, i.e. relative to the actor they are owned by.
		/// </summary>
		property Matrix LocalPose
		{
			Matrix get();
			void set(Matrix value);
		}

		property Vector3 LocalPosePosition
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Quaternion LocalPoseQuat
		{
			Quaternion get();
			void set(Quaternion value);
		}

		/// <summary>
		/// Gets or sets the shape materials.
		/// </summary>
		property array<PhysX::Material^>^ Materials
		{
			array<PhysX::Material^>^  get();
			void set(array<PhysX::Material^>^ value);
		}

		/// <summary>Gets or sets an object, usually to create a 1:1 relationship with a user object.</summary>
		property Object^ UserData;
		
	internal:
		property PxShape* UnmanagedPointer
		{
			PxShape* get();
		}

		property bool UnmanagedOwner;
	};
};