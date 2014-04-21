#pragma once

#include "IDisposable.h"

class NxForceFieldKernel;

namespace StillDesign
{
	namespace PhysX
	{
		public ref class ForceFieldKernel abstract : IDisposable
		{
			public:
				virtual event EventHandler^ OnDisposing;
				virtual event EventHandler^ OnDisposed;
				
			private:
				NxForceFieldKernel* _kernel;
				
				Object^ _userData;
				
			protected:
				ForceFieldKernel( NxForceFieldKernel* kernel );
			public:
				~ForceFieldKernel();
			protected:
				!ForceFieldKernel();
			public:
				property bool IsDisposed
				{
					virtual bool get();
				}
				
			public:
				/// <summary>Gets or Sets an abitary 1:1 object</summary>
				property Object^ UserData
				{
					Object^ get();
					void set( Object^ value );
				}
				
			internal:
				property NxForceFieldKernel* UnmanagedPointer
				{
					NxForceFieldKernel* get();
				}
		};
	};
};