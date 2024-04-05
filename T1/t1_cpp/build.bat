emcc --no-entry -O3 t1.c -o t1.wasm -s EXPORTED_FUNCTIONS="['_bocchi_shut_up', '_self_malloc', '_self_free']"
