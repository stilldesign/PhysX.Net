#pragma once

#include "Enums.h"
#include "Ray.h"
#include "Element Collection.h"
#include "Groups Mask.h"

using namespace System;
UsingFrameworkNamespace

namespace StillDesign
{
	namespace PhysX
	{
		ref class Scene;
		ref class ClothRaycastResult;
		ref class Shape;
		ref class Actor;
		ref class MeshData;
		value class Bounds3;
		ref class ClothDescription;
		interface class IStreamWriter;
		interface class IStreamReader;
		ref class ClothMesh;
		ref class Core;
		ref class Compartment;
		
		public ref class Cloth : StillDesign::PhysX::IDisposable
		{
			public:
				virtual event EventHandler^ OnDisposing;
				virtual event EventHandler^ OnDisposed;
				
			private:
				NxCloth* _cloth;
				
				StillDesign::PhysX::Scene^ _scene;
				
				StillDesign::PhysX::MeshData^ _meshData;
				StillDesign::PhysX::ClothMesh^ _clothMesh;
				
				StillDesign::PhysX::Compartment^ _compartment;
				
				Object^ _userData;
			
			internal:
				Cloth( NxCloth* cloth, StillDesign::PhysX::MeshData^ meshData );
			public:
				~Cloth();
			protected:
				!Cloth();
			public:
				property bool IsDisposed
				{
					virtual bool get();
				}
			
			public:
				/// <summary>Saves the cloth descriptor</summary>
				ClothDescription^ SaveToDescription();
				/// <summary>Saves the current cloth state to a stream</summary>
				void SaveStateToStream( Stream^ stream );
				/// <summary>Saves the current cloth state to a stream</summary>
				void SaveStateToStream( Stream^ stream, bool permute );
				/// <summary>Loads the current cloth state from a stream</summary>
				void LoadStateFromStream( Stream^ stream );
				
				/// <summary>Applies a force (or impulse) defined in the global coordinate frame, to a particular vertex of the cloth</summary>
				void AddForceToVertex( Vector3 force, int vertexId );
				/// <summary>Applies a force (or impulse) defined in the global coordinate frame, to a particular vertex of the cloth</summary>
				void AddForceToVertex( Vector3 force, int vertexId, ForceMode forceMode );
				/// <summary>Applies a radial force (or impulse) at a particular position. All vertices within radius will be affected with a quadratic drop-off</summary>
				void AddForceAtPosition( Vector3 position, float magnitude, float radius );
				/// <summary>Applies a radial force (or impulse) at a particular position. All vertices within radius will be affected with a quadratic drop-off</summary>
				void AddForceAtPosition( Vector3 position, float magnitude, float radius, ForceMode forceMode );
				/// <summary>Applies a directed force (or impulse) at a particular position. All vertices within radius will be affected with a quadratic drop-off</summary>
				void AddDirectedForceAtPosition( Vector3 position, Vector3 force, float radius );
				/// <summary>Applies a directed force (or impulse) at a particular position. All vertices within radius will be affected with a quadratic drop-off. </summary>
				void AddDirectedForceAtPosition( Vector3 position, Vector3 force, float radius, ForceMode forceMode );
				
				/// <summary>Attaches the Cloth to a Shape. All Cloth Points Currently Inside the Shape are Attached</summary>
				void AttachToShape( Shape^ shape, ClothAttachmentFlag attachmentFlags );
				/// <summary>Attaches the Cloth to All Shapes, Currently Colliding</summary>
				void AttachToCollidingShapes( ClothAttachmentFlag attachmentFlags );
				/// <summary>Detaches the Cloth from a Shape it has been Attached to Before</summary>
				void DetachFromShape( Shape^ shape );
				/// <summary>Attaches a cloth vertex to a local position within a shape</summary>
				void AttachVertexToShape( int vertexIndex, Shape^ shape, Vector3 localPosition, ClothAttachmentFlag attachmentFlags );
				/// <summary>Attaches a cloth vertex to a position in world space</summary>
				void AttachVertexToGlobalPosition( int vertexIndex, Vector3 position );
				/// <summary>Frees a previously attached cloth point</summary>
				void FreeVertex( int vertexIndex );
				/// <summary>Attaches the cloth to an actor</summary>
				void AttachToCore( Actor^ actor, float impulseThreshold );
				/// <summary>Attaches the cloth to an actor</summary>
				void AttachToCore( Actor^ actor, float impulseThreshold, float penetrationDepth );
				/// <summary>Tears the cloth at a given vertex</summary>
				void TearVertex( int vertexIndex, Vector3 normal );
				/// <summary>Executes a raycast against the cloth</summary>
				ClothRaycastResult^ Raycast( Ray worldRay );
				/// <summary>Finds triangles touching the input bounds</summary>
				array<int>^ OverlapAABBTriangles( Bounds3 bounds );
				/// <summary>Queries the cloth for the currently interacting shapes. Must be called prior to SaveStateToStream in order for attachments and collisons to be saved</summary>
				int QueryShapePointers();
				/// <summary>Gets the byte size of the current cloth state</summary>
				int GetStateSizeInByte();
				
				/// <summary>Wakes up the cloth if it is sleeping</summary>
				void WakeUp();
				/// <summary>Wakes up the cloth if it is sleeping</summary>
				void WakeUp( float wakeCounterValue );
				/// <summary>Forces the cloth to sleep</summary>
				void Sleep();
				
				/// <summary>Changes the weight of a vertex in the cloth solver for a period of time</summary>
				/// <param name="vertexId">Index of the vertex</param>
				/// <param name="expirationTime">Time period where dominance will be active for this vertex</param>
				/// <param name="dominanceWeight">Dominance weight for this vertex</param>
				void DominateVertex( int vertexId, float expirationTime, float dominanceWeight );
				/// <summary>Return the attachment status of the given vertex</summary>
				/// <param name="vertexId">Index of the vertex.</param>
				ClothVertexAttachmentStatus GetVertexAttachmentStatus( int vertexId );
				/// <summary>Returns the pointer to an attached shape pointer of the given vertex</summary>
				/// <param name="vertexId">Index of the vertex</param>
				Shape^ GetVertexAttachmentShape( int vertexId );
				/// <summary>Returns the attachment position of the given vertex</summary>
				/// <param name="vertexId">Index of the vertex</param>
				Vector3 GetVertexAttachmentPosition( int vertexId );
				
				/// <summary>Gets the position of a particular vertex of the cloth</summary>
				/// <param name="vertexId">Index of the vertex</param>
				Vector3 GetVertexPosition( int vertexId );
				/// <summary>Sets the position of a particular vertex of the cloth</summary>
				/// <param name="vertexId">Index of the vertex</param>
				/// <param name="position">New position of the vertex</param>
				void SetVertexPosition( int vertexId, Vector3 position );
				/// <summary>Gets the velocity of a particular vertex of the cloth</summary>
				/// <param name="vertexId">Index of the vertex</param>
				Vector3 GetVertexVelocity( int vertexId );
				/// <summary>Sets the velocity of a particular vertex of the cloth</summary>
				/// <param name="vertexId">Index of the vertex</param>
				/// <param name="velocity">New velocity of the vertex</param>
				void SetVertexVelocity( int vertexId, Vector3 velocity );
				
				/// <summary>Get or Sets the Name of the Cloth</summary>
				property String^ Name
				{
					String^ get();
					void set( String^ value );
				}
				
				/// <summary>Gets the Scene the Cloth is Created in</summary>
				property StillDesign::PhysX::Scene^ Scene
				{
					StillDesign::PhysX::Scene^ get();
				}
				
				/// <summary>Gets the MeshData Which Contains the Vertices, Indices, Normals and Other Important Values</summary>
				property StillDesign::PhysX::MeshData^ MeshData
				{
					StillDesign::PhysX::MeshData^ get();
				}
				/// <summary>Returns the corresponding cloth mesh</summary>
				property StillDesign::PhysX::ClothMesh^ ClothMesh
				{
					StillDesign::PhysX::ClothMesh^ get();
				}
				
				/// <summary>Gets or Sets Retrieves the cloth's simulation compartment, as specified by the user at creation time</summary>
				property StillDesign::PhysX::Compartment^ Compartment
				{
					StillDesign::PhysX::Compartment^ get();
				}
				
				/// <summary>Gets or Sets the positions of the cloth</summary>
				property array<Vector3>^ ParticlePositions
				{
					array<Vector3>^ get();
					void set( array<Vector3>^ value );
				}
				/// <summary>Gets or Sets the velocities of the cloth</summary>
				property array<Vector3>^ ParticleVelocities
				{
					array<Vector3>^ get();
					void set( array<Vector3>^ value );
				}
				/// <summary>Gets the number of cloth particles</summary>
				property int ParticleCount
				{
					int get();
				}
				
				/// <summary>Gets or Sets which collision group this cloth is part of</summary>
				property short Group
				{
					short get();
					void set( short value );
				}
				/// <summary>Sets 128-bit mask used for collision filtering</summary>
				property StillDesign::PhysX::GroupsMask GroupsMask
				{
					StillDesign::PhysX::GroupsMask get();
					void set( StillDesign::PhysX::GroupsMask value );
				}
				
				/// <summary>Gets or Sets the flags</summary>
				property ClothFlag Flags
				{
					ClothFlag get();
					void set( ClothFlag value );
				}
				/// <summary>Get or Sets cloth thickness</summary>
				property float Thickness
				{
					float get();
					void set( float value );
				}
				/// <summary>Get or Sets cloth density</summary>
				property float Density
				{
					float get();
				}
				/// <summary>Gets the relative grid spacing for the broad phase</summary>
				property float RelativeGridSpacing
				{
					float get();
				}
				/// <summary>Gets or Sets the cloth bending stiffness in the range from 0 to 1. </summary>
				property float BendingStiffness
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the damping coefficient in the range from 0 to 1</summary>
				property float StretchingStiffness
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the damping coefficient in the range from 0 to 1</summary>
				property float DampingCoefficient
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the cloth friction coefficient in the range from 0 to 1</summary>
				property float Friction
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the cloth pressure coefficient (must be non negative)</summary>
				property float Pressure
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the cloth tear factor (must be larger than one)</summary>
				property float TearFactor
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the cloth attachment tear factor (must be larger than one)</summary>
				property float AttachmentTearFactor
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the collision response coefficient</summary>
				property float CollisionResponceCoefficient
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the attachment response coefficient</summary>
				property float AttachmentResponseCoefficient
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the response coefficient for collisions from fluids to this cloth</summary>
				property float FromFluidResponseCoefficient
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the response coefficient for collisions from this cloth to fluids</summary>
				property float ToFluidResponseCoefficient
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
				/// <summary>Gets or Sets the cloth solver iterations</summary>
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
				property Vector3 WindAcceleration
				{
					Vector3 get();
					void set( Vector3 value );
				}
				/// <summary>Gets or Sets the linear velocity below which a cloth may go to sleep</summary>
				property float SleepLinearVelocity
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the valid bounds of the cloth in world space</summary>
				property Bounds3 ValidBounds
				{
					Bounds3 get();
					void set( Bounds3 value );
				}
				/// <summary>Gets the world space AABB enclosing all cloth points</summary>
				property Bounds3 WorldBounds
				{
					Bounds3 get();
				}
				
				/// <summary>Get True if this cloth is sleeping</summary>
				property bool IsSleeping
				{
					bool get();
				}
				
				/// <summary>Gets or Sets an arbitrary 1:1 object</summary>
				property Object^ UserData
				{
					Object^ get();
					void set( Object^ value );
				}
			
			internal:
				property NxCloth* UnmanagedPointer
				{
					NxCloth* get();
				}
		};
		
		public ref class ClothRaycastResult : RaycastResult
		{
			private:
				int _vertexIndex;
			
			public:
				ClothRaycastResult( bool hit, Vector3 hitPosition, int vertexId );
				
				/// <summary>Gets the index to the nearest vertex hit by the raycast</summary>
				property int VertexIndex
				{
					int get();
				}
		};
	};
};