#pragma once

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::ComponentModel;

namespace StillDesign
{
	namespace PhysX
	{
		private ref class Functions
		{
			public:
				static String^ UnmanagedToManagedString( const char* string );
				static const char* ManagedToUnmanagedString( String^ string );
				
				static void OutputString( const char* string );
				
				////[EditorBrowsable(EditorBrowsableState.Never)]
				//static int GetTypeSize( Type^ typeSize );
				//static int GetObjectSize( Object^ object );
				//
				//static void CopyObjectDataToPointer( Object^ object, IntPtr^ pointer );
		};
	};
};