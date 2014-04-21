#pragma once

#include "Enums.h"
#include "IDisposable.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;

namespace StillDesign
{
	namespace PhysX
	{
		ref class ShapeDescription;
		ref class Actor;
		ref class Material;
		value class Bounds3;
		value class Capsule;
		value class Box;
		ref class Actor;
		ref class CCDSkeleton;
		value class Ray;
		ref class RaycastHit;
		value class Sphere;
		
		public ref class Shape abstract : StillDesign::PhysX::IDisposable
		{
			public:
				virtual event EventHandler^ OnDisposing;
				virtual event EventHandler^ OnDisposed;
				
			private:
				NxShape* _shape;
				
				StillDesign::PhysX::Actor^ _actor;
				StillDesign::PhysX::Material^ _material;
				
				StillDesign::PhysX::CCDSkeleton^ _ccdSkeleton;
				
			protected:
				Shape( NxShape* shape );
			public:
				!Shape();
			protected:
				~Shape();
			public:
				property bool IsDisposed
				{
					virtual bool get();
				}
			
			protected:
				void SaveToDescription( ShapeDescription^ shapeDescription );
			
			private:
				void _material_OnDisposing( System::Object^ sender, EventArgs^ e );
			
			public:
				/// <summary>Retrieves the information computed from a ray intersection</summary>
				/// <param name="worldRay">The ray to intersect against the shape in the global frame</param>
				/// <param name="maximumDistance">The maximum distance to check along the ray</param>
				/// <param name="hintFlags">A combination of RaycastBit flags. Specifies which members of RaycastHit the user is interested in (e.g. normal, material etc)</param>
				/// <param name="computeHitOnly">Is a hint saying you're only interested in a boolean answer</param>
				RaycastHit^ Raycast( StillDesign::PhysX::Ray worldRay, float maximumDistance, RaycastBit hintFlags, bool computeHitOnly );
				
				/// <summary>Checks Whether the Shape Overlaps a World Space Axis Aligned Bounding Box</summary>
				/// <param name="worldBounds">The world space axis aligned box to check against</param>
				virtual bool CheckOverlapsAABB( Bounds3 worldBounds );
				/// <summary>Checks whether the shape overlaps a world-space OBB or not</summary>
				/// <param name="worldBox">The world space axis aligned box to check against</param>
				virtual bool CheckOverlapsOBB( StillDesign::PhysX::Box worldBox );
				/// <summary>Checks Whether the Shape Overlaps a World Space Sphere</summary>
				/// <param name="sphere">The sphere description in the global frame to test against</param>
				virtual bool CheckOverlapsSphere( Sphere sphere );
				/// <summary>Checks whether the shape overlaps a world-space capsule or not</summary>
				/// <param name="capsule">The world space capsule to check against</param>
				virtual bool CheckOverlapsCapsule( Capsule capsule );
				
				/// <summary>Retrieves the status of a shape flag</summary>
				/// <param name="flag">The flag to retrieve</param>
				bool GetFlag( ShapeFlag flag );
				/// <summary>The new shape flags to set for this shape</summary>
				/// <param name="flag">True to set the flags. False to clear the flags specified in flag</param>
				void SetFlag( ShapeFlag flag, bool value );
				
				//
				
				/// <summary>Gets the Actor Associated with this Base Shape</summary>
				property StillDesign::PhysX::Actor^ Actor
				{
					StillDesign::PhysX::Actor^ get();
				}
				
				/// <summary>Gets or Sets the Name of the Shape</summary>
				property String^ Name
				{
					String^ get();
					void set( String^ value );
				}
				/// <summary>Gets the Type of the Shape</summary>
				property ShapeType Type
				{
					ShapeType get();
				}
				property ShapeFlag Flags
				{
					ShapeFlag get();
					void set( ShapeFlag value );
				}
				
				/// <summary>Gets or Sets the Material of the Actor</summary>
				property StillDesign::PhysX::Material^ Material
				{
					StillDesign::PhysX::Material^ get();
					void set( StillDesign::PhysX::Material^ value );
				}
				
				/// <summary>Gets or Sets Which Collision Group this Shape is Part of</summary>
				/// <remarks>When Setting the Group the Value Must be below 32</remarks>
				property short Group
				{
					short get();
					void set( short value );
				}
				
				/// <summary>Gets the World Space Bounds of the Shape</summary>
				property Bounds3 WorldSpaceBounds
				{
					virtual Bounds3 get();
				}
				
				property float SkinWidth
				{
					float get();
					void set( float value );
				}
				
				/// <summary>Gets or Sets the Local Pose of the Shape Relative to the Parent Actor</summary>
				property Matrix LocalPose
				{
					Matrix get();
					void set( Matrix value );
				}
				/// <summary>Gets or Sets the Local Position of the Shape Relative to the Parent Actor</summary>
				property Vector3 LocalPosition
				{
					Vector3 get();
					void set( Vector3 value );
				}
				/// <summary>Gets or Sets the Local Orientation of the Shape Relative to the Parent Actor</summary>
				property Matrix LocalOrientation
				{
					Matrix get();
					void set( Matrix value );
				}
				
				/// <summary>Gets or Sets the global pose of the shape</summary>
				property Matrix GlobalPose
				{
					Matrix get();
					void set( Matrix value );
				}
				/// <summary>Gets or Sets the global position of the shape</summary>
				property Vector3 GlobalPosition
				{
					Vector3 get();
					void set( Vector3 value );
				}
				/// <summary>Gets or Sets the global orientation of the shape</summary>
				property Matrix GlobalOrientation
				{
					Matrix get();
					void set( Matrix value );
				}
				
				/// <summary>Retrieves the CCDSkeleton for this shape</summary>
				property StillDesign::PhysX::CCDSkeleton^ CCDSkeleton
				{
					StillDesign::PhysX::CCDSkeleton^ get();
					void set( StillDesign::PhysX::CCDSkeleton^ value );
				}
				
				property ShapeCompartmentType NonInteractingCompartmentTypes
				{
					ShapeCompartmentType get();
					void set( ShapeCompartmentType value );
				}
				
				/// <summary>Gets or Sets an associative object.</summary>
				property Object^ UserData;
				
			internal:
				/// <summary>Gets a Pointer to the NxShape Object</summary>
				property NxShape* UnmanagedPointer
				{
					virtual NxShape* get();
					void set( NxShape* value );
				}
		};
	};
};