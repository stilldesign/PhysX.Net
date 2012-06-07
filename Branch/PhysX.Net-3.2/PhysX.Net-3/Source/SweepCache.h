#pragma once

#include <PxSweepCache.h> 

namespace PhysX
{
	ref class BoxGeometry;

	public ref class SweepCache
	{
	private:
		PxSweepCache* _sweepCache;

	internal:
		SweepCache(PxSweepCache* sweepCache);
	public:
		~SweepCache();
	protected:
		!SweepCache();

	public:
		void SetVolume(BoxGeometry^ box, Matrix transform);

		property PxSweepCache* UnmanagedPointer
		{
			PxSweepCache* get();
		}
	};
};