#pragma once

#include "ExtensionEnum.h"
#include <PxPhysics.h>
#include <PxDistanceJoint.h>
#include <PxRigidDynamic.h>

namespace PhysX
{
	ref class Scene;
	ref class SceneDesc;
	ref class Material;
	ref class TriangleMesh;
	ref class RigidDynamic;
	ref class Actor;
	ref class RigidStatic;
	ref class RigidActor;
	ref class ParticleSystem;
	ref class ErrorCallback;
	ref class DeformableMesh;
	ref class Stream;
	ref class Deformable;
	ref class DeformableDesc;
	ref class HeightFieldDesc;
	ref class HeightField;
	ref class ParticleFluid;
	ref class ParticleSystemDesc;
	ref class Foundation;
	ref class Cooking;
	ref class CookingParams;
	ref class Attachment;
	ref class Shape;
	
	namespace VisualDebugger
	{
		ref class Connection;
	};

	/// <summary>
	/// Abstract singleton factory class used for instancing objects in the Physics SDK.
	/// </summary>
	public ref class Physics : IDisposable
	{
		public:
			/// <summary>Raised before any disposing is performed.</summary>
			virtual event EventHandler^ OnDisposing;
			/// <summary>Raised once all disposing is performed.</summary>
			virtual event EventHandler^ OnDisposed;

		private:
			static bool _instantiated;

			PxPhysics* _physics;
			PxAllocatorCallback* _allocator;
			ErrorCallback^ _errorCallback;

			Foundation^ _foundation;

			List<Scene^>^ _scenes;
			List<Material^>^ _materials;
			List<RigidActor^>^ _rigidActors;
			List<ParticleSystem^>^ _particleSystems;
			List<ParticleFluid^>^ _particleFluids;
			List<Deformable^>^ _deformables;
			List<DeformableMesh^>^ _deformableMeshes;
			List<HeightField^>^ _heightFields;
			List<Cooking^>^ _cooks;
			List<TriangleMesh^>^ _triangleMeshes;

			Physics(PxPhysics* physics);
		public:
			static Physics();
			Physics([Optional] ErrorCallback^ errorCallback);
		private:
			void Init();
			void PostInit();
		public:
			~Physics();
		protected:
			!Physics();

		public:
			property bool Disposed
			{
				virtual bool get();
			}

			//

			/// <summary>
			/// Connect to pvd using a network socket. This blocks for at most inTimeoutInMillisecondsbefore returning a new connection (or nothing). PVD needs to be started before this call is made.
			/// </summary>
			/// <param name="host">Host in x.x.x.x network notation.</param>
			/// <param name="port">Port to connect to. The default is 5425.</param>
			/// <param name="timeout">How long to block waiting for a new connection.</param>
			/// <param name="checkApi">
			/// Whether to check the PVD network calls to ensure that if someone defines a property to be a
			/// float, a float is actually sent. This is extremely useful when creating new objects and
			/// implementing new debugger bindings.
			/// </param>
			/// <param name="flags">The type information you want sent over the connection.</param>
			VisualDebugger::Connection^ ConnectToRemoteDebugger(String^ host, [Optional] Nullable<int> port, [Optional] Nullable<TimeSpan> timeout, [Optional] Nullable<bool> checkApi, [Optional] Nullable<RemoteDebuggerConnectionFlags> flags);

			//

			property bool Instantiated
			{
				static bool get();
			}

			property PhysX::Foundation^ Foundation
			{
				PhysX::Foundation^ get();
			}

			#pragma region Scene
			/// <summary>
			///	Creates a scene. 
			/// The scene can then create its contained entities.
			/// </summary>
			/// <returns>The new scene object.</returns>
			Scene^ CreateScene();
			/// <summary>
			///	Creates a scene. 
			/// The scene can then create its contained entities.
			/// </summary>
			///	<param name="sceneDesc">Scene descriptor. See <see cref="SceneDesc" />.</param>
			/// <returns>The new scene object.</returns>
			Scene^ CreateScene(SceneDesc^ sceneDesc);

			/// <summary>Gets the collection of scenes</summary>
			property IEnumerable<Scene^>^ Scenes
			{
				IEnumerable<Scene^>^ get();
			}
			#pragma endregion

			#pragma region Material
			/// <summary>
			/// Creates a new material with default properties.
			/// </summary>
			/// <param name="staticFriction">The coefficient of static friction.</param>
			/// <param name="dynamicFriction">The coefficient of dynamic friction .</param>
			/// <param name="restitution">The coefficient of restitution.</param>
			/// <returns>The new material.</returns>
			Material^ CreateMaterial(float staticFriction, float dynamicFriction, float restitution);

			/// <summary>
			/// Gets the materials.
			/// </summary>
			property IEnumerable<Material^>^ Materials
			{
				IEnumerable<Material^>^ get();
			}
			#pragma endregion

			#pragma region Material
			/// <summary>
			/// Creates a triangle mesh object.
			/// This can then be instanced into PxShape objects.
			/// </summary>
			/// <param name="stream">The triangle mesh stream.</param>
			/// <returns>The new triangle mesh.</returns>
			TriangleMesh^ CreateTriangleMesh(System::IO::Stream^ stream);
			#pragma endregion

			#pragma region HeightField
			/// <summary>
			/// Creates a PxHeightField object.
			/// This can then be instanced into PxShape objects.
			/// </summary>
			/// <param name="desc">The descriptor to load the object from.</param>
			HeightField^ CreateHeightField(HeightFieldDesc^ desc);
			#pragma endregion

			#pragma region Rigid Actors
			/// <summary>
			///	Creates a dynamic rigid actor with the specified pose and all other fields initialized to their default values.
			/// </summary>
			/// <param name="pose">The initial pose of the actor. Must be a valid transform, or null. If null is passed in, Matrix.Identity will be used instead.</param>
			RigidDynamic^ CreateRigidDynamic([Optional] Nullable<Matrix> pose);

			/// <summary>
			///	Creates a static rigid actor with the specified pose and all other fields initialized to their default values.
			/// </summary>
			/// <param name="pose">The initial pose of the actor. Must be a valid transform, or null. If null is passed in, Matrix.Identity will be used instead.</param>
			RigidStatic^ CreateRigidStatic([Optional] Nullable<Matrix> pose);

			/// <summary>
			///	Gets the rigid actors.
			/// </summary>
			property IEnumerable<RigidActor^>^ RigidActors
			{
				IEnumerable<RigidActor^>^ get();
			}
			#pragma endregion

			#pragma region Particle System
			/// <summary>
			/// Creates a particle system.
			/// </summary>
			/// <param name="desc">Description of the particle system object to create. See <see cref="ParticleSystemDesc" />.</param>
			ParticleSystem^ CreateParticleSystem(ParticleSystemDesc^ desc);

			/// <summary>
			///	Gets the particle systems.
			/// </summary>
			property IEnumerable<ParticleSystem^>^ ParticleSystems
			{
				IEnumerable<ParticleSystem^>^ get();
			}
			#pragma endregion

			#pragma region Particle Fluid

			#pragma endregion

			#pragma region Deformable
			/// <summary>
			/// Creates a deformable.
			/// </summary>
			/// <param name="desc">Description of the deformable object to create.</param>
			Deformable^ CreateDeformable(DeformableDesc^ desc);

			/// <summary>
			/// Creates a deformable mesh from a cooked deformable mesh stored in a stream.
			/// Stream has to be created with PxCookDeformableMesh().
			/// </summary>
			DeformableMesh^ CreateDeformableMesh(System::IO::Stream^ stream);
			#pragma endregion

			#pragma region Cooking
			/// <summary>
			/// Create an instance of the cooking interface.
			/// </summary>
			Cooking^ CreateCooking([Optional] CookingParams^ parameters);

			/// <summary>
			/// Creates a deformable attachment.
			/// </summary>
			/// <param name="deformable">The deformable to attach.</param>
			/// <param name="shape">The shape to attach to ('0' for static attachments).</param>
			/// <param name="vertexIndices">The indices of the vertices to attach.</param>
			/// <param name="positions">The attachment positions in shape-local coordinates or world space for world attachments.</param>
			/// <param name="flags">Flags for each attached vertex: One or two way interaction, tearable or non-tearable.</param>
			Attachment^ CreateAttachment(Deformable^ deformable, Shape^ shape, array<int>^ vertexIndices, array<Vector3>^ positions, array<int>^ flags);
			#pragma endregion

			//

		internal:
			property PxPhysics* UnmanagedPointer
			{
				PxPhysics* get();
			}
	};
};