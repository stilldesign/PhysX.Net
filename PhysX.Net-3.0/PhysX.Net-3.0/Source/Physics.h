#include <PxPhysics.h>

namespace PhysX
{
	ref class Scene;
	ref class SceneDesc;
	ref class Material;

	public ref class Physics
	{
		private:
			PxPhysics* _physics;
			PxAllocatorCallback* _allocator;
			PxErrorCallback* _errorCallback;

			List<Scene^>^ _scenes;
			List<Material^>^ _materials;

			Physics(PxPhysics* physics);
		public:
			Physics();
			void Init();
			~Physics();
		protected:
			!Physics();

		public:
			property bool Disposed
			{
				bool get();
			}

			#pragma region Scene
			// Scene
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
			///	Creates a scene. 
			/// Creates a new material with default properties. 
			/// </summary>
			/// <param name="staticFriction">The coefficient of static friction.</param>
			/// <param name="dynamicFriction">The coefficient of dynamic friction .</param>
			/// <param name="restitution">The coefficient of restitution.</param>
			/// <returns>The new material.</returns>
			Material^ CreateMaterial(float staticFriction, float dynamicFriction, float restitution);
			#pragma endregion
	};
};