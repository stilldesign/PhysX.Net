#include "StdAfx.h"

#include "Read Only List.h"
#include "List Base.h"

using namespace StillDesign::PhysX;

generic<class T>
ReadOnlyList<T>::ReadOnlyList( ListBase<T>^ list ) : System::Collections::ObjectModel::ReadOnlyCollection<T>( list )
{
	list->ItemAdded += gcnew EventHandlerItem<T>( this, &ReadOnlyList<T>::ReadOnlyList_ItemAdded );
	list->ItemRemoved += gcnew EventHandlerItem<T>( this, &ReadOnlyList<T>::ReadOnlyList_ItemRemoved );
}

generic<class T>
void ReadOnlyList<T>::ReadOnlyList_ItemAdded( Object^ sender, T item )
{
	ItemAdded( sender, item );
}
generic<class T>
void ReadOnlyList<T>::ReadOnlyList_ItemRemoved( Object^ sender, T item )
{
	ItemRemoved( sender, item );
}