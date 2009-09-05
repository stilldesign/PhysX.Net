#pragma once

#include "Enums.h"
#include "IDisposable.h"
#include "Material.h"
#include "Ray.h"
#include "Raycast Hit.h"
#include "Raycast Reporting.h"
#include "Element Collection.h"
#include "Actor.h"
#include "Joint.h"
#include "Cloth.h"
#include "Controller Manager.h"
#include "Fluid.h"
#include "Force Field.h"
#include "Triangle Mesh.h"
#include "Controller Manager.h"
#include "Soft Body.h"
#include "Compartment.h"
#include "Active Transform.h"
#include "Actor Group Pair.h"
#include "Force Field Linear Kernel.h"

using namespace System;
using namespace System::Collections::Generic;

UsingFrameworkNamespace

class NxScene;

namespace StillDesign
{
	namespace PhysX
	{
		ref class Core;
		ref class SceneDescription;
		ref class Material;
		value class Sphere;
		value class SceneTimingInformation;
		ref class SceneStatistics;
		ref class SceneLimits;
		ref class Shape;
		ref class DebugRenderable;
		ref class ActorDescription;
		ref class Joint;
		ref class JointDescription;
		ref class Cloth;
		ref class ClothDescription;
		ref class ForceField;
		ref class ForceFieldDescription;
		//ref class ImplicitScreenMesh;
		//ref class ImplicitScreenMeshDescription;
		ref class Fluid;
		ref class FluidDescription;
		ref class TriangleMesh;
		interface class IStreamReader;
		ref class Controller;
		ref class SweepCache;
		ref class SoftBodyDescription;
		ref class Compartment;
		ref class UserNotify;
		ref class FluidUserNotify;
		ref class UserContactModify;
		ref class UserTriggerReport;
		ref class UserContactReport;
		ref class UserEntitySweepQueryHitReport;
		ref class UserEntityShapeReport;
		ref class UserActorPairFiltering;
		ref class Compartment;
		ref class PairFlag;
		value class ConstraintDominance;
		ref class ForceFieldLinearKernelDescription;
		
