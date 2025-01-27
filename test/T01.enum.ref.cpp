// File: T01_enum.cpp
#include <T01.enum.hpp> // A
#include <T01.enum.hpp> // E1
#include <T01.enum.hpp> // E2_struct
#include <T01.enum.hpp> // E3_class
#include <sstream> // __str__

#include <functional>
#include <pybind11/pybind11.h>
#include <string>

#ifndef BINDER_PYBIND11_TYPE_CASTER
	#define BINDER_PYBIND11_TYPE_CASTER
	PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>)
	PYBIND11_DECLARE_HOLDER_TYPE(T, T*)
	PYBIND11_MAKE_OPAQUE(std::shared_ptr<void>)
#endif

void bind_T01_enum(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	// E1 file:T01.enum.hpp line:16
	pybind11::enum_<E1>(M(""), "E1", pybind11::arithmetic(), "")
		.value("E1_V0", E1_V0)
		.value("E1_V1", E1_V1)
		.export_values();

;

	// E2_struct file:T01.enum.hpp line:18
	pybind11::enum_<E2_struct>(M(""), "E2_struct", "")
		.value("V0", E2_struct::V0)
		.value("V1", E2_struct::V1)
		.export_values();

;

	// E3_class file:T01.enum.hpp line:19
	pybind11::enum_<E3_class>(M(""), "E3_class", "")
		.value("V0", E3_class::V0)
		.value("V1", E3_class::V1);

;

	{ // A file:T01.enum.hpp line:22
		pybind11::class_<A, std::shared_ptr<A>> cl(M(""), "A", "");
		cl.def( pybind11::init( [](){ return new A(); } ) );

		pybind11::enum_<A::AE1>(cl, "AE1", pybind11::arithmetic(), "")
			.value("AE1_V0", A::AE1_V0)
			.value("AE1_V1", A::AE1_V1)
			.export_values();


		pybind11::enum_<A::AE2_struct>(cl, "AE2_struct", "")
			.value("AE3_V0", A::AE2_struct::AE3_V0)
			.value("AE3_V1", A::AE2_struct::AE3_V1)
			.export_values();


		pybind11::enum_<A::AE3_class>(cl, "AE3_class", "")
			.value("AE2_V0", A::AE3_class::AE2_V0)
			.value("AE2_V1", A::AE3_class::AE2_V1);

	}
}


#include <map>
#include <algorithm>
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>

#include <pybind11/pybind11.h>

typedef std::function< pybind11::module & (std::string const &) > ModuleGetter;

void bind_T01_enum(std::function< pybind11::module &(std::string const &namespace_) > &M);


PYBIND11_MODULE(T01_enum, root_module) {
	root_module.doc() = "T01_enum module";

	std::map <std::string, pybind11::module> modules;
	ModuleGetter M = [&](std::string const &namespace_) -> pybind11::module & {
		auto it = modules.find(namespace_);
		if( it == modules.end() ) throw std::runtime_error("Attempt to access pybind11::module for namespace " + namespace_ + " before it was created!!!");
		return it->second;
	};

	modules[""] = root_module;

	static std::vector<std::string> const reserved_python_words {"nonlocal", "global", };

	auto mangle_namespace_name(
		[](std::string const &ns) -> std::string {
			if ( std::find(reserved_python_words.begin(), reserved_python_words.end(), ns) == reserved_python_words.end() ) return ns;
			else return ns+'_';
		}
	);

	std::vector< std::pair<std::string, std::string> > sub_modules {
	};
	for(auto &p : sub_modules ) modules[p.first.size() ? p.first+"::"+p.second : p.second] = modules[p.first].def_submodule( mangle_namespace_name(p.second).c_str(), ("Bindings for " + p.first + "::" + p.second + " namespace").c_str() );

	//pybind11::class_<std::shared_ptr<void>>(M(""), "_encapsulated_data_");

	bind_T01_enum(M);

}

// Source list file: TEST/T01_enum.sources
// T01_enum.cpp
// T01_enum.cpp

// Modules list file: TEST/T01_enum.modules
// 
