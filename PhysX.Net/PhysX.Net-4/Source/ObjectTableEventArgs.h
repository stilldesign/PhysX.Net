#pragma once

namespace PhysX
{
	public ref class ObjectTableEventArgs : System::EventArgs
	{
		public:
			ObjectTableEventArgs(intptr_t unmanagedObject, Object^ managedObject)
			{
				this->UnmanagedObject = unmanagedObject;
				this->ManagedObject = managedObject;
			}
				
			property intptr_t UnmanagedObject;
			property Object^ ManagedObject;
	};
};