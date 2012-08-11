#include "StdAfx.h"
#include "D6JointDrive.h"

D6JointDrive::D6JointDrive()
{
	
}
D6JointDrive::D6JointDrive(float driveSpring, float driveDamping, float forceLimit, bool isAcceleration)
{
	Spring = driveSpring;
	Damping = driveDamping;
	ForceLimit = forceLimit;
	Flags = (isAcceleration ? D6JointDriveFlag::Acceleration : (D6JointDriveFlag)0);
}

D6JointDrive^ D6JointDrive::ToManaged(PxD6JointDrive drive)
{
	auto d = gcnew D6JointDrive();
		d->Damping = drive.damping;
		d->Flags = ToManagedEnum(D6JointDriveFlag, drive.flags);
		d->ForceLimit = drive.forceLimit;
		d->Spring = drive.spring;

	return d;
}
PxD6JointDrive D6JointDrive::ToUnmanaged(D6JointDrive^ drive)
{
	ThrowIfNull(drive, "drive");

	PxD6JointDrive d;
		d.damping = drive->Damping;
		d.flags = ToUnmanagedEnum(PxD6JointDriveFlag, drive->Flags);
		d.forceLimit = drive->ForceLimit;
		d.spring = drive->Spring;

	return d;
}