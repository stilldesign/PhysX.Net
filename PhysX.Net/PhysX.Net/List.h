#pragma once

#include "Read Only List.h"

namespace StillDesign
{
	namespace PhysX
	{
		generic<class T, class R>
			where R : ReadOnlyList<T>, gcnew()
		public ref class List : ListBase<T>
		{
			private:
				R _readOnlyCollection;
			
			public:
				List()
				{
					_readOnlyCollection = gcnew R();
						_readOnlyCollection->SetCollection( this );
				}
				
				property R ReadOnlyCollection
				{
					R get()
					{
						return _readOnlyCollection;
					}
				}
		};
	};
};