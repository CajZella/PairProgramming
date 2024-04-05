emcc --no-entry -O3 mancala_result.c -o mancala_result.wasm -s EXPORTED_FUNCTIONS="['_mancala_result', '_self_malloc', '_self_free']"
