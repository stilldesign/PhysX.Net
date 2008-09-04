
#pragma once



namespace StillDesign
{
	namespace PhysX
	{

		public ref class PhysXException : public System::Exception
		{
		internal:
			PhysXException( System::String^ message )
				: System::Exception( message )
			{
			}
		};

	}
}