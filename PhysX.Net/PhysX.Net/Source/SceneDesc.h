#pragma once

#include "SceneEnum.h"
#include "TolerancesScale.h"
#include "SimulationEventCallback.h"
#include "BroadPhase.h"

namespace PhysX
{
	ref class ContactModifyCallback;
	ref class SimulationFilterShader;
	ref class BroadPhaseCallback;
	ref class SceneLimits;
	ref class SimulationFilterCallback;
	ref class CudaContextManager;

	public ref class SceneDesc : IDisposable
	{
		public:
			/// <summary>Raised before any disposing is performed.</summary>
			virtual event EventHandler^ OnDisposing;
			/// <summary>Raised once all disposing is performed.</summary>
			virtual event EventHandler^ OnDisposed;

		private:
			PxSceneDesc* _sceneDesc;

			PhysX::SimulationEventCallback^ _simulationEventCallback;
			PhysX::SimulationFilterCallback^ _simulationFilterCallback;
			PhysX::SimulationFilterShader^ _filterShader;
			PhysX::ContactModifyCallback^ _contactModifyCallback;
			PhysX::CudaContextManager^ _cudaContextManager;
			PhysX::BroadPhaseCallback^ _broadPhaseCallback;

		public:
			SceneDesc([Optional] Nullable<PhysX::TolerancesScale> tolerancesScale);
			~SceneDesc();
		protected:
			!SceneDesc();
			
		public:
			property bool Disposed
			{
				virtual bool get();
			}

			bool IsValid();
			void SetToDefault([Optional] Nullable<TolerancesScale> tolerancesScale);

			/// <summary>
			/// Gravity vector.
			/// </summary>
			/// <remarks>When setting gravity, you should probably also set bounce threshold.</remarks>
			property Vector3 Gravity
			{
				Vector3 get();
				void set(Vector3 value);
			}

			/// <summary>
			/// Selects the friction algorithm to use for simulation.
			/// </summary>
			property PhysX::FrictionType FrictionType
			{
				PhysX::FrictionType get();
				void set(PhysX::FrictionType value);
			}

			/// <summary>
			/// Flags used to select scene options.
			/// </summary>
			property SceneFlag Flags
			{
				SceneFlag get();
				void set(SceneFlag value);
			}

			property PhysX::BroadPhaseType BroadPhaseType
			{
				PhysX::BroadPhaseType get();
				void set(PhysX::BroadPhaseType value);
			}

			/// <summary>
			/// Possible notification callback.
			/// This callback will be associated with the
			/// client PX_DEFAULT_CLIENT. Please use PxScene::setSimulationEventCallback() to
			/// register callbacks for other clients.
			/// Default: NULL
			/// </summary>
			property PhysX::SimulationEventCallback^ SimulationEventCallback
			{
				PhysX::SimulationEventCallback^ get();
				void set(PhysX::SimulationEventCallback^ value);
			}

			property PhysX::SimulationFilterCallback^ SimulationFilterCallback
			{
				PhysX::SimulationFilterCallback^ get();
				void set(PhysX::SimulationFilterCallback^ value);
			}

			property PhysX::ContactModifyCallback^ ContactModifyCallback
			{
				PhysX::ContactModifyCallback^ get();
				void set(PhysX::ContactModifyCallback^ value);
			}

			property PhysX::SimulationFilterShader^ FilterShader
			{
				PhysX::SimulationFilterShader^ get();
				void set(PhysX::SimulationFilterShader^ value);
			}

			property int CCDMaximumPasses
			{
				int get();
				void set(int value);
			}

			property PhysX::CudaContextManager^ CudaContextManager
			{
				PhysX::CudaContextManager^ get();
				void set(PhysX::CudaContextManager^ value);
			}

			property PhysX::BroadPhaseCallback^ BroadPhaseCallback
			{
				PhysX::BroadPhaseCallback^ get();
				void set(PhysX::BroadPhaseCallback^ value);
			}

			property SceneLimits^ Limits
			{
				SceneLimits^ get();
				void set(SceneLimits^ value);
			}

			property float BounceThresholdVelocity
			{
				float get();
				void set(float value);
			}

			property float FrictionOffsetThreshold
			{
				float get();
				void set(float value);
			}

			property int DynamicTreeRebuildRateHint
			{
				int get();
				void set(int value);
			}

			property int SolverBatchSize
			{
				int get();
				void set(int value);
			}

			property int NumberOfContactDataBlocks
			{
				int get();
				void set(int value);
			}

			property int MaxNumberOfContactDataBlocks
			{
				int get();
				void set(int value);
			}

			property int ContactReportStreamBufferSize
			{
				int get();
				void set(int value);
			}

			property int CCDMaxPasses
			{
				int get();
				void set(int value);
			}

			property float WakeCounterResetValue
			{
				float get();
				void set(float value);
			}

			property Bounds3 SanityBounds
			{
				Bounds3 get();
				void set(Bounds3 value);
			}

			/// <summary>
			/// A slop value used to zero contact offsets from the body's COM on an axis if the offset along that axis is smaller than this threshold. Can be used to compensate for small numerical errors in contact generation.
			/// </summary>
			property float SolverOffsetSlop
			{
				float get();
				void set(float value);
			}

			/// <summary>
			/// Selects the solver algorithm to use.
			/// </summary>
			property PhysX::SolverType SolverType
			{
				PhysX::SolverType get();
				void set(PhysX::SolverType value);
			}

		internal:
			property PxSceneDesc* UnmanagedPointer
			{
				PxSceneDesc* get();
			}
	};
};