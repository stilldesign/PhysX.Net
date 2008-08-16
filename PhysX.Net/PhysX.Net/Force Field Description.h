#pragma once

#include "Enums.h"
#include "IDisposable.h"
#include "Force Field Shape Group.h"
#include "Force Field Shape Description.h"

using namespace System;
UsingFrameworkNamespace

class NxForceFieldDesc;

namespace StillDesign
{
	namespace PhysX
	{
		value class GroupsMask;
		ref class Actor;
		ref class ForceFieldKernel;
		
		public ref class ForceFieldDescription : IDisposable
		{
			public:
				// TODO: Check for disposals
				ref class ForceFieldShapeGroupCollection : ListNotifiable<ForceFieldShapeGroup^>
				{
					
				};
				ref class ForceFieldShapeDescriptionCollection : ListNotifiable<ForceFieldShapeDescription^>
				{
					
				};
				
				virtual event EventHandler^ onDisposing;
				virtual event EventHandler^ onDisposed;
			
			private:
				NxForceFieldDesc* _forceFieldDesc;
				
				StillDesign::PhysX::Actor^ _actor;
				
				ForceFieldKernel^ _kernel;
				ForceFieldShapeGroupCollection^ _groups;
				ForceFieldShapeDescriptionCollection^ _shapeDescriptions;
				
				Object^ _userData;
			
			public:
				ForceFieldDescription();
			internal:
				ForceFieldDescription( NxForceFieldDesc* forceFieldDesc );
			public:
				~ForceFieldDescription();
			protected:
				!ForceFieldDescription();
			public:
				property bool IsDisposed
				{
					virtual bool get();
				}
			internal:
				void CreateAux();
				
			public:
				/// <summary>Resets the structure to the default</summary>
				void SetToDefault();
				/// <summary>Returns true if the descriptor is valid</summary>
				bool IsValid();
				
			private:
				void _group_onAdd( Object^ sender, ForceFieldShapeGroup^ e );
				void _group_onRemove( Object^ sender, ForceFieldShapeGroup^ e );
				
				void _shapeDescriptions_onAdd( Object^ sender, ForceFieldShapeDescription^ e );
				void _shapeDescriptions_onRemove( Object^ sender, ForceFieldShapeDescription^ e );
				
			public:
				/// <summary>Get or Sets the kernel function of the force field</summary>
				property ForceFieldKernel^ Kernel
				{
					ForceFieldKernel^ get();
					void set( ForceFieldKernel^ value );
				}
				
				property ForceFieldShapeGroupCollection^ ShapeGroups
				{
					ForceFieldShapeGroupCollection^ get();
				}
				property ForceFieldShapeDescriptionCollection^ IncludeGroupShapes
				{
					ForceFieldShapeDescriptionCollection^ get();
				}
				
				/// <summary>Gets or Sets the force field variety Index, index != 0 has to be created</summary>
				property short ForceFieldVariety
				{
					short get();
					void set( short value );
				}
				
				/// <summary>Gets or Sets the Actor Associated with the Force Field Description</summary>
				property StillDesign::PhysX::Actor^ Actor
				{
					StillDesign::PhysX::Actor^ get();
					void set( StillDesign::PhysX::Actor^ value );
				}
				
				/// <summary>Gets the Name of the descriptor</summary>
				property String^ Name
				{
					String^ get();
					void set( String^ value );
				}
				
				/// <summary>Gets or Sets the global or (if actor is set) actor relative transformation of the force field</summary>
				property Matrix Pose
				{
					Matrix get();
					void set( Matrix value );
				}
				
				/// <summary>Gets or Sets the coordinate space of the field</summary>
				property ForceFieldCoordinate Coordinates
				{
					ForceFieldCoordinate get();
					void set( ForceFieldCoordinate value );
				}
				
				/// <summary>Gets or Sets the collision group used for collision filtering</summary>
				property short Group
				{
					short get();
					void set( short value );
				}
				/// <summary>Gets or Sets the groups mask used for collision filtering</summary>
				property StillDesign::PhysX::GroupsMask GroupsMask
				{
					StillDesign::PhysX::GroupsMask get();
					void set( StillDesign::PhysX::GroupsMask value );
				}
				
				/// <summary>Gets or Sets the force field type for fluids</summary>
				property ForceFieldType FluidType
				{
					ForceFieldType get();
					void set( ForceFieldType value );
				}
				/// <summary>Gets or Sets the force field type for cloth</summary>
				property ForceFieldType ClothType
				{
					ForceFieldType get();
					void set( ForceFieldType value );
				}
				/// <summary>Gets or Sets the force field type for soft bodies</summary>
				property ForceFieldType SoftBodyType
				{
					ForceFieldType get();
					void set( ForceFieldType value );
				}
				/// <summary>Gets or Sets the force field type for rigid bodies</summary>
				property ForceFieldType RigidBodyType
				{
					ForceFieldType get();
					void set( ForceFieldType value );
				}
				
				/// <summary>Gets or Sets an arbitary 1:1 object</summary>
				property Object^ UserData
				{
					Object^ get();
					void set( Object^ value );
				}
				
			internal:
				property NxForceFieldDesc* UnmanagedPointer
				{
					NxForceFieldDesc* get();
				}
		};
	};
};