# MLPSample - Flashlight

ICP Build Steps (Workaround to ICP 1000 Globals Limit):
	1. clear && icpp build-wasm --config=icpp_libraries.toml && wasm2wat build/ICMLPSample.wasm --output=build/ICMLPSample.wasm.wat
	2. edit .wat file with editor to remove all lines having export except '(export "canister_query train".....)'
	3. wat2wasm build/ICMLPSample.wasm.wat --output=build/ICMLPSample_noexports.wasm && ../binaryen/bin/wasm-opt build/ICMLPSample_noexports.wasm -o build/ICMLPSample.wasm -Oz --enable-bulk-memory && dfx deploy && dfx canister --network local call ICMLPSample train


	Call Canister on main ic network:
	dfx canister --network ic call 52uwu-yyaaa-aaaag-aldoa-cai train