#include "StdAfx.h"

#include "Functions.h"

using namespace System::Runtime::InteropServices;

using namespace StillDesign::PhysX;

String^ StillDesign::PhysX::Functions::UnmanagedToManagedString( const char* string )
{
	return Marshal::PtrToStringAnsi( (IntPtr)(char*)string );
}
const char* StillDesign::PhysX::Functions::ManagedToUnmanagedString( String^ string )
{
	return (const char*)Marshal::StringToHGlobalAnsi( string ).ToPointer();
}
void StillDesign::PhysX::Functions::OutputString( const char* string )
{
	Console::WriteLine( UnmanagedToManagedString( string ) );
}

generic<typename T>
T StillDesign::PhysX::Functions::CloneFloatStruct( float numOfFloats, void* p_unmanaged )
{
	int size = numOfFloats * sizeof(float);

#if DEBUG
	if( sizeof(T) != size )
		throw gcnew ArgumentException( String::Format( "T must be of size {0}*float", numOfFloats ) );
#endif

	T managed = T();

	pin_ptr<T> p_managed = &managed;

	memcpy_s( p_managed, size, p_unmanaged, size );

	return managed;
}

//int StillDesign::PhysX::Functions::GetTypeSize( Type^ typeSize )
//{
//	if( !typeSize->IsValueType )
//	{
//		throw gcnew InvalidOperationException();
//	}if( typeSize->BaseType == Enum::typeid ){
//		return Marshal::SizeOf( Enum::GetUnderlyingType( typeSize ) );
//	}
//	
//	return Marshal::SizeOf( typeSize );
//}
//int StillDesign::PhysX::Functions::GetObjectSize( Object^ object )
//{
//	Type^ typeSize = (Type^)object;
//	if( typeSize != nullptr )
//		return GetTypeSize( typeSize );
//	
//	Type^ type = object->GetType();
//	if( type->IsArray )
//	{
//		int num = GetTypeSize( object->GetType()->GetElementType() );
//		
//		return ((Array^)object)->Length * num;
//	}
//	
//	return GetTypeSize( type );
//}
//void StillDesign::PhysX::Functions::CopyObjectDataToPointer( Object^ object, IntPtr^ pointer )
//{
//	int typeSize;
//	GCHandle handle;
//	Type^ objectType = object->GetType();
//	
//	if( objectType->IsArray == true )
//	{
//		handle = GCHandle::Alloc( object, GCHandleType::Pinned );
//		Type^ elementType = objectType->GetElementType();
//		typeSize = ((System::Array^)object)->Length * GetTypeSize( elementType );
//	}else{
//		Type^ enumType = object->GetType();
//		Object^ obj2 = object;
//		if( objectType->BaseType == Enum::typeid )
//		{
//			obj2 = Convert::ChangeType( object, Enum::GetUnderlyingType( enumType ), System::Globalization::CultureInfo::CurrentUICulture );
//		}else if( enumType == Boolean::typeid ){
//			bool flag = Convert::ToBoolean( object, System::Globalization::CultureInfo::CurrentUICulture );
//			memcpy( &flag, pointer->ToPointer(), 1 );
//		return;
//		}
//		
//		handle = GCHandle::Alloc( obj2, GCHandleType::Pinned );
//		typeSize = GetTypeSize( obj2->GetType() );
//	}
//	
//	IntPtr ptr = handle.AddrOfPinnedObject();
//	memcpy( ptr.ToPointer(), pointer->ToPointer(), typeSize );
//	
//	handle.Free();
//}