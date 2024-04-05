import { readFileSync } from 'fs';

function mancala_board(flag, seq, size) {
    const wasmSource = new Uint8Array(readFileSync("./mancala_board.wasm"));
    const wasmModule = new WebAssembly.Module(wasmSource);

    const wasmInstance = new WebAssembly.Instance(wasmModule, {
        env: {
        }
    });

    const heap = new Uint8Array(wasmInstance.exports.memory.buffer);

    const mancala_board = wasmInstance.exports.mancala_board;
    //处理数组
    const malloc = wasmInstance.exports.self_malloc;
    const free = wasmInstance.exports.self_free;

    const c_array = malloc(size)

    seq.forEach((value, index) => {
        heap[c_array + index * 4] = value;
    });

    // 调用导出的函数
    const ret = mancala_board(flag, c_array, size);
    let arr = new Array(15);
    for(let i = 0;i < 15;i++) {
        arr[i] = heap[ret + i * 4];
    }
    free(c_array)
    free(ret)
    return arr
}

export { mancala_board };