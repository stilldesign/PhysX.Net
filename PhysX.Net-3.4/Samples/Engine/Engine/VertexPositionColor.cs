using System;
using System.Collections.Generic;
using System.Linq;
using SharpDX;

namespace PhysX.Samples
{
	public struct VertexPosition
	{
		public Vector3 Position;

		public VertexPosition(Vector3 position)
		{
			this.Position = position;
		}
		public VertexPosition(float x, float y, float z)
		{
			this.Position = new Vector3(x, y, z);
		}

		public static int SizeInBytes
		{
			get
			{
				return Vector3.SizeInBytes;
			}
		}
	}

	public struct VertexPosition4
	{
		public Vector4 Position;

		public VertexPosition4(Vector3 position)
		{
			this.Position = new Vector4(position, 1.0f);
		}
		public VertexPosition4(float x, float y, float z)
			: this(new Vector3(x, y, z))
		{

		}

		public static int SizeInBytes
		{
			get
			{
				return Vector4.SizeInBytes;
			}
		}
	}

	public struct VertexPositionNormal
	{
		public Vector3 Position;
		public Vector3 Normal;

		public VertexPositionNormal(Vector3 position, Vector3 normal)
		{
			this.Position = position;
			this.Normal = normal;
		}

		public static int SizeInBytes
		{
			get
			{
				return Vector3.SizeInBytes + Vector3.SizeInBytes;
			}
		}
	}

	public struct VertexPositionTextured
	{
		public Vector3 Position;
		public float U, V;

		public VertexPositionTextured(Vector3 position, float u, float v)
		{
			this.Position = position;
			this.U = u;
			this.V = v;
		}
		public VertexPositionTextured(float x, float y, float z, float u, float v)
		{
			this.Position = new Vector3(x, y, z);
			this.U = u;
			this.V = v;
		}

		public static int SizeInBytes
		{
			get
			{
				return Vector3.SizeInBytes + sizeof(float) + sizeof(float);
			}
		}
	}

	public struct VertexPositionNormalTextured
	{
		public float X, Y, Z;
		public Vector3 Normal;
		public float U, V;

		public VertexPositionNormalTextured(Vector3 position, Vector3 normal, float u, float v)
			: this()
		{
			this.Position = position;
			this.Normal = normal;
			this.U = u;
			this.V = v;
		}

		public Vector3 Position
		{
			get
			{
				return new Vector3(X, Y, Z);
			}
			set
			{
				X = value.X;
				Y = value.Y;
				Z = value.Z;
			}
		}

		public static int SizeInBytes
		{
			get
			{
				return
					Vector3.SizeInBytes +  // Position
					Vector3.SizeInBytes + // Normal
					Vector2.SizeInBytes; // Tex UV
			}
		}
	}
	public struct VertexPositionNormalTextured3
	{
		public float X, Y, Z;
		public Vector3 Normal;
		public float U, V, P;

		public VertexPositionNormalTextured3(Vector3 position, Vector3 normal, float u, float v, float p)
			: this()
		{
			this.Position = position;
			this.Normal = normal;
			this.U = u;
			this.V = v;
			this.P = p;
		}

		public Vector3 Position
		{
			get
			{
				return new Vector3(X, Y, Z);
			}
			set
			{
				X = value.X;
				Y = value.Y;
				Z = value.Z;
			}
		}

		public static int SizeInBytes
		{
			get
			{
				return
					Vector3.SizeInBytes +  // Position
					Vector3.SizeInBytes + // Normal
					Vector3.SizeInBytes; // Tex UVP
			}
		}
	}

	public struct VertexPositionNormalColored
	{
		public Vector3 Position;
		public Vector3 Normal;
		public int Color;

		public VertexPositionNormalColored(Vector3 position, Vector3 normal, int color)
		{
			this.Position = position;
			this.Normal = normal;
			this.Color = color;
		}

		public static int SizeInBytes
		{
			get
			{
				return Vector3.SizeInBytes + Vector3.SizeInBytes + sizeof(int);
			}
		}
	}

	public struct VertexPositionColor
	{
		public Vector4 Position;
		public Color Color;

		public VertexPositionColor(float x, float y, float z)
			: this(new Vector3(x, y, z), new Color())
		{

		}
		public VertexPositionColor(Vector3 position, int color)
			: this(position, Color.FromArgb(color))
		{

		}
		public VertexPositionColor(float x, float y, float z, int color)
			: this(new Vector3(x, y, z), Color.FromArgb(color))
		{

		}
		public VertexPositionColor(float x, float y, float z, Color color)
			: this(new Vector3(x, y, z), color)
		{

		}

		public VertexPositionColor(Vector3 position, Color color)
		{
			this.Position = new Vector4(position, 1);
			this.Color = color;
		}

		public static int SizeInBytes
		{
			get
			{
				return Vector4.SizeInBytes + Color.SizeInBytes;
			}
		}
	}

	public struct VertexTransformedTextured
	{
		public Vector4 Position;
		public float U, V;

		public VertexTransformedTextured(Vector4 position, float u, float v)
		{
			this.Position = position;
			this.U = u;
			this.V = v;
		}
		public VertexTransformedTextured(float x, float y, float z, float w, float u, float v)
		{
			this.Position = new Vector4(x, y, z, w);
			this.U = u;
			this.V = v;
		}

		public override string ToString()
		{
			return String.Format("Position: ({0:0.00}, {1:0.00}, {2:0.00}) UV: ({3:0.00}, {4:0.00})", Position.X, Position.Y, Position.Z, U, V);
		}

		public static int SizeInBytes
		{
			get
			{
				return Vector4.SizeInBytes + sizeof(float) + sizeof(float);
			}
		}
	}

	public struct VertexPositionPointSizeDiffuse
	{
		public Vector3 Position;
		private float Size;
		private int Color;

		public VertexPositionPointSizeDiffuse(Vector3 position, float size, int color)
		{
			Position = position;
			Color = color;
			Size = size;
		}
		public VertexPositionPointSizeDiffuse(float x, float y, float z, int color, float size)
		{
			Position = new Vector3(x, y, z);
			Color = color;
			Size = size;
		}

		public static int SizeInBytes
		{
			get
			{
				return Vector3.SizeInBytes + sizeof(float) + sizeof(int);
			}
		}
	}
}