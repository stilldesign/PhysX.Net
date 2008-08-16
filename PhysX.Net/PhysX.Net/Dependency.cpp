#include "StdAfx.h"



using namespace StillDesign::PhysX;

//Dependency::Dependency( ... array<StillDesign::PhysX::IDisposable^>^ dependencies )
//{
//	_dependencies = gcnew System::Collections::Generic::List<StillDesign::PhysX::IDisposable^>();
//	
//	for each( StillDesign::PhysX::IDisposable^ dependency in dependencies )
//	{
//		AddDependency( dependency );
//	}
//}
//
//void Dependency::AddDependency( StillDesign::PhysX::IDisposable^ dependency )
//{
//	if( dependency != nullptr )
//	{
//		if( dependency->IsDisposed == true )
//			throw gcnew ApplicationException( "Dependency is disposed" );
//		
//		dependency->onDisposing += gcnew EventHandler( this, &Dependency::dependency_onDisposing );
//		
//		_dependencies->Add( dependency );
//	}
//}
//void Dependency::RemoveDependency( StillDesign::PhysX::IDisposable ^dependency )
//{
//	if( dependency != nullptr )
//	{
//		dependency->onDisposing -= gcnew EventHandler( this, &Dependency::dependency_onDisposing );
//		
//		_dependencies->Remove( dependency );
//	}
//}
//
//void Dependency::dependency_onDisposing( Object^ sender, EventArgs^ e )
//{
//	//Console::WriteLine( "DISPOSE " + (this)->ToString() );
//	
//	delete this;
//}