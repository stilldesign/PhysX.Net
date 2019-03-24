#pragma once

namespace PhysX
{
	public interface class IGpuLoadHook
	{
		virtual property String^ DebugDllName
		{
			String^ get();
		}

		virtual property String^ CheckedDllName
		{
			String^ get();
		}

		virtual property String^ ProfileDllName
		{
			String^ get();
		}

		virtual property String^ DllName
		{
			String^ get();
		}
	};
}