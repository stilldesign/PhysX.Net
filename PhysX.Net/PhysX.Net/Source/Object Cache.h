#pragma once 

namespace StillDesign
{
	namespace PhysX
	{
		private ref class ObjectCache
		{
			private:
				static System::Collections::Generic::Dictionary<intptr_t, Object^>^ _cache;
				
			private:
				static ObjectCache()
				{
					_cache = gcnew System::Collections::Generic::Dictionary<intptr_t, Object^>();
				}
				
			public:
				static void Add( intptr_t pointer, Object^ object );
				
				static bool Remove( intptr_t pointer );
				static bool Remove( Object^ object );
				
				generic<class T>
				//where T : ref class
				static T GetObject( intptr_t pointer );
				//generic<class T>
				//where T : ref class
				//static T GetObjectOrNull( intptr_t pointer );
				
				//generic<class T>
				//static T GetObjectByIndexIfType( int index );
				//generic<class T>
				//where T : ref class
				//static array<T>^ GetObjectsOfType();
				
			private:
				static void _cache_onDisposing( Object^ sender, EventArgs^ e );
				
			public:
				property System::Collections::Generic::Dictionary<intptr_t, Object^>^ Cache
				{
					static System::Collections::Generic::Dictionary<intptr_t, Object^>^ get()
					{
						return _cache;
					}
				}
		};
	};
};