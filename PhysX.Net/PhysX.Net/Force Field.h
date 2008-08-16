#pragma once

#include "Enums.h"

#include "Force Field Shape Group.h"
#include "Element Collection.h"

using namespace System;
UsingFrameworkNamespace

class NxForceField;

namespace StillDesign
{
	namespace PhysX
	{
		ref class Scene;
		ref class ForceFieldDescription;
		ref class ForceFieldShapeDescription;
		ref class Actor;
		ref class ForceFieldKernel;
		
		public ref class ForceField : StillDesign::PhysX::IDisposable
		{
			public:
				ref class ForceFieldShapeGroupCollection : ReadOnlyElementCollection<ForceFieldShapeGroup^>
				{
					
				};
				
				ref class SamplePointForcesResult
				{
					public:
						array<Vector3>^ _forces;
						array<Vector3>^ _torques;
						
						SamplePointForcesResult( array<Vector3>^ forces, array<Vector3>^ torques );
						
						property array<Vector3>^ Forces
						{
							array<Vector3>^ get();
						}
						property array<Vector3>^ Torques
						{
							array<Vector3>^ get();
						}
				};
				
			public:
				virtual event EventHandler^ onDisposing;
				virtual event EventHandler^ onDisposed;
				
			private:
				NxForceField* _forceField;
				Scene^ _scene;
				
				Actor^ _actor;
				
				ElementCollection<ForceFieldShapeGroup^, ForceFieldShapeGroupCollection^>^ _shapeGroups;
				StillDesign::PhysX::ForceFieldKernel^ _forceFieldKernel;
				
				Object^ _userData;
				
			internal:
				ForceField( NxForceField* forceField );
			public:
				~ForceField();
			protected:
				!ForceField();
			public:
				property bool IsDisposed
				{
					virtual bool get();
				}
			
			public:
				/// <summary>Adds a force field shape group to this force field to define its volume of activity</summary>
				void AddShapeGroup( ForceFieldShapeGroup^ group );
				/// <summary>Removes a force field shape group from this force field</summary>
				bool RemoveShapeGroup( ForceFieldShapeGroup^ group );
				
				SamplePointForcesResult^ SamplePointForces( array<Vector3>^ points );
				SamplePointForcesResult^ SamplePointForces( array<Vector3>^ points, array<Vector3>^ velocities );
				
				//
				
				/// <summary>Gets the scene which this force field belongs to</summary>
				property StillDesign::PhysX::Scene^ Scene
				{
					StillDesign::PhysX::Scene^ get();
				}
				/// <summary>Gets the actor pointer that this force field is attached to</summary>
				property StillDesign::PhysX::Actor^ Actor
				{
					StillDesign::PhysX::Actor^ get();
					void set( StillDesign::PhysX::Actor^ value );
				}
				
				property ForceField::ForceFieldShapeGroupCollection^ ShapeGroups
				{
					ForceField::ForceFieldShapeGroupCollection^ get();
				}
				
				/// <summary>Retrieves the kernel function which this field is using</summary>
				property StillDesign::PhysX::ForceFieldKernel^ ForceFieldKernel
				{
					StillDesign::PhysX::ForceFieldKernel^ get();
					void set( StillDesign::PhysX::ForceFieldKernel^ value );
				}
				
				/// <summary></summary>
				property String^ Name
				{
					String^ get();
					void set( String^ value );
				}
				
				/// <summary>Gets or Sets the force field's transform</summary>
				property Matrix Pose
				{
					Matrix get();
					void set( Matrix value );
				}
				
				/// <summary></summary>
				property ForceFieldCoordinate Coordinates
				{
					ForceFieldCoordinate get();
					void set( ForceFieldCoordinate value );
				}
				
				/// <summary></summary>
				property short Group
				{
					short get();
					void set( short value );
				}
				/// <summary></summary>
				property StillDesign::PhysX::GroupsMask GroupsMask
				{
					StillDesign::PhysX::GroupsMask get();
					void set( StillDesign::PhysX::GroupsMask value );
				}
				
				/// <summary></summary>
				property ForceFieldFlag Flags
				{
					ForceFieldFlag get();
					void set( ForceFieldFlag value );
				}
				
				property Object^ UserData
				{
					Object^ get();
					void set( Object^ value );
				}
				
			internal:
				property NxForceField* UnmanagedPointer
				{
					NxForceField* get();
				}
		};
	};
};