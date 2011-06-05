#pragma once

class PxAttachment;

namespace PhysX
{
	ref class Physics;
	ref class Scene;
	ref class Deformable;
	ref class Shape;

	public ref class Attachment : IDisposable
	{
		public:
			virtual event EventHandler^ OnDisposing;
			virtual event EventHandler^ OnDisposed;

		private:
			PxAttachment* _attachment;

		internal:
			Attachment(PxAttachment* attachment, PhysX::Physics^ owner);
		public:
			~Attachment();
		protected:
			!Attachment();

		public:
			property bool Disposed
			{
				virtual bool get();
			}

			/// <summary>
			/// Retrieve attachment positions for all deformable vertices attached to the shape.
			/// </summary>
			array<Vector3>^ GetPositions();
			/// <summary>
			/// Set attachment positions for all deformable vertices attached to the shape.
			/// </summary>
			/// <param name="positions">List of attachment positions (in shape local space for shape attachments and global space for world attachments).</param>
			void SetPositions(array<Vector3>^ positions);

			/// <summary>
			/// Retrieve vertex indices for all deformable vertices attached to the shape.
			/// </summary>
			array<int>^ GetVertexIndices();

			/// <summary>
			/// Retrieve attachment flags for all deformable vertices attached to the shape.
			/// </summary>
			array<int>^ GetFlags();

			//

			/// <summary>
			/// Retrieves the scene which this attachment belongs to.
			/// </summary>
			property PhysX::Scene^ Scene
			{
				PhysX::Scene^ get();
			}

			/// <summary>
			/// Returns the deformable whose vertices are attached.
			/// </summary>
			property PhysX::Deformable^ Deformable
			{
				PhysX::Deformable^ get();
			}

			/// <summary>
			/// Returns the shape the deformable vertices are attached to.
			/// </summary>
			property PhysX::Shape^ Shape
			{
				PhysX::Shape^ get();
			}

			/// <summary>
			/// Gets the number of deformable vertices attached to the shape.
			/// </summary>
			property int NumberOfVertices
			{
				int get();
			}

		internal:
			property PxAttachment* UnmanagedPointer
			{
				PxAttachment* get();
			}
	};
};