using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Xml;
using System.Xml.XPath;
using SlimDX;
using SlimDX.Direct3D10;

using Buffer = SlimDX.Direct3D10.Buffer;

namespace StillDesign.PhysX.Samples
{
	/// <summary>A very basic COLLADA loader.</summary>
	/// <remarks>
	/// This basically loads the torus DAE file for use as a convex mesh.
	/// </remarks>
	public static class ColladaLoader
	{
		public static Model Load(string file, Device device)
		{
			XmlDocument document = new XmlDocument();
			document.Load(file);

			XmlNamespaceManager ns = new XmlNamespaceManager(document.NameTable);
			ns.AddNamespace("c", "http://www.collada.org/2005/11/COLLADASchema");

			// Read vertex positions
			var positionsNode = document.SelectSingleNode("/c:COLLADA/c:library_geometries/c:geometry[@id='geom-Torus001']/c:mesh/c:source[@id='geom-Torus001-positions']/c:float_array[@id='geom-Torus001-positions-array']", ns);
			var indicesNode = document.SelectSingleNode("/c:COLLADA/c:library_geometries/c:geometry[@id='geom-Torus001']/c:mesh/c:triangles/c:p", ns);

			var positions = ParseVector3s(positionsNode.InnerText).ToArray();
			var indices = ParseInts(indicesNode.InnerText).ToArray();

			// Mixing concerns here, but oh well
			var positionsBuffer = new DataStream(positions, true, false);
			var indicesBuffer = new DataStream(indices, true, false);

			var model = new Model()
			{
				VertexBuffer = new Buffer(device, positionsBuffer, positions.Length * Vector3.SizeInBytes, ResourceUsage.Default, BindFlags.VertexBuffer, CpuAccessFlags.None, ResourceOptionFlags.None),
				IndexBuffer = new Buffer(device, indicesBuffer, indices.Length * sizeof(int), ResourceUsage.Default, BindFlags.IndexBuffer, CpuAccessFlags.None, ResourceOptionFlags.None),
				IndexCount = indices.Length,
				VertexPositions = positions
			};

			return model;
		}

		private static IEnumerable<Vector3> ParseVector3s(string positionsText)
		{
			var positions = positionsText.Split(new[] { ' ', '\n' }, StringSplitOptions.RemoveEmptyEntries);

			for (int i = 0; i < positions.Length; i += 3)
			{
				float x = float.Parse(positions[i + 0]);
				float y = float.Parse(positions[i + 1]);
				float z = float.Parse(positions[i + 2]);

				yield return new Vector3(x, y, z);
			}
		}
		private static IEnumerable<int> ParseInts(string indicesText)
		{
			var indices = indicesText.Split(new[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);

			for (int i = 0; i < indices.Length; i++)
			{
				yield return int.Parse(indices[i]);
			}
		}
	}

	public class Model
	{
		public Buffer VertexBuffer { get; set; }
		public Buffer IndexBuffer { get; set; }
		public int IndexCount { get; set; }

		public Vector3[] VertexPositions { get; set; }
	}
}