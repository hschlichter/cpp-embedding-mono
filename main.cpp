#include <iostream>
#include <mono/jit/jit.h>
#include <mono/metadata/loader.h>
#include <mono/metadata/assembly.h>
#include <string>

MonoMethod* find_method(MonoClass* klass, const char* name) {
	MonoMethod* method = nullptr;
	MonoMethod* m = nullptr;
	void* iter = nullptr;
	while ((m = mono_class_get_methods(klass, &iter))) {
		if (strcmp(mono_method_get_name(m), name) == 0) {
			method = m;
		}
	}

	return method;
}

MonoString* interop_fubar() {
	std::cout << "fubar interop called" << std::endl;
	return mono_string_new(mono_domain_get(), "heyho");
}

/*
 * mcs -t:library *.cs
 */

int main(int argc, char* argv[]) {
	std::cout << "hello world" << std::endl;

	auto domain = mono_jit_init("hello_world_test");

	mono_add_internal_call("Test.Interop::Fubar()", reinterpret_cast<void*>(interop_fubar));

	auto assembly = mono_domain_assembly_open(domain, "hello.dll");
	if (!assembly) {
		return 1;
	}

	auto image = mono_assembly_get_image(assembly);
	auto klass = mono_class_from_name(image, "Test", "Hello");
	if (!klass) {
		return 1;
	}

	auto instance = mono_object_new(domain, klass);
	mono_runtime_object_init(instance);

	auto method = find_method(klass, "Update");
	if (!method) {
		return 1;
	}

	mono_runtime_invoke(method, instance, nullptr, nullptr);

	mono_jit_cleanup(domain);
	return 0;
}
