using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Input;

namespace PhysX.Samples.Engine
{
	public class Keyboard
	{
		public event KeyEventHandler OnKeyDown, OnKeyUp;

		private List<Key> _pressedKeys;

		public Keyboard(Engine engine)
		{
			_pressedKeys = new List<Key>();

			engine.Window.KeyDown += window_KeyDown;
			engine.Window.KeyUp += window_KeyUp;
		}

		public bool IsKeyDown(Key key)
		{
			return PressedKeys.Contains(key);
		}

		private void window_KeyDown(object sender, KeyEventArgs e)
		{
			if (!_pressedKeys.Contains(e.Key))
				_pressedKeys.Add(e.Key);

			if (OnKeyDown != null)
				OnKeyDown(this, e);
		}
		private void window_KeyUp(object sender, KeyEventArgs e)
		{
			_pressedKeys.Remove(e.Key);

			if (OnKeyUp != null)
				OnKeyUp(this, e);
		}

		public IEnumerable<Key> PressedKeys
		{
			get
			{
				return _pressedKeys;
			}
		}
	}
}