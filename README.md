# ICSoccerWorld Server
Backend for a soccer simulation built for ICP using ICPP. Based on code sample from book "AI Game Programming by Example".
Demo is built in C++ and uses Jolt physics Engine. Flashlight Multilayer Perceptron Deep Learning used for training Soccer Agents on ICP blockchain.

### Prerequisites
dfx
icpp

## Installation
ICP Build Steps (Workaround to ICP exports Limit):

```bash
1. clear && icpp build-wasm --config=icpp_libraries.toml && wasm2wat build/SimSoccerServer.wasm --output=build/SimSoccerServer.wasm.wat

2. edit .wat file with editor to remove all lines having export except:
  (export "canister_update start_match" (func 2489))
  (export "canister_update play_match" (func 352))
  (export "canister_update delete_file" (func 1370))
  (export "canister_update train" (func 117))
  (export "canister_query file_download_chunk" (func 148))
  (export "canister_query health" (func 1753))
  (export "canister_update file_upload_chunk" (func 194))  

3. wat2wasm build/SimSoccerServer.wasm.wat --output=build/SimSoccerServer_noexports.wasm && ../binaryen/bin/wasm-opt build/SimSoccerServer_noexports.wasm -o build/SimSoccerServer.wasm -Oz --enable-bulk-memory && dfx deploy

```

## Usage

### Local
Usage examples for local query:

```bash
$ dfx canister --network local call SimSoccerServer start
$ dfx canister --network local call SimSoccerServer play_match '(1674211940: nat64, 60: nat64)'
```

Usage examples for uploading training data and training:
```bash
$ dfx canister --network local call SimSoccerServer delete_file '("Models/latest_model": text)'
$ python -m scripts.upload Models/observations.txt --network local --canister SimSoccerServer
$ python -m scripts.upload Models/actions.txt --network local --canister SimSoccerServer
$ dfx canister --network local call SimSoccerServer train '("Models/latest_model": text, "Models/observations.txt": text, "Models/actions.txt": text, 20: nat64, 0.009: float32)'
```

## License
This project is licensed under the MIT license.

