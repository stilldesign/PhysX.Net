#pragma once

namespace StillDesign
{
	namespace PhysX
	{
		public value class Triangle
		{
			public:
				Triangle( Vector3 vertex0, Vector3 vertex1, Vector3 vertex2 );
				
			internal:
				static explicit operator NxTriangle( Triangle triangle );
				static explicit operator Triangle( NxTriangle triangle );
				
			public:
				Vector3 Normal();
				Vector3 Center();
				void Inflate( float fatCoeff, bool constantBorder );
				
				property Vector3 Vertex0;
				property Vector3 Vertex1;
				property Vector3 Vertex2;
				
				property Vector3 default[ int ]
				{
					Vector3 get( int index );
					void set( int index, Vector3 value );
				}
		};
	};
};