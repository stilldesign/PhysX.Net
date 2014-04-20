#pragma once

#include "Enums.h"
#include "IDisposable.h"

using namespace System;
class NxBodyDesc;

namespace StillDesign
{
	namespace PhysX
	{
		public ref class BodyDescription
		{
			private:
				NxBodyDesc* _desc;
			
			public:
				BodyDescription();
				BodyDescription( float mass );
			internal:
				BodyDescription( NxBodyDesc* bodyDesc );
			public:
				~BodyDescription();
			protected:
				!BodyDescription();
			
			public:
				/// <summary>Resets the structure to the default</summary>
				void SetToDefault();
				/// <summary>Returns true if the descriptor is valid</summary>
				bool IsValid();
				
				/// <summary>Gets or Sets the position and orientation of the center of mass</summary>
				property Matrix MassLocalPose
				{
					Matrix get();
					void set( Matrix value );
				}
				/// <summary>Gets or Sets the diagonal mass space inertia tensor in bodies mass frame</summary>
				property Vector3 MassSpaceInertia
				{
					Vector3 get();
					void set( Vector3 value );
				}
				/// <summary>Gets or Sets the mass of body</summary>
				property float Mass
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the linear Velocity of the body</summary>
				property Vector3 LinearVelocity
				{
					Vector3 get();
					void set( Vector3 value );
				}
				/// <summary>Gets or Sets the angular velocity of the body</summary>
				property Vector3 AngularVelocity
				{
					Vector3 get();
					void set( Vector3 value );
				}
				
				/// <summary>Gets or Sets the body's initial wake up counter</summary>
				property float WakeUpCounter
				{
					float get();
					void set( float value );
				}
				
				/// <summary>Gets or Sets the linear damping applied to the body</summary>
				property float LinearDamping
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the angular damping applied to the body</summary>
				property float AngularDamping
				{
					float get();
					void set( float value );
				}
				
				/// <summary>Gets or Sets the maximum allowed angular velocity</summary>
				property float MaxAngularVelocity
				{
					float get();
					void set( float value );
				}
				
				/// <summary>Gets or Sets the CCD</summary>
				property float CCDMotionThreshold
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the Flags</summary>
				property BodyFlag BodyFlags
				{
					BodyFlag get();
					void set( BodyFlag value );
				}
				/// <summary>Gets or Sets the maximum linear velocity at which body can go to sleep</summary>
				property float SleepLinearVelocity
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the maximum angular velocity at which body can go to sleep</summary>
				property float SleepAngularVelocity
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the number of solver iterations performed when processing joint/contacts connected to this body</summary>
				property int SolverIterationCount
				{
					int get();
					void set( int value );
				}
				/// <summary>Gets or Sets the threshold for the energy-based sleeping algorithm. Only used when the BodyFlag.EnergySleepTest flag is set</summary>
				property float SleepEnergyThreshold
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the damping factor for bodies that are about to sleep</summary>
				property float SleepDamping
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the force threshold for contact reports</summary>
				property float ContactReportThreshold
				{
					float get();
					void set( float value );
				}
				
			internal:
				property NxBodyDesc* UnmanagedPointer
				{
					NxBodyDesc* get();
				}
		};
	};
};