#pragma once

namespace StillDesign
{
	namespace PhysX
	{
		public enum class RemoteDebuggerEventMask
		{
			// ---- Masks - Use these when calling connect
			Everything = NX_DBG_EVENTMASK_EVERYTHING,

			// Basic object
			BasicObjects = NX_DBG_EVENTMASK_BASIC_OBJECTS,
			BasicObjectsDynamicData = NX_DBG_EVENTMASK_BASIC_OBJECTS_DYNAMIC_DATA,
			BasicObjectsStaticData = NX_DBG_EVENTMASK_BASIC_OBJECTS_STATIC_DATA,
			BasicObjectsAllData = NX_DBG_EVENTMASK_BASIC_OBJECTS_ALL_DATA,

			// Joints
			Joints = NX_DBG_EVENTMASK_JOINTS,
			JointsData = NX_DBG_EVENTMASK_JOINTS_DATA,

			// Contacts
			Contacts = NX_DBG_EVENTMASK_CONTACTS,
			ContactsData = NX_DBG_EVENTMASK_CONTACTS_DATA,

			// Triggers
			Triggers = NX_DBG_EVENTMASK_TRIGGERS,

			// Profiling
			Profiling = NX_DBG_EVENTMASK_PROFILING,

			// Cloth
			Cloth = NX_DBG_EVENTMASK_CLOTH,
			ClothDynamicData = NX_DBG_EVENTMASK_CLOTH_DYNAMIC_DATA,
			ClothStaticData = NX_DBG_EVENTMASK_CLOTH_STATIC_DATA,
			ClothAllData = NX_DBG_EVENTMASK_CLOTH_ALL_DATA,

			// Fluid
			Fluid = NX_DBG_EVENTMASK_FLUID,
			FluidDynamicData = NX_DBG_EVENTMASK_FLUID_DYNAMIC_DATA,
			FluidStaticData = NX_DBG_EVENTMASK_FLUID_STATIC_DATA,
			FluidAllData = NX_DBG_EVENTMASK_FLUID_ALL_DATA
		};
		
		public enum class RemoteDebuggerEventGroup
		{
			BasicObjects = NX_DBG_EVENTGROUP_BASIC_OBJECTS,
			BasicObjectsDynamicData = NX_DBG_EVENTGROUP_BASIC_OBJECTS_DYNAMIC_DATA,
			BasicObjectStaticData = NX_DBG_EVENTGROUP_BASIC_OBJECTS_STATIC_DATA,

			// Joints
			Joints = NX_DBG_EVENTGROUP_JOINTS,
			JointData = NX_DBG_EVENTGROUP_JOINTS_DATA,

			// Contacts
			Contacts = NX_DBG_EVENTGROUP_CONTACTS,
			ContactsData = NX_DBG_EVENTGROUP_CONTACTS_DATA,

			// Triggers
			Triggers = NX_DBG_EVENTGROUP_TRIGGERS,

			// Profiling
			Profiling = NX_DBG_EVENTGROUP_PROFILING,

			// Cloth
			Cloth = NX_DBG_EVENTGROUP_CLOTH,
			ClothDynamicData = NX_DBG_EVENTGROUP_CLOTH_DYNAMIC_DATA,
			ClothStaticData = NX_DBG_EVENTGROUP_CLOTH_STATIC_DATA,

			// Soft body
			SoftBody = NX_DBG_EVENTGROUP_SOFTBODY,
			SoftBodyDynamicData = NX_DBG_EVENTGROUP_SOFTBODY_DYNAMIC_DATA,
			SoftBodyStaticData = NX_DBG_EVENTGROUP_SOFTBODY_STATIC_DATA,

			// Fluid
			Fluid = NX_DBG_EVENTGROUP_FLUID,
			FluidDynamicData = NX_DBG_EVENTGROUP_FLUID_DYNAMIC_DATA,
			FluidStaticData = NX_DBG_EVENTGROUP_FLUID_STATIC_DATA
		};
		
		public enum class RemoteDebuggerObjectType
		{
			Generic = NX_DBG_OBJECTTYPE_GENERIC,
			Actor = NX_DBG_OBJECTTYPE_ACTOR,
			Plane = NX_DBG_OBJECTTYPE_PLANE,
			Box = NX_DBG_OBJECTTYPE_BOX,
			Sphere = NX_DBG_OBJECTTYPE_SPHERE,
			Capsule = NX_DBG_OBJECTTYPE_CAPSULE,
			Cylinder = NX_DBG_OBJECTTYPE_CYLINDER,
			Convex = NX_DBG_OBJECTTYPE_CONVEX,
			Mesh = NX_DBG_OBJECTTYPE_MESH,
			Wheel = NX_DBG_OBJECTTYPE_WHEEL,
			Joint = NX_DBG_OBJECTTYPE_JOINT,
			Contact = NX_DBG_OBJECTTYPE_CONTACT,
			BoundingBox = NX_DBG_OBJECTTYPE_BOUNDINGBOX,
			Vector = NX_DBG_OBJECTTYPE_VECTOR,
			Camera = NX_DBG_OBJECTTYPE_CAMERA,
			Cloth = NX_DBG_OBJECTTYPE_CLOTH,
			SoftBody = NX_DBG_OBJECTTYPE_SOFTBODY,
			Fluid = NX_DBG_OBJECTTYPE_FLUID
		};
	};
};