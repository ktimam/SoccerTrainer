//Run 'python3 -m http.server' from root workspace directory first
//Then run this file

const importObject = {
  imports: {
    imported_func: arg => {
      console.log(arg);
    }
  }
};

fetch("http://localhost:8000/build/ICMLPSample.wasm")
  .then((response) => response.arrayBuffer())
  .then((bytes) => WebAssembly.instantiate(bytes, importObject))
  .then((results) => {
    results.instance.exports.train();
  });
