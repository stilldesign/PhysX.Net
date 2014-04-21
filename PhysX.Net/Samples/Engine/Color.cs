using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using SlimDX;

namespace StillDesign.PhysX.Samples
{
	[StructLayout(LayoutKind.Sequential)]
	public struct Color
	{
		public const int SizeInBytes = 16; // 4 bytes x RGBA

		public Color(float r, float g, float b, float a = 1.0f)
			: this()
		{
			this.Alpha = a;
			this.Red = r;
			this.Green = g;
			this.Blue = b;
		}

		public int ToArgb()
		{
			int a = (int)(this.Alpha * byte.MaxValue);
			int r = (int)(this.Red * byte.MaxValue);
			int g = (int)(this.Green * byte.MaxValue);
			int b = (int)(this.Blue * byte.MaxValue);

			return (a << 24) | (r << 16) | (g << 8) | (b << 0);
		}

		/// <summary>Returns a color structure based on the color input</summary>
		/// <param name="color">The color to use (AARRGGBB)</param>
		public static Color FromArgb(int color)
		{
			byte a = (byte)((color & 0xFF000000) >> 24);
			byte r = (byte)((color & 0x00FF0000) >> 16);
			byte g = (byte)((color & 0x0000FF00) >> 8);
			byte b = (byte)((color & 0x000000FF) >> 0);

			return Color.FromArgb(r, g, b, a);
		}
		public static Color FromArgb(byte r, byte g, byte b, byte a = 255)
		{
			return new Color(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
		}
		//public static Color FromArgb( byte r, byte g, byte b, byte a )
		//{
		//    int ia = ( (int)a << 24 );
		//    int ir = ( (int)r << 16 );
		//    int ig = ( (int)g << 8 );
		//    int ib = ( (int)b << 0 );

		//    int color = ia | ir | ig | ib;

		//    return Color.FromArgb( color );
		//}

		/// <summary>Converts a Vector4 to a Color object.</summary>
		/// <param name="vector">A vector where each component in the vector maps to a color component; X: Red, Y: Green, Z: Blue, W: Alpha.</param>
		public static Color FromVector4(Vector4 vector)
		{
			return new Color(vector.X, vector.Y, vector.Z, vector.W);
		}

		public static Color? TryParse(string hexColor)
		{
			try
			{
				return Parse(hexColor);
			}
			catch
			{
				return null;
			}
		}
		/// <summary>Parse a string based hex representation of a 32 bit color value.</summary>
		/// <param name="hexColor">A hex string representing the color. Acceptable inputs are: [#]RGB, [#]RGBA, [#]RRGGBBAA</param>
		public static Color Parse(string hexColor)
		{
			if (hexColor == null)
				throw new ArgumentNullException("hexColor");
			if (string.IsNullOrWhiteSpace(hexColor))
				throw new ArgumentException("Hex color string is empty", "hexColor");

			if (hexColor[0] == '#')
				hexColor = hexColor.Substring(1);

			hexColor = ExpandHexStringInternal(hexColor);

			byte r, g, b, a;

			if (hexColor.Length == 6)
			{
				r = ParseAsByte(hexColor, 0, 2);
				g = ParseAsByte(hexColor, 2, 2);
				b = ParseAsByte(hexColor, 4, 2);
				a = 0xFF;
			}
			else if (hexColor.Length == 8)
			{
				r = ParseAsByte(hexColor, 0, 2);
				g = ParseAsByte(hexColor, 2, 2);
				b = ParseAsByte(hexColor, 4, 2);
				a = ParseAsByte(hexColor, 6, 2);
			}
			else
			{
				throw new ArgumentException("Hex color string must be of length 3, 4, 6 or 8 (excluding the leading hash character)", "hexColor");
			}

			return Color.FromArgb(r, g, b, a);
		}
		private static byte ParseAsByte(string hexNumber, int charIndex, int length)
		{
			try
			{
				return Convert.ToByte(hexNumber.Substring(charIndex, length), 16);
			}
			catch
			{
				throw new ArgumentException(String.Format("Unable to parse hex color string component. From: {0} To: {1} In: {2}", charIndex, length, hexNumber));
			}
		}

		/// <summary>Expands the hex string to 2 bytes per component.</summary>
		/// <param name="hexColor">A hex representation of a 32 bit color value. Values can be [#]RGB or [#]RGBA</param>
		public static string ExpandHexString(string hexColor)
		{
			if (string.IsNullOrWhiteSpace(hexColor))
				throw new ArgumentException("Hex color string is empty", "hexColor");

			bool leadingHash = false;
			if (hexColor[0] == '#')
			{
				hexColor = hexColor.Substring(1);
				leadingHash = true;
			}

			if (hexColor.Length == 3)
			{
				// RGB = RRGGBB
				hexColor = String.Format("{0}{0}{1}{1}{2}{2}", hexColor[0], hexColor[1], hexColor[2]);
			}
			else if (hexColor.Length == 4)
			{
				// RGBA = RRGGBBAA
				hexColor = String.Format("{0}{0}{1}{1}{2}{2}{3}{3}", hexColor[0], hexColor[1], hexColor[2], hexColor[3]);
			}
			else
			{
				throw new FormatException("Hex must of length 3 or 4");
			}

			if (leadingHash)
				return "#" + hexColor;
			else
				return hexColor;
		}
		private static string ExpandHexStringInternal(string hexColor)
		{
			// Leading # is stripped off by caller

			// Expand the short hand versions (RGB and RGBA) into full 2 byte representations
			if (hexColor.Length == 3)
			{
				return ExpandHexString(hexColor);
			}
			else if (hexColor.Length == 4)
			{
				return ExpandHexString(hexColor);
			}
			else
			{
				return hexColor;
			}
		}

		public override string ToString()
		{
			return String.Format("R: {0:0.00} G: {1:0.00} B: {2:0.00}, A: {3:0.00}", this.Red, this.Green, this.Blue, this.Alpha);
		}
		/// <summary>Produces a 32 bit hex string representation of this color. Format is #RRGGBBAA</summary>
		public string ToHexString()
		{
			int r = (int)(this.Red * byte.MaxValue);
			int g = (int)(this.Green * byte.MaxValue);
			int b = (int)(this.Blue * byte.MaxValue);
			int a = (int)(this.Alpha * byte.MaxValue);

			return String.Format("#{0:X2}{1:X2}{2:X2}{3:X2}", r, g, b, a);
		}

		/// <summary>Converts the color to a vector (RGBA).</summary>
		/// <returns></returns>
		public Vector4 ToVector4()
		{
			return new Vector4(this.Red, this.Green, this.Blue, this.Alpha);
		}
		/// <summary>Converts the Color struct to a SlimDX Color4 struct.</summary>
		/// <returns></returns>
		public Color4 ToColor4()
		{
			return new Color4(this.Alpha, this.Red, this.Green, this.Blue);
		}

		public override bool Equals(object obj)
		{
			return obj != null && obj is Color && (Color)obj == this;
		}
		public override int GetHashCode()
		{
			return base.GetHashCode();
		}

		public static bool operator ==(Color x, Color y)
		{
			return
				x.Alpha == y.Alpha &&
				x.Red == y.Red &&
				x.Green == y.Green &&
				x.Blue == y.Blue;
		}
		public static bool operator !=(Color x, Color y)
		{
			return !(x == y);
		}

		//

		public float Red { get; set; }
		public float Green { get; set; }
		public float Blue { get; set; }
		public float Alpha { get; set; }
	}
}