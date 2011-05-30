#pragma once

#include <PxSceneDesc.h>
#include "SceneEnum.h"
#include "TolerancesScale.h"
#include <PxCpuDispatcher.h>
#include <PxTask.h>

using namespace PhysX::MathPrimitives;

namespace PhysX
{
	class CpuDis : public physx::pxtask::CpuDispatcher
	{
		public:
			virtual void submitTask( physx::pxtask::BaseTask& task )
			{
				
			}
	};

	public ref class SceneDesc : IDisposable
	{
		public:
			/// <summary>Raised before any disposing is performed.</summary>
			virtual event EventHandler^ OnDisposing;
			/// <summary>Raised once all disposing is performed.</summary>
			virtual event EventHandler^ OnDisposed;

		private:
			PxSceneDesc* _sceneDesc;

		public:
			SceneDesc();
			SceneDesc(PhysX::TolerancesScale tolerancesScale);
		private:
			void Init();
		public:
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

		internal:
			property PxSceneDesc* UnmanagedPointer
			{
				PxSceneDesc* get();
			}
	};
};