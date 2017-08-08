#pragma once


namespace PhysX
{
	[StructLayout(LayoutKind::Sequential)]
	public value class Bounds3
	{
		public:
			/// <summary>Constructs a bounds object.</summary>
			/// <param name="size">The size of the bounds.</param>
			Bounds3(Vector3 size);
			/// <summary>Constructs a bounds object.</summary>
			/// <param name="min">The minimum point.</param>
			/// <param name="min">The maximum point.</param>
			Bounds3(Vector3 min, Vector3 max);
			/// <summary>Constructs a bounds object.</summary>
			/// <param name="minX">The X component of the minimum point.</param>
			/// <param name="minY">The Y component of the minimum point.</param>
			/// <param name="minZ">The Z component of the minimum point.</param>
			/// <param name="maxX">The X component of the maximum point.</param>
			/// <param name="maxY">The Y component of the maximum point.</param>
			/// <param name="maxZ">The Z component of the maximum point.</param>
			Bounds3(float minX, float minY, float minZ, float maxX, float maxY, float maxZ);
			
		internal:
			static PxBounds3 ToUnmanaged(Bounds3 bounds);
			static Bounds3 ToManaged(PxBounds3 bounds);
				
		public:
			void Include(Vector3 vector);
			void Combine(Bounds3 bounds);
			void BoundsOfOBB(Matrix orientation, Vector3 translation, Vector3 halfDimensions);
			void Transform(Matrix orientation, Vector3 translation);
			void Scale(float scaleFactor);
			void Expand(float distance);
				
			/// <summary>Does the Bounds intersect another Bounds object</summary>
			/// <param name="bounds>The other Bounds object to check</param>
			bool Intersects(Bounds3 bounds);
			/// <summary>Is a point contained inside the Bounds</summary>
			/// <param name="point">The point to check</param>
			bool Contains(Vector3 point);
				
			/// <summary>Sets the components of Minimum and Maximum to 0</summary>
			void SetToEmpty();
				
			virtual String^ ToString() override;
				
			//
				
			/// <summary>
			/// Gets a Bounds3 object with the components of Minimum and Maximum set to 0.
			/// </summary>
			property Bounds3 Empty
			{
				static Bounds3 get();
			}
			/// <summary>
			/// Gets a Bounds3 object with the components of Minimum set to Single.MinValue and Maximum set to Single.MaxValue.
			/// </summary>
			property Bounds3 Extremes
			{
				static Bounds3 get();
			}
				
			/// <summary>Gets or Sets the minimum point of the Bounds</summary>
			property Vector3 Min;
			/// <summary>Gets or Sets the maximum point of the Bounds</summary>
			property Vector3 Max;
				
			/// <summary>Gets the center of the Bounds</summary>
			property Vector3 Center
			{
				Vector3 get();
			}
			/// <summary>Gets the size of the Bounds</summary>
			property Vector3 Size
			{
				Vector3 get();
			}
			/// <summary>Gets the extents of the Bounds which is half the size</summary>
			property Vector3 Extents
			{
				Vector3 get();
			}
				
			/// <summary>Is the Bounds empty</summary>
			property bool IsEmpty
			{
				bool get();
			}
	};
};