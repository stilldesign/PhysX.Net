#pragma once

#include <PxScene.h>
#include "SceneFlag.h"

namespace PhysX
{
	ref class SceneDesc;

	/// <summary>
	/// A scene is a collection of bodies, deformables, particle systems and constraints which can interact.
	/// </summary>
	public ref class Scene
	{
		private:
			PxScene* _scene;

		internal:
			Scene(PxScene* scene);
		public:
			~Scene();
		protected:
			!Scene();
			
		public:
			property bool Disposed
			{
				bool get();
			}

			/// <summary>
			/// Saves the Scene descriptor.
			/// </summary>
			SceneDesc^ SaveToDesc();

			/// <summary>
			/// Get or sets the scene flags.
			/// </summary>
			property SceneFlag Flags
			{
				SceneFlag get();
				void set(SceneFlag value);
			}

		internal:
			property PxScene* UnmanagedPointer
			{
				PxScene* get();
			}
	};
};