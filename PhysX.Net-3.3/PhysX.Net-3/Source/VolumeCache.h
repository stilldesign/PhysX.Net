#pragma once


namespace PhysX
{
	ref class Geometry;
	ref class BoxGeometry;
	ref class ActorShape;

	public enum class VolumeCacheFillStatus
	{
		Ok = PxVolumeCache::FillStatus::FILL_OK,
		OutOfMemory = PxVolumeCache::FillStatus::FILL_OUT_OF_MEMORY,
		OverMaximumCount = PxVolumeCache::FillStatus::FILL_OVER_MAX_COUNT,
		UnsupportedGeometryType = PxVolumeCache::FillStatus::FILL_UNSUPPORTED_GEOMETRY_TYPE
	};

	class InternalShapeIterator : public PxVolumeCache::Iterator
	{
	private:
		gcroot<Action<array<ActorShape^>^>^> _action;

	public:
		InternalShapeIterator(gcroot<Action<array<ActorShape^>^>^> action);

		virtual void processShapes(PxU32 count, const PxActorShape* actorShapePairs);
	};

	public ref class CacheVolumeResult
	{
	public:
		property Geometry^ Geometry;
		property Matrix Transform;
	};

	public ref class VolumeCache
	{
	private:
		PxVolumeCache* _volumeCache;

	internal:
		VolumeCache(PxVolumeCache* volumeCache);
	public:
		~VolumeCache();
	protected:
		!VolumeCache();

	public:
		VolumeCacheFillStatus Fill(Geometry^ cacheVolume, Matrix pose);

		bool IsValid();

		void Invalidate();

		CacheVolumeResult^ GetCacheVolume();

		void Foreach(Action<array<ActorShape^>^>^ action);

		void Release();

		//bool Raycast(Vector3 origin, Vector3 unitDirection, float distance, 

		property int NumberOfCachedShapes
		{
			int get();
		}

		property int MaximumNumberOfStaticShapes
		{
			int get();
			void set(int value);
		}

		property int MaximumNumberOfDynamicShapes
		{
			int get();
			void set(int value);
		}

	internal:
		property PxVolumeCache* UnmanagedPointer
		{
			PxVolumeCache* get();
		}
	};
};