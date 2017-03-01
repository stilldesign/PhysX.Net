using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace PhysX.Test
{
	[TestClass]
	public class ActorSerialization : Test
	{
		[TestMethod]
		public void Actor_GetConcreteTypeName()
		{
			using (var physics = CreatePhysicsAndScene())
			{
				var box = CreateBoxActor(physics.Scene, 5, 5, 5);

				var serializableActor = box.AsSerializable();

				string concreteTypeName = serializableActor.ConcreteTypeName;

				Assert.AreEqual("PxRigidDynamic", concreteTypeName);
			}
		}

		[TestMethod]
		public void Actor_GetConcreteType()
		{
			using (var physics = CreatePhysicsAndScene())
			{
				var box = CreateBoxActor(physics.Scene, 5, 5, 5);

				var serializableActor = box.AsSerializable();

				ConcreteType concreteType = serializableActor.ConcreteType;

				Assert.AreEqual(ConcreteType.RigidDynamic, concreteType);
			}
		}
	}
}