#pragma once 

#include "IDisposable.h"

namespace PhysX
{
	ref class ObjectTableEventArgs;
		
	public ref class ObjectTable sealed
	{
		public:
			static event System::EventHandler<ObjectTableEventArgs^>^ ObjectAdded;
			static event System::EventHandler<ObjectTableEventArgs^>^ ObjectRemoved;
			
		private:
			static Dictionary<intptr_t, Object^>^ _objectTable;
			static System::Collections::Generic::Dictionary<IDisposable^, IDisposable^>^ _ownership;
				
			static Object^ _syncObject;
			
		private:
			ObjectTable() { }
			static ObjectTable()
			{
				_objectTable = gcnew System::Collections::Generic::Dictionary<intptr_t, Object^>();
				_ownership = gcnew System::Collections::Generic::Dictionary<IDisposable^, IDisposable^>();
				
				_syncObject = gcnew Object();
			}
			
		public:
			static void Add(intptr_t pointer, IDisposable^ object, IDisposable^ owner);
				
			static bool Remove(intptr_t pointer);
			static bool Remove(Object^ object);
				
			static void Clear();
			
			static Object^ GetObject(intptr_t pointer)
			{
				return Objects[pointer];
			}
			generic<typename T>
			static T GetObject(intptr_t pointer);
			static intptr_t GetObject(Object^ object);
			
			generic<typename T> where T : ref class
			static array<T>^ GetObjectsOfType();

			static bool Contains(intptr_t pointer);
			static bool Contains(Object^ object);
				
			property int Count
			{
				static int get();
			}
			
		private:
			static void disposableObject_OnDisposing(Object^ sender, EventArgs^ e);

			static void DisposeOfObjectAndDependents(IDisposable^ disposable);
				
		internal:
			property System::Collections::Generic::Dictionary<intptr_t, Object^>^ Objects
			{
				static System::Collections::Generic::Dictionary<intptr_t, Object^>^ get()
				{
					return _objectTable;
				}
			}
	};
	
	private ref class ObjectTableEventArgs : System::EventArgs
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