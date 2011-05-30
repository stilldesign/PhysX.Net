#pragma once

namespace PhysX
{
	ref class Scene;
	ref class Aggregate;
	ref class ArticulationLink;
	value class Bounds3;

	public ref class Articulation : IDisposable
	{
		public:
			virtual event EventHandler^ OnDisposing;
			virtual event EventHandler^ OnDisposed;

		private:
			PxArticulation* _articulation;
			PhysX::Scene^ _scene;

		internal:
			Articulation(PxArticulation* articulation, PhysX::Scene^ owner);
		public:
			~Articulation();
		protected:
			!Articulation();

		public:
			property bool Disposed
			{
				virtual bool get();
			}

			/// <summary>
			/// Gets the scene which this articulation belongs to.
			/// </summary>
			property PhysX::Scene^ Scene
			{
				PhysX::Scene^ get();
			}

			/// <summary>
			/// Gets or sets the maximum projection iterations.
			/// </summary>
			property int MaximumProjectionIterations
			{
				int get();
				void set(int value);
			}

			/// <summary>
			/// Gets or sets the separation tolerance.
			/// </summary>
			property float SeparationTolerance
			{
				float get();
				void set(float value);
			}

			/// <summary>
			/// Gets or sets the number of iterations used to compute the drive response to internal forces.
			/// </summary>
			property int InternalDriveIterations
			{
				int get();
				void set(int value);
			}

			/// <summary>
			/// Gets or sets the number of iterations used to compute the drive response to external forces.
			/// </summary>
			property int ExternalDriveIterations
			{
				int get();
				void set(int value);
			}

			/// <summary>
			/// Gets the set of links in the articulation.
			/// </summary>
			property array<ArticulationLink^>^ ArticulationLinks
			{
				array<ArticulationLink^>^ get();
			}

			/// <summary>
			/// Gets the set of links in the articulation.
			/// </summary>
			property String^ Name
			{
				String^ get();
				void set(String^ value);
			}

			/// <summary>
			/// Gets the axis aligned bounding box enclosing the articulation.
			/// </summary>
			property Bounds3 WorldBounds
			{
				Bounds3 get();
			}

			/// <summary>
			/// Gets the aggregate the articulation might be a part of.
			/// </summary>
			property PhysX::Aggregate^ Aggregate
			{
				PhysX::Aggregate^ get();
			}

			/// <summary>
			/// Gets or sets an object, usually to create a 1:1 relationship with a user object.
			/// </summary>
			property Object^ UserData;

		internal:
			property PxArticulation* UnmanagedPointer
			{
				PxArticulation* get();
			}
	};
};