#pragma once

#include "Enums.h"
#include "Description.h"

namespace StillDesign
{
	namespace PhysX
	{
		public ref class CoreDescription
		{
			private:
				NxPhysicsSDKDesc* _desc;
			
			public:
				CoreDescription();
			internal:
				CoreDescription( NxPhysicsSDKDesc* desc );
			public:
				~CoreDescription();
			protected:
				!CoreDescription();
				
			public:
				/// <summary>Returns true if the descriptor is valid</summary>
				bool IsValid();
				/// <summary>Resets the structure to the default</summary>
				void SetToDefault();
				
				/// <summary>Gets or Sets the size of hardware mesh pages. Currently only the value 65536 is supported</summary>
				property int HardwarePageSize
				{
					int get();
					void set( int value );
				}
				/// <summary>Gets or Sets the maximum number of hardware pages supported concurrently on hardware. The valid value must be power of 2</summary>
				property int HardwarePageMaximum
				{
					int get();
					void set( int value );
				}
				/// <summary>Gets or Sets the maximum number of convex meshes which will be resident on hardware. The valid value must be power of 2</summary>
				property int HardwareConvexMaximum
				{
					int get();
					void set( int value );
				}
				/// <summary>Thread affinity mask for the background cooker thread. Defaults to 0 which means the SDK determines the affinity</summary>
				property unsigned int CookerThreadMask
				{
					unsigned int get();
					void set( unsigned int value );
				}
				/// <summary>Gets or Sets SDK creation flags</summary>
				property CoreCreationFlag Flags
				{
					CoreCreationFlag get();
					void set( CoreCreationFlag value );
				}
			
			internal:
				property NxPhysicsSDKDesc* UnmanagedPointer
				{
					NxPhysicsSDKDesc* get();
				}
		};
	};
};