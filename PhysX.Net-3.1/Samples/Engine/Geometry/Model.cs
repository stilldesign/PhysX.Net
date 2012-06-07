using System;
using System.Collections.Generic;
using System.Linq;
using PhysX.Math;

using Buffer = SlimDX.Direct3D10.Buffer;

namespace PhysX.Samples.Engine
{
	public class Model
	{
		public Buffer VertexBuffer { get; set; }
		public Buffer IndexBuffer { get; set; }
		public int IndexCount { get; set; }

		public Vector3[] VertexPositions { get; set; }
		public int[] Indices { get; set; }
	}
}