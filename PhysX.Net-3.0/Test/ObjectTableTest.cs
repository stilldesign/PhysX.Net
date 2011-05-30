using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace PhysX.Test
{
	[TestClass]
	public class ObjectTableTest : Test
	{
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