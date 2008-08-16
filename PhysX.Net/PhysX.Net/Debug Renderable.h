#pragma once

UsingFrameworkNamespace

class NxDebugRenderable;

namespace StillDesign
{
	namespace PhysX
	{
		public value class DebugPoint
		{
			private:
				Vector3 _point;
				int _color;
			
			public:
				DebugPoint( Vector3 point, int color );
				
				property Vector3 Point
				{
					Vector3 get();
				}
				property int Color
				{
					int get();
				}
		};
		public value class DebugLine
		{
			private:
				Vector3 _point0;
				Vector3 _point1;
				int _color;
			
			public:
				DebugLine( Vector3 point0, Vector3 point1, int color );
				
				property Vector3 Point0
				{
					Vector3 get();
				}
				property Vector3 Point1
				{
					Vector3 get();
				}
				property int Color
				{
					int get();
				}
		};
		public value class DebugTriangle
		{
			private:
				Vector3 _point0;
				Vector3 _point1;
				Vector3 _point2;
				int _color;
			
			public:
				DebugTriangle( Vector3 point0, Vector3 point1, Vector3 point2, int color );
				
				property Vector3 Point0
				{
					Vector3 get();
				}
				property Vector3 Point1
				{
					Vector3 get();
				}
				property Vector3 Point2
				{
					Vector3 get();
				}
				property int Color
				{
					int get();
				}
		};
		
		public ref class DebugRenderable
		{
			private:
				const NxDebugRenderable* _debugRenderable;
			
			private:
				DebugRenderable();
			public:
				~DebugRenderable();
			protected:
				!DebugRenderable();
			
			public:
				static DebugRenderable^ FromUnmanagedPointer( const NxDebugRenderable* debugRenderable );
				
				array< DebugPoint >^ GetDebugPoints();
				array< DebugLine >^ GetDebugLines();
				array< DebugTriangle >^ GetDebugTriangles();
				
				/// <summary>Gets the Number of Points to Render</summary>
				property int PointCount
				{
					int get();
				}
				/// <summary>Gets the Number of Lines to Render</summary>
				property int LineCount
				{
					int get();
				}
				/// <summary>Gets the Number of Triangles to Render</summary>
				property int TriangleCount
				{
					int get();
				}
		};
	};
};