using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Xml;
using StillDesign.PhysX.MathPrimitives;

namespace StillDesign.PhysX.Samples
{
	public static class SoftBodySample
	{
		public static PhysX.SoftBody TeapotSoftBody(Scene scene)
		{
			var doc = new XmlDocument();
			doc.Load(@"Resources\Teapot.xml");

			// Not how NxuStream are meant to used but what ever :S
			var vertices = ReadVertices(doc.SelectSingleNode("/NXUSTREAM2/NxuPhysicsCollection/NxSoftBodyMeshDesc/vertices"));
			var tetrahedraSingles = ReadTetrahedra(doc.SelectSingleNode("/NXUSTREAM2/NxuPhysicsCollection/NxSoftBodyMeshDesc/tetrahedra"));

			var softBodyMeshDesc = new SoftBodyMeshDescription()
			{
				VertexCount = vertices.Length,
				TetrahedraCount = tetrahedraSingles.Length / 4 // Tetrahedras come in quadruples of ints
			};

			softBodyMeshDesc.AllocateVertices<Vector3>(softBodyMeshDesc.VertexCount);
			softBodyMeshDesc.AllocateTetrahedra<int>(softBodyMeshDesc.TetrahedraCount); // Note: T is an int. T is the type of each point

			softBodyMeshDesc.VertexStream.SetData(vertices);
			softBodyMeshDesc.TetrahedraStream.SetData(tetrahedraSingles);

			var memoryStream = new MemoryStream();

			Cooking.InitializeCooking();
			Cooking.CookSoftBodyMesh(softBodyMeshDesc, memoryStream);
			Cooking.CloseCooking();

			memoryStream.Position = 0;

			var softBodyMesh = scene.Core.CreateSoftBodyMesh(memoryStream);

			var desc = new SoftBodyDescription()
			{
				GlobalPose = Matrix.Translation(-30, 20, -30),
				SoftBodyMesh = softBodyMesh
			};
			desc.Flags |= SoftBodyFlag.Visualization;

			desc.MeshData.AllocatePositions<Vector3>(vertices.Length);
			desc.MeshData.AllocateIndices<int>(tetrahedraSingles.Length);

			desc.MeshData.NumberOfVertices = vertices.Length;
			desc.MeshData.NumberOfIndices = tetrahedraSingles.Length;

			desc.MeshData.MaximumVertices = vertices.Length;
			desc.MeshData.MaximumIndices = tetrahedraSingles.Length;

			var softBody = scene.CreateSoftBody(desc);

			return softBody;
		}

		private static Vector3[] ReadVertices(XmlNode node)
		{
			var numbers = Regex.Matches(node.InnerText, @"-?\d+(\.\d+)?");

			System.Diagnostics.Debug.Assert(numbers.Count % 3 == 0);

			var floats = from Match c in numbers
						 select Single.Parse(c.Groups[0].Value);

			var vertices = new Vector3[floats.Count() / 3];
			for (int i = 0; i < floats.Count(); i += 3)
			{
				float x = floats.ElementAt(i + 0);
				float y = floats.ElementAt(i + 1);
				float z = floats.ElementAt(i + 2);

				vertices[i / 3] = new Vector3(x, y, z);
			}

			return vertices;
		}
		private static int[] ReadTetrahedra(XmlNode node)
		{
			var numbers = Regex.Matches(node.InnerText, @"\d+");

			var tet = from Match c in numbers
					  select Int32.Parse(c.Groups[0].Value);

			return tet.ToArray();
		}
	}
}