#include "StdAfx.h"
#include "D6JointDrive.h"

D6JointDrive::D6JointDrive()
{
	
}
D6JointDrive::D6JointDrive(float driveStiffness, float driveDamping, float forceLimit, bool isAcceleration)
{
	Stiffness = driveStiffness;
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
		d->Stiffness = drive.stiffness;

	return d;
}
PxD6JointDrive D6JointDrive::ToUnmanaged(D6JointDrive^ drive)
{
	ThrowIfNull(drive, "drive");

	PxD6JointDrive d;
		d.damping = drive->Damping;
		d.flags = ToUnmanagedEnum(PxD6JointDriveFlag, drive->Flags);
		d.forceLimit = drive->ForceLimit;
		d.stiffness = drive->Stiffness;

	return d;
}