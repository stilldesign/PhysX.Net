using System;
using System.Collections.Generic;
using System.Linq;
using StillDesign.PhysX.MathPrimitives;

namespace StillDesign.PhysX.Samples
{
	public static class Report
	{
		public static void CreateContactReport(Scene scene, Actor groundActor)
		{
			// Contact report
			// When the capsule actor hits the ground make it bounce by using the conact report
			{
				CapsuleShapeDescription capsuleShapeDesc = new CapsuleShapeDescription(1, 5);

				ActorDescription actorDesc = new ActorDescription()
				{
					GlobalPose = Matrix.Translation(-30, 20, 0),
					BodyDescription = new BodyDescription(10.0f),
					Name = "Report Capsule",
					Shapes = { capsuleShapeDesc }
				};

				var contactReportActor = scene.CreateActor(actorDesc);

				scene.SetActorPairFlags(contactReportActor, groundActor, ContactPairFlag.All);

				scene.UserContactReport = new ContactReport(contactReportActor, groundActor);
			}

			// Trigger Reports
			{
				BoxShapeDescription boxShapeDesc = new BoxShapeDescription(15, 8, 15);
				boxShapeDesc.Flags |= (ShapeFlag.TriggerOnEnter | ShapeFlag.TriggerOnLeave);

				ActorDescription actorDesc = new ActorDescription()
				{
					GlobalPose = Matrix.Translation(-30, 4, 0),
					Shapes = { boxShapeDesc }
				};
				scene.CreateActor(actorDesc);

				scene.UserTriggerReport = new TriggerReport();
			}

			scene.UserNotify = new Notify();
		}
	}
}