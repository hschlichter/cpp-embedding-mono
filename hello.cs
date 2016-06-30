using System;

namespace Test {
	class Hello {
		string message = "Hello from Mono C#.";

		Hello() {
			Console.WriteLine("Hello constructor.");
		}

		void Update() {
			Console.WriteLine("Yay update is called.");
			Console.WriteLine(this.Message);
			var fubar = Test.Interop.Fubar();
			Console.WriteLine(fubar);
		}

		string Message {
			get {
				return message;
			}
		}
	}
}
