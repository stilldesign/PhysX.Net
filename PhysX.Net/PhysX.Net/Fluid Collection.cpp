#include "StdAfx.h"
//
//#include "Fluid Collection.h"
//#include "Fluid.h"
//
//using namespace System;
//using namespace stillDesign::PhysX;
//
//FluidCollection::FluidCollection()
//{
//	this->onAdd += gcnew EventHandlerItem< Fluid^ >( this, &FluidCollection::FluidCollection_onAdd );
//	this->onRemove += gcnew EventHandlerItem< Fluid^ >( this, &FluidCollection::FluidCollection_onRemove );
//}
//
//FluidCollection::~FluidCollection()
//{
//	this->onAdd -= gcnew EventHandlerItem< Fluid^ >( this, &FluidCollection::FluidCollection_onAdd );
//	this->onRemove -= gcnew EventHandlerItem< Fluid^ >( this, &FluidCollection::FluidCollection_onRemove );
//}
//
//ReadOnlyListNotifiableConstructor< Fluid^ >^ FluidCollection::Create()
//{
//	FluidCollection^ list = gcnew FluidCollection();
//	
//	ReadOnlyListModifiers< Fluid^ >^ modifiers = gcnew ReadOnlyListModifiers< Fluid^ >
//	(
//		gcnew ReadOnlyListModifiers< Fluid^ >::Add( list, &stillDesign::PhysX::FluidCollection::Add ),
//		gcnew ReadOnlyListModifiers< Fluid^ >::Insert( list, &stillDesign::PhysX::FluidCollection::Insert ),
//		gcnew ReadOnlyListModifiers< Fluid^ >::Remove( list, &stillDesign::PhysX::FluidCollection::Remove ),
//		gcnew ReadOnlyListModifiers< Fluid^ >::RemoveAt( list, &stillDesign::PhysX::FluidCollection::RemoveAt ),
//		gcnew ReadOnlyListModifiers< Fluid^ >::Clear( list, &stillDesign::PhysX::FluidCollection::Clear )
//	);
//	
//	return gcnew ReadOnlyListNotifiableConstructor< Fluid^ >( list, modifiers );
//}
//
//void FluidCollection::FluidCollection_onAdd( System::Object^ sender, Fluid^ item )
//{
//	item->onDisposing += gcnew EventHandler( this, &FluidCollection::Fluid_onDisposing );
//}
//void FluidCollection::FluidCollection_onRemove( System::Object^ sender, Fluid^ item )
//{
//	item->onDisposing -= gcnew EventHandler( this, &FluidCollection::Fluid_onDisposing );
//}
//
//void FluidCollection::Fluid_onDisposing( System::Object^ sender, EventArgs^ e )
//{
//	this->Remove( (Fluid^)sender );
//}
//
//bool FluidCollection::Contains( String^ name )
//{
//	return IndexOf( name ) != -1;
//}
//int FluidCollection::IndexOf( String^ name )
//{
//	for( int x = 0; x < this->Count; x++ )
//	{
//		if( this[ x ]->Name == name )
//			return x;
//	}
//	
//	return -1;
//}
//
//Fluid^ FluidCollection::default::get( String^ name )
//{
//	int index = IndexOf( name );
//	
//#if _DEBUG
//	if( index == -1 )
//		throw gcnew PhysicsException( String::Format( "Cannot Find Fluid '{0}'", name ) );
//#endif
//	
//	return this[ index ];
//}