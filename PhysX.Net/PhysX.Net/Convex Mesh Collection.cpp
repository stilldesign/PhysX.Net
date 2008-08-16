#include "StdAfx.h"

#include "Convex Mesh Collection.h"
//#include "Convex Mesh.h"

//using namespace System;
//using namespace stillDesign::PhysX;

//ConvexMeshCollection::ConvexMeshCollection()
//{
//	this->onAdd += gcnew EventHandlerItem< ConvexMesh^ >( this, &ConvexMeshCollection::ConvexMeshCollection_onAdd );
//	this->onRemove += gcnew EventHandlerItem< ConvexMesh^ >( this, &ConvexMeshCollection::ConvexMeshCollection_onRemove );
//}
//
//ConvexMeshCollection::~ConvexMeshCollection()
//{
//	this->onAdd -= gcnew EventHandlerItem< ConvexMesh^ >( this, &ConvexMeshCollection::ConvexMeshCollection_onAdd );
//	this->onRemove -= gcnew EventHandlerItem< ConvexMesh^ >( this, &ConvexMeshCollection::ConvexMeshCollection_onRemove );
//}
//
//ReadOnlyListNotifiableConstructor< ConvexMesh^ >^ ConvexMeshCollection::Create()
//{
//	ConvexMeshCollection^ list = gcnew ConvexMeshCollection();
//	
//	ReadOnlyListModifiers< ConvexMesh^ >^ modifiers = gcnew ReadOnlyListModifiers< ConvexMesh^ >
//	(
//		gcnew ReadOnlyListModifiers< ConvexMesh^ >::Add( list, &stillDesign::PhysX::ConvexMeshCollection::Add ),
//		gcnew ReadOnlyListModifiers< ConvexMesh^ >::Insert( list, &stillDesign::PhysX::ConvexMeshCollection::Insert ),
//		gcnew ReadOnlyListModifiers< ConvexMesh^ >::Remove( list, &stillDesign::PhysX::ConvexMeshCollection::Remove ),
//		gcnew ReadOnlyListModifiers< ConvexMesh^ >::RemoveAt( list, &stillDesign::PhysX::ConvexMeshCollection::RemoveAt ),
//		gcnew ReadOnlyListModifiers< ConvexMesh^ >::Clear( list, &stillDesign::PhysX::ConvexMeshCollection::Clear )
//	);
//	
//	return gcnew ReadOnlyListNotifiableConstructor< ConvexMesh^ >( list, modifiers );
//}
//
//void ConvexMeshCollection::ConvexMeshCollection_onAdd( System::Object^ sender, ConvexMesh^ item )
//{
//	item->onDisposing += gcnew EventHandler( this, &ConvexMeshCollection::ConvexMesh_onDisposing );
//}
//void ConvexMeshCollection::ConvexMeshCollection_onRemove( System::Object^ sender, ConvexMesh^ item )
//{
//	item->onDisposing -= gcnew EventHandler( this, &ConvexMeshCollection::ConvexMesh_onDisposing );
//}
//
//void ConvexMeshCollection::ConvexMesh_onDisposing( System::Object^ sender, EventArgs^ e )
//{
//	this->Remove( (ConvexMesh^)sender );
//}