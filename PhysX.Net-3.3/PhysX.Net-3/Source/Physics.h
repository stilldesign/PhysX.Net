#pragma once

#include "ClothEnum.h"
#include "ClothParticle.h"
#include "JointEnum.h"

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
	ref class HeightFieldDesc;
	ref class HeightField;
	ref class ParticleFluid;
	ref class Foundation;
	ref class Cooking;
	ref class CookingParams;
	ref class Attachment;
	ref class Shape;
	ref class ParticleFluidDesc;
	ref class Collection;
	ref class ConvexMesh;
	ref class Constraint;
	ref class ConstraintConnector;
	ref class ConstraintShaderTable;
	ref class OutputStream;
	ref class VehicleSDK;
	ref class Cloth;
	ref class ClothFabric;
	ref class ClothCollisionData;
	ref class ClothFabricDesc;
	ref class Articulation;
	ref class Aggregate;
	ref class Joint;


	namespace VisualDebugger
	{
		ref class Connection;
		ref class ConnectionManager;
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

		Foundation^ _foundation;

		VehicleSDK^ _vehicleSDK;

		PhysX::VisualDebugger::ConnectionManager^ _connectionManager;

	public:
		static Physics();

		/// <summary>Creates a new instance of the Physics class.</summary>
		Physics(PhysX::Foundation^ foundation, [Optional] bool checkRuntimeFiles);
	public:
		~Physics();
	protected:
		!Physics();
	public:
		property bool Disposed
		{
			virtual bool get();
		}

	private:
		void Init();
		void PostInit(Foundation^ owner);

	public:
		property bool Instantiated
		{
			static bool get();
		}

		/// <summary>
		///	Gets the parent foundation of the physics instance.
		/// </summary>
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

		#pragma region Triangle Mesh
		/// <summary>
		/// Creates a triangle mesh object.
		/// This can then be instanced into PxShape objects.
		/// </summary>
		/// <param name="stream">The triangle mesh stream.</param>
		/// <returns>The new triangle mesh.</returns>
		TriangleMesh^ CreateTriangleMesh(System::IO::Stream^ stream);
		#pragma endregion

		#pragma region Convex Mesh
		/// <summary>
		/// Creates a convex mesh object.
		/// This can then be instanced into PxShape objects.
		/// </summary>
		/// <param name="stream">The stream to load the convex mesh from.</param>
		/// <returns>The new convex mesh.</returns>
		ConvexMesh^ CreateConvexMesh(System::IO::Stream^ stream);
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

		#pragma region Joints
		/// <summary>
		/// Creates a joint.
		/// </summary>
		/// <param name="type">The type of the joint.</param>
		/// <param name="actor0">An actor to which the joint is attached. Null may be used to attach the joint to a specific point in the world frame.</param>
		/// <param name="">The position and orientation of the joint relative to actor0.</param>
		/// <param name="actor1">An actor to which the joint is attached. Null may be used to attach the joint to a specific point in the world frame.</param>
		/// <param name="">The position and orientation of the joint relative to actor1.</param>
		/// <returns>A joint of the specified type.</returns>
		Joint^ CreateJoint(JointType type, RigidActor^ actor0, Matrix localFrame0, RigidActor^ actor1, Matrix localFrame1);

		/// <summary>
		/// Creates a joint.
		/// </summary>
		/// <param name="type">The type of the joint.</param>
		/// <param name="actor0">An actor to which the joint is attached. Null may be used to attach the joint to a specific point in the world frame.</param>
		/// <param name="">The position and orientation of the joint relative to actor0.</param>
		/// <param name="actor1">An actor to which the joint is attached. Null may be used to attach the joint to a specific point in the world frame.</param>
		/// <param name="">The position and orientation of the joint relative to actor1.</param>
		/// <returns>A joint of the specified type.</returns>
		generic<typename T> where T : Joint
			T CreateJoint(RigidActor^ actor0, Matrix localFrame0, RigidActor^ actor1, Matrix localFrame1);

		#pragma endregion

		#pragma region Particle System
		/// <summary>
		/// Creates a particle system.
		/// </summary>
		ParticleSystem^ CreateParticleSystem(int maxParticles);
		/// <summary>
		/// Creates a particle system.
		/// </summary>
		ParticleSystem^ CreateParticleSystem(int maxParticles, bool perParticleRestOffset);

		/// <summary>
		///	Gets the particle systems.
		/// </summary>
		property IEnumerable<ParticleSystem^>^ ParticleSystems
		{
			IEnumerable<ParticleSystem^>^ get();
		}
		#pragma endregion

		#pragma region Particle Fluid
		/// <summary>
		/// Creates a particle fluid.
		/// </summary>
		/// <param name="maximumParticles">The maximum number of particles that may be placed in the particle fluid.</param>
		ParticleFluid^ CreateParticleFluid(int maximumParticles);
		/// <summary>
		/// Creates a particle fluid.
		/// </summary>
		/// <param name="maximumParticles">The maximum number of particles that may be placed in the particle fluid.</param>
		/// <param name="perParticleRestOffset">Whether the ParticleFluid supports perParticleRestOffset.</param>
		ParticleFluid^ CreateParticleFluid(int maximumParticles, bool perParticleRestOffset);

		/// <summary>
		/// Gets the particle fluids.
		/// </summary>
		property array<ParticleFluid^>^ ParticleFluids
		{
			array<ParticleFluid^>^ get();
		}
		#pragma endregion

		#pragma region Cooking
		/// <summary>
		/// Create an instance of the cooking interface.
		/// </summary>
		Cooking^ CreateCooking([Optional] CookingParams^ parameters);
		#pragma endregion

		#pragma region Collection
		/// <summary>
		/// Creates a collection object.
		/// Objects can only be serialized or deserialized through a collection. For serialization, users must add
		/// objects to the collection and serialize the collection as a whole. For deserialization, the system
		/// gives back a collection of deserialized objects to users.
		/// </summary>
		Collection^ CreateCollection();
		#pragma endregion

		#pragma region Remote Debugger
		/// <summary>
		/// The factory manager allows notifications when a new connection to pvd is made.
		/// It also allows the users to specify a scheme to handle the read-side of a
		/// network connection. By default, the SDK specifies that a thread gets launched
		/// which blocks reading on the network socket.
		/// </summary>
		property PhysX::VisualDebugger::ConnectionManager^ PvdConnectionManager
		{
			PhysX::VisualDebugger::ConnectionManager^ get();
		}

		/// <summary>
		/// The factory manager allows notifications when a new connection to pvd is made.
		/// It also allows the users to specify a scheme to handle the read-side of a
		/// network connection. By default, the SDK specifies that a thread gets launched
		/// which blocks reading on the network socket.
		/// </summary>
		/// <remarks>This property is simply an alias to Physics.PvdConnectionManager.</remarks>
		property PhysX::VisualDebugger::ConnectionManager^ RemoteDebugger
		{
			PhysX::VisualDebugger::ConnectionManager^ get();
		}
		#pragma endregion

		#pragma region Vehicle
		property PhysX::VehicleSDK^ VehicleSDK
		{
			PhysX::VehicleSDK^ get();
		}
		#pragma endregion

		Constraint^ CreateConstraint(RigidActor^ actor0, RigidActor^ actor1, ConstraintConnector^ connector, ConstraintShaderTable^ shaders, int dataSize);

		#pragma region Cloth
		/// <summary>
		/// Creates a cloth.
		/// </summary>
		/// <param name="globalPose">The world space transform of the cloth.</param>
		/// <param name="fabric">The fabric the cloth should use.</param>
		/// <param name="particles">Particle definition buffer. The size of the buffer has to match the number of points of the cloth mesh which elements must match with the provided.</param>
		/// <param name="collisionData">Collision information.</param>
		/// <param name="flags">Cloth flags.</param>
		Cloth^ CreateCloth(Matrix globalPose, ClothFabric^ fabric, array<ClothParticle>^ particles, ClothFlag flags);

		/// <summary>
		/// Gets cloths.
		/// </summary>
		property IEnumerable<Cloth^>^ Cloths
		{
			IEnumerable<Cloth^>^ get();
		}

		/// <summary>
		/// Creates a cloth fabric object.
		/// This can then be instanced into PxCloth objects.
		/// </summary>
		/// <param name="cookedStream">The stream to load the cloth fabric from.</param>
		ClothFabric^ CreateClothFabric(System::IO::Stream^ cookedStream);
		/// <summary>
		/// Creates a cloth fabric object from particle connectivity and restlength information.
		/// This can then be instanced into PxCloth objects.
		/// Note: We recommended using PxCooking.cookClothFabric() to create cloth fabrics from meshes and then
		/// using createClothFabric(const PxInputStream& stream). This method should only be used if you need
		/// to provide fully customized particle fiber/connectivity information for your fabric or if you did
		/// custom cloth fabric serialization and want to deserialize.
		/// </summary>
		ClothFabric^ CreateClothFabric(ClothFabricDesc^ desc);

		/// <summary>
		/// Gets cloth fabrics.
		/// </summary>
		property IEnumerable<ClothFabric^>^ ClothFabrics
		{
			IEnumerable<ClothFabric^>^ get();
		}
		#pragma endregion

		#pragma region Articulation
		Articulation^ CreateArticulation();
		#pragma endregion
		
		#pragma region Aggregate
		Aggregate^ CreateAggregate(int maximumSize, bool enableSelfCollision);
		#pragma endregion

	internal:
		property PxPhysics* UnmanagedPointer
		{
			PxPhysics* get();
		}
	};
};