#pragma once

#include "GeometryEnum.h"
#include "Bounds3.h"
#include "ShapeFlag.h"
#include <PxShape.h>

namespace PhysX
{
	ref class Actor;

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
			Actor^ _actor;

		internal:
			Shape(PxShape* shape, PhysX::Actor^ parentActor);
		public:
			~Shape();
		protected:
			!Shape();

		public:
			property bool Disposed
			{
				virtual bool get();
			}

			/// <summary>
			/// Get the geometry type of the shape.
			/// </summary>
			property GeometryType Type
			{
				GeometryType get();
			}

			/// <summary>
			/// Retrieves the actor which this shape is associated with. 
			/// </summary>
			property PhysX::Actor^ Actor
			{
				PhysX::Actor^ get();
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

			/// <summary>Gets or sets an object, usually to create a 1:1 relationship with a user object.</summary>
			property Object^ UserData;

		internal:
			property PxShape* UnmanagedPointer
			{
				PxShape* get();
			}
	};
};