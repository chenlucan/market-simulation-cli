#ifndef GENERATE_GENERATOR_H
#define GENERATE_GENERATOR_H

#include <string>

namespace generate {

class BMGenerator {
public:
	BMGenerator();
	virtual ~BMGenerator();

	static void generate(std::string file_name);
};

}
#endif // GENERATE_GENERATOR_H

