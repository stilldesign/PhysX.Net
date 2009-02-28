#pragma once

#include "Joint.h"

UsingFrameworkNamespace

namespace StillDesign
{
	namespace PhysX
	{
		ref class SphericalJointDescription;
		
		public ref class SphericalJoint : Joint
		{
			internal:
				SphericalJoint( NxSphericalJoint* sphericalJoint );
				
			public:
				/// <summary>Use this for changing a significant number of joint parameters at once.</summary>
				/// <param name="description">The descriptor used to set the state of the object.</param>
				void LoadFromDescription( SphericalJointDescription^ description );
				/// <summary>Saves all of the object's attributes.</summary>
				SphericalJointDescription^ SaveToDescription();
				
				/// <summary>Gets or Sets the current flag settings.</summary>
				property RevoluteJointFlag Flags
				{
					RevoluteJointFlag get();
					void set( RevoluteJointFlag value );
				}
				/// <summary>Gets or Sets the projection mode.</summary>
				property JointProjectionMode ProjectionMode
				{
					JointProjectionMode get();
					void set( JointProjectionMode value );
				} 
			
			internal:
				property NxSphericalJoint* UnmanagedPointer
				{
					NxSphericalJoint* get() new;
				}
		};
	};
};