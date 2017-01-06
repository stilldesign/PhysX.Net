#pragma once

#include "SceneEnum.h"
#include "TolerancesScale.h"
#include "SimulationEventCallback.h"
#include "BroadPhase.h"
#include "SimulationFilterShader.h"

namespace PhysX
{
	ref class ContactModifyCallback;
	ref class GpuDispatcher;
	interface class SimulationFilterShader;
	ref class BroadPhaseCallback;
	ref class CCDContactModifyCallback;

	public ref class SceneDesc : IDisposable
	{
		public:
			/// <summary>Raised before any disposing is performed.</summary>
			virtual event EventHandler^ OnDisposing;
			/// <summary>Raised once all disposing is performed.</summary>
			virtual event EventHandler^ OnDisposed;

		private:
			PxSceneDesc* _sceneDesc;

			SimulationEventCallback^ _simulationEventCallback;
			PhysX::SimulationFilterShader^ _filterShader;
			PhysX::ContactModifyCallback^ _contactModifyCallback;
			PhysX::GpuDispatcher^ _gpuDispatcher;
			PhysX::BroadPhaseCallback^ _broadPhaseCallback;
			PhysX::CCDContactModifyCallback^ _ccdContactModifyCallback;

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

			void SetSFS(Action^ a)
			{
				__int64* w = (__int64*)Marshal::GetFunctionPointerForDelegate(a).ToPointer();
				__int64* p = (__int64*)malloc(sizeof(__int64));
				auto i = reinterpret_cast<std::uintptr_t>(w);
				//i = 44;
				memcpy(p, &i, sizeof(uintptr_t));
				

				_sceneDesc->filterShaderData = p;
				_sceneDesc->filterShaderDataSize = sizeof(intptr_t);
			}

			property int CCDMaximumPasses
			{
				int get();
				void set(int value);
			}

			property PhysX::GpuDispatcher^ GpuDispatcher
			{
				PhysX::GpuDispatcher^ get();
				void set(PhysX::GpuDispatcher^ value);
			}

			property PhysX::BroadPhaseCallback^ BroadPhaseCallback
			{
				PhysX::BroadPhaseCallback^ get();
				void set(PhysX::BroadPhaseCallback^ value);
			}

			property PhysX::CCDContactModifyCallback^ CCDContactModifyCallback
			{
				PhysX::CCDContactModifyCallback^ get();
				void set(PhysX::CCDContactModifyCallback^ value);
			}

		internal:
			property PxSceneDesc* UnmanagedPointer
			{
				PxSceneDesc* get();
			}
	};
};