using System;
using System.Runtime.CompilerServices;

namespace Test {
	public class Interop {

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static string Fubar();
	}
}
