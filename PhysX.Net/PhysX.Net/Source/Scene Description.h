#pragma once

#include "Enums.h"
#include "IDisposable.h"
#include "Bounds.h"
#include "Description.h"

using namespace System;
UsingFrameworkNamespace

namespace StillDesign
{
	namespace PhysX
	{
		ref class Scene;
		ref class UserNotify;
		ref class SceneLimits;
		ref class FluidUserNotify;
		ref class UserContactReport;
		ref class UserTriggerReport;
		ref class UserContactModify;
		ref class UserContactReport;
		
		public ref class SceneDescription : Description, IDisposable
		{
			public:
				virtual event EventHandler^ OnDisposing;
				virtual event EventHandler^ OnDisposed;
			
			private:
				NxSceneDesc* _sceneDescription;
				
				String^ _name;
				
				UserNotify^ _userNotify;
				FluidUserNotify^ _fluidUserNotify;
				UserContactModify^ _userContactModify;
				UserContactReport^ _userContactReport;
				UserTriggerReport^ _userTriggerReport;
				
				SceneLimits^ _sceneLimits;
				
				Object^ _userData;
				
			public:
				SceneDescription();
			internal:
				SceneDescription( NxSceneDesc* desc );
			public:
				~SceneDescription();
			protected:
				!SceneDescription();
			public:
				property bool IsDisposed
				{
					virtual bool get();
				}
				
				/// <summary>(re)sets the structure to the default (no gravity, no ground plane, collision detection on)</summary>
				void SetToDefault();
				/// <summary>Returns 0 if the current settings are valid.</summary>
				virtual int CheckValid() override;
				/// <summary></summary>
				bool IsValid();
				
				/// <summary>Gets or Sets the name of the scene</summary>
				property String^ Name
				{
					String^ get();
					void set( String^ value );
				}
				
				/// <summary>Gets or Sets the gravity vector</summary>
				property Vector3 Gravity
				{
					Vector3 get();
					void set( Vector3 value );
				}
				
				/// <summary>Gets or Sets a possible notification callback</summary>
				property StillDesign::PhysX::UserNotify^ UserNotify
				{
					StillDesign::PhysX::UserNotify^ get();
					void set( StillDesign::PhysX::UserNotify^ value );
				}
				/// <summary>Gets or Sets a possible notification callback for fluids</summary>
				property StillDesign::PhysX::FluidUserNotify^ FluidUserNotify
				{
					StillDesign::PhysX::FluidUserNotify^ get();
					void set( StillDesign::PhysX::FluidUserNotify^ value );
				}
				/// <summary>Gets or Sets a possible asynchronous callback for contact modification</summary>
				property StillDesign::PhysX::UserContactModify^ UserContactModify
				{
					StillDesign::PhysX::UserContactModify^ get();
					void set( StillDesign::PhysX::UserContactModify^ value );
				}
				/// <summary>Gets or Sets a possible contact callback</summary>
				property StillDesign::PhysX::UserContactReport^ UserContactReport
				{
					StillDesign::PhysX::UserContactReport^ get();
					void set( StillDesign::PhysX::UserContactReport^ value );
				}
				/// <summary>Gets or Sets a possible trigger callback</summary>
				property StillDesign::PhysX::UserTriggerReport^ UserTriggerReport
				{
					StillDesign::PhysX::UserTriggerReport^ get();
					void set( StillDesign::PhysX::UserTriggerReport^ value );
				}
				
				/// <summary>Gets or Sets the maximum substep size</summary>
				property float MaximumTimestep
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the maximum number of substeps to take</summary>
				property int MaximumIterations
				{
					int get();
					void set( int value );
				}
				/// <summary>Gets or Sets the integration method</summary>
				property StillDesign::PhysX::TimestepMethod TimestepMethod
				{
					StillDesign::PhysX::TimestepMethod get();
					void set( StillDesign::PhysX::TimestepMethod value );
				}
				
				/// <summary>Gets or Sets optional max scene bounds</summary>
				property Nullable<Bounds3> MaximumBounds
				{
					Nullable<Bounds3> get();
					void set( Nullable<Bounds3> value );
				}
				/// <summary>Gets or Sets expected scene limits</summary>
				property SceneLimits^ Limits
				{
					SceneLimits^ get();
					void set( SceneLimits^ value );
				}
				
				/// <summary>Gets or Sets whether the scene is a master hardware or software scene</summary>
				property StillDesign::PhysX::SimulationType SimulationType
				{
					StillDesign::PhysX::SimulationType get();
					void set( StillDesign::PhysX::SimulationType value );
				}
				
				/// <summary>Gets or Sets if whether to enable or disable default ground plane</summary>
				property bool GroundPlaneEnabled
				{
					bool get();
					void set( bool value );
				}
				/// <summary>Gets or Sets whether to enable or disable 6 planes around maxBounds (if available)</summary>
				property bool BoundsPlanesEnabled
				{
					bool get();
					void set( bool value );
				}
				/// <summary>Gets or Sets the flags used to select scene options</summary>
				property SceneFlag Flags
				{
					SceneFlag get();
					void set( SceneFlag value );
				}
				/// <summary>Gets or Sets the stack size for the main simulation thread</summary>
				property int SimulationThreadStackSize
				{
					int get();
					void set( int value );
				}
				/// <summary>Gets or Sets thread priority of the main simulation thread</summary>
				property StillDesign::PhysX::ThreadPriority SimulationThreadPriority
				{
					StillDesign::PhysX::ThreadPriority get();
					void set( StillDesign::PhysX::ThreadPriority value );
				}
				/// <summary>Gets or Sets which (logical) processor to allocate the simulation thread to</summary>
				property unsigned int SimulateThreadMask
				{
					unsigned int get();
					void set( unsigned int value );
				}
				/// <summary>Gets or Sets the number of SDK managed worker threads used when running the simulation in parallel</summary>
				property int InternalThreadCount
				{
					int get();
					void set( int value );
				}
				/// <summary>Gets or Sets the user to specify the stack size for the worker threads created by the SDK</summary>
				property int WorkerThreadStackSize
				{
					int get();
					void set( int value );
				}
				/// <summary>Gets or Sets the thread priority of the SDK created worker threads</summary>
				property StillDesign::PhysX::ThreadPriority WorkerThreadPriority
				{
					StillDesign::PhysX::ThreadPriority get();
					void set( StillDesign::PhysX::ThreadPriority value );
				}
				/// <summary>Gets or Sets which (logical) processor to allocate SDK internal worker threads to</summary>
				property unsigned int ThreadMask
				{
					unsigned int get();
					void set( unsigned int value );
				}
				/// <summary>Gets or Sets the number of SDK managed threads which will be processing background tasks</summary>
				property int BackgroundThreadCount
				{
					int get();
					void set( int value );
				}
				/// <summary>Gets or Sets the thread priority of the SDK created background threads</summary>
				property ThreadPriority BackgroundThreadPriority
				{
					ThreadPriority get();
					void set( ThreadPriority value );
				}
				/// <summary>Gets or Sets (logical) processor to allocate SDK background threads</summary>
				property unsigned int BackgroundThreadMask
				{
					unsigned int get();
					void set( unsigned int value );
				}
				/// <summary>Gets or Sets the up axis for your world</summary>
				property int UpAxis
				{
					int get();
					void set( int value );
				}
				/// <summary>Gets or Sets the subdivision level for acceleration structures used for scene queries</summary>
				property int SubdivisionLevel
				{
					int get();
					void set( int value );
				}
				/// <summary>Gets or Sets the structure used to store static objects</summary>
				property PruningStructure StaticStructure
				{
					PruningStructure get();
					void set( PruningStructure value );
				}
				/// <summary>Gets or Sets the structure used to store dynamic objects</summary>
				property PruningStructure DynamicStructure
				{
					PruningStructure get();
					void set( PruningStructure value );
				}
				/// <summary>Hint for how much work should be done per simulation frame to rebuild the pruning structure</summary>
				property int DynamicTreeRebuildRateHint
				{
					int get();
					void set( int value );
				}
				
				/// <summary>Gets or Sets which type of broadphase to use</summary>
				property StillDesign::PhysX::BroadPhaseType BroadPhaseType
				{
					StillDesign::PhysX::BroadPhaseType get();
					void set( StillDesign::PhysX::BroadPhaseType value );
				}
				
				/// <summary>Gets or Sets the number of broadphase cells along the grid x-axis</summary>
				property int NumberOfGridCellsX
				{
					int get();
					void set( int value );
				}
				/// <summary>Gets or Sets the number of broadphase cells along the grid y-axis</summary>
				property int NumberOfGridCellsY
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
				property NxSceneDesc* UnmanagedPointer
				{
					NxSceneDesc* get();
				}
		};
	};
};