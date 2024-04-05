emcc --no-entry -O3 mancala_board.c -o mancala_board.wasm -s EXPORTED_FUNCTIONS="['_mancala_board', '_self_malloc', '_self_free']"
