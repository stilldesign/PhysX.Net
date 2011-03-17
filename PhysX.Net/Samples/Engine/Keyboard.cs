using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;

namespace StillDesign.PhysX.Samples
{
	public class Keyboard
	{
		public event KeyEventHandler OnKeyDown, OnKeyUp;

		private List<Keys> _pressedKeys;

		public Keyboard(Engine engine)
		{
			_pressedKeys = new List<Keys>();

			engine.Window.KeyDown += window_KeyDown;
			engine.Window.KeyUp += window_KeyUp;
		}

		public bool IsKeyDown(Keys key)
		{
			return PressedKeys.Contains(key);
		}

		private void window_KeyDown(object sender, KeyEventArgs e)
		{
			if (!_pressedKeys.Contains(e.KeyCode))
				_pressedKeys.Add(e.KeyCode);

			if (OnKeyDown != null)
				OnKeyDown(this, e);
		}
		private void window_KeyUp(object sender, KeyEventArgs e)
		{
			_pressedKeys.Remove(e.KeyCode);

			if (OnKeyUp != null)
				OnKeyUp(this, e);
		}

		public IEnumerable<Keys> PressedKeys
		{
			get
			{
				return _pressedKeys;
			}
		}
	}
}