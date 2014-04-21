#pragma once

namespace StillDesign
{
	namespace PhysX
	{
		generic<class T>
		public delegate void EventHandlerItem( Object^ sender, T item );
	};
};