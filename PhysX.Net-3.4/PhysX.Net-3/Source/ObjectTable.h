#pragma once

#include "IDisposable.h"
#include "ObjectTableOwnershipType.h"
#include "ObjectTableEventArgs.h"

namespace PhysX
{
	ref class ObjectTableEventArgs;
	
	// TODO: Make ObjectTable an instance class instead of containing all static data and methods, but then wrap in singleton pattern.
	/// <summary>
	/// Manages lookups and disposals for unmanaged-managed pairs.
	/// This class is not thread safe.
	/// </summary>
	public ref class ObjectTable sealed
	{
		public:
			static event EventHandler<ObjectTableEventArgs^>^ ObjectAdded;
			static event EventHandler<ObjectTableEventArgs^>^ ObjectRemoved;
			
		private:
			// A collection of native objects to their managed version
			static Dictionary<intptr_t, Object^>^ _objectTable;
			// A collection of managed objects to their managed owner
			static Dictionary<IDisposable^, IDisposable^>^ _ownership;
			// A collection of ownership-type pairs to a collection of objects
			// This dictionary is used to lookup objects which are owned by X and of type Y. (e.g. property Physics.Cloths > Key: Owner: physics, Type: Cloth yields a collection of Cloth).
			static Dictionary<ObjectTableOwnershipType, List<Object^>^>^ _ownerTypeLookup;
			
			static bool _performingDisposal;
			
		private:
			ObjectTable();
			static ObjectTable()
			{
				_objectTable = gcnew Dictionary<intptr_t, Object^>();
				_ownership = gcnew Dictionary<IDisposable^, IDisposable^>();
				_ownerTypeLookup = gcnew Dictionary<ObjectTableOwnershipType, List<Object^>^>();
				
				_performingDisposal = false;
			}
			
		public:
			static void Add(intptr_t pointer, IDisposable^ object, IDisposable^ owner);
			static void EnsureUnmanagedObjectIsOnlyWrappedOnce(intptr_t unmanaged, Type^ managedType);
			
			static void AddObjectOwner(IDisposable^ object, IDisposable^ owner);
			static void AddOwnerTypeLookup(Object^ owner, IDisposable^ object);

			static bool Remove(intptr_t pointer);
			static bool Remove(Object^ object);
				
			static void Clear();
			
			generic<typename T>
			static T GetObject(intptr_t pointer);

			generic<typename T>
			static T TryGetObject(intptr_t pointer);

			static intptr_t GetObject(Object^ object);

			generic<typename T>
			static array<T>^ GetObjects(intptr_t* pointers, int count);
			
			generic<typename T> where T : ref class
			static array<T>^ GetObjectsOfType();

			generic<typename T> where T : ref class
			static array<T>^ GetObjectsOfOwnerAndType(Object^ owner);

			static bool Contains(intptr_t pointer);
			static bool Contains(Object^ object);
			
		private:
			static void disposableObject_OnDisposing(Object^ sender, EventArgs^ e);

			static void DisposeOfObjectAndDependents(IDisposable^ disposable);

			static array<IDisposable^>^ GetDependents(IDisposable^ disposable);
			static void GetDependents(IDisposable^ disposable, List<IDisposable^>^ disposables);
			
		public:
			property int Count
			{
				static int get();
			}

			property Dictionary<intptr_t, Object^>^ Objects
			{
				static Dictionary<intptr_t, Object^>^ get();
			}
			property Dictionary<IDisposable^, IDisposable^>^ Ownership
			{
				static Dictionary<IDisposable^, IDisposable^>^ get();
			}
			property Dictionary<ObjectTableOwnershipType, List<Object^>^>^ OwnerTypeLookup
			{
				static Dictionary<ObjectTableOwnershipType, List<Object^>^>^ get();
			}
	};
};