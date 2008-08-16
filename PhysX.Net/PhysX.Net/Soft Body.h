#pragma once

#include "Enums.h"
#include "Bounds.h"
#include "IDisposable.h"
#include "Ray.h"

UsingFrameworkNamespace
using namespace System;
using namespace System::Runtime::InteropServices;

namespace StillDesign
{
	namespace PhysX
	{
		ref class SoftBodyMesh;
		ref class SoftBodyMeshDescription;
		ref class MeshData;
		value class GroupsMask;
		ref class Scene;
		ref class Shape;
		interface class IStreamWriter;
		interface class IStreamReader;
		value class Ray;
		ref class SoftBodyDescription;
		ref class Compartment;
		ref class SoftBodySplitPairData;
		
		public ref class SoftBody : StillDesign::PhysX::IDisposable
		{
			public:
				ref class SoftBodyRaycastResult;
			
			public:
				virtual event EventHandler^ onDisposing;
				virtual event EventHandler^ onDisposed;
				
			private:
				NxSoftBody* _softBody;
				
				StillDesign::PhysX::Scene^ _scene;
				
				StillDesign::PhysX::SoftBodyMesh^ _mesh;
				StillDesign::PhysX::MeshData^ _meshData;
				SoftBodySplitPairData^ _splitPairData;
				
				StillDesign::PhysX::Compartment^ _compartment;
				
				Object^ _userData;
			
			internal:
				SoftBody( NxSoftBody* softBody, StillDesign::PhysX::MeshData^ meshData, SoftBodySplitPairData^ splitPairData );
			public:
				~SoftBody();
			protected:
				!SoftBody();
			public:
				property bool IsDisposed
				{
					virtual bool get();
				}
			
			public:
				/// <summary>Saves the soft body descriptor</summary>
				SoftBodyDescription^ SaveToDescription();
				
				/// <summary>Gets the positions of the soft body</summary>
				array<Vector3>^ GetPositions();
				/// <summary>Sets the positions of the soft body</summary>
				/// <param name="value">The user supplied buffer containing all positions for the soft body</param>
				void SetPositions( array<Vector3>^ value );
				/// <summary>Gets the position of a particular vertex of the soft body</summary>
				/// <param name="particleIndex">Index of the vertex</param>
				Vector3 GetPosition( int particleIndex );
				/// <summary>Sets the position of a particular vertex of the soft body</summary>
				/// <param name="particleIndex">New position of the vertex</param>
				/// <param name="position">Index of the vertex</param>
				void SetPosition( int particleIndex, Vector3 position );
				
				/// <summary>Gets the velocities of the soft body</summary>
				array<Vector3>^ GetVelocities();
				/// <summary>Sets the velocities of the soft body</summary>
				/// <param name="value">The user supplied buffer containing all velocities for the soft body</param>
				void SetVelocities( array<Vector3>^ value );
				/// <summary>Gets the velocity of a particular vertex of the soft body</summary>
				/// <param name="particleIndex">Index of the vertex</param>
				Vector3 GetVelocity( int particleIndex );
				/// <summary>Sets the velocity of a particular vertex of the soft body</summary>
				/// <param name="particleIndex">Index of the vertex</param>
				/// <param name="velocity">New velocity of the vertex</param>
				void SetVelocity( int particleIndex, Vector3 velocity );
				
				/// <summary>Attaches the soft body to a shape. All soft body vertices currently inside the shape are attached</summary>
				/// <param name="shape">Shape to which the soft body should be attached to</param>
				/// <param name="attachmentFlags">One or two way interaction, tearable or non-tearable</param>
				void AttachToShape( Shape^ shape, SoftBodyAttachmentFlag attachmentFlags );
				/// <summary>Attaches the soft body to all shapes, currently colliding</summary>
				/// <param name="attachmentFlags">One or two way interaction, tearable or non-tearable</param>
				void AttachToCollidingShapes( int attachmentFlags );
				/// <summary>Detaches the soft body from a shape it has been attached to before</summary>
				/// <param name="shape">Shape from which the soft body should be detached</param>
				void DetachFromShape( Shape^ shape );
				/// <summary>Attaches a soft body vertex to a local position within a shape</summary>
				/// <param name="vertexId">Index of the vertex to attach</param>
				/// <param name="shape">Shape to attach the vertex to</param>
				/// <param name="localPosition">The position relative to the pose of the shape</param>
				/// <param name="attachmentFlags">One or two way interaction, tearable or non-tearable</param>
				void AttachVertexToShape( int vertexId, Shape^ shape, Vector3 localPosition, SoftBodyAttachmentFlag attachmentFlags );
				/// <summary>Attaches a soft body vertex to a position in world space</summary>
				/// <param name="vertexId">Index of the vertex to attach</param>
				/// <param name="globalPosition">The position in world space</param>
				void AttachVertexToGlobalPosition( int vertexId, Vector3 globalPosition );
				/// <summary>Frees a previously attached soft body vertex</summary>
				/// <param name="vertexId">Index of the vertex to free</param>
				void FreeVertex( int vertexId );
				/// <summary>[Experimental] Tears the soft body at a given vertex</summary>
				/// <param name="vertexId">Index of the vertex to tear</param>
				/// <param name="normal">The normal of the split plane</param>
				void TearVertex( int vertexId, Vector3 normal );
				/// <summary>Executes a raycast against the soft body</summary>
				/// <param name="worldRay">The ray in world space</param>
				SoftBodyRaycastResult^ Raycast( StillDesign::PhysX::Ray worldRay );
				
				/// <summary>Queries the soft body for the currently interacting shapes. Must be called prior to SaveStateToStream in order for attachments and collisons to be saved</summary>
				int QueryShapePointers();
				
				/// <summary>Gets shape currently interacting with the SoftBody</summary>
				array<Shape^>^ GetInteractingShapes();
				void SetInteractingShapes( array<Shape^>^ shapes );
				
				/// <summary>Gets the byte size of the current soft body state</summary>
				int GetStateByteSize();
				void SaveStateToStream( Stream^ stream );
				void SaveStateToStream( Stream^ stream, bool permute );
				void LoadStateFromStream( Stream^ stream );
				
				//
				
				/// <summary>Gets the Scene the SoftBody is owned by</summary>
				property StillDesign::PhysX::Scene^ Scene
				{
					StillDesign::PhysX::Scene^ get();
				}
				
				property StillDesign::PhysX::Compartment^ Compartment
				{
					StillDesign::PhysX::Compartment^ get();
				}
				
				/// <summary>Gets the SoftBodyMesh</summary>
				property StillDesign::PhysX::SoftBodyMesh^ SoftBodyMesh
				{
					StillDesign::PhysX::SoftBodyMesh^ get();
				}
				
				/// <summary>Gets or Sets the name of the SoftBody</summary>
				property String^ Name
				{
					String^ get();
					void set( String^ value );
				}
				
				/// <summary>Gets the number of soft body particles</summary>
				property int NumberOfParticles
				{
					int get();
				}
				
				/// <summary>Gets the soft body particle radius</summary>
				property float ParticleRadius
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets the soft body density</summary>
				property float Density
				{
					float get();
				}
				/// <summary>Gets the soft body volume stiffness</summary>
				property float VolumeStiffness
				{
					float get();
					void set( float value );
				}
				/// <summary>Retrieves the soft body stretching stiffness</summary>
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
				property float SleepLinearVelocity
				{
					float get();
					void set( float value );
				}
				property StillDesign::PhysX::MeshData^ MeshData
				{
					StillDesign::PhysX::MeshData^ get();
					void set( StillDesign::PhysX::MeshData^ value );
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
				property Bounds3 ValidBounds
				{
					Bounds3 get();
					void set( Bounds3 value );
				}
				property float RelativeGridSpacing
				{
					float get();
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
				property NxSoftBody* UnmanagedPointer
				{
					NxSoftBody* get();
				}
				
				//
				
			public:
				ref class SoftBodyRaycastResult : RaycastResult
				{
					private:
						int _vertexID;
					
					public:
						SoftBodyRaycastResult( bool hit, Vector3 hitPosition, int vertexID );
						
						/// <summary>Index of the nearest vertex hit by the raycast</summary>
						property int VertexID
						{
							int get();
						}
				};
		};
	};
};