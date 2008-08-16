#pragma once

#include "Enums.h"
#include "Bounds.h"

UsingFrameworkNamespace
using namespace System;

namespace StillDesign
{
	namespace PhysX
	{
		ref class SoftBodyMesh;
		ref class MeshData;
		value class GroupsMask;
		ref class Compartment;
		ref class SoftBodySplitPairData;
		
		public ref class SoftBodyDescription
		{
			private:
				NxSoftBodyDesc* _desc;
				
				StillDesign::PhysX::SoftBodyMesh^ _mesh;
				StillDesign::PhysX::MeshData^ _meshData;
				SoftBodySplitPairData^ _splitPairData;
				
				StillDesign::PhysX::Compartment^ _compartment;
				
				Object^ _userData;
				
			public:
				SoftBodyDescription();
			internal:
				SoftBodyDescription( NxSoftBodyDesc* desc, StillDesign::PhysX::MeshData^ meshData );
			public:
				~SoftBodyDescription();
			protected:
				!SoftBodyDescription();
				
			public:
				void SetToDefault();
				bool IsValid();
				
				/// <summary>Gets or Sets cooked soft body mesh</summary>
				property StillDesign::PhysX::SoftBodyMesh^ SoftBodyMesh
				{
					StillDesign::PhysX::SoftBodyMesh^ get();
					void set( StillDesign::PhysX::SoftBodyMesh^ value );
				}
				/// <summary>Gets or Sets the compartment to place the soft body in. The soft body feature currently uses the cloth simulation, so this must be of type SoftBody (or Cloth, since cloth and softbody currently use the same compartments). A null compartment means creating the soft body in the first available cloth compartment (a default cloth compartment is created if none exists). A software soft body with a NULL compartment is created in the scene on which CreateSoftBody() is called</summary>
				property StillDesign::PhysX::Compartment^ Compartment
				{
					StillDesign::PhysX::Compartment^ get();
					void set( StillDesign::PhysX::Compartment^ value );
				}
				
				property String^ Name
				{
					String^ get();
					void set( String^ value );
				}
				
				property Matrix GlobalPose
				{
					Matrix get();
					void set( Matrix value );
				}
				property float ParticleRadius
				{
					float get();
					void set( float value );
				}
				property float Density
				{
					float get();
					void set( float value );
				}
				property float VolumeStiffness
				{
					float get();
					void set( float value );
				}
				property float StretchingStiffness
				{
					float get();
					void set( float value );
				}
				property float DampingStiffness
				{
					float get();
					void set( float value );
				}
				property float Friction
				{
					float get();
					void set( float value );
				}
				property float TearFactor
				{
					float get();
					void set( float value );
				}
				property float CollisionResponseCoefficient
				{
					float get();
					void set( float value );
				}
				property float AttachmentResponseCoefficient
				{
					float get();
					void set( float value );
				}
				property float AttachmentTearFactor
				{
					float get();
					void set( float value );
				}
				property float ToFluidResponseCoefficient
				{
					float get();
					void set( float value );
				}
				property float FromFluidResponseCoefficient
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
				property int SolverIterations
				{
					int get();
					void set( int value );
				}
				property Vector3 ExternalAcceleration
				{
					Vector3 get();
					void set( Vector3 value );
				}
				property float WakeUpCounter
				{
					float get();
					void set( float value );
				}
				property float SleepLinearVelocity
				{
					float get();
					void set( float value );
				}
				property StillDesign::PhysX::MeshData^ MeshData
				{
					StillDesign::PhysX::MeshData^ get();
				}
				property short CollisionGroup
				{
					short get();
					void set( short value );
				}
				property StillDesign::PhysX::GroupsMask GroupsMask
				{
					StillDesign::PhysX::GroupsMask get();
					void set( StillDesign::PhysX::GroupsMask value );
				}
				property SoftBodySplitPairData^ SplitPairData
				{
					SoftBodySplitPairData^ get();
				}
				property short ForceFieldMaterial
				{
					short get();
					void set( short value );
				}
				property Bounds3 ValidBounds
				{
					Bounds3 get();
					void set( Bounds3 value );
				}
				property float RelativeGridSpacing
				{
					float get();
					void set( float value );
				}
				property SoftBodyFlag Flags
				{
					SoftBodyFlag get();
					void set( SoftBodyFlag value );
				}
				
				property Object^ UserData
				{
					Object^ get();
					void set( Object^ value );
				}
				
			internal:
				property NxSoftBodyDesc* UnmanagedPointer
				{
					NxSoftBodyDesc* get();
				}
		};
	};
};