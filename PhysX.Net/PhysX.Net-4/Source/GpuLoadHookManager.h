#pragma once

namespace PhysX
{
	interface class IGpuLoadHook;

	class InternalGpuLoadHookManager : public PxGpuLoadHook
	{
	public:
		char* _debug;
		char* _checked;
		char* _profile;
		char* _dll;

		InternalGpuLoadHookManager(char* debug, char* checked, char* profile, char* dll);
		~InternalGpuLoadHookManager();

		char* CopyStr(char* str);

		virtual const char* getPhysXGpuDEBUGDllName() const;
		virtual const char* getPhysXGpuCHECKEDDllName() const;
		virtual const char* getPhysXGpuPROFILEDllName() const;
		virtual const char* getPhysXGpuDllName() const;
	};

	public ref class GpuLoadHookManager
	{
	private:
		GpuLoadHookManager() {}

	public:
		static void SetPhysXGpuLoadHook(IGpuLoadHook^ hook);
	};
}