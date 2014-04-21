#pragma once

namespace StillDesign
{
	namespace PhysX
	{
		ref class RemoteDebugger;
		
		public ref class Foundation
		{
			private:
				NxFoundationSDK* _foundationSDK;
				
				StillDesign::PhysX::RemoteDebugger^ _remoteDebugger;
			
			internal:
				Foundation( NxFoundationSDK* foundationSDK );
			protected:
				~Foundation();
			public:
				!Foundation();
				
				property StillDesign::PhysX::RemoteDebugger^ RemoteDebugger
				{
					StillDesign::PhysX::RemoteDebugger^ get();
				}
			
			internal:
				property NxFoundationSDK* UnmanagedPointer
				{
					NxFoundationSDK* get();
				}
		};
	};
};