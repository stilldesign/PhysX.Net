using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace PhysX.Test.Actor
{
	[TestClass]
	public class ActorTest : Test
	{
		[TestMethod]
		public void ActorCollectionOfScene()
		{
			using (var physics = CreatePhysicsAndScene())
			{
				var material = physics.Physics.CreateMaterial(0.2f, 0.3f, 0.1f);

				Assert.AreEqual(0, physics.Scene.RigidDynamicActors.Count());

				var rigidActor1 = physics.Scene.Physics.CreateRigidDynamic();

				Assert.AreEqual(1, physics.Scene.RigidDynamicActors.Count());

				var rigidActor2 = physics.Scene.Physics.CreateRigidDynamic();

				Assert.AreEqual(2, physics.Scene.RigidDynamicActors.Count());
			}
		}

		// https://github.com/stilldesign/PhysX.Net/issues/27
		[TestMethod]
		public void CreateAndDisposeRigidDynamicActor_EnsureItsRemovedFromTheObjectTable()
		{
			unsafe
			{
				using (var physics = CreatePhysicsAndScene())
				{
					var material = physics.Physics.CreateMaterial(0.2f, 0.3f, 0.1f);

					// Create
					// And assert things are setup
					Assert.AreEqual(0, physics.Scene.RigidDynamicActors.Length);

					var rigidActor1 = physics.Scene.Physics.CreateRigidDynamic();

					Assert.AreEqual(1, physics.Scene.RigidDynamicActors.Length);

					physx.PxRigidDynamic* rigidActor1Ptr = rigidActor1.UnmanagedPointer;

					Assert.AreEqual(rigidActor1, ObjectTable.Instance.Objects[(long)rigidActor1Ptr]);
					Assert.AreEqual(physics.Physics, ObjectTable.Instance.Ownership[rigidActor1]);
					Assert.AreEqual(rigidActor1, ObjectTable.Instance.OwnerTypeLookup[new ObjectTableOwnershipType
					{
						Owner = physics.Physics,
						Type = typeof(RigidDynamic)
					}].Single());

					//

					rigidActor1.Dispose();

					//

					// Actor should no longer be in RigidDynamicActors
					Assert.AreEqual(0, physics.Scene.RigidDynamicActors.Length);
					// Removed from the list of objects
					Assert.IsFalse(ObjectTable.Instance.Objects.ContainsKey((long)rigidActor1Ptr));
					// Nor in the ObjectTable's list of object owners
					Assert.IsFalse(ObjectTable.Instance.Ownership.ContainsKey(rigidActor1));
					// Nor in the ObjectTable's 'owner type lookup'
					Assert.IsFalse(ObjectTable.Instance.OwnerTypeLookup.ContainsKey(new ObjectTableOwnershipType
					{
						Owner = physics.Physics,
						Type = typeof(RigidDynamic)
					}));
				}
			}
		}
	}
}