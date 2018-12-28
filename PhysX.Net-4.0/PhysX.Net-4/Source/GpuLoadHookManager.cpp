#include "StdAfx.h"
#include "GpuLoadHookManager.h"
#include "IGpuLoadHook.h"

InternalGpuLoadHookManager::InternalGpuLoadHookManager(char* debug, char* checked, char* profile, char* dll)
{
	_debug = CopyStr(debug);
	_checked = CopyStr(checked);
	_profile = CopyStr(profile);
	_dll = CopyStr(dll);
}
InternalGpuLoadHookManager::~InternalGpuLoadHookManager()
{
	delete[] _debug;
	delete[] _checked;
	delete[] _profile;
	delete[] _dll;
}

char* InternalGpuLoadHookManager::CopyStr(char* str)
{
	int l = strlen(str) + 1;
	char* str2 = new char[l];
	ZeroMemory(str2, l);
	strcpy(str2, str);
	return str2;
}

const char* InternalGpuLoadHookManager::getPhysXGpuDEBUGDllName() const
{
	return _debug;
}
const char* InternalGpuLoadHookManager::getPhysXGpuCHECKEDDllName() const
{
	return _checked;
}
const char* InternalGpuLoadHookManager::getPhysXGpuPROFILEDllName() const
{
	return _profile;
}
const char* InternalGpuLoadHookManager::getPhysXGpuDllName() const
{
	return _dll;
}

//

void GpuLoadHookManager::SetPhysXGpuLoadHook(IGpuLoadHook^ hook)
{
	ThrowIfNull(hook, "hook");
	
	char* debug = Util::ToUnmanagedString(hook->DebugDllName);
	char* checked = Util::ToUnmanagedString(hook->CheckedDllName);
	char* profile = Util::ToUnmanagedString(hook->ProfileDllName);
	char* dll = Util::ToUnmanagedString(hook->DllName);

	// TODO: As PxSetPhysXGpuLoadHook takes a copy of the char pointer instead of the chars themselves, we need to keep
	// the InternalGpuLoadHookManager alive (as not to delete the char*s), but I'm not sure when PhysX uses these char* values
	// So for now, just leave this variable alive
	auto i = new InternalGpuLoadHookManager(debug, checked, profile, dll);
	PxSetPhysXGpuLoadHook(i);

	Marshal::FreeHGlobal((IntPtr)debug);
	Marshal::FreeHGlobal((IntPtr)checked);
	Marshal::FreeHGlobal((IntPtr)profile);
	Marshal::FreeHGlobal((IntPtr)dll);
}