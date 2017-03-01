using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace PhysX.Test
{
	[TestClass]
	public class ObjectTableTest : Test
	{
		[TestInitialize]
		public void InitalizeTest()
		{
			// Make sure the object table is completely empty at the beginning of each test
			// TODO: This need should be elimited once the object table class is changed to be a singleton pattern instead
			// of a static class
			ObjectTable.Clear();
		}

		[TestMethod]
		public void OwnershipDisposale()
		{
			// Create a hierarchy of objects -
			// Physics is the root
			//	Scene
			//		Actor1
			//		Actor2
			//	Material1
			//	Material2
			var physics = new MockPhysics();
			var scene = new MockScene();
			var mat1 = new MockMaterial();
			var mat2 = new MockMaterial();
			var actor1 = new MockActor();
			var actor2 = new MockActor();

			ObjectTable.Add(1, physics, null);
			ObjectTable.Add(2, mat1, physics);
			ObjectTable.Add(3, mat2, physics);
			ObjectTable.Add(4, scene, physics);
			ObjectTable.Add(5, actor1, scene);
			ObjectTable.Add(6, actor2, scene);

			//

			// Dispose of the root object. This should dispose all object beneath it recursively
			physics.Dispose();

			Assert.IsTrue(physics.Disposed);
			Assert.IsTrue(mat1.Disposed);
			Assert.IsTrue(mat2.Disposed);
			Assert.IsTrue(scene.Disposed);
			Assert.IsTrue(actor1.Disposed);
			Assert.IsTrue(actor2.Disposed);
		}

		[TestMethod]
		public void EnsureUnmanagedObjectIsOnlyWrappedOnce()
		{
			var obj0 = new MockPhysics();
			var obj1 = new MockPhysics();

			// Add the object at address '5'
			ObjectTable.Add(5, obj0, null);

			// We should not be able to add the same unmanaged address
			try
			{
				ObjectTable.Add(5, obj1, null);

				Assert.Fail("The unmanaged object/address has already been wrapped and added to the ObjectTable, it can not be added again, instead it should be retrieved");
			}
			catch (InvalidOperationException)
			{

			}
		}

		[TestMethod]
		public void GetObjectsOfOwnerAndType()
		{
			var physics = new MockPhysics();

			// Create 2 material
			var material1 = new MockMaterial();
			var material2 = new MockMaterial();

			// Add them to the object table with the physics parent
			ObjectTable.Add(5, material1, physics);
			ObjectTable.Add(6, material2, physics);

			// Ask for the 2 material owned by the physics
			var materialsOfPhysics = ObjectTable.GetObjectsOfOwnerAndType<MockMaterial>(physics);

			Assert.IsNotNull(materialsOfPhysics);
			Assert.AreEqual(2, materialsOfPhysics.Count());
		}

		[TestMethod]
		public void GetObjectsOfOwnerAndType_MultipleEnumerationsYieldTheSameObjects()
		{
			var physics = new MockPhysics();

			// Create 2 material
			var material1 = new MockMaterial();
			var material2 = new MockMaterial();

			// Add them to the object table with the physics parent
			ObjectTable.Add(5, material1, physics);
			ObjectTable.Add(6, material2, physics);

			// Ask for the 2 material owned by the physics
			var materialsOfPhysics = ObjectTable.GetObjectsOfOwnerAndType<MockMaterial>(physics);

			Assert.IsNotNull(materialsOfPhysics);

			// Enumerate the objects once
			Assert.AreEqual(2, materialsOfPhysics.Count());

			// Enumerate the object again
			Assert.AreEqual(2, materialsOfPhysics.Count());
		}

		[TestMethod]
		public void Disposing_RemovedFromObjectTableDictionary()
		{
			var physics = new MockPhysics();

			var material1 = new MockMaterial();
			var material2 = new MockMaterial();

			ObjectTable.Add(5, material1, physics);
			ObjectTable.Add(6, material2, physics);

			// Make sure the objects are present to begin with
			Assert.IsTrue(ObjectTable.Objects.ContainsValue(material1));
			Assert.IsTrue(ObjectTable.Objects.ContainsValue(material2));

			material2.Dispose();

			Assert.IsTrue(ObjectTable.Objects.ContainsValue(material1));
			Assert.IsFalse(ObjectTable.Objects.ContainsValue(material2));
		}

		[TestMethod]
		public void Disposing_RemovedFromOwnershipDictionary()
		{
			var physics = new MockPhysics();

			var material1 = new MockMaterial();
			var material2 = new MockMaterial();

			ObjectTable.Add(5, material1, physics);
			ObjectTable.Add(6, material2, physics);

			// Make sure the objects are present to begin with
			Assert.IsTrue(ObjectTable.Ownership.ContainsKey(material1));
			Assert.IsTrue(ObjectTable.Ownership.ContainsKey(material2));

			material2.Dispose();

			Assert.IsTrue(ObjectTable.Ownership.ContainsKey(material1));
			Assert.IsFalse(ObjectTable.Ownership.ContainsKey(material2));
		}

		[TestMethod]
		public void Disposing_RemovedFromOwnerTypeDictionary()
		{
			var physics = new MockPhysics();

			var material1 = new MockMaterial();
			var material2 = new MockMaterial();

			ObjectTable.Add(5, material1, physics);
			ObjectTable.Add(6, material2, physics);

			// Make sure the objects are present to begin with
			{
				var materialKey = new ObjectTableOwnershipType(physics, typeof(MockMaterial));

				Assert.IsTrue(ObjectTable.OwnerTypeLookup.ContainsKey(materialKey));

				var materialsOwnedByPhysics = ObjectTable.GetObjectsOfOwnerAndType<MockMaterial>(physics);

				Assert.IsNotNull(materialsOwnedByPhysics);
				Assert.AreEqual(2, materialsOwnedByPhysics.Count());
				Assert.AreEqual(material1, materialsOwnedByPhysics.ElementAt(0));
				Assert.AreEqual(material2, materialsOwnedByPhysics.ElementAt(1));
			}

			material1.Dispose();

			{
				var materialKey = new ObjectTableOwnershipType(physics, typeof(MockMaterial));

				Assert.IsTrue(ObjectTable.OwnerTypeLookup.ContainsKey(materialKey));

				var materialsOwnedByPhysics = ObjectTable.GetObjectsOfOwnerAndType<MockMaterial>(physics);

				Assert.IsNotNull(materialsOwnedByPhysics);
				Assert.AreEqual(1, materialsOwnedByPhysics.Count());
				Assert.AreEqual(material2, materialsOwnedByPhysics.ElementAt(0));
			}
		}

		[TestMethod]
		public void Disposing_OwnerTypeListIsRemovedWhenEmpty()
		{
			var physics = new MockPhysics();

			var material1 = new MockMaterial();
			var material2 = new MockMaterial();

			ObjectTable.Add(5, material1, physics);
			ObjectTable.Add(6, material2, physics);

			// Make sure the objects are present to begin with
			{
				var materialKey = new ObjectTableOwnershipType(physics, typeof(MockMaterial));

				Assert.IsTrue(ObjectTable.OwnerTypeLookup.ContainsKey(materialKey));
				Assert.IsNotNull(ObjectTable.OwnerTypeLookup[materialKey]);
			}

			material1.Dispose();
			material2.Dispose();

			{
				var materialKey = new ObjectTableOwnershipType(physics, typeof(MockMaterial));

				// As we have disposed both materials; the entry in the dictionary for Physics-MockMaterial should
				// be removed
				Assert.IsFalse(ObjectTable.OwnerTypeLookup.ContainsKey(materialKey));
			}
		}

		[TestMethod]
		public void GetObjectHandlesNull()
		{
			RigidActor actor = ObjectTable.GetObject<RigidActor>(0);

			Assert.IsNull(actor);
		}

		[TestMethod]
		[ExpectedException(typeof(PhysXException))]
		public void NullKeyIsNotAllowed()
		{
			ObjectTable.Add(0, new MockMaterial(), null);
		}

		//

		public abstract class MockDisposableObject : IDisposable
		{
			protected MockDisposableObject()
			{
				Disposed = false;
			}

			#region IDisposable Members

			public bool Disposed { get; set; }

			public event EventHandler OnDisposed;

			public event EventHandler OnDisposing;

			#endregion

			#region IDisposable Members

			public void Dispose()
			{
				if (Disposed)
					Assert.Fail("Object is already disposed");

				if (OnDisposing != null)
					OnDisposing(this, null);

				Disposed = true;

				if (OnDisposed != null)
					OnDisposed(this, null);
			}

			#endregion
		}

		public class MockPhysics : MockDisposableObject
		{
			
		}

		public class MockMaterial : MockDisposableObject
		{
			
		}

		public class MockScene : MockDisposableObject
		{
			
		}

		public class MockActor : MockDisposableObject
		{

		}
	}
}