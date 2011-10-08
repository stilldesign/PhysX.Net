using System;
using System.Collections.Generic;
using System.Linq;
using PhysX.Math;

namespace PhysX.Samples.VehicleSample
{
	public class VehicleSample : Sample
	{
		private const int
			COLLISION_FLAG_GROUND = 1 << 0,
			COLLISION_FLAG_WHEEL = 1 << 1,
			COLLISION_FLAG_CHASSIS = 1 << 2,
			COLLISION_FLAG_OBSTACLE = 1 << 3,
			COLLISION_FLAG_DRIVABLE_OBSTACLE = 1 << 4,

			COLLISION_FLAG_GROUND_AGAINST = COLLISION_FLAG_CHASSIS | COLLISION_FLAG_OBSTACLE | COLLISION_FLAG_DRIVABLE_OBSTACLE,
			COLLISION_FLAG_WHEEL_AGAINST = COLLISION_FLAG_WHEEL | COLLISION_FLAG_CHASSIS | COLLISION_FLAG_OBSTACLE,
			COLLISION_FLAG_CHASSIS_AGAINST = COLLISION_FLAG_GROUND | COLLISION_FLAG_WHEEL | COLLISION_FLAG_CHASSIS | COLLISION_FLAG_OBSTACLE | COLLISION_FLAG_DRIVABLE_OBSTACLE,
			COLLISION_FLAG_OBSTACLE_AGAINST = COLLISION_FLAG_GROUND | COLLISION_FLAG_WHEEL | COLLISION_FLAG_CHASSIS | COLLISION_FLAG_OBSTACLE | COLLISION_FLAG_DRIVABLE_OBSTACLE,
			COLLISION_FLAG_DRIVABLE_OBSTACLE_AGAINST = COLLISION_FLAG_GROUND | COLLISION_FLAG_CHASSIS | COLLISION_FLAG_OBSTACLE | COLLISION_FLAG_DRIVABLE_OBSTACLE;

		protected override void LoadContent()
		{

		}

		protected override void LoadPhysics(Scene scene)
		{
			var physics = scene.Physics;

			Vehicle4W.Initalize(scene.Physics);

			var vehicleActor = physics.CreateRigidDynamic();

			var chassisMaterial = physics.CreateMaterial(0.1f, 0.1f, 0.1f);

			var boxGeom = new BoxGeometry(3, 2, 5);
			var chassisActor = scene.Physics.CreateRigidDynamic();
			chassisActor.CreateShape(boxGeom, chassisMaterial);

			var wheelMaterial = physics.CreateMaterial(0.2f, 0.2f, 0.1f);

			var frontLeftWheelGeom = new SphereGeometry(0.5f);
			var frontRightWheelGeom = new SphereGeometry(0.5f);
			var rearLeftWheelGeom = new SphereGeometry(0.5f);
			var rearRightWheelGeom = new SphereGeometry(0.5f);

			//ConvexMeshGeometry frontLeftWheelGeom = new ConvexMeshGeometry(wheelConvexMeshes[0]);
			//PxConvexMeshGeometry frontRightWheelGeom(wheelConvexMeshes[1]);
			//PxConvexMeshGeometry rearLeftWheelGeom(wheelConvexMeshes[2]);
			//PxConvexMeshGeometry rearRightWheelGeom(wheelConvexMeshes[3]);
			//PxMaterial* wheelMaterial=material;
			FilterData wheelCollFilterData = new FilterData()
			{
				Word0 = COLLISION_FLAG_WHEEL,
				Word1 = COLLISION_FLAG_WHEEL_AGAINST
			};

			var setup = new VehicleSimpleSetup()
			{
				ChassisMass = 1500,
				ChassisMOI = ComputeChassisMOI(boxGeom.Size, 1500),
				FrontWheelMass = 20.0f,
				RearWheelMass = 20.0f,
				FrontTyreType = (int)TyreType.Slicks,
				RearTyreType = (int)TyreType.Wets,
				DiffType = VehicleDifferentialType.LS4WheelDrive,
				WheelCentreCMOffsets = new[]
			    {
			        new Vector3(-1.5f, 0, 2.5f),
			        new Vector3(1.5f, 0, 2.5f),
			        new Vector3(-1.5f, 0, -2.5f),
			        new Vector3(1.5f, 0, -2.5f)
			    }
			};

			var simData = setup.ToSimulationData();

			var s = new Vehicle4WSetupDesc()
			{
				ChassisCollisionFilterData = new FilterData(),
				ChassisMaterial = chassisMaterial,
				FrontLeftWheelGeometry = frontLeftWheelGeom,
				FrontRightWheelGeometry = frontRightWheelGeom,
				Geometries = new Vehicle4WSetupDescGeometry[]
				{
					new Vehicle4WSetupDescGeometry()
					{
						ChassisGeometry = boxGeom,
						ChassisLocalPose = Matrix.Identity
					}
				},
				Physics = physics,
				RearLeftWheelGeometry = rearLeftWheelGeom,
				RearRightWheelGeometry = rearRightWheelGeom,
				SimulationData = simData,
				VehicleActor = chassisActor,
				VehicleQueryFilterData = Vehicle4W.SetupVehicleShapeQueryFilterData(0),
				WheelCollisionFilterData = new FilterData(COLLISION_FLAG_WHEEL, COLLISION_FLAG_WHEEL_AGAINST, 0, 0),
				WheelMaterial = wheelMaterial
			};

			// Note: this is not currently working, it errors with a invalid memory exception
			var vehicle = Vehicle4W.Setup(s);
		}

		private Vector3 ComputeChassisMOI(Vector3 chassisDims, float chassisMass)
		{
			//We can approximately work out the chassis moment of inertia from the aabb.
			Vector3 chassisMOI = new Vector3
			(
				chassisDims.Y * chassisDims.Y + chassisDims.Z * chassisDims.Z,
				chassisDims.X * chassisDims.X + chassisDims.Z * chassisDims.Z,
				chassisDims.X * chassisDims.X + chassisDims.Y * chassisDims.Y
			);

			chassisMOI *= chassisMass * 0.0833f;
			//Well, the AABB moi gives rather sluggish behaviour so lets let the car turn a bit quicker.
			chassisMOI.Y *= 0.8f;

			return chassisMOI;
		}

		private Actor CreateWheelActor(Scene scene)
		{
			var wheelMaterial = scene.Physics.CreateMaterial(0.2f, 0.2f, 0.01f);

			var wheelFrontLeftGeom = new SphereGeometry(0.5f);

			var actor = scene.Physics.CreateRigidDynamic();

			actor.CreateShape(wheelFrontLeftGeom, wheelMaterial);

			scene.AddActor(actor);

			return actor;
		}

		protected override void Update(TimeSpan elapsed)
		{

		}

		protected override void Draw()
		{

		}
	}
}