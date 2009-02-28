#pragma once

UsingFrameworkNamespace

namespace StillDesign
{
	namespace PhysX
	{
		public value class Box
		{
			public:
				Box( Vector3 center, Vector3 size );
				Box( Vector3 center, Vector3 size, Quaternion rotation );
				
				static explicit operator Box( NxBox box );
				static explicit operator NxBox( Box box );
				
				bool IsValid();
				
				property static Box Empty
				{
					Box get();
				}
				
				property Vector3 Center;
				property Vector3 Extents
				{
					Vector3 get();
					void set( Vector3 value );
				}
				property Vector3 Size;
				property Quaternion Rotation;
		};
	};
};