		/// <summary>A scene is a collection of bodies, constraints, and effectors which can interact</summary>
		public ref class Scene : StillDesign::PhysX::IDisposable
		{
			private:
				ref class RaycastReport : UserRaycastReport
				{
					private:
						System::Collections::Generic::List<RaycastHit^>^ _hits;
					
					public:
						RaycastReport();
						
						virtual bool OnHit( RaycastHit^ hit ) override;
						
						property System::Collections::Generic::List<RaycastHit^>^ Hits
						{
							System::Collections::Generic::List<RaycastHit^>^ get();
						};
				};
				
			public:
				/// <summary>Raised before any disposing is performed</summary>
				virtual event EventHandler^ OnDisposing;
				/// <summary>Raised once all disposing is performed</summary>
				virtual event EventHandler^ OnDisposed;
				
			private:
				NxScene* _scene;
				Core^ _core;
				
				Material^ _defaultMaterial;
				
				ElementCollection< Compartment^ >^ _compartments;
				ElementCollection< Actor^ >^ _actors;
				ElementCollection< Material^ >^ _materials;
				ElementCollection< Joint^ >^ _joints;
				ElementCollection< Cloth^ >^ _cloths;
				ElementCollection< ForceField^ >^ _forceFields;
				ElementCollection< ForceFieldLinearKernel^ >^ _forceFieldLinearKernels;
				ElementCollection< ForceFieldShapeGroup^ >^ _forceFieldShapeGroups;
				ElementCollection< ControllerManager^ >^ _controllerManagers;
				ElementCollection< Fluid^ >^ _fluids;
				ElementCollection< SoftBody^ >^ _softBodies;
				
				StillDesign::PhysX::UserNotify^ _userNotify;
				StillDesign::PhysX::FluidUserNotify^ _fluidUserNotify;
				StillDesign::PhysX::UserContactModify^ _userContactModify;
				StillDesign::PhysX::UserContactReport^ _userContactReport;
				StillDesign::PhysX::UserTriggerReport^ _userTriggerReport;
				StillDesign::PhysX::UserActorPairFiltering^ _userActorPairFiltering;
				
				String^ _name;
				
				Object^ _userData;
				
			internal:
				Scene( NxScene* scene );
			public:
				~Scene();
			protected:
				!Scene();
			public:
				/// <summary>Is the Scene Disposed</summary>
				property bool IsDisposed
				{
					virtual bool get();
				}
				
			internal:
				Actor^ AddActor( NxActor* actor );
				Material^ AddMaterial( NxMaterial* material );
				Joint^ AddJoint( NxJoint* joint );
				Cloth^ AddCloth( NxCloth* cloth );
				ForceField^ AddForceField( NxForceField* forceField );
				ControllerManager^ AddControllerManager( NxControllerManager* manager );
				Fluid^ AddFluid( NxFluid* fluid );
				ForceFieldLinearKernel^ AddForceFieldLinearKernel( NxForceFieldLinearKernel* kernel );
				ForceFieldShapeGroup^ AddForceFieldShapeGroup( NxForceFieldShapeGroup* group );
				SoftBody^ AddSoftBody( NxSoftBody* softBody );
				
			public:
				/// <summary>Saves a description of this scene</summary>
				SceneDescription^ SaveToDescription();
				
				/// <summary>Creates an Actor in this scene</summary>
				Actor^ CreateActor( ActorDescription^ actorDescription );
				/// <summary>Creates a Material in this scene</summary>
				Material^ CreateMaterial( MaterialDescription^ materialDescription );
				generic<class T>
				where T : Joint
				T CreateJoint( JointDescription^ jointDescription );
				/// <summary>Creates a Joint in this scene</summary>
				Joint^ CreateJoint( JointDescription^ jointDescription );
				/// <summary>Creates a Cloth in this scene</summary>
				Cloth^ CreateCloth( ClothDescription^ clothDescription );
				/// <summary>Creates an Force Field in this scene</summary>
				ForceField^ CreateForceField( ForceFieldDescription^ forceFieldDescription );
				/// <summary>Creates a Controller Management in this scene</summary>
				ControllerManager^ CreateControllerManager();
				/// <summary>Creates a Fluid in this scene</summary>
				Fluid^ CreateFluid( FluidDescription^ fluidDescription );
				ForceFieldLinearKernel^ CreateForceFieldLinearKernel( ForceFieldLinearKernelDescription^ kernelDescription );
				short CreateForceFieldMaterial();
				void ReleaseForceFieldMaterial( short materialIndex );
				short CreateForceFieldVariety();
				void ReleaseForceFieldVariety( short varietyIndex );
				ForceFieldShapeGroup^ CreateForceFieldShapeGroup( ForceFieldShapeGroupDescription^ groupDescription );
				
				/// <summary>Creates a Sweep Cache in this scene</summary>
				SweepCache^ CreateSweepCache();
				/// <summary>Creates a Soft Body in this scene</summary>
				SoftBody^ CreateSoftBody( SoftBodyDescription^ softBodyDescription );
				/// <summary>Creates a Compartment in this scene</summary>
				Compartment^ CreateCompartment( CompartmentDescription^ compartmentDescription );
				/// <summary>Creates a Scene Query</summary>
				//SceneQuery^ CreateSceneQuery( SceneQueryDescription^ sceneQueryDescription );
				
				/// <summary>Advances the Simulation by the Elapsed Time Specified</summary>
				/// <param name="elapsedTime">The amount of time to advance the simulation (in seconds)</param>
				void Simulate( float elapsedTime );
				/// <summary>Flush the scene's command queue for processing</summary>
				void FlushStream();
				void FetchResults( SimulationStatus status, bool block );
				/// <summary>Flush internal caches</summary>
				void FlushCaches();
				/// <summary>Blocks all parallel raycast/overlap queries</summary>
				void LockQueries();
				/// <summary>Unlock parallel raycast/overlap queries</summary>
				void UnlockQueries();
				
				/// <summary>This checks to see if the part of the simulation run whose results you are interested in has completed</summary>
				/// <param name="status">The part of the simulation to check</param>
				bool CheckResults( SimulationStatus status );
				/// <summary>This checks to see if the part of the simulation run whose results you are interested in has completed</summary>
				/// <param name="status">The part of the simulation to check</param>
				/// <param name="block">When set to true will block until the condition is met</param>
				bool CheckResults( SimulationStatus status, bool block );
				
				/// <summary>Pre-cooks all triangles from static NxTriangleMeshShapes of the scene which are intersecting with the given bounds</summary>
				/// <param name="bounds">The volume whose contents should be pre-cooked </param>
				/// <param name="packetSizeMultiplier"></param>
				/// <param name="restParticlesPerMeter"></param>
				/// <param name="kernelRadiusMultiplier"></param>
				/// <param name="motionLimitMultiplier"></param>
				/// <param name="collisionDistanceMultiplier"></param>
				/// <returns>Operation succeeded</returns>
				bool CookFluidMeshHotspot( Bounds3 bounds, int packetSizeMultiplier, float restParticlePerMeter, float kernelRadiusMultiplier, float motionLimitMultiplier, float collisionDistanceMultiplier );
				/// <summary>Pre-cooks all triangles from static NxTriangleMeshShapes of the scene which are intersecting with the given bounds</summary>
				/// <param name="bounds">The volume whose contents should be pre-cooked </param>
				/// <param name="packetSizeMultiplier"></param>
				/// <param name="restParticlesPerMeter"></param>
				/// <param name="kernelRadiusMultiplier"></param>
				/// <param name="motionLimitMultiplier"></param>
				/// <param name="collisionDistanceMultiplier"></param>
				/// <param name="compartment">The specific compartment to perform the pre-cooking for</param>
				/// <param name="forceStrictCookingFormat">Forces specified cooking parameters. Otherwise they might internaly be reinterpreted depending on created fluids. Not implemented yet</param>
				/// <returns>Operation succeeded</returns>
				bool CookFluidMeshHotspot( Bounds3 bounds, int packetSizeMultiplier, float restParticlePerMeter, float kernelRadiusMultiplier, float motionLimitMultiplier, float collisionDistanceMultiplier, Compartment^ compartment, bool forceStrictCookingFormat );
				
				/// <summary>Poll for work to execute on the current thread</summary>
				ThreadPollResult PollForWork( ThreadWait waitType );
				/// <summary>Polls for background work</summary>
				ThreadPollResult PollForBackgroundWork( ThreadWait waitType );
				/// <summary>Reset parallel simulation</summary>
				void ResetPollForWork();
				/// <summary>Release threads which are blocking to allow the SDK to be destroyed safely</summary>
				void ShutdownWorkerThreads();
				
#pragma region Overlap Testing
				/// <summary>Returns the set of shapes overlapped by the world-space sphere</summary>
				/// <param name="sphere">Sphere description in world space</param>
				/// <param name="type">Choose if to intersect with static, dynamic or both types of shape</param>
				array< Shape^ >^ OverlappedShapes( Sphere sphere, ShapesType type );
				/// <summary>Returns the set of shapes overlapped by the world-space sphere</summary>
				/// <param name="sphere">Sphere description in world space</param>
				/// <param name="type">Choose if to intersect with static, dynamic or both types of shape</param>
				/// <param name="activeGroups">Mask used to filter shape objects</param>
				/// <param name="groupsMask">Alternative mask used to filter shapes</param>
				/// <param name="accurateCollision">True to test the sphere against the actual shapes, false to test against the AABBs only</param>
				array< Shape^ >^ OverlappedShapes( Sphere sphere, ShapesType type, unsigned int activeGroups, Nullable<GroupsMask> groupsMask, bool accurateCollision );
				/// <summary>Returns the set of shapes overlapped by the world-space sphere</summary>
				/// <param name="sphere">Sphere description in world space</param>
				/// <param name="type">Choose if to intersect with static, dynamic or both types of shape</param>
				/// <param name="activeGroups">Mask used to filter shape objects</param>
				/// <param name="groupsMask">Alternative mask used to filter shapes</param>
				/// <param name="accurateCollision">True to test the sphere against the actual shapes, false to test against the AABBs only</param>
				/// <param name="callback">Alternative method to retrieve overlapping shapes. Is called with sets of overlapping shapes</param>
				int OverlappedShapes( Sphere sphere, ShapesType type, unsigned int activeGroups, Nullable<GroupsMask> groupsMask, bool accurateCollision, UserEntityShapeReport^ callback );
				
				/// <summary>Returns the set of shapes overlapped by the world-space AABB</summary>
				/// <param name="worldBounds">Axis Aligned Bounding Box in world space</param>
				/// <param name="type">Choose if to intersect with static, dynamic or both types of shape</param>
				array< Shape^ >^ OverlappedShapes( Bounds3 worldBounds, ShapesType type );
				/// <summary>Returns the set of shapes overlapped by the world-space AABB</summary>
				/// <param name="worldBounds">Axis Aligned Bounding Box in world space</param>
				/// <param name="type">Choose if to intersect with static, dynamic or both types of shape</param>
				/// <param name="activeGroups">Mask used to filter shape objects</param>
				/// <param name="groupsMask">Alternative mask used to filter shapes</param>
				/// <param name="accurateCollision">True to test the AABB against the actual shapes, false to test against the AABBs only</param>
				array< Shape^ >^ OverlappedShapes( Bounds3 worldBounds, ShapesType type, unsigned int activeGroups, Nullable<GroupsMask> groupsMask, bool accurateCollision );
				/// <summary>Returns the set of shapes overlapped by the world-space AABB</summary>
				/// <param name="worldBounds">Axis Aligned Bounding Box in world space</param>
				/// <param name="type">Choose if to intersect with static, dynamic or both types of shape</param>
				/// <param name="activeGroups">Mask used to filter shape objects</param>
				/// <param name="groupsMask">Alternative mask used to filter shapes</param>
				/// <param name="accurateCollision">True to test the AABB against the actual shapes, false to test against the AABBs only</param>
				/// <param name="callback">Alternative method to retrieve overlapping shapes. Is called with sets of overlapping shapes</param>
				int OverlappedShapes( Bounds3 worldBounds, ShapesType type, unsigned int activeGroups, Nullable<GroupsMask> groupsMask, bool accurateCollision, UserEntityShapeReport^ callback );
				
				/// <summary>Returns the set of shapes overlapped by the world-space OBB</summary>
				/// <param name="worldBox">Oriented Bounding Box in world space</param>
				/// <param name="type">Choose if to intersect with static, dynamic or both types of shape</param>
				array< Shape^ >^ OverlappedShapes( Box worldBox, ShapesType type );
				/// <summary>Returns the set of shapes overlapped by the world-space OBB</summary>
				/// <param name="worldBox">Oriented Bounding Box in world space</param>
				/// <param name="type">Choose if to intersect with static, dynamic or both types of shape</param>
				/// <param name="activeGroups">Mask used to filter shape objects</param>
				/// <param name="groupsMask">Alternative mask used to filter shapes</param>
				/// <param name="accurateCollision">True to test the OBB against the actual shapes, false to test against the AABBs only</param>
				array< Shape^ >^ OverlappedShapes( Box worldBox, ShapesType type, unsigned int activeGroups, Nullable<GroupsMask> groupsMask, bool accurateCollision );
				/// <summary>Returns the set of shapes overlapped by the world-space OBB</summary>
				/// <param name="worldBox">Oriented Bounding Box in world space</param>
				/// <param name="type">Choose if to intersect with static, dynamic or both types of shape</param>
				/// <param name="activeGroups">Mask used to filter shape objects</param>
				/// <param name="groupsMask">Alternative mask used to filter shapes</param>
				/// <param name="accurateCollision">True to test the OBB against the actual shapes, false to test against the AABBs only</param>
				/// <param name="callback">Alternative method to retrieve overlapping shapes. Is called with sets of overlapping shapes</param>
				int OverlappedShapes( Box worldBox, ShapesType type, unsigned int activeGroups, Nullable<GroupsMask> groupsMask, bool accurateCollision, UserEntityShapeReport^ callback );
				
				/// <summary>Returns the set of shapes overlapped by the world-space capsule</summary>
				/// <param name="worldCapsule">capsule in world space</param>
				/// <param name="type">Choose if to intersect with static, dynamic or both types of shape</param>
				array< Shape^ >^ OverlappedShapes( Capsule worldCapsule, ShapesType type );
				/// <summary>Returns the set of shapes overlapped by the world-space capsule</summary>
				/// <param name="worldCapsule">capsule in world space</param>
				/// <param name="type">Choose if to intersect with static, dynamic or both types of shape</param>
				/// <param name="activeGroups">Mask used to filter shape objects</param>
				/// <param name="groupsMask">Alternative mask used to filter shapes</param>
				/// <param name="accurateCollision">True to test the OBB against the actual shapes, false to test against the AABBs only</param>
				array< Shape^ >^ OverlappedShapes( Capsule worldCapsule, ShapesType type, unsigned int activeGroups, Nullable<GroupsMask> groupsMask, bool accurateCollision );
				/// <summary>Returns the set of shapes overlapped by the world-space capsule</summary>
				/// <param name="worldCapsule">capsule in world space</param>
				/// <param name="type">Choose if to intersect with static, dynamic or both types of shape</param>
				/// <param name="activeGroups">Mask used to filter shape objects</param>
				/// <param name="groupsMask">Alternative mask used to filter shapes</param>
				/// <param name="accurateCollision">True to test the OBB against the actual shapes, false to test against the AABBs only</param>
				/// <param name="callback">Alternative method to retrieve overlapping shapes. Is called with sets of overlapping shapes</param>
				int OverlappedShapes( Capsule worldCapsule, ShapesType type, unsigned int activeGroups, Nullable<GroupsMask> groupsMask, bool accurateCollision, UserEntityShapeReport^ callback ); 
#pragma endregion
				
				/// <summary>Call this method to retrieve statistics about the current scene</summary>
				SceneStatistics^ GetStatistics();
				/// <summary>Call to retrieve the expected object count limits set in the scene descriptor</summary>
				SceneLimits^ GetLimits();
				
				array<PairFlag^>^ GetPairFlags();
				/// <summary>Retrieves the pair flags for the given pair of actors</summary>
				ContactPairFlag GetActorPairFlags( Actor^ actorA, Actor^ actorB );
				/// <summary>Sets the pair flags for the given pair of actors</summary>
				void SetActorPairFlags( Actor^ actorA, Actor^ actorB, ContactPairFlag contactPairFlag );
				
				ContactPairFlag GetShapePairFlags( Shape^ shapeA, Shape^ shapeB );
				void SetShapePairFlags( Shape^ shapeA, Shape^ shapeB, ContactPairFlag contactPairFlag );
				
				/// <summary>Determines if collision detection is performed between a pair of groups</summary>
				bool GetGroupCollisionFlag( short group1, short group2 );
				/// <summary>Specifies if collision should be performed by a pair of shape groups</summary>
				void SetGroupCollisionFlag( short group1, short group2, bool enable );
				
				/// <summary>Samples the dominance matrix</summary>
				ConstraintDominance GetDominanceGroupPair( short group1, short group2 );
				/// <summary>Specifies the dominance behavior of constraints between two actors with two certain dominance groups</summary>
				void SetDominanceGroupPair( short group1, short group2, ConstraintDominance dominance );
				
				int GetActorGroupPairFlags( short group1, short group2 );
				/// <summary>With this method one can set contact reporting flags between actors belonging to a pair of groups</summary>
				void SetActorGroupPairFlags( short group1, short group2, ContactPairFlag contactPairFlag );
				array<ActorGroupPair>^ GetActorGroupPairs();
				
				void SetFilterOperations( FilterOperation op0, FilterOperation op1, FilterOperation op2 );
				void SetFilterBoolean( bool flag );
				void SetFilterConstant0( GroupsMask mask );
				void SetFilterConstant1( GroupsMask mask );
				void GetFilterOperations( [Out] FilterOperation% op0, [Out] FilterOperation% op1, [Out] FilterOperation% op2 );
				bool GetFilterBoolean();
				GroupsMask GetFilterConstant0();
				GroupsMask GetFilterConstant1();
				
				/// <summary>Retrieves the debug renderable</summary>
				DebugRenderable^ GetDebugRenderable();
				
#pragma region Raycast
				/// <summary>Returns true if any axis aligned bounding box enclosing a shape of type shapeType is intersected by the ray</summary>
				/// <param name="worldRay">The ray to cast in the global frame</param>
				/// <param name="shapesType">Choose if to raycast against static, dynamic or both types of shape</param>
				bool RaycastAnyBounds( Ray worldRay, ShapesType shapesType );
				/// <summary>Returns true if any axis aligned bounding box enclosing a shape of type shapeType is intersected by the ray</summary>
				/// <param name="worldRay">The ray to cast in the global frame</param>
				/// <param name="shapesType">Choose if to raycast against static, dynamic or both types of shape</param>
				/// <param name="groups">Mask used to filter shape objects</param>
				/// <param name="maximumDistance">Max distance to check along the ray for intersecting bounds</param>
				/// <param name="groupsMask">Alternative mask used to filter shapes</param>
				bool RaycastAnyBounds( Ray worldRay, ShapesType shapesType, unsigned int groups, float maximumDistance, Nullable<GroupsMask> groupsMask );
				
				/// <summary>Returns true if any shape of type ShapeType is intersected by the ray</summary>
				/// <param name="worldRay">The ray to cast in the global frame</param>
				/// <param name="shapesType">Choose if to raycast against static, dynamic or both types of shape</param>
				bool RaycastAnyShape( Ray worldRay, ShapesType shapesType );
				/// <summary>Returns true if any shape of type ShapeType is intersected by the ray</summary>
				/// <param name="worldRay">The ray to cast in the global frame</param>
				/// <param name="shapesType">Choose if to raycast against static, dynamic or both types of shape</param>
				/// <param name="groups">Mask used to filter shape objects</param>
				/// <param name="maximumDistance">Max distance to check along the ray for intersecting objects</param>
				/// <param name="groupsMask">Alternative mask used to filter shapes</param>
				/// <param name="cache">Possible cache for persistent raycasts, filled out by the SDK</param>
				bool RaycastAnyShape( Ray worldRay, ShapesType shapesType, unsigned int groups, float maximumDistance, Nullable<GroupsMask> groupsMask, [Out] Shape^ cache );
				
				/// <summary>Calls the report's hitCallback() method for all the axis aligned bounding boxes enclosing shapes of type ShapeType intersected by the ray</summary>
				/// <param name="worldRay">The ray to cast in the global frame</param>
				/// <param name="userRaycastReport">User callback, to be called when an intersection is encountered</param>
				/// <param name="shapesType">Choose if to raycast against static, dynamic or both types of shape</param>
				int RaycastAllBounds( Ray worldRay, UserRaycastReport^ userRaycastReport, ShapesType shapesType );
				/// <summary>Calls the report's hitCallback() method for all the axis aligned bounding boxes enclosing shapes of type ShapeType intersected by the ray</summary>
				/// <param name="worldRay">The ray to cast in the global frame</param>
				/// <param name="userRaycastReport">User callback, to be called when an intersection is encountered</param>
				/// <param name="shapesType">Choose if to raycast against static, dynamic or both types of shape</param>
				/// <param name="groups">Mask used to filter shape objects</param>
				/// <param name="maximumDistance">Max distance to check along the ray for intersecting objects</param>
				/// <param name="hintFlags">Allows the user to specify which field of RaycastHit they are interested in. The default is 0xFFFFFFFF</param>
				/// <param name="groupsMask">Alternative mask used to filter shapes</param>
				int RaycastAllBounds( Ray worldRay, UserRaycastReport^ userRaycastReport, ShapesType shapesType, unsigned int groups, float maximumDistance, unsigned int hintFlags, Nullable<GroupsMask> groupsMask );
				
				/// <summary>Calls the report's hitCallback() method for all the shapes of type ShapeType intersected by the ray</summary>
				/// <param name="worldRay">The ray to cast in the global frame</param>
				/// <param name="userRaycastReport">User callback, to be called when an intersection is encountered</param>
				/// <param name="shapesType">Choose if to raycast against static, dynamic or both types of shape</param>
				int RaycastAllShapes( Ray worldRay, UserRaycastReport^ userRaycastReport, ShapesType shapesType );
				/// <summary>Calls the report's hitCallback() method for all the shapes of type ShapeType intersected by the ray</summary>
				/// <param name="worldRay">The ray to cast in the global frame</param>
				/// <param name="userRaycastReport">User callback, to be called when an intersection is encountered</param>
				/// <param name="shapesType">Choose if to raycast against static, dynamic or both types of shape</param>
				/// <param name="groups">Mask used to filter shape objects</param>
				/// <param name="maximumDistance">Max distance to check along the ray for intersecting objects</param>
				/// <param name="hintFlags">Allows the user to specify which field of RaycastHit they are interested in. The default is 0xFFFFFFFF</param>
				/// <param name="groupsMask">Alternative mask used to filter shapes</param>
				int RaycastAllShapes( Ray worldRay, UserRaycastReport^ userRaycastReport, ShapesType shapesType, unsigned int groups, float maximumDistance, unsigned int hintFlags, Nullable<GroupsMask> groupsMask );
				/// <summary>Returns the shapes hit by the ray</summary>
				/// <param name="worldRay">The ray to cast in the global frame</param>
				/// <param name="shapesType">Choose if to raycast against static, dynamic or both types of shape</param>
				array<RaycastHit^>^ RaycastAllShapes( StillDesign::PhysX::Ray worldRay, ShapesType shapesType );
				
				/// <summary>Returns the first axis aligned bounding box enclosing a shape of type shapeType that is hit along the ray</summary>
				/// <param name="worldRay">The ray to cast in the global frame</param>
				/// <param name="shapesTypes">Choose if to raycast against static, dynamic or both types of shape</param>
				RaycastHit^ RaycastClosestBounds( Ray worldRay, ShapesType shapesTypes );
				/// <summary>Returns the first axis aligned bounding box enclosing a shape of type shapeType that is hit along the ray</summary>
				/// <param name="worldRay">The ray to cast in the global frame</param>
				/// <param name="shapesType">Choose if to raycast against static, dynamic or both types of shape</param>
				/// <param name="groups">Mask used to filter shape objects</param>
				/// <param name="maximumDistance">Max distance to check along the ray for intersecting objects</param>
				/// <param name="hintFlags">Allows the user to specify which field of RaycastHit they are interested in. The default is 0xFFFFFFFF</param>
				/// <param name="groupsMask">Alternative mask used to filter shapes</param>
				RaycastHit^ RaycastClosestBounds( Ray worldRay, ShapesType shapesType, unsigned int groups, float maximumDistance, unsigned int hintFlags, Nullable<GroupsMask> groupsMask );
				
				/// <summary>Returns the first shape of type shapeType that is hit along the ray</summary>
				/// <param name="worldRay">The ray to cast in the global frame</param>
				/// <param name="shapesType">Choose if to raycast against static, dynamic or both types of shape</param>
				RaycastHit^ RaycastClosestShape( Ray worldRay, ShapesType shapesType );
				/// <summary>Returns the first shape of type shapeType that is hit along the ray</summary>
				/// <param name="worldRay">The ray to cast in the global frame</param>
				/// <param name="shapesType">Choose if to raycast against static, dynamic or both types of shape</param>
				/// <param name="groups">Mask used to filter shape objects</param>
				/// <param name="maximumDistance">Max distance to check along the ray for intersecting objects</param>
				/// <param name="hintFlags">Allows the user to specify which field of RaycastHit they are interested in. The default is 0xFFFFFFFF</param>
				/// <param name="groupsMask">Alternative mask used to filter shapes</param>
				RaycastHit^ RaycastClosestShape( Ray worldRay, ShapesType shapesType, unsigned int groups, float maximumDistance, unsigned int hintFlags, Nullable<GroupsMask> groupsMask );
#pragma endregion
				
#pragma region Sweep
				/// <summary>Performs a linear sweep through space with an oriented box</summary>
				/// <param name="worldBox">The oriented box (Box object) that is to be swept</param>
				/// <param name="motion">Length and direction of the sweep</param>
				/// <param name="flags">Flags controlling the mode of the sweep</param>
				/// <param name="userData">User data to impart to the returned data struct</param>
				array<SweepQueryHit^>^ LinearObbSweep( Box worldBox, Vector3 motion, SweepFlags flags, Object^ userData );
				array<SweepQueryHit^>^ LinearObbSweep( Box worldBox, Vector3 motion, SweepFlags flags, Object^ userData, unsigned int activeGroups, Nullable<GroupsMask> groupsMask );
				/// <summary>Performs a linear sweep through space with an oriented box</summary>
				/// <param name="worldBox">The oriented box (Box object) that is to be swept</param>
				/// <param name="motion">Length and direction of the sweep</param>
				/// <param name="flags">Flags controlling the mode of the sweep</param>
				/// <param name="userData">User data to impart to the returned data struct</param>
				/// <param name="maximumShapes">Maximum number of shapes to report</param>
				/// <param name="callback">Callback function invoked on the closest hit (if any)</param>
				/// <param name="activeGroups">Mask used to filter shape objects</param>
				/// <param name="groupsMask">Alternative mask used to filter shapes</param>
				void LinearObbSweep( Box worldBox, Vector3 motion, SweepFlags flags, Object^ userData, UserEntitySweepQueryHitReport^ callback );
				void LinearObbSweep( Box worldBox, Vector3 motion, SweepFlags flags, Object^ userData, UserEntitySweepQueryHitReport^ callback, unsigned int activeGroups, Nullable<GroupsMask> groupsMask );
				
				/// <summary>Performs a linear sweep through space with an oriented capsule</summary>
				/// <param name="worldCapsule">The oriented capsule (Capsule object) that is to be swept</param>
				/// <param name="motion">Length and direction of the sweep</param>
				/// <param name="flags">Flags controlling the mode of the sweep</param>
				/// <param name="userData">User data to impart to the returned data struct</param>
				array<SweepQueryHit^>^ LinearCapsuleSweep( Capsule worldCapsule, Vector3 motion, SweepFlags flags, Object^ userData );
				array<SweepQueryHit^>^ LinearCapsuleSweep( Capsule worldCapsule, Vector3 motion, SweepFlags flags, Object^ userData, unsigned int activeGroups, Nullable<GroupsMask> groupsMask );
				/// <summary>Performs a linear sweep through space with an oriented capsule</summary>
				/// <summary>Performs a linear sweep through space with an oriented box</summary>
				/// <param name="worldCapsule">The oriented capsule (Capsule object) that is to be swept</param>
				/// <param name="motion">Length and direction of the sweep</param>
				/// <param name="flags">Flags controlling the mode of the sweep</param>
				/// <param name="userData">User data to impart to the returned data struct</param>
				/// <param name="maximumShapes">Maximum number of shapes to report</param>
				/// <param name="callback">Callback function invoked on the closest hit (if any)</param>
				/// <param name="activeGroups">Mask used to filter shape objects</param>
				/// <param name="groupsMask">Alternative mask used to filter shapes</param>
				void LinearCapsuleSweep( Capsule worldCapsule, Vector3 motion, SweepFlags flags, Object^ userData, UserEntitySweepQueryHitReport^ callback );
				void LinearCapsuleSweep( Capsule worldCapsule, Vector3 motion, SweepFlags flags, Object^ userData, UserEntitySweepQueryHitReport^ callback, unsigned int activeGroups, Nullable<GroupsMask> groupsMask );
				
			private:
				generic<class T> where T : ValueType
				array<SweepQueryHit^>^ LinearSweep( T sweepObject, Vector3 motion, SweepFlags flags, Object^ userData, UserEntitySweepQueryHitReport^ callback, unsigned int activeGroups, Nullable<GroupsMask> groupsMask );
#pragma endregion
				
			public:
				/// <summary>Returns the set of shapes which are in the negative half space of a number of planes</summary>
				/// <param name="planes">Set of planes to test</param>
				/// <param name="shapesType">Choose if to intersect with static, dynamic or both types of shape</param>
				array<Shape^>^ CullShapes( array<Plane>^ planes, ShapesType shapesType );
				/// <summary>Returns the set of shapes which are in the negative half space of a number of planes</summary>
				/// <param name="planes">Set of planes to test</param>
				/// <param name="shapesType">Choose if to intersect with static, dynamic or both types of shape</param>
				/// <param name="activeGroups">Mask used to filter shape objects</param>
				/// <param name="groupsMask">Alternative mask used to filter shapes</param>
				array<Shape^>^ CullShapes( array<Plane>^ planes, ShapesType shapesType, unsigned int activeGroups, Nullable<GroupsMask> groupsMask );
				/// <summary>Returns the set of shapes which are in the negative half space of a number of planes</summary>
				/// <param name="planes">Set of planes to test</param>
				/// <param name="shapesType">Choose if to intersect with static, dynamic or both types of shape</param>
				/// <param name="activeGroups">Mask used to filter shape objects</param>
				/// <param name="groupsMask">Alternative mask used to filter shapes</param>
				/// <param name="callback">Alternative method to retrieve overlapping shapes. Is called with sets of overlapping shapes</param>
				int CullShapes( array<Plane>^ planes, ShapesType shapesType, unsigned int activeGroups, Nullable<GroupsMask> groupsMask, UserEntityShapeReport^ callback );
				
				/// <summary>Queries the Scene for a list of the NxActors whose transforms have been updated during the previous simulation step</summary>
				array<ActiveTransform^>^ GetActiveTransforms();
				
				float GetForceFieldScale( short varietyIndex, short materialIndex );
				void SetForceFieldScale( short varietyIndex, short materialIndex, float value );
				
			private:
				//void Actors_onAdd( Object^ sender, Actor^ item );
				//void Actors_onRemove( Object^ sender, Actor^ item );
				//void Actors_Shapes_onAdd( Object^ sender, Shape^ item );
				//void Actors_Shapes_onRemove( Object^ sender, Shape^ item );
				//
				//void _controllerManagerCollection_onAdd( Object^ sender, ControllerManager^ e );
				//void _controllerManagerCollection_onRemove( Object^ sender, ControllerManager^ e );
				//
				//void Controllers_onAdd( Object^ sender, StillDesign::PhysX::Controller^ e );
				//void Controllers_onRemove( Object^ sender, StillDesign::PhysX::Controller^ e );
				
				//
				
			public:
				/// <summary>Gets the Core parent of the scene</summary>
				property StillDesign::PhysX::Core^ Core
				{
					StillDesign::PhysX::Core^ get();
				}
				
				/// <summary>Gets the Actors in the Scene</summary>
				property ReadOnlyList< Actor^ >^ Actors
				{
					ReadOnlyList< Actor^ >^ get();
				}
				/// <summary>Gets the Shapes in the Scene</summary>
				//property ReadOnlyList< Shape^ >^ Shapes
				//{
				//	ReadOnlyList< Shape^ >^ get();
				//}
				/// <summary>Gets the Materials in the Scene</summary>
				property ReadOnlyList< Material^ >^ Materials
				{
					ReadOnlyList< Material^ >^ get();
				}
				/// <summary>Gets the Controller Managers in the Scene</summary>
				property ReadOnlyList< ControllerManager^ >^ ControllerManagers
				{
					ReadOnlyList< ControllerManager^ >^ get();
				}
				/// <summary>Gets the Controllers in the Scene</summary>
				//property ReadOnlyList< Controller^ >^ Controllers
				//{
				//	ReadOnlyList< Controller^ >^ get();
				//}
				/// <summary>Gets the Joints in the Scene</summary>
				property ReadOnlyList< Joint^ >^ Joints
				{
					ReadOnlyList< Joint^ >^ get();
				}
				/// <summary>Gets the Cloths in the Scene</summary>
				property ReadOnlyList< Cloth^ >^ Cloths
				{
					ReadOnlyList< Cloth^ >^ get();
				}
				/// <summary>Gets the Force Fields in the Scene</summary>
				property ReadOnlyList< ForceField^ >^ ForceFields
				{
					ReadOnlyList< ForceField^ >^ get();
				}
				/// <summary>Gets the Fluids in the Scene</summary>
				property ReadOnlyList< Fluid^ >^ Fluids
				{
					ReadOnlyList< Fluid^ >^ get();
				}
				/// <summary>Gets the Soft Bodies in the Scene</summary>
				property ReadOnlyList< SoftBody^ >^ SoftBodies
				{
					ReadOnlyList< SoftBody^ >^ get();
				}
				/// <summary>Gets the Compartments in the Scene</summary>
				property ReadOnlyList< Compartment^ >^ Compartments
				{
					ReadOnlyList< Compartment^ >^ get();
				}
				
				property ReadOnlyList< ForceFieldLinearKernel^ >^ ForceFieldLinearKernels
				{
					ReadOnlyList< ForceFieldLinearKernel^ >^ get();
				}
				property ReadOnlyList< ForceFieldShapeGroup^ >^ ForceFieldShapeGroups
				{
					ReadOnlyList< ForceFieldShapeGroup^ >^ get();
				}
				
				// Callbacks
				/// <summary>Gets or Sets a user notify object which receives special simulation events when they occur</summary>
				property StillDesign::PhysX::UserNotify^ UserNotify
				{
					StillDesign::PhysX::UserNotify^ get();
					void set( StillDesign::PhysX::UserNotify^ value );
				}
				/// <summary>Gets or Sets a user notify object which receives special fluid simulation events when they occur</summary>
				property StillDesign::PhysX::FluidUserNotify^ FluidUserNotify
				{
					StillDesign::PhysX::FluidUserNotify^ get();
					void set( StillDesign::PhysX::FluidUserNotify^ value );
				}
				/// <summary>Gets or Sets a user callback object, which receives callbacks on all contacts generated for specified actors</summary>
				property StillDesign::PhysX::UserContactModify^ UserContactModify
				{
					StillDesign::PhysX::UserContactModify^ get();
					void set( StillDesign::PhysX::UserContactModify^ value );
				}
				/// <summary>Gets or Sets a contact report object which receives collision contact events</summary>
				property UserContactReport^ UserContactReport
				{
					StillDesign::PhysX::UserContactReport^ get();
					void set( StillDesign::PhysX::UserContactReport^ value );
				}
				/// <summary>Gets or Sets a trigger report object which receives collision trigger events</summary>
				property StillDesign::PhysX::UserTriggerReport^ UserTriggerReport
				{
					StillDesign::PhysX::UserTriggerReport^ get();
					void set( StillDesign::PhysX::UserTriggerReport^ value );
				}
				/// <summary>Gets or Sets the custom actor pair filtering to use for this scene</summary>
				property StillDesign::PhysX::UserActorPairFiltering^ UserActorPairFiltering
				{
					StillDesign::PhysX::UserActorPairFiltering^ get();
					void set( StillDesign::PhysX::UserActorPairFiltering^ value );
				}
				
				//
				
				/// <summary>Gets or Sets the name of the scene</summary>
				property String^ Name
				{
					String^ get();
					void set( String^ value );
				}
				
				/// <summary>Get or Sets the Gravity of the Scene</summary>
				property Vector3 Gravity
				{
					Vector3 get();
					void set( Vector3 value );
				}
				
				/// <summary>Gets the default material for the scene</summary>
				property Material^ DefaultMaterial
				{
					Material^ get();
				}
				/// <summary>Gets the current highest valid material index</summary>
				property short HighestMaterialIndex
				{
					short get();
				}
				
				/// <summary>Gets the number of pairs for which pairFlags are defined. Note that this includes compartments</summary>
				property int NumberOfPairs
				{
					int get();
				}
				/// <summary>Gets the number of actor group flags (as set by setActorGroupPairFlags)</summary>
				property int NumberOfActorGroupPairs
				{
					int get();
				}
				
				/// <summary>Get the scene flags</summary>
				property SceneFlag Flags
				{
					SceneFlag get();
				}
				
				/// <summary>Gets or Sets simulation timing parameters</summary>
				property SceneTimingInformation TimingInformation
				{
					SceneTimingInformation get();
					void set( SceneTimingInformation value );
				}
				
				/// <summary>Is the scene is in a state that allows the application to update scene state</summary>
				property bool IsWritable
				{
					bool get();
				}
				
				/// <summary>Get the simulation type</summary>
				property StillDesign::PhysX::SimulationType SimulationType
				{
					StillDesign::PhysX::SimulationType get();
				}
				
				/// <summary>Hint for how much work should be done per simulation frame to rebuild the pruning structure</summary>
				property int DynamicTreeRebuildRateHint
				{
					int get();
					void set( int value );
				}
				
				/// <summary>Gets or Sets the number of actors required to spawn a separate rigid body solver thread</summary>
				property int SolverBatchSize
				{
					int get();
					void set( int value );
				}
				
				/// <summary>Gets or Sets an abitary 1:1 object</summary>
				property Object^ UserData
				{
					Object^ get();
					void set( Object^ value );
				}
				
			internal:
				property NxScene* UnmanagedPointer
				{
					NxScene* get();
				}
		};
	};	
};