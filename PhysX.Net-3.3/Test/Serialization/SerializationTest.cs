using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace PhysX.Test.Serialization
{
	[TestClass]
	public class SerializationTest : Test
	{
		[TestMethod]
		public void BasicSingleCubeSerialization()
		{
			using (var core = CreatePhysicsAndScene())
			{
				var box = CreateBoxActor(core.Scene, 5, 5, 5);

				var collection = core.Physics.CreateCollection();
				collection.Add(box);

				var sr = PhysX.Serialization.CreateSerializationRegistry(core.Physics);

				using (var serializeStream = new MemoryStream())
				{
					bool result = PhysX.Serialization.SerializeCollectionToXml(serializeStream, collection, sr);

					Assert.IsTrue(result);

					serializeStream.Flush();

					Assert.IsTrue(serializeStream.Length > 0);

					string xml;
					using (StreamReader reader = new StreamReader(serializeStream))
					{
						xml = reader.ReadToEnd();
					}
				}
			}
		}

		//[TestMethod]
		//public void DeserializeCollection()
		//{
		//    byte[] serialzedScene;

		//    // Serialize
		//    using (var core = CreatePhysicsAndScene())
		//    {
		//        CreateBoxActor(core.Scene, 5, 5, 5);

		//        var collection = core.Physics.CreateCollection();

		//        using (var serializeStream = new MemoryStream())
		//        {
		//            collection.CollectPhysicsForExport(core.Physics);

		//            collection.Serialize(serializeStream);
		//            serializeStream.Flush();
		//            serializeStream.Position = 0;

		//            serialzedScene = serializeStream.ToArray();
		//        }
		//    }

		//    // Deserialize
		//    using (var core = CreatePhysicsAndScene())
		//    {
		//        var collection = core.Physics.CreateCollection();

		//        using (var serializeStream = new MemoryStream())
		//        {
		//            serializeStream.Write(serialzedScene, 0, serialzedScene.Length);
		//            serializeStream.Position = 0;

		//            bool result = collection.Deserialize(serializeStream);

		//            Assert.IsTrue(result);
		//        }
		//    }
		//}
	}
}