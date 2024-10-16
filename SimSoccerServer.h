#pragma once

#include "wasm_symbol.h"

void start_match() WASM_SYMBOL_EXPORTED("canister_update start_match");
void play_match() WASM_SYMBOL_EXPORTED("canister_update play_match");
void delete_file() WASM_SYMBOL_EXPORTED("canister_update delete_file");
void train() WASM_SYMBOL_EXPORTED("canister_update train");