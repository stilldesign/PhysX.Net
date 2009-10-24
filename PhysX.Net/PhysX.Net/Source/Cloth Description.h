#pragma once

#include "Enums.h"
#include "IDisposable.h"

using namespace System;
UsingFrameworkNamespace

namespace StillDesign
{
	namespace PhysX
	{
		ref class Cloth;
		ref class ClothMesh;
		ref class MeshData;
		ref class Core;
		value class GroupsMask;
		value class Bounds3;
		ref class Compartment;
		ref class ClothSplitPairData;
		
		public ref class ClothDescription : StillDesign::PhysX::IDisposable
		{
			public:
				virtual event EventHandler^ OnDisposing;
				virtual event EventHandler^ OnDisposed;
				
			private:
				NxClothDesc* _clothDesc;
				
				StillDesign::PhysX::ClothMesh^ _clothMesh;
				StillDesign::PhysX::MeshData^ _meshData;
				
				StillDesign::PhysX::Compartment^ _compartment;
				
				ClothSplitPairData^ _splitPairData;
				
				Object^ _userData;
			
			public:
				ClothDescription();
			internal:
				ClothDescription( NxClothDesc* description, StillDesign::PhysX::MeshData^ meshData );
			public:
				~ClothDescription();
			protected:
				!ClothDescription();
			private:
				void Create(); // Common constructor logic
			public:
				property bool IsDisposed
				{
					virtual bool get();
				}
				
			public:
				/// <summary>Returns true if the current settings are valid</summary>
				bool IsValid();
				/// <summary>(Re)sets the structure to the default</summary>
				void SetToDefault();
				
				/// <summary>The cooked cloth mesh</summary>
				property StillDesign::PhysX::ClothMesh^ ClothMesh
				{
					StillDesign::PhysX::ClothMesh^ get();
					void set( StillDesign::PhysX::ClothMesh^ value );
				}
				/// <summary>The buffers in meshData are used to communicate the dynamic data of the cloth back to the user</summary>
				property StillDesign::PhysX::MeshData^ MeshData
				{
					StillDesign::PhysX::MeshData^ get();
				}
				
				/// <summary>Gets or Sets the compartment to place the cloth in. Must be of type Cloth. A null compartment means creating a hardware cloth is done in the first available cloth compartment (a default cloth compartment is created if none exists). Software cloth with a null compartment is created in the scene proper</summary>
				property StillDesign::PhysX::Compartment^ Compartment
				{
					StillDesign::PhysX::Compartment^ get();
					void set( StillDesign::PhysX::Compartment^ value );
				}
				
				/// <summary>Gets or Sets the name of the cloth description</summary>
				property String^ Name
				{
					String^ get();
					void set( String^ value );
				}
				/// <summary>Gets or Sets the global pose of the cloth in the world</summary>
				property Matrix GlobalPose
				{
					Matrix get();
					void set( Matrix value );
				}
				
				/// <summary>Gets or Sets the thickness of the cloth</summary>
				property float Thickness
				{
					float get();
					void set( float value );
				}
				property float SelfCollisionThickness
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the density of the cloth (mass per area).</summary>
				property float Density
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the bending stiffness of the cloth in the range 0 to 1</summary>
				property float BendingStiffness
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the stretching stiffness of the cloth in the range 0 to 1</summary>
				property float StretchingStiffness
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the spring damping of the cloth in the range 0 to 1</summary>
				property float DampingCoefficient
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the friction coefficient in the range 0 to 1</summary>
				property float Friction
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the volume of air inside the mesh as volume = pressure * restVolume. Valid if the flag ClothFlag.Pressure is set</summary>
				property float Pressure
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the elongation factor that causes the cloth to tear. Valid if the flag ClothFlag.Tearable is set</summary>
				property float TearFactor
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the factor for the impulse transfer from cloth to colliding rigid bodies</summary>
				property float CollisionResponceCoefficient
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the factor for the impulse transfer from cloth to attached rigid bodies</summary>
				property float AttachmentResponseCoefficient
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets elongation factor that causes the attachment to tear. Valid if the ClothAttachmentFlag.Tearable is set in the attachment method</summary>
				property float AttachmentTearFactor
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the impulse transfer from this cloth to colliding fluids</summary>
				property float ToFluidResponseCoefficent
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the impulse transfer from colliding fluids to this cloth</summary>
				property float FromFluidResponseCoefficent
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets if the cloth moves partially in the frame of the attached actor if the ClothFlag.Ahere flag is set</summary>
				property float MinimumAdhereVelocity
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the solver iterations</summary>
				property int SolverIterations
				{
					int get();
					void set( int value );
				}
				/// <summary>Gets or Sets the external acceleration which affects all non attached particles of the cloth</summary>
				property Vector3 ExternalAcceleration
				{
					Vector3 get();
					void set( Vector3 value );
				}
				/// <summary>Gets or Sets the acceleration which acts normal to the cloth surface at each vertex</summary>
				property Vector3 WindAcceleration
				{
					Vector3 get();
					void set( Vector3 value );
				}
				/// <summary>Gets or Sets the cloth wake up counter</summary>
				property float WakeUpCounter
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the maximum linear velocity at which cloth can go to sleep</summary>
				property float SleepLinearVelocity
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets which collision group this cloth is part of</summary>
				property short CollisionGroup
				{
					short get();
					void set( short value );
				}
				/// <summary>Gets or Sets the 128-bit mask used for collision filtering</summary>
				property StillDesign::PhysX::GroupsMask GroupsMask
				{
					StillDesign::PhysX::GroupsMask get();
					void set( StillDesign::PhysX::GroupsMask value );
				}
				property short ForceFieldMaterial
				{
					short get();
					void set( short value );
				}
				/// <summary>Gets or Sets the volume outside of which cloth particle are automatically removed from the simulation. Valid if ClothFlag.ValidBounds is set</summary>
				property Bounds3 ValidBounds
				{
					Bounds3 get();
					void set( Bounds3 value );
				}
				/// <summary>Gets or Sets the parameter defines the size of grid cells for collision detection</summary>
				property float RelativeGridSpacing
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the flag bits</summary>
				property ClothFlag Flags
				{
					ClothFlag get();
					void set( ClothFlag value );
				}
				/// <summary>Gets or Sets how many iterations of the hierarchical solver to run at each time step</summary>
				property int HierarchicalSolverIterations
				{
					int get();
					void set( int value );
				}
				property float HardStretchLimitationFactor
				{
					float get();
					void set( float value );
				}
				property ClothSplitPairData^ SplitPairData
				{
					ClothSplitPairData^ get();
				}
				
				/// <summary>Gets or Sets an arbitrary 1:1 object</summary>
				property Object^ UserData
				{
					Object^ get();
					void set( Object^ value );
				}
				
			internal:
				property NxClothDesc* UnmanagedPointer
				{
					NxClothDesc* get();
				}
		};
	};
};