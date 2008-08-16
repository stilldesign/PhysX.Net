#pragma once

using namespace System;

namespace StillDesign
{
	namespace PhysX
	{
		public ref class DescriptorValidity
		{
			private:
				bool _isValid;
				int _errorCode;
				String^ _errorMessage;
			
			public:
				DescriptorValidity( bool isValid, String^ errorMessage );
				DescriptorValidity( bool isValid, int errorCode, String^ errorMessage );
				
				static DescriptorValidity^ Invalid( String^ message );
				
				static bool operator ==( DescriptorValidity^ descriptor, bool isValid );
				static bool operator !=( DescriptorValidity^ descriptor, bool isValid );
				
				static operator DescriptorValidity^( bool valid );
				static operator bool( DescriptorValidity^ v );
				
				property bool IsValid
				{
					bool get();
					void set( bool value );
				}
				property int ErrorCode
				{
					int get();
					void set( int value );
				}
				property String^ ErrorMessage
				{
					String^ get();
					void set( String^ value );
				}
		};
	};
};