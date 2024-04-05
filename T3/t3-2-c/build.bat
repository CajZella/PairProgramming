emcc --no-entry -O3 mancala_operator.c -o mancala_operator.wasm -s EXPORTED_FUNCTIONS="['_mancala_operator', '_self_malloc', '_self_free']"
