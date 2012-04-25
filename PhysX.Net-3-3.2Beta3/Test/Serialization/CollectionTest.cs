using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.IO;

namespace PhysX.Test.Serialization
{
	[TestClass]
	public class CollectionTest : Test
	{
		[TestMethod]
		public void SerializeCollection()
		{
			using (var core = CreatePhysicsAndScene())
			{
				CreateBoxActor(core.Scene, 5, 5, 5);

				var collection = core.Physics.CreateCollection();

				collection.CollectPhysicsForExport(core.Physics);

				using (var serializeStream = new MemoryStream())
				{
					collection.Serialize(serializeStream);

					serializeStream.Flush();

					Assert.IsTrue(serializeStream.Length > 0);
				}
			}
		}

		[TestMethod]
		public void DeserializeCollection()
		{
			byte[] serialzedScene;

			using (var core = CreatePhysicsAndScene())
			{
				CreateBoxActor(core.Scene, 5, 5, 5);

				var collection = core.Physics.CreateCollection();

				using (var serializeStream = new MemoryStream())
				{
					collection.CollectPhysicsForExport(core.Physics);

					collection.Serialize(serializeStream);
					serializeStream.Flush();
					serializeStream.Position = 0;

					serialzedScene = serializeStream.ToArray();
				}
			}

			using (var core = CreatePhysicsAndScene())
			{
				var collection = core.Physics.CreateCollection();

				using (var serializeStream = new MemoryStream())
				{
					serializeStream.Write(serialzedScene, 0, serialzedScene.Length);
					serializeStream.Position = 0;

					bool result = collection.Deserialize(serializeStream);

					Assert.IsTrue(result);
				}
			}
		}
	}
}