#pragma once 

namespace StillDesign
{
	namespace PhysX
	{
		ref class OwnershipObjects;
		ref class ObjectTableEventArgs;
		
		private ref class ObjectTable sealed
		{
			public:
                static event System::EventHandler<ObjectTableEventArgs^>^ ObjectAdded;
                static event System::EventHandler<ObjectTableEventArgs^>^ ObjectRemoved;
			
			private:
				static System::Collections::Generic::Dictionary<intptr_t, Object^>^ _objectTable;
				static System::Collections::Generic::Dictionary<Object^, OwnershipObjects^>^ _ownership;
				
				static Object^ _syncObject;
				
			private:
				static ObjectTable()
				{
					_objectTable = gcnew System::Collections::Generic::Dictionary<intptr_t, Object^>();
					_ownership = gcnew System::Collections::Generic::Dictionary<Object^, OwnershipObjects^>();
					
					_syncObject = gcnew Object();
				}
				
			public:
				static void Add( intptr_t pointer, Object^ object );
				static void Add( intptr_t pointer, Object^ object, Object^ owner );
				
				static bool Remove( intptr_t pointer );
				static bool Remove( Object^ object );
				
				static void Clear();
				
				generic<class T>
				static T GetObject( intptr_t pointer );
				static intptr_t GetObject( Object^ object );
				
				//generic<class T>
				//where T : ref class
				//static T GetObjectOrNull( intptr_t pointer );
				
				//generic<class T>
				//static T GetObjectByIndexIfType( int index );
				//generic<class T>
				//where T : ref class
				//static array<T>^ GetObjectsOfType();
				
				static bool Contains( intptr_t pointer );
				
				static void AddOwnership( Object^ object, Object^ owner );
				
				property int Count
				{
					static int get();
				}
				
			private:
				static void _objectTable_OnDisposing( Object^ sender, EventArgs^ e );
				
			internal:
				property System::Collections::Generic::Dictionary<intptr_t, Object^>^ Objects
				{
					static System::Collections::Generic::Dictionary<intptr_t, Object^>^ get()
					{
						return _objectTable;
					}
				}
		};
		
		private ref class OwnershipObjects : System::Collections::Generic::List<Object^>
		{
			
		};
		
		private ref class ObjectTableEventArgs : System::EventArgs
		{
			public:
				ObjectTableEventArgs( intptr_t unmanagedObject, Object^ managedObject )
				{
					this->UnmanagedObject = unmanagedObject;
					this->ManagedObject = managedObject;
				}
				
				property intptr_t UnmanagedObject;
				property Object^ ManagedObject;
		};
	};
};