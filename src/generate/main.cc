#include "config/config.h"

#include "generate/bmgenerator.h"

int main(int argc, char* argv[]) {
  config::Config config;
  generate::BMGenerator::generate(config.get_tree().get("quotes_file", "quotes.txt"));
}

