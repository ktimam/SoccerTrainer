// Main entry point for a native debug executable.
// Build it with: `icpp build-native` from the parent folder where 'icpp.toml' resides

#include "main.h"

#include <iostream>

#include "../SimSoccerServer.h"

// The Mock IC
#include "mock_ic.h"

int main() {
  MockIC mockIC(true);

  // -----------------------------------------------------------------------------
  // Configs for the tests:

  // The pretend principals of the caller
  std::string my_principal{
      "expmt-gtxsw-inftj-ttabj-qhp5s-nozup-n3bbo-k7zvn-dg4he-knac3-lae"};
  std::string anonymous_principal{"2vxsx-fae"};

  bool silent_on_trap = true;

  // -----------------------------------------------------------------------------
  // '()' -> '("hello!")'
  // mockIC.run_test("play_match", play_match, "4449444c000278786472ca63000000000f00000000000000",
  //                 "", silent_on_trap, my_principal);

  mockIC.run_test("train", train, "4449444c00057171717873134d6f64656c732f6c61746573745f6d6f64656c174d6f64656c732f6f62736572766174696f6e732e747874124d6f64656c732f616374696f6e732e747874e803000000000000bc74133c",
                  "", silent_on_trap, my_principal);
  
  // returns 1 if any tests failed
  return mockIC.test_summary();
}