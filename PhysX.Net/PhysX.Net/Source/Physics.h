#pragma once

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
	ref class ErrorCallback;
	ref class HeightFieldDesc;
	ref class HeightField;
	ref class Foundation;
	ref class Cooking;
	ref class CookingParams;
	ref class Attachment;
	ref class Shape;
	ref class Collection;
	ref class ConvexMesh;
	ref class Constraint;
	ref class ConstraintConnector;
	ref class ConstraintShaderTable;
	ref class OutputStream;
	ref class VehicleSDK;
	ref class Articulation;
	ref class Aggregate;
	ref class Joint;


	namespace VisualDebugger
	{
		ref class Connection;
		ref class Pvd;
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

		event Action<Material^>^ OnMaterialAdded;
		event Action<Material^>^ OnMaterialRemoved;

	private:
		static bool _instantiated;

		PxPhysics* _physics;

		Foundation^ _foundation;

		VehicleSDK^ _vehicleSDK;

		PhysX::VisualDebugger::Pvd^ _pvd;

	public:
		static Physics();

		/// <summary>Creates a new instance of the Physics class.</summary>
		Physics(PhysX::Foundation^ foundation, [Optional] bool checkRuntimeFiles, [Optional] PhysX::VisualDebugger::Pvd^ pvd);
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

		void OnObjectTableAdded(Object^ sender, ObjectTableEventArgs^ e);
		void OnObjectTableRemoved(Object^ sender, ObjectTableEventArgs^ e);

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
		property array<Scene^>^ Scenes
		{
			array<Scene^>^ get();
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
		property array<Material^>^ Materials
		{
			array<Material^>^ get();
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

		/// <summary>
		/// Gets the triangle mesh.
		/// </summary>
		property array<PhysX::TriangleMesh^>^ TriangleMesh
		{
			array<PhysX::TriangleMesh^>^ get();
		}
		#pragma endregion

		#pragma region Convex Mesh
		/// <summary>
		/// Creates a convex mesh object.
		/// This can then be instanced into PxShape objects.
		/// </summary>
		/// <param name="stream">The stream to load the convex mesh from.</param>
		/// <returns>The new convex mesh.</returns>
		ConvexMesh^ CreateConvexMesh(System::IO::Stream^ stream);

		/// <summary>
		/// Gets the convex mesh.
		/// </summary>
		property array<PhysX::ConvexMesh^>^ ConvexMesh
		{
			array<PhysX::ConvexMesh^>^ get();
		}
		#pragma endregion

		#pragma region HeightField
		/// <summary>
		/// Creates a height field object.
		/// This can then be instanced into Shape objects.
		/// </summary>
		/// <param name="stream">The stream to load the height field from.</param>
		HeightField^ CreateHeightField(System::IO::Stream^ stream);

		/// <summary>
		/// Gets the height field.
		/// </summary>
		property array<PhysX::HeightField^>^ HeightFields
		{
			array<PhysX::HeightField^>^ get();
		}
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
		property array<RigidActor^>^ RigidActors
		{
			array<RigidActor^>^ get();
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
		/// <param name="localFrame0">The position and orientation of the joint relative to actor0.</param>
		/// <param name="actor1">An actor to which the joint is attached. Null may be used to attach the joint to a specific point in the world frame.</param>
		/// <param name="localFrame1">The position and orientation of the joint relative to actor1.</param>
		/// <returns>A joint of the specified type.</returns>
		generic<typename T> where T : Joint
			T CreateJoint(RigidActor^ actor0, Matrix localFrame0, RigidActor^ actor1, Matrix localFrame1);

		/// <summary>
		/// Gets the collection of joints.
		/// </summary>
		property array<Joint^>^ Joints
		{
			array<Joint^>^ get();
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

		#pragma region PVD
		/// <summary>
		/// The factory manager allows notifications when a new connection to pvd is made.
		/// It also allows the users to specify a scheme to handle the read-side of a
		/// network connection. By default, the SDK specifies that a thread gets launched
		/// which blocks reading on the network socket.
		/// </summary>
		property PhysX::VisualDebugger::Pvd^ Pvd
		{
			PhysX::VisualDebugger::Pvd^ get();
		}
		#pragma endregion

		#pragma region Vehicle
		property PhysX::VehicleSDK^ VehicleSDK
		{
			PhysX::VehicleSDK^ get();
		}
		#pragma endregion

		Constraint^ CreateConstraint(RigidActor^ actor0, RigidActor^ actor1, ConstraintConnector^ connector, ConstraintShaderTable^ shaders, int dataSize);

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