#pragma once

using namespace System;

namespace StillDesign
{
	namespace PhysX
	{
		public ref class BufferData abstract
		{
			protected:
				BufferData( bool objectOwner, bool dataOwner );

			internal:
				property bool ObjectOwner;
				property bool DataOwner;
		};
	};
};