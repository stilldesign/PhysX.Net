using System;
using System.Collections.Generic;
using System.Linq;
using System.Diagnostics;

namespace PhysX.Test
{
	public class ErrorLog : PhysX.ErrorCallback
	{
		private List<string> _errors;

		public ErrorLog()
		{
			_errors = new List<string>();
		}

		public override void ReportError(ErrorCode errorCode, string message, string file, int lineNumber)
		{
			string e = string.Format("Code: {0}, Message: {1}", errorCode, message);

			_errors.Add(e);

			Trace.WriteLine(e);
		}

		public override string ToString()
		{
			if (_errors.Count == 0)
				return "No errors";
			else
				return string.Format("{0} errors. Last error: {1}", _errors.Count, _errors[_errors.Count - 1]);
		}

		public int ErrorCount
		{
			get
			{
				return _errors.Count;
			}
		}

		public bool HasErrors
		{
			get
			{
				return _errors.Any();
			}
		}

		public string LastError
		{
			get
			{
				return _errors.LastOrDefault() ?? String.Empty;
			}
		}
	}
}