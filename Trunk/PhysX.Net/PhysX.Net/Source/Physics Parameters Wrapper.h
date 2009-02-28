#pragma once

#include "Core.h"



namespace StillDesign
{
	namespace PhysX
	{

		[System::ComponentModel::TypeConverter( System::ComponentModel::ExpandableObjectConverter::typeid )]
		public ref class PhysicsParametersWrapper
		{
		public:
			#define WRAPPER_PROPERTY_BOOL( name ) \
				property bool name { \
					bool get() { return _core->GetParameter( PhysicsParameter::name ) != 0.0f; } \
					void set(bool value) { _core->SetParameter( PhysicsParameter::name, value ); } \
				}
			#define WRAPPER_PROPERTY_FLOAT( name ) \
				property float name { \
					float get() { return _core->GetParameter( PhysicsParameter::name ); } \
					void set(float value) { _core->SetParameter( PhysicsParameter::name, value ); } \
				}
			#define WRAPPER_PROPERTY_CONST( name ) \
				property int name { \
					int get() { return static_cast<int>(_core->GetParameter( PhysicsParameter::name )); } \
				}

			WRAPPER_PROPERTY_FLOAT( SkinWidth )
			WRAPPER_PROPERTY_FLOAT( DefaultSleepLinearVelocitySquared )
			WRAPPER_PROPERTY_FLOAT( DefaultSleepAngularVelocitySquared )
			WRAPPER_PROPERTY_FLOAT( BounceThreshold )
			WRAPPER_PROPERTY_FLOAT( DynamicFrictionScaling )
			WRAPPER_PROPERTY_FLOAT( StaticFrictionScaling )
			WRAPPER_PROPERTY_FLOAT( MaximumAngularVelocity )
			WRAPPER_PROPERTY_BOOL( ContinuousCollisionDetection )
			WRAPPER_PROPERTY_FLOAT( VisualizationScale )
			WRAPPER_PROPERTY_BOOL( VisualizeWorldAxes )
			WRAPPER_PROPERTY_BOOL( VisualizeBodyAxes )
			WRAPPER_PROPERTY_BOOL( VisualizeBodyMassAxes )
			WRAPPER_PROPERTY_BOOL( VisualizeBodyLinearVelocity )
			WRAPPER_PROPERTY_BOOL( VisualizeBodyAngularVelocity )
			WRAPPER_PROPERTY_BOOL( VisualizeBodyJointGroups )
			WRAPPER_PROPERTY_BOOL( VisualizeJointLocalAxes )
			WRAPPER_PROPERTY_BOOL( VisualizeJointWorldAxes )
			WRAPPER_PROPERTY_BOOL( VisualizeJointLimits )
			WRAPPER_PROPERTY_BOOL( VisualizeContactPoint )
			WRAPPER_PROPERTY_BOOL( VisualizeContactNormal )
			WRAPPER_PROPERTY_BOOL( VisualizeContactError )
			WRAPPER_PROPERTY_BOOL( VisualizeContactForce )
			WRAPPER_PROPERTY_BOOL( VisualizeActorAxes )
			WRAPPER_PROPERTY_BOOL( VisualizeCollisionAxisAlignedBoundingBoxes )
			WRAPPER_PROPERTY_BOOL( VisualizeCollisionShapes )
			WRAPPER_PROPERTY_BOOL( VisualizeCollisionAxes )
			WRAPPER_PROPERTY_BOOL( VisualizeCollisionCompounds )
			WRAPPER_PROPERTY_BOOL( VisualizeCollisionVertexNormals )
			WRAPPER_PROPERTY_BOOL( VisualizeCollisionFaceNormals )
			WRAPPER_PROPERTY_BOOL( VisualizeCollisionEdgeNormals )
			WRAPPER_PROPERTY_BOOL( VisualizeCollisionSpheres )
			//WRAPPER_PROPERTY_BOOL( VisualizeCollisionSAPStructures )
			WRAPPER_PROPERTY_BOOL( VisualizeCollisionStaticPruningStructures )
			WRAPPER_PROPERTY_BOOL( VisualizeCollisionDynamicPruningStructures )
			WRAPPER_PROPERTY_BOOL( VisualizeCollisionFreePruningStructures )
			WRAPPER_PROPERTY_BOOL( VisualizeContinuousCollisionDetectionTests )
			WRAPPER_PROPERTY_BOOL( VisualizeCollisionSkeletons )
			WRAPPER_PROPERTY_BOOL( VisualizeFluidEmitters )
			WRAPPER_PROPERTY_BOOL( VisualizeFluidPosition )
			WRAPPER_PROPERTY_BOOL( VisualizeFluidVelocity )
			WRAPPER_PROPERTY_BOOL( VisualizeFluidKernelRadius )
			WRAPPER_PROPERTY_BOOL( VisualizeFluidBounds )
			WRAPPER_PROPERTY_BOOL( VisualizeFluidPackets )
			WRAPPER_PROPERTY_BOOL( VisualizeFluidMotionLimit )
			WRAPPER_PROPERTY_BOOL( VisualizeFluidDynamicCollision )
			WRAPPER_PROPERTY_BOOL( VisualizeFluidStaticCollision )
			WRAPPER_PROPERTY_BOOL( VisualizeFluidMeshPackets )
			WRAPPER_PROPERTY_BOOL( VisualizeFluidDrains )
			WRAPPER_PROPERTY_BOOL( VisualizeFluidPacketData )
			WRAPPER_PROPERTY_BOOL( VisualizeClothMesh )
			WRAPPER_PROPERTY_BOOL( VisualizeClothCollision )
			WRAPPER_PROPERTY_BOOL( VisualizeClothSelfCollision )
			WRAPPER_PROPERTY_BOOL( VisualizeClothWorkPackets )
			WRAPPER_PROPERTY_BOOL( VisualizeClothSleep )
			WRAPPER_PROPERTY_BOOL( VisualizeClothSleepVertex )
			WRAPPER_PROPERTY_BOOL( VisualizeClothTearableVertices )
			WRAPPER_PROPERTY_BOOL( VisualizeClothTearing )
			WRAPPER_PROPERTY_BOOL( VisualizeClothAttachment )
			WRAPPER_PROPERTY_BOOL( VisualizeClothValidBounds )
			WRAPPER_PROPERTY_BOOL( VisualizeSoftBodyMesh )
			WRAPPER_PROPERTY_BOOL( VisualizeSoftBodyCollisions )
			WRAPPER_PROPERTY_BOOL( VisualizeSoftBodyWorkPackets )
			WRAPPER_PROPERTY_BOOL( VisualizeSoftBodySleep )
			WRAPPER_PROPERTY_BOOL( VisualizeSoftBodySleepVertex )
			WRAPPER_PROPERTY_BOOL( VisualizeSoftBodyTearableVertices )
			WRAPPER_PROPERTY_BOOL( VisualizeSoftBodyTearing )
			WRAPPER_PROPERTY_BOOL( VisualizeSoftBodyAttachment )
			WRAPPER_PROPERTY_BOOL( VisualizeSoftBodyValidBounds )
			WRAPPER_PROPERTY_BOOL( VisualizeActiveVertices )
			WRAPPER_PROPERTY_BOOL( VisualizeForceFields )		
			WRAPPER_PROPERTY_BOOL( CollisionVetoJointed )
			WRAPPER_PROPERTY_BOOL( TriggerTriggerCallback )
			WRAPPER_PROPERTY_FLOAT( ContinuousCollisionDetectionEpsilon )
			WRAPPER_PROPERTY_FLOAT( SolverConvergenceThreshold )
			WRAPPER_PROPERTY_FLOAT( BoundingBoxNoiseLevel )
			WRAPPER_PROPERTY_FLOAT( ImplicitSweepCacheSize )
			WRAPPER_PROPERTY_FLOAT( DefaultSleepEnergy )
			WRAPPER_PROPERTY_CONST( ConstantFluidMaximumPackets )
			WRAPPER_PROPERTY_CONST( ConstantFluidMaximumParticlesPerStep )
			WRAPPER_PROPERTY_BOOL( AsynchronousMeshCreation )
			WRAPPER_PROPERTY_FLOAT( ForceFieldCustomKernelEpsilon )
			WRAPPER_PROPERTY_BOOL( ImprovedSpringSolver )

			#undef WRAPPER_PROPERTY_BOOL
			#undef WRAPPER_PROPERTY_FLOAT
			#undef WRAPPER_PROPERTY_CONST

		internal:
			PhysicsParametersWrapper(Core^ core)
				: _core(core)
			{
				if ( core == nullptr )
					throw gcnew ArgumentNullException( "core" );
			}

		private:
			Core^ _core;
		};

	}
